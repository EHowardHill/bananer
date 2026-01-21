#include "raylib.h"

#define GAME_WIDTH 640
#define GAME_HEIGHT 480

int main(void)
{
    // Enable window resizing so user can maximize or drag window
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(GAME_WIDTH, GAME_HEIGHT, "My XP Visual Novel");
    SetWindowMinSize(GAME_WIDTH, GAME_HEIGHT);

    // 1. Create a "Virtual Screen" (The Texture we draw the game onto)
    RenderTexture2D target = LoadRenderTexture(GAME_WIDTH, GAME_HEIGHT);
    SetTextureFilter(target.texture, TEXTURE_FILTER_POINT); // Pixel perfect crispness

    // Example VN Assets
    // Texture2D background = LoadTexture("bg.png");
    // Font pixelFont = LoadFont("pixel_font.fnt");

    while (!WindowShouldClose())
    {
        // --- SCALE CALCULATION ---
        float scale = (float)GetScreenWidth() / GAME_WIDTH;
        if ((float)GetScreenHeight() / GAME_HEIGHT < scale) {
            scale = (float)GetScreenHeight() / GAME_HEIGHT;
        }
        
        // Calculate headers for letterboxing (centering the game)
        int virtualMouseX = 0;
        int virtualMouseY = 0;
        Vector2 gameScreenOffset = { 
            (GetScreenWidth() - (GAME_WIDTH * scale)) * 0.5f, 
            (GetScreenHeight() - (GAME_HEIGHT * scale)) * 0.5f 
        };

        // Update Mouse for Virtual Resolution (so buttons work at any scale)
        Vector2 mouse = GetMousePosition();
        virtualMouseX = (mouse.x - gameScreenOffset.x) / scale;
        virtualMouseY = (mouse.y - gameScreenOffset.y) / scale;

        // -------------------------
        // DRAW TO VIRTUAL SCREEN
        // -------------------------
        BeginTextureMode(target);
            ClearBackground(BLACK); // Clear the virtual screen
            
            // Draw your Visual Novel content here using (0,0) to (640,480) coords
            DrawRectangleGradientV(0, 0, GAME_WIDTH, GAME_HEIGHT, DARKBLUE, BLACK); // Placeholder BG
            
            DrawText("XP VISUAL NOVEL ENGINE", 10, 10, 20, WHITE);
            DrawText("Supports: 640x480 Scaled", 10, 40, 10, GREEN);
            
            // Example Button Logic using Virtual Mouse
            if (virtualMouseX > 200 && virtualMouseX < 440 && virtualMouseY > 200 && virtualMouseY < 250) {
                DrawRectangle(200, 200, 240, 50, WHITE);
                DrawText("START GAME", 240, 215, 20, BLACK);
            } else {
                DrawRectangleLines(200, 200, 240, 50, WHITE);
                DrawText("START GAME", 240, 215, 20, WHITE);
            }

        EndTextureMode();

        // -------------------------
        // DRAW VIRTUAL SCREEN TO WINDOW
        // -------------------------
        BeginDrawing();
            ClearBackground(BLACK); // Letterbox bars color
            
            // Draw the render texture scaled and centered
            Rectangle sourceRec = { 0.0f, 0.0f, (float)target.texture.width, (float)-target.texture.height };
            Rectangle destRec = { 
                gameScreenOffset.x, 
                gameScreenOffset.y, 
                (float)GAME_WIDTH * scale, 
                (float)GAME_HEIGHT * scale 
            };
            DrawTexturePro(target.texture, sourceRec, destRec, (Vector2){ 0, 0 }, 0.0f, WHITE);
            
        EndDrawing();
    }

    UnloadRenderTexture(target);
    CloseWindow();

    return 0;
}