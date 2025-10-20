#include "palette.h"
#include "core/math/color.h"

void Palette::set_colors(const PackedColorArray &p_colors) {
	colors = p_colors;
	emit_changed();
}

void Palette::set_color(int p_index, const Color &p_color) {
	ERR_FAIL_INDEX(p_index, colors.size());

	colors.set(p_index, p_color);
	emit_changed();
}

Color Palette::get_color(int p_index) {
	ERR_FAIL_INDEX_V(p_index, colors.size(), Color());

	return colors[p_index];
}

void Palette::add_color(const Color &p_color) {
	colors.append(p_color);
	emit_changed();
}

Error Palette::remove_color(const Color &p_color) {
	int idx = colors.find(p_color);

	if (idx != -1) {
		colors.remove_at(idx);
	} else {
		return ERR_DOES_NOT_EXIST;
	}

	emit_changed();
	return OK;
}
