#include "bn_sprite_ptr.h"
#include "bn_regular_bg_ptr.h"
#include "bn_camera_ptr.h"
#include "bn_sound_items.h"
#include "bn_music_item.h"
#include "bn_core.h"
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <iostream>
#include <memory>
#include <fstream>
#include <cstring>

namespace bn
{
    class sprite_impl;
    class regular_bg_impl;

    static std::vector<sprite_impl *> g_active_sprites;
    static std::vector<regular_bg_impl *> g_active_bgs;

    // Cache Maps
    static std::map<std::string, Texture2D> g_texture_cache;
    static std::map<std::string, int> g_texture_counts;
    static std::map<std::string, Sound> g_sound_cache;

    // --- BMP PARSER ---
    Color GetBmpTransparencyKey(const std::string &path)
    {
        std::ifstream file(path, std::ios::binary);
        if (!file)
            return MAGENTA;

        char signature[2];
        file.read(signature, 2);
        if (signature[0] != 'B' || signature[1] != 'M')
            return MAGENTA;

        file.seekg(14, std::ios::beg);
        uint32_t dib_header_size = 0;
        file.read(reinterpret_cast<char *>(&dib_header_size), 4);

        file.seekg(28, std::ios::beg);
        uint16_t bpp = 0;
        file.read(reinterpret_cast<char *>(&bpp), 2);

        if (bpp > 8)
            return MAGENTA;

        file.seekg(14 + dib_header_size, std::ios::beg);
        unsigned char b, g, r, a;
        file.read(reinterpret_cast<char *>(&b), 1);
        file.read(reinterpret_cast<char *>(&g), 1);
        file.read(reinterpret_cast<char *>(&r), 1);
        file.read(reinterpret_cast<char *>(&a), 1);

        return Color{r, g, b, 255};
    }

    // --- ASSET MANAGEMENT ---

    Texture2D acquire_texture(const char *path)
    {
        std::string key = path;

        if (g_texture_cache.find(key) == g_texture_cache.end())
        {
            // std::cout << "[RAM] Loading texture: " << key << std::endl;

            Color transparencyKey = GetBmpTransparencyKey(key);
            Image img = LoadImage(path);

            if (img.data == NULL)
            {
                std::cerr << "ERROR: Failed to load image: " << path << ". Using placeholder." << std::endl;
                img = GenImageColor(32, 32, MAGENTA);
            }

            ImageFormat(&img, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
            Color *pixels = (Color *)img.data;
            int pixelCount = img.width * img.height;

            for (int i = 0; i < pixelCount; i++)
            {
                if (pixels[i].r == transparencyKey.r &&
                    pixels[i].g == transparencyKey.g &&
                    pixels[i].b == transparencyKey.b)
                {
                    pixels[i].a = 0;
                }
            }

            g_texture_cache[key] = LoadTextureFromImage(img);
            UnloadImage(img);
            g_texture_counts[key] = 0;
        }

        g_texture_counts[key]++;
        return g_texture_cache[key];
    }

    void release_texture(const char *path)
    {
        std::string key = path;
        if (g_texture_counts.find(key) != g_texture_counts.end())
        {
            g_texture_counts[key]--;

            if (g_texture_counts[key] <= 0)
            {
                // std::cout << "[RAM] Unloading texture: " << key << std::endl;
                UnloadTexture(g_texture_cache[key]);
                g_texture_cache.erase(key);
                g_texture_counts.erase(key);
            }
        }
    }

    Sound get_cached_sound(const char *path)
    {
        std::string key = path;
        if (g_sound_cache.find(key) == g_sound_cache.end())
        {
            if (FileExists(path))
            {
                // std::cout << "[RAM] Loading sound: " << key << std::endl;
                g_sound_cache[key] = LoadSound(path);
            }
            else
            {
                std::cerr << "ERROR: Sound file missing: " << path << std::endl;

                // Manually create a silent wave
                Wave wave;
                wave.frameCount = 44100 / 2; // 0.5 seconds
                wave.sampleRate = 44100;
                wave.sampleSize = 16;
                wave.channels = 1;
                wave.data = malloc(wave.frameCount * wave.sampleSize / 8);

                if (wave.data)
                {
                    memset(wave.data, 0, wave.frameCount * wave.sampleSize / 8);
                    g_sound_cache[key] = LoadSoundFromWave(wave);
                    free(wave.data);
                }
            }
        }
        return g_sound_cache[key];
    }

    // --- SOUND ITEM IMPLEMENTATION ---
    void sound_item::play(fixed volume) const
    {
        Sound snd = get_cached_sound(_path);
        SetSoundVolume(snd, volume.to_float());
        PlaySound(snd);
    }

    // --- MUSIC IMPLEMENTATION ---
    static Music g_current_music = {0};
    static bool g_music_playing = false;
    static float g_music_volume = 1.0f;
    static const music_item *g_current_music_item = nullptr;

    namespace music
    {
        void play(const music_item &item, fixed volume, bool loop);

        void play(const music_item &item, fixed volume, bool loop)
        {
            if (!FileExists(item._path))
            {
                std::cerr << "ERROR: Music file missing: " << item._path << std::endl;
                return;
            }

            if (g_music_playing)
                StopMusicStream(g_current_music);
            if (g_current_music.stream.buffer != NULL)
                UnloadMusicStream(g_current_music);

            g_current_music = LoadMusicStream(item._path);
            g_music_volume = volume.to_float();

            SetMusicVolume(g_current_music, g_music_volume);
            g_current_music.looping = loop;

            PlayMusicStream(g_current_music);
            g_music_playing = true;

            g_current_music_item = &item;
        }

        void play(const music_item &item, fixed volume)
        {
            play(item, volume, true);
        }

        void stop()
        {
            StopMusicStream(g_current_music);
            g_music_playing = false;
            g_current_music_item = nullptr;
        }

        void pause()
        {
            PauseMusicStream(g_current_music);
            g_music_playing = false;
        }

        void resume()
        {
            ResumeMusicStream(g_current_music);
            g_music_playing = true;
        }

        bool playing()
        {
            return IsMusicStreamPlaying(g_current_music);
        }

        optional<music_item> playing_item()
        {
            if (g_music_playing && g_current_music_item)
                return make_optional(*g_current_music_item);
            return nullopt;
        }

        void set_volume(fixed volume)
        {
            g_music_volume = volume.to_float();
            if (g_current_music.stream.buffer != NULL)
            {
                SetMusicVolume(g_current_music, g_music_volume);
            }
        }

        fixed volume() { return fixed(g_music_volume); }

        void _update_stream()
        {
            if (g_current_music.stream.buffer != NULL && g_music_playing)
            {
                UpdateMusicStream(g_current_music);
            }
        }
    }

    void music_item::play(fixed volume, bool loop) const
    {
        bn::music::play(*this, volume, loop);
    }

    void internal_music_update()
    {
        bn::music::_update_stream();
    }

    // --- BLENDING ---
    static float g_transparency_alpha = 1.0f;
    static float g_intensity_alpha = 0.0f;

    namespace blending
    {
        void set_transparency_alpha(fixed alpha)
        {
            g_transparency_alpha = alpha.to_float();
            if (g_transparency_alpha < 0.0f)
                g_transparency_alpha = 0.0f;
            if (g_transparency_alpha > 1.0f)
                g_transparency_alpha = 1.0f;
        }
        fixed transparency_alpha() { return fixed(g_transparency_alpha); }
        void set_intensity_alpha(fixed alpha)
        {
            g_intensity_alpha = alpha.to_float();
            if (g_intensity_alpha < 0)
                g_intensity_alpha = 0;
            if (g_intensity_alpha > 1)
                g_intensity_alpha = 1;
        }
        fixed intensity_alpha() { return fixed(g_intensity_alpha); }
        void set_fade_alpha(fixed alpha) {}
    }

    // --- RENDERER & CLASSES ---

    class regular_bg_impl
    {
    public:
        float x, y;
        const regular_bg_item *item;
        Texture2D texture;
        bool blending = false;
        camera_ptr camera = camera_ptr::create(0, 0);

        regular_bg_impl(float _x, float _y, const regular_bg_item *_item)
            : x(_x), y(_y), item(_item)
        {
            texture = acquire_texture(item->path());
            SetTextureWrap(texture, TEXTURE_WRAP_REPEAT);
            g_active_bgs.push_back(this);
        }

        ~regular_bg_impl()
        {
            release_texture(item->path());
            auto it = std::find(g_active_bgs.begin(), g_active_bgs.end(), this);
            if (it != g_active_bgs.end())
                g_active_bgs.erase(it);
        }
    };

    regular_bg_ptr regular_bg_item::create_bg(fixed x, fixed y) const { return regular_bg_ptr::create(x, y, *this); }
    regular_bg_ptr regular_bg_ptr::create(fixed x, fixed y, const regular_bg_item &item) { return regular_bg_ptr(std::make_shared<regular_bg_impl>(x.to_float(), y.to_float(), &item)); }
    regular_bg_ptr::regular_bg_ptr(std::shared_ptr<regular_bg_impl> impl) : _impl(impl) {}
    void regular_bg_ptr::set_x(fixed x)
    {
        if (_impl)
            _impl->x = x.to_float();
    }
    void regular_bg_ptr::set_y(fixed y)
    {
        if (_impl)
            _impl->y = y.to_float();
    }
    void regular_bg_ptr::set_position(fixed x, fixed y)
    {
        if (_impl)
        {
            _impl->x = x.to_float();
            _impl->y = y.to_float();
        }
    }
    fixed regular_bg_ptr::x() const { return _impl ? fixed(_impl->x) : fixed(0); }
    fixed regular_bg_ptr::y() const { return _impl ? fixed(_impl->y) : fixed(0); }

    void regular_bg_ptr::set_blending_enabled(bool enabled)
    {
        if (_impl)
            _impl->blending = enabled;
    }
    bool regular_bg_ptr::blending_enabled() const { return _impl ? _impl->blending : false; }

    void regular_bg_ptr::set_camera(const camera_ptr &camera)
    {
        if (_impl)
            _impl->camera = camera;
    }

    class sprite_impl
    {
    public:
        float x, y;
        const sprite_item *item;
        Texture2D texture;
        bool visible;

        float scale_x = 1.0f;
        float scale_y = 1.0f;

        bool flip_x = false;
        bool flip_y = false;

        int z_order = 0;

        float rotation = 0.0f;
        bool blending = false;
        int graphics_index = 0;

        camera_ptr camera = camera_ptr::create(0, 0);

        sprite_impl(float _x, float _y, const sprite_item *_item, int _index)
            : x(_x), y(_y), item(_item), visible(true), graphics_index(_index)
        {
            texture = acquire_texture(item->path());
            g_active_sprites.push_back(this);
        }

        ~sprite_impl()
        {
            if (item)
                release_texture(item->path());
            auto it = std::find(g_active_sprites.begin(), g_active_sprites.end(), this);
            if (it != g_active_sprites.end())
                g_active_sprites.erase(it);
        }

        void set_item(const sprite_item *new_item)
        {
            if (item == new_item)
                return;
            if (item)
                release_texture(item->path());
            item = new_item;
            if (item)
                texture = acquire_texture(item->path());
        }
    };

    sprite_ptr sprite_item::create_sprite(float x, float y) const { return sprite_ptr::create(x, y, *this, 0); }
    sprite_ptr sprite_item::create_sprite(float x, float y, int graphics_index) const { return sprite_ptr::create(x, y, *this, graphics_index); }
    sprite_ptr sprite_item::create_sprite(fixed x, fixed y) const { return sprite_ptr::create(x.to_float(), y.to_float(), *this, 0); }
    sprite_ptr sprite_item::create_sprite(fixed x, fixed y, int graphics_index) const { return sprite_ptr::create(x.to_float(), y.to_float(), *this, graphics_index); }

    sprite_ptr sprite_ptr::create(float x, float y, const sprite_item &item, int graphics_index)
    {
        return sprite_ptr(std::make_shared<sprite_impl>(x, y, &item, graphics_index));
    }

    sprite_ptr::sprite_ptr(std::shared_ptr<sprite_impl> impl) : _impl(impl) {}

    void sprite_ptr::set_x(fixed x)
    {
        if (_impl)
            _impl->x = x.to_float();
    }
    void sprite_ptr::set_y(fixed y)
    {
        if (_impl)
            _impl->y = y.to_float();
    }
    void sprite_ptr::set_position(fixed x, fixed y)
    {
        if (_impl)
        {
            _impl->x = x.to_float();
            _impl->y = y.to_float();
        }
    }
    fixed sprite_ptr::x() const { return _impl ? fixed(_impl->x) : fixed(0); }
    fixed sprite_ptr::y() const { return _impl ? fixed(_impl->y) : fixed(0); }
    void sprite_ptr::set_visible(bool v)
    {
        if (_impl)
            _impl->visible = v;
    }
    bool sprite_ptr::visible() const { return _impl ? _impl->visible : false; }

    void sprite_ptr::set_scale(double scale)
    {
        if (_impl)
        {
            _impl->scale_x = (float)scale;
            _impl->scale_y = (float)scale;
        }
    }

    void sprite_ptr::set_scale(fixed scale)
    {
        if (_impl)
        {
            float s = scale.to_float();
            _impl->scale_x = s;
            _impl->scale_y = s;
        }
    }

    void sprite_ptr::set_scale(fixed x, fixed y)
    {
        if (_impl)
        {
            _impl->scale_x = x.to_float();
            _impl->scale_y = y.to_float();
        }
    }

    void sprite_ptr::set_horizontal_scale(fixed scale)
    {
        if (_impl)
            _impl->scale_x = scale.to_float();
    }
    void sprite_ptr::set_vertical_scale(fixed scale)
    {
        if (_impl)
            _impl->scale_y = scale.to_float();
    }

    fixed sprite_ptr::horizontal_scale() const { return _impl ? fixed(_impl->scale_x) : fixed(1); }
    fixed sprite_ptr::vertical_scale() const { return _impl ? fixed(_impl->scale_y) : fixed(1); }

    void sprite_ptr::set_horizontal_flip(bool flip)
    {
        if (_impl)
            _impl->flip_x = flip;
    }
    void sprite_ptr::set_vertical_flip(bool flip)
    {
        if (_impl)
            _impl->flip_y = flip;
    }

    bool sprite_ptr::horizontal_flip() const { return _impl ? _impl->flip_x : false; }
    bool sprite_ptr::vertical_flip() const { return _impl ? _impl->flip_y : false; }

    void sprite_ptr::set_z_order(int z)
    {
        if (_impl)
            _impl->z_order = z;
    }
    int sprite_ptr::z_order() const { return _impl ? _impl->z_order : 0; }

    void sprite_ptr::set_rotation_angle(int angle)
    {
        if (_impl)
            _impl->rotation = (float)angle;
    }
    void sprite_ptr::set_rotation_angle(fixed angle)
    {
        if (_impl)
            _impl->rotation = angle.to_float();
    }

    void sprite_ptr::set_blending_enabled(bool enabled)
    {
        if (_impl)
            _impl->blending = enabled;
    }

    fixed sprite_ptr::rotation_angle() const { return _impl ? fixed(_impl->rotation) : fixed(0); }

    void sprite_ptr::put_above()
    {
        if (!_impl)
            return;
        auto it = std::find(g_active_sprites.begin(), g_active_sprites.end(), _impl.get());
        if (it != g_active_sprites.end())
        {
            g_active_sprites.erase(it);
            g_active_sprites.push_back(_impl.get());
        }
    }

    void sprite_ptr::put_below()
    {
        if (!_impl)
            return;
        auto it = std::find(g_active_sprites.begin(), g_active_sprites.end(), _impl.get());
        if (it != g_active_sprites.end())
        {
            g_active_sprites.erase(it);
            g_active_sprites.insert(g_active_sprites.begin(), _impl.get());
        }
    }

    void sprite_ptr::set_palette(const sprite_palette_item &palette_item) {}

    void sprite_ptr::set_tiles(int graphics_index)
    {
        if (_impl)
            _impl->graphics_index = graphics_index;
    }

    void sprite_ptr::set_tiles(const sprite_item &item, int graphics_index)
    {
        if (!_impl)
            return;
        _impl->graphics_index = graphics_index;
        _impl->set_item(&item);
    }

    void sprite_ptr::set_tiles(const sprite_tiles_item &item, int graphics_index)
    {
        if (!_impl)
            return;
        _impl->graphics_index = graphics_index;
        _impl->set_item(&item.item());
    }

    void sprite_ptr::set_camera(const camera_ptr &camera)
    {
        if (_impl)
            _impl->camera = camera;
    }

    // --- CAMERA IMPLEMENTATION ---
    struct camera_ptr::impl
    {
        fixed x, y;
    };
    camera_ptr camera_ptr::create(fixed x, fixed y)
    {
        auto i = std::make_shared<impl>();
        i->x = x;
        i->y = y;
        return camera_ptr(i);
    }
    camera_ptr::camera_ptr(std::shared_ptr<impl> impl) : _impl(impl) {}
    fixed camera_ptr::x() const { return _impl ? _impl->x : 0; }
    fixed camera_ptr::y() const { return _impl ? _impl->y : 0; }
    void camera_ptr::set_x(fixed x)
    {
        if (_impl)
            _impl->x = x;
    }
    void camera_ptr::set_y(fixed y)
    {
        if (_impl)
            _impl->y = y;
    }
    void camera_ptr::set_position(fixed x, fixed y)
    {
        if (_impl)
        {
            _impl->x = x;
            _impl->y = y;
        }
    }

    // --- RENDER ---
    void internal_render_sprites()
    {
        // === RENDER BACKGROUNDS ===
        for (regular_bg_impl *bg : g_active_bgs)
        {
            float cam_x = bg->camera.x().to_float();
            float cam_y = bg->camera.y().to_float();

            // Calculate the offset to center the texture on screen
            float offset_x = (bg->texture.width - GAME_WIDTH) / 2.0f;
            float offset_y = (bg->texture.height - GAME_HEIGHT) / 2.0f;

            // Corrected scroll calculation (this is working per user feedback)
            float scroll_x = offset_x - bg->x + cam_x;
            float scroll_y = offset_y - bg->y + cam_y;

            Rectangle source = {
                roundf(scroll_x),
                roundf(scroll_y),
                (float)GAME_WIDTH,
                (float)GAME_HEIGHT};
            Rectangle dest = {0, 0, (float)GAME_WIDTH, (float)GAME_HEIGHT};
            Vector2 origin = {0, 0};

            Color tint = WHITE;
            if (bg->blending)
            {
                unsigned char a = (unsigned char)(g_transparency_alpha * 255.0f);
                tint = Color{255, 255, 255, a};
            }

            DrawTexturePro(bg->texture, source, dest, origin, 0.0f, tint);
        }

        // === RENDER SPRITES ===
        // Sort by z_order: higher z_order = further back = drawn first
        std::stable_sort(g_active_sprites.begin(), g_active_sprites.end(),
                         [](const sprite_impl *a, const sprite_impl *b)
                         {
                             return a->z_order > b->z_order;
                         });

        for (sprite_impl *s : g_active_sprites)
        {
            if (!s->visible)
                continue;

            float cam_x = s->camera.x().to_float();
            float cam_y = s->camera.y().to_float();

            // In Butano:
            // - (0, 0) is the CENTER of the screen
            // - Sprite x/y position refers to the CENTER of the sprite
            // - Positive X is right, positive Y is down
            //
            // Convert Butano center-based coords to Raylib screen coords:
            // The sprite's CENTER should appear at this screen position:
            float center_x = roundf((s->x - cam_x) + (GAME_WIDTH / 2.0f));
            float center_y = roundf((s->y - cam_y) + (GAME_HEIGHT / 2.0f));

            // Calculate scaled dimensions
            float scaled_w = s->item->width() * s->scale_x;
            float scaled_h = s->item->height() * s->scale_y;

            // Source rectangle: which frame from the spritesheet
            float src_x = 0;
            float src_y = s->graphics_index * s->item->height();
            float src_w = (float)s->item->width();
            float src_h = (float)s->item->height();

            // Handle flipping via negative source dimensions
            if (s->flip_x)
                src_w *= -1.0f;
            if (s->flip_y)
                src_h *= -1.0f;

            Rectangle source = {src_x, src_y, src_w, src_h};

            // In DrawTexturePro, when origin is set:
            // - The point (origin.x, origin.y) within the dest rect will be placed at (dest.x, dest.y)
            // - So to center the sprite at (center_x, center_y), we set:
            //   - dest.x = center_x, dest.y = center_y
            //   - origin = center of the scaled sprite
            Rectangle dest = {
                center_x,
                center_y,
                scaled_w,
                scaled_h};

            // Origin at center of scaled sprite - this makes dest.x/y the center position
            Vector2 origin = {scaled_w / 2.0f, scaled_h / 2.0f};

            Color tint = WHITE;
            if (s->blending)
            {
                unsigned char a = (unsigned char)(g_transparency_alpha * 255.0f);
                tint = Color{255, 255, 255, a};
            }

            // Rotation is negated because Butano uses clockwise-positive angles
            // while Raylib uses counter-clockwise-positive
            DrawTexturePro(s->texture, source, dest, origin, -s->rotation, tint);
        }
    }
}