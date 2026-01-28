// If on Dreamcast:
// #include <kos.h>

#include "bn_core.h"
#include "raylib.h"
#include <iostream>
#include <cstdlib>

// Helper logic
namespace bn
{
    void internal_render_sprites();
    void internal_music_update();

    // --- FIX: Defined missing asset management functions ---
    void preload_all_assets()
    {
        // Stub: Assets are loaded lazily in bn_sprites.cpp when created.
        // Explicit preloading can be implemented here by iterating directories if needed.
    }

    void unload_all_assets()
    {
        // Stub: Assets are RAII managed or cleared by OS on exit.
    }
    // -----------------------------------------------------
}

static RenderTexture2D target;
static Vector2 render_offset = {0, 0};
static float render_scale = 3.0f;

// GBA Timing Constants
// GBA Screen Refresh Rate: ~59.7275 Hz
static const double GBA_FRAME_TIME = 1.0 / 59.7275;
static double next_frame_time = 0.0;

namespace bn::core
{
    void init()
    {
        SetTraceLogLevel(LOG_WARNING);

        // CHANGED: Removed FLAG_VSYNC_HINT.
        // VSync locks us to 60hz (or 144hz), which causes GBA audio desync/pitch shift.
        SetConfigFlags(FLAG_WINDOW_RESIZABLE);

        InitWindow(GAME_WIDTH * 3, GAME_HEIGHT * 3, "Glass Eyes");
        SetWindowMinSize(GAME_WIDTH, GAME_HEIGHT);

        // CHANGED: Ensure audio buffer is large enough to handle slight frame jitter
        // without under-running (which causes pitch warping).
        SetAudioStreamBufferSizeDefault(4096);
        InitAudioDevice();

        target = LoadRenderTexture(GAME_WIDTH, GAME_HEIGHT);
        SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);

        bn::preload_all_assets();

        // Initialize the timing accumulator
        next_frame_time = GetTime();
    }

    bool closed()
    {
        return WindowShouldClose();
    }

    void exit()
    {
        bn::unload_all_assets();
        CloseAudioDevice();
        UnloadRenderTexture(target);
        CloseWindow();
    }

    void update()
    {
        // Check for escape key to close the game
        if (WindowShouldClose())
        {
            exit();
            std::exit(0); // Force immediate termination
        }

        // --- FRAMERATE LOCKING LOGIC ---
        double current_time = GetTime();

        // If we are ahead of schedule (running fast), wait until the next frame time
        if (current_time < next_frame_time)
        {
            while (current_time < next_frame_time)
            {
                // CRITICAL: Keep feeding the music stream while waiting!
                // If we simply Sleep() without this, the audio buffer drains,
                // causing the random pitch fluctuations/glitches.
                bn::internal_music_update();

                // If we have a significant gap (> 2ms), sleep to save CPU.
                // Otherwise, busy-wait for high precision.
                double wait_diff = next_frame_time - current_time;
                if (wait_diff > 0.002)
                {
                    WaitTime((float)(wait_diff - 0.001));
                }

                current_time = GetTime();
            }
        }
        else if (current_time > next_frame_time + (GBA_FRAME_TIME * 3.0))
        {
            // If we dropped too many frames (lag spike), reset the timer
            // so the game doesn't fast-forward to catch up.
            next_frame_time = current_time;
        }

        // Advance the target time for the next frame
        next_frame_time += GBA_FRAME_TIME;
        // -------------------------------

        // 1. Update Music (Standard call)
        // Ensure it runs even if we didn't enter the wait loop (lagging).
        bn::internal_music_update();

        // 2. Update Scaling Logic
        float scaleW = (float)GetScreenWidth() / GAME_WIDTH;
        float scaleH = (float)GetScreenHeight() / GAME_HEIGHT;
        render_scale = (scaleW < scaleH) ? scaleW : scaleH;

        render_offset = {
            (GetScreenWidth() - (GAME_WIDTH * render_scale)) * 0.5f,
            (GetScreenHeight() - (GAME_HEIGHT * render_scale)) * 0.5f};

        // 3. Draw to internal framebuffer
        BeginTextureMode(target);
        ClearBackground(BLACK);
        bn::internal_render_sprites();
        EndTextureMode();

        // 4. Draw to Screen
        BeginDrawing();
        ClearBackground(BLACK);

        Rectangle sourceRec = {0.0f, 0.0f, (float)target.texture.width, -(float)target.texture.height};
        Rectangle destRec = {render_offset.x, render_offset.y, GAME_WIDTH * render_scale, GAME_HEIGHT * render_scale};
        Vector2 origin = {0.0f, 0.0f};

        DrawTexturePro(target.texture, sourceRec, destRec, origin, 0.0f, WHITE);

        EndDrawing();
    }
}