import os
from json import load

# Ensure build directory exists
if not os.path.exists("build"):
    os.makedirs("build")

# Ensure include directory exists for info headers
if not os.path.exists("include"):
    os.makedirs("include")


# --- GRAPHICS PROCESSING (Existing) ---
def run_graphics(dir):
    if not os.path.exists(dir):
        return

    for graphic in os.listdir(dir):
        if ".bmp" in graphic:
            name = graphic.replace(".bmp", "")

            metadata = {}
            json_path = dir + "/" + name + ".json"

            # Load metadata if it exists
            if os.path.exists(json_path):
                with open(json_path) as f:
                    try:
                        metadata = load(f)
                    except:
                        print(f"Warning: Failed to parse JSON for {graphic}")

            # Default to sprite if no JSON
            type_ = metadata.get("type", "sprite")

            header_content = ""

            # --- Handle Sprites ---
            if type_ == "sprite":
                guard = f"BN_SPRITE_ITEMS_{name.upper()}_H"

                header_content = f"#ifndef {guard}\n"
                header_content += f"#define {guard}\n\n"
                header_content += '#include "bn_sprite_item.h"\n\n'
                header_content += "namespace bn::sprite_items\n{\n"

                size = metadata.get("height")

                if size is None:
                    size = 32

                size = str(size)
                tiles = str(metadata.get("tiles_count", 1))

                header_content += f"    constexpr sprite_item {name}(\n"
                header_content += f'        "graphics/{graphic}",\n'
                header_content += f"        {size}, {size}, {tiles}\n"
                header_content += "    );\n"
                header_content += "}\n\n"
                header_content += "#endif"

                with open(f"build/bn_sprite_items_{name}.h", "w") as f:
                    f.write(header_content)

            # --- Handle Backgrounds ---
            elif type_ == "regular_bg":
                guard = f"BN_REGULAR_BG_ITEMS_{name.upper()}_H"

                header_content = f"#ifndef {guard}\n"
                header_content += f"#define {guard}\n\n"
                header_content += '#include "bn_regular_bg_item.h"\n\n'
                header_content += "namespace bn::regular_bg_items\n{\n"

                width = str(metadata.get("width", 256))
                height = str(metadata.get("height", 256))

                header_content += f"    constexpr regular_bg_item {name}(\n"
                header_content += f'        "graphics/{graphic}",\n'
                header_content += f"        {width}, {height}\n"
                header_content += "    );\n"
                header_content += "}\n\n"
                header_content += "#endif"

                with open(f"build/bn_regular_bg_items_{name}.h", "w") as f:
                    f.write(header_content)


run_graphics("graphics")
run_graphics(os.path.join("common", "graphics"))

# --- AUDIO PROCESSING ---
if os.path.exists("audio"):

    # 1. HEADERS & INFO STRINGS
    music_header_items = ""
    music_info_array = ""

    sound_header_items = ""
    sound_info_array = ""

    found_music = False
    found_sound = False

    music_extensions = {".mod", ".xm", ".it", ".s3m"}

    for audio_file in sorted(os.listdir("audio")):
        name, ext = os.path.splitext(audio_file)
        # Sanitize variable name
        var_name = name.replace("-", "_").replace(" ", "_")

        # Handle Music
        if ext.lower() in music_extensions:
            found_music = True
            music_header_items += (
                f'    constexpr inline music_item {var_name}("audio/{audio_file}");\n'
            )
            music_info_array += (
                f'        {{ music_items::{var_name}, "{var_name}" }},\n'
            )

        # Handle Sounds
        elif ext.lower() == ".wav":
            found_sound = True
            sound_header_items += (
                f'    constexpr sound_item {var_name}("audio/{audio_file}");\n'
            )
            sound_info_array += (
                f'        {{ sound_items::{var_name}, "{var_name}" }},\n'
            )

    # --- WRITE MUSIC FILES ---
    if found_music:
        # bn_music_items.h
        with open("build/bn_music_items.h", "w") as f:
            f.write("#ifndef BN_MUSIC_ITEMS_H\n#define BN_MUSIC_ITEMS_H\n\n")
            f.write('#include "bn_music_item.h"\n\n')
            f.write("namespace bn::music_items\n{\n")
            f.write(music_header_items)
            f.write("}\n\n#endif")

        # bn_music_items_info.h
        with open("include/bn_music_items_info.h", "w") as f:
            f.write("#ifndef BN_MUSIC_ITEMS_INFO_H\n#define BN_MUSIC_ITEMS_INFO_H\n\n")
            f.write('#include "bn_span.h"\n#include "bn_music_item.h"\n')
            f.write('#include "bn_string_view.h"\n#include "bn_music_items.h"\n\n')
            f.write("namespace bn::music_items_info\n{\n")
            f.write("    struct pair { music_item item; string_view name; };\n\n")
            f.write("    constexpr inline pair array[] = {\n")
            f.write(music_info_array)
            f.write("    };\n\n")
            f.write("    constexpr inline span<const pair> span(array);\n")
            f.write("}\n\n#endif")

    # --- WRITE SOUND FILES ---
    if found_sound:
        # bn_sound_items.h
        with open("build/bn_sound_items.h", "w") as f:
            f.write("#ifndef BN_SOUND_ITEMS_H\n#define BN_SOUND_ITEMS_H\n\n")
            f.write('#include "bn_sound_item.h"\n\n')
            f.write("namespace bn::sound_items\n{\n")
            f.write(sound_header_items)
            f.write("}\n\n#endif")

        # bn_sound_items_info.h (Requested)
        with open("include/bn_sound_items_info.h", "w") as f:
            f.write("#ifndef BN_SOUND_ITEMS_INFO_H\n#define BN_SOUND_ITEMS_INFO_H\n\n")
            f.write('#include "bn_span.h"\n#include "bn_sound_item.h"\n')
            f.write('#include "bn_string_view.h"\n#include "bn_sound_items.h"\n\n')
            f.write("namespace bn::sound_items_info\n{\n")
            f.write("    struct pair { sound_item item; string_view name; };\n\n")
            f.write("    constexpr inline pair array[] = {\n")
            f.write(sound_info_array)
            f.write("    };\n\n")
            f.write("    constexpr inline span<const pair> span(array);\n")
            f.write("}\n\n#endif")
