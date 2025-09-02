/**************************************************************************/
/*  color_mode.cpp                                                        */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#include "color_mode.h"

#include "core/math/color.h"
#include "scene/gui/slider.h"
#include "scene/resources/gradient_texture.h"

void SliderStyleBox::draw(RID p_canvas_item, const Rect2 &p_rect) const {
	if (bg_texture.is_valid()) {
		bg_texture->draw_rect(p_canvas_item, p_rect, true);
	}

	if (texture.is_valid()) {
		texture->draw_rect(p_canvas_item, p_rect, false);
	}
}

void SliderStyleBox::set_bg_texture(Ref<Texture2D> p_bg_texture) {
	if (p_bg_texture == bg_texture) {
		return;
	}
	bg_texture = p_bg_texture;
	emit_changed();
}

void SliderStyleBox::set_texture(Ref<Texture2D> p_texture) {
	if (p_texture == texture) {
		return;
	}
	texture = p_texture;
	emit_changed();
}

void SliderStyleBox::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_texture", "texture"), &SliderStyleBox::set_texture);
	ClassDB::bind_method(D_METHOD("get_texture"), &SliderStyleBox::get_texture);

	ClassDB::bind_method(D_METHOD("set_bg_texture", "texture"), &SliderStyleBox::set_bg_texture);
	ClassDB::bind_method(D_METHOD("get_bg_texture"), &SliderStyleBox::get_bg_texture);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_texture", "get_texture");
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "bg_texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_bg_texture", "get_bg_texture");
}

void ColorMode::slider_update(int p_which) {
	const Color color = color_picker->color_normalized;
	const Color left_color = Color(
			p_which == 0 ? 0 : color.r,
			p_which == 1 ? 0 : color.g,
			p_which == 2 ? 0 : color.b,
			p_which == 3 ? 0 : 1);
	const Color right_color = Color(
			p_which == 0 ? 1 : color.r,
			p_which == 1 ? 1 : color.g,
			p_which == 2 ? 1 : color.b);

	Ref<GradientTexture2D> gradient_texture = color_picker->slider_style_box[p_which]->get_texture();
	Ref<Gradient> gradient = gradient_texture->get_gradient();

	Gradient::ColorSpace color_space;
	if (p_which == 3 || typeid(*this) == typeid(ColorModeRGB)) {
		color_space = Gradient::GRADIENT_COLOR_SPACE_SRGB;
	} else {
		color_space = Gradient::GRADIENT_COLOR_SPACE_LINEAR_SRGB;
	}

	gradient->set_interpolation_color_space(color_space);
	gradient->set_offsets({ 0.f, 1.f });
	bool rtl = color_picker->get_slider(p_which)->is_layout_rtl();
	gradient->set_colors(rtl ? Vector<Color>{ right_color, left_color } : Vector<Color>{ left_color, right_color });
}

void ColorMode::slider_draw(int p_which) {
	HSlider *slider = color_picker->get_slider(p_which);
	RID slider_ci = slider->get_canvas_item();

	const ColorPicker::ThemeCache &theme_cache = color_picker->theme_cache;
	const Size2 size = slider->get_size();
	const Point2 pos = Point2(MIN(1.0, slider->get_value() / slider->get_max()), 0.5) * size;
	Color color = color_picker->color_normalized;
	bool rtl = color_picker->get_slider(p_which)->is_layout_rtl();

	if (p_which == 3) {
		Size2 checkerboard_size = theme_cache.slider_cursor_checkerboard->get_size();
		Point2 checkerboard_position = pos - checkerboard_size * 0.5;
		theme_cache.slider_cursor_checkerboard->draw(slider_ci, rtl ? Point2(size.width - checkerboard_position.x - checkerboard_size.width, checkerboard_position.y) : checkerboard_position);
	} else {
		color.a = 1.f;
	}

	Size2 cursor_bg_size = theme_cache.slider_cursor_bg->get_size();
	Point2 cursor_bg_pos = pos - cursor_bg_size * 0.5;
	theme_cache.slider_cursor_bg->draw(slider_ci, rtl ? Point2(size.width - cursor_bg_pos.x - cursor_bg_size.width, cursor_bg_pos.y) : cursor_bg_pos, color);

	Size2 cursor_size = theme_cache.slider_cursor->get_size();
	Point2 cursor_pos = pos - cursor_size * 0.5;
	theme_cache.slider_cursor->draw(slider_ci, rtl ? Point2(size.width - cursor_pos.x - cursor_size.width, cursor_pos.y) : cursor_pos);
}

ColorMode::ColorMode(ColorPicker *p_color_picker) {
	color_picker = p_color_picker;
}

float ColorModeRGB::get_slider_value(int idx) const {
	return color_picker->color_normalized.components[idx] * 255;
}

Color ColorModeRGB::get_color() const {
	Vector<float> values = color_picker->get_active_slider_values();
	Color color;
	for (int i = 0; i < 4; i++) {
		color.components[i] = values[i] / 255.0;
	}
	return color;
}

void ColorModeRGB::_greater_value_inputted() {
	HSlider **sliders = color_picker->sliders;
	Color color_prev = color_picker->color;
	for (int i = 0; i < 3; i++) {
		if (sliders[i]->get_value() > 255) {
			color_prev.components[i] = sliders[i]->get_value() / 255.0;
		}
	}
	Color linear_color = color_prev.srgb_to_linear();
	float multiplier = MAX(1, MAX(MAX(linear_color.r, linear_color.g), linear_color.b));
	Color srgb = Color(linear_color.r / multiplier, linear_color.g / multiplier, linear_color.b / multiplier, linear_color.a).linear_to_srgb();
	sliders[0]->set_value_no_signal(srgb.r * 255);
	sliders[1]->set_value_no_signal(srgb.g * 255);
	sliders[2]->set_value_no_signal(srgb.b * 255);

	color_picker->intensity = Math::log2(multiplier);
	color_picker->intensity_slider->set_value_no_signal(color_picker->intensity);
}

void ColorModeHSV::_value_changed() {
	Vector<float> values = color_picker->get_active_slider_values();

	if (values[1] > 0 || values[0] != cached_hue) {
		cached_hue = values[0];
	}
	if (values[2] > 0 || values[1] != cached_saturation) {
		cached_saturation = values[1];
	}

	// Cache real HSV values in ColorPicker.
	color_picker->h = color_picker->sliders[0]->get_value() / 360.0;
	color_picker->s = color_picker->sliders[1]->get_value() / 100.0;
	color_picker->v = color_picker->sliders[2]->get_value() / 100.0;

	color_picker->hsv_cached = true;
}

float ColorModeHSV::get_slider_value(int idx) const {
	switch (idx) {
		case 0: {
			if (color_picker->color_normalized.get_s() > 0) {
				return color_picker->color_normalized.get_h() * 360.0;
			} else {
				return cached_hue;
			}
		}
		case 1: {
			if (color_picker->color_normalized.get_v() > 0) {
				return color_picker->color_normalized.get_s() * 100.0;
			} else {
				return cached_saturation;
			}
		}
		case 2:
			return color_picker->color_normalized.get_v() * 100.0;
		case 3:
			return color_picker->color_normalized.a * 255.0;
		default:
			ERR_FAIL_V_MSG(0, "Couldn't get slider value.");
	}
}

Color ColorModeHSV::get_color() const {
	Vector<float> values = color_picker->get_active_slider_values();
	return Color::from_hsv(values[0] / 360.0, values[1] / 100.0, values[2] / 100.0, values[3] / 255.0);
}

void ColorModeHSV::slider_update(int p_which) {
	if (p_which == 3) {
		ColorMode::slider_update(p_which);
		return;
	}

	Ref<GradientTexture2D> gradient_texture = color_picker->slider_style_box[p_which]->get_texture();
	Ref<Gradient> gradient = gradient_texture->get_gradient();
	gradient->set_interpolation_color_space(Gradient::GRADIENT_COLOR_SPACE_SRGB);
	const Color color = color_picker->color_normalized;
	bool rtl = color_picker->get_slider(p_which)->is_layout_rtl();

	if (p_which == 0) {
		const int precision = 7;

		PackedFloat32Array offsets;
		offsets.resize(precision);
		PackedColorArray colors;
		colors.resize(precision);

		for (int i = 0; i < precision; i++) {
			float h = i / float(precision - 1);
			offsets.write[i] = h;
			colors.write[rtl ? (precision - 1) - i : i] = Color::from_hsv(h, color.get_s(), color.get_v());
		}

		gradient->set_offsets(offsets);
		gradient->set_colors(colors);
		return;
	}

	Color s_col, v_col;
	s_col.set_hsv(color.get_h(), 0, color.get_v());
	const Color left_color = (p_which == 1) ? s_col : Color(0, 0, 0);

	float s_col_hue = (Math::is_zero_approx(color.get_s())) ? cached_hue / 360.0 : color.get_h();
	s_col.set_hsv(s_col_hue, 1, color.get_v());
	v_col.set_hsv(color.get_h(), color.get_s(), 1);
	const Color right_color = (p_which == 1) ? s_col : v_col;

	gradient->set_offsets({ 0.f, 1.f });
	gradient->set_colors(rtl ? Vector<Color>{ right_color, left_color } : Vector<Color>{ left_color, right_color });
	gradient_texture->emit_changed();
}

float ColorModeLinear::get_slider_value(int idx) const {
	Color color = color_picker->color_normalized.srgb_to_linear();
	return color.components[idx];
}

Color ColorModeLinear::get_color() const {
	Vector<float> values = color_picker->get_active_slider_values();
	Color color;
	for (int i = 0; i < 4; i++) {
		color.components[i] = values[i];
	}
	return color.linear_to_srgb();
}

void ColorModeLinear::_greater_value_inputted() {
	HSlider **sliders = color_picker->sliders;
	Color color_prev = color_picker->color;
	Color linear_color = color_prev.srgb_to_linear();
	for (int i = 0; i < 3; i++) {
		if (sliders[i]->get_value() > 1 + CMP_EPSILON) {
			linear_color.components[i] = sliders[i]->get_value();
		}
	}

	float multiplier = MAX(1, MAX(MAX(linear_color.r, linear_color.g), linear_color.b));

	sliders[0]->set_value_no_signal(linear_color.r / multiplier);
	sliders[1]->set_value_no_signal(linear_color.g / multiplier);
	sliders[2]->set_value_no_signal(linear_color.b / multiplier);

	color_picker->intensity = Math::log2(multiplier);
	color_picker->intensity_slider->set_value_no_signal(color_picker->intensity);
}

void ColorModeOKHSL::_value_changed() {
	Vector<float> values = color_picker->get_active_slider_values();

	if (values[1] > 0 || values[0] != cached_hue) {
		cached_hue = values[0];
	}
	if (values[2] > 0 || values[1] != cached_saturation) {
		cached_saturation = values[1];
	}

	// Cache real OKHSL values in ColorPicker.
	color_picker->ok_hsl_h = color_picker->sliders[0]->get_value() / 360.0;
	color_picker->ok_hsl_s = color_picker->sliders[1]->get_value() / 100.0;
	color_picker->ok_hsl_l = color_picker->sliders[2]->get_value() / 100.0;

	color_picker->okhsl_cached = true;
}

float ColorModeOKHSL::get_slider_value(int idx) const {
	switch (idx) {
		case 0: {
			if (color_picker->color_normalized.get_ok_hsl_s() > 0) {
				return color_picker->color_normalized.get_ok_hsl_h() * 360.0;
			} else {
				return cached_hue;
			}
		}
		case 1: {
			if (color_picker->color_normalized.get_ok_hsl_l() > 0) {
				return color_picker->color_normalized.get_ok_hsl_s() * 100.0;
			} else {
				return cached_saturation;
			}
		}
		case 2:
			return color_picker->color_normalized.get_ok_hsl_l() * 100.0;
		case 3:
			return color_picker->color_normalized.a * 255.0;
		default:
			ERR_FAIL_V_MSG(0, "Couldn't get slider value.");
	}
}

Color ColorModeOKHSL::get_color() const {
	Vector<float> values = color_picker->get_active_slider_values();
	return Color::from_ok_hsl(values[0] / 360.0, values[1] / 100.0, values[2] / 100.0, values[3] / 255.0);
}

void ColorModeOKHSL::slider_update(int p_which) {
	if (p_which == 3) {
		ColorMode::slider_update(p_which);
		return;
	}

	Ref<GradientTexture2D> gradient_texture = color_picker->slider_style_box[p_which]->get_texture();
	Ref<Gradient> gradient = gradient_texture->get_gradient();
	const Color color = color_picker->color_normalized;
	const float okhsl_l = color.get_ok_hsl_l();
	bool rtl = color_picker->get_slider(p_which)->is_layout_rtl();

	if (p_which == 0 || p_which == 2) {
		const float slider_sat = (Math::is_zero_approx(okhsl_l) || Math::is_equal_approx(okhsl_l, 1)) ? cached_saturation / 100.0 : color.get_ok_hsl_s();
		const int precision = 7;

		PackedFloat32Array offsets;
		offsets.resize(precision);
		PackedColorArray colors;
		colors.resize(precision);

		if (p_which == 0) {
			for (int i = 0; i < precision; i++) {
				float h = i / float(precision - 1);
				offsets.write[i] = h;
				colors.write[rtl ? (precision - 1) - i : i] = Color::from_ok_hsl(h, slider_sat, okhsl_l);
			}
			gradient->set_interpolation_color_space(Gradient::GRADIENT_COLOR_SPACE_OKLAB);
		} else {
			const float slider_hue = (Math::is_zero_approx(color.get_ok_hsl_s())) ? cached_hue / 360.0 : color.get_ok_hsl_h();

			for (int i = 0; i < precision; i++) {
				float l = i / float(precision - 1);
				offsets.write[i] = l;
				colors.write[rtl ? (precision - 1) - i : i] = Color::from_ok_hsl(slider_hue, slider_sat, l);
			}
			gradient->set_interpolation_color_space(Gradient::GRADIENT_COLOR_SPACE_SRGB);
		}

		gradient->set_offsets(offsets);
		gradient->set_colors(colors);
		return;
	}

	gradient->set_interpolation_color_space(Gradient::GRADIENT_COLOR_SPACE_SRGB);

	const float slider_hue = (Math::is_zero_approx(color.get_ok_hsl_s())) ? cached_hue / 360.0 : color.get_ok_hsl_h();

	gradient->set_offsets({ 0.f, 1.f });
	const Color left_color = Color::from_ok_hsl(slider_hue, 0, okhsl_l);
	const Color right_color = Color::from_ok_hsl(slider_hue, 1, okhsl_l);
	gradient->set_colors(rtl ? Vector<Color>{ right_color, left_color } : Vector<Color>{ left_color, right_color });
}
