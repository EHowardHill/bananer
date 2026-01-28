import os


def generate_headers():
    audio_dir = "audio"
    include_dir = "include"

    if not os.path.exists(audio_dir):
        print(f"Warning: '{audio_dir}' directory not found. skipping music generation.")
        return

    # supported extensions
    extensions = {".mod", ".xm", ".it", ".s3m"}
    music_files = []

    for filename in sorted(os.listdir(audio_dir)):
        name, ext = os.path.splitext(filename)
        if ext.lower() in extensions:
            # sanitise name (e.g. "my-song.mod" -> "my_song")
            var_name = name.replace("-", "_").replace(" ", "_")
            music_files.append((var_name, filename))

    # --- Generate bn_music_items.h ---
    items_path = os.path.join(include_dir, "bn_music_items.h")
    with open(items_path, "w") as f:
        f.write("#ifndef BN_MUSIC_ITEMS_H\n")
        f.write("#define BN_MUSIC_ITEMS_H\n\n")
        f.write('#include "bn_music_item.h"\n\n')
        f.write("namespace bn::music_items\n{\n")
        for var_name, filename in music_files:
            # FIX: Pass the path string, not the index
            f.write(
                f'    constexpr inline music_item {var_name}("audio/{filename}");\n'
            )
        f.write("}\n\n")
        f.write("#endif\n")

    # --- Generate bn_music_items_info.h ---
    info_path = os.path.join(include_dir, "bn_music_items_info.h")
    with open(info_path, "w") as f:
        f.write("#ifndef BN_MUSIC_ITEMS_INFO_H\n")
        f.write("#define BN_MUSIC_ITEMS_INFO_H\n\n")
        f.write('#include "bn_span.h"\n')
        f.write('#include "bn_music_item.h"\n')
        f.write('#include "bn_string_view.h"\n')
        f.write('#include "bn_music_items.h"\n\n')
        f.write("namespace bn::music_items_info\n{\n")

        # Define a simple pair struct locally if not available globally
        f.write("    struct pair { music_item item; string_view name; };\n\n")

        f.write("    constexpr inline pair array[] = {\n")
        for var_name, filename in music_files:
            f.write(f'        {{ music_items::{var_name}, "{var_name}" }},\n')

        # Empty dummy if no files, to prevent compiler error on empty array
        if not music_files:
            f.write('        { music_items::music_item(0), "" }\n')

        f.write("    };\n\n")
        f.write("    constexpr inline span<const pair> span(array);\n")
        f.write("}\n\n")
        f.write("#endif\n")


if __name__ == "__main__":
    generate_headers()
