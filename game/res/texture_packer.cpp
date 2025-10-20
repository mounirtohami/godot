#include "texture_packer.h"

#include "core/io/image.h"
#include "images.gen.h"

bool TexturePacker::has_image(const StringName &p_name) {
	return images_map.has(p_name);
}

Ref<Image> TexturePacker::get_image(const StringName &p_name) {
	if (!images_map.has(p_name)) {
		return Ref<Image>();
	}

	return Ref<Image>(memnew(Image(images_map[p_name])));
}

PackedStringArray TexturePacker::get_images() {
	PackedStringArray arr;
	arr.resize(images_map.size());

	int i = 0;
	for (const KeyValue<StringName, const unsigned char *> &E : images_map) {
		arr.set(i++, E.key);
	}

	return arr;
}

void TexturePacker::create() {
	for (unsigned int i = 0; i < images_count; ++i) {
		images_map.insert(images_names[i], images_sources[i]);
	}
}

void TexturePacker::clear() {
	images_map.clear();
}
