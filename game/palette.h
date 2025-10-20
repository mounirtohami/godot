#pragma once

#include "core/io/resource.h"

class Palette : Resource {
	GDCLASS(Palette, Resource)

private:
	PackedColorArray colors;

public:
	void set_colors(const PackedColorArray &p_colors);
	_FORCE_INLINE_ PackedColorArray get_colors() const { return colors; }

	void add_color(const Color &p_color);
	Error remove_color(const Color &p_color);

	void set_color(int p_index, const Color &p_color);
	Color get_color(int p_index);

	_FORCE_INLINE_ Error resize(int p_size) { return colors.resize(p_size); }

	Palette() {}
	Palette(const String &p_name, const PackedColorArray &p_colors) {
		set_name(p_name);
		colors = p_colors;
	}
};
