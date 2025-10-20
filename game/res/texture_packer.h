#pragma once

#include "core/object/object.h"
#include "core/templates/hash_map.h"

class Image;

class TexturePacker : Object {
	GDCLASS(TexturePacker, Object)

	struct ImageData {
		size_t offset = 0; // offset in the binary data, pointing at width field
		size_t size = 0;
		int width = 0;
		int height = 0;
	};

	inline static HashMap<StringName, const unsigned char *> images_map;

public:
	static bool has_image(const StringName &p_name);
	static Ref<Image> get_image(const StringName &p_name);
	static PackedStringArray get_images();
	static void create();
	static void clear();
};
