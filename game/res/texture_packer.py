import os

import methods


"""
    with open(str(target[0]), "w") as f:
        f.write("/* THIS FILE IS GENERATED. EDITS WILL BE LOST. */\n\n")
        f.write("#pragma once\n\n")

        # emit the actual image data
        f.write("\n".join(image_defs))
        f.write("\n\n")

        # emit the arrays of names and sources
        f.write(f"inline constexpr int images_count = {len(image_names)};\n\n")
        f.write("inline constexpr const char *images_names[] = {\n\t" + ",\n\t".join(image_names) + "\n};\n\n")
        f.write("inline constexpr const unsigned char *images_sources[] = {\n\t" + ",\n\t".join(image_ptrs) + "\n};\n")

"""


def pack_textures(target, source, env):
    images_defs = []
    images_ptrs = []
    images_names = []

    for src in source:
        path = str(src)
        buffer = methods.get_buffer(path)
        image_name = os.path.basename(path).removesuffix(".png")
        images_names.append(f'"{image_name}"')

        formatted_bytes = methods.format_buffer(buffer, 1)
        image_name = image_name.replace(" ", "_")
        images_ptrs.append(image_name)
        images_defs.append(f"inline constexpr unsigned char {image_name}[] = {{\n\t{formatted_bytes}\n}};")

    defs = "\n".join(images_defs)
    images_names_str = ",\n\t".join(images_names)
    ptrs = ",\n\t".join(images_ptrs)

    # --- Generate C++ file ---
    with open(str(target[0]), "w") as file:
        file.write(f"""\
/* THIS FILE IS GENERATED. EDITS WILL BE LOST. */

#pragma once

{defs}

inline constexpr int images_count = {len(images_names)};

inline constexpr const char *images_names[] = {{
\t{images_names_str}
}};

inline constexpr const unsigned char *images_sources[] = {{
\t{ptrs}
}};
""")
