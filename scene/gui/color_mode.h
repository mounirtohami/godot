/**************************************************************************/
/*  color_mode.h                                                          */
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

#pragma once

#include "scene/gui/color_picker.h"

class GradientTexture2D;

class SliderStyleBox : public StyleBox {
	GDCLASS(SliderStyleBox, StyleBox)

	Ref<Texture2D> bg_texture;
	Ref<Texture2D> texture;

protected:
	static void _bind_methods();

public:
	virtual void draw(RID p_canvas_item, const Rect2 &p_rect) const override;

	void set_bg_texture(Ref<Texture2D> p_bg_texture);
	_ALWAYS_INLINE_ Ref<Texture2D> get_bg_texture() const { return bg_texture; }

	void set_texture(Ref<Texture2D> p_texture);
	_ALWAYS_INLINE_ Ref<Texture2D> get_texture() const { return texture; }
};

class ColorMode {
public:
	ColorPicker *color_picker = nullptr;

	_ALWAYS_INLINE_ virtual String get_name() const = 0;
	_ALWAYS_INLINE_ virtual float get_slider_step() const = 0;
	_ALWAYS_INLINE_ virtual float get_spinbox_arrow_step() const { return get_slider_step(); }
	_ALWAYS_INLINE_ virtual String get_slider_label(int idx) const = 0;
	_ALWAYS_INLINE_ virtual float get_slider_max(int idx) const = 0;
	_ALWAYS_INLINE_ virtual bool get_allow_greater(int idx) const { return false; }

	virtual float get_slider_value(int idx) const = 0;
	virtual Color get_color() const = 0;
	virtual void _value_changed() {}
	virtual void _greater_value_inputted() {}
	virtual void slider_draw(int p_which);
	virtual void slider_update(int p_which);

	ColorMode(ColorPicker *p_color_picker);
	virtual ~ColorMode() {}
};

class ColorModeHSV : public ColorMode {
public:
	String labels[4] = { "H", "S", "V", "A" };
	float slider_max[4] = { 359, 100, 100, 255 };
	float cached_hue = 0.0;
	float cached_saturation = 0.0;

	_ALWAYS_INLINE_ virtual String get_name() const override { return "HSV"; }

	_ALWAYS_INLINE_ virtual float get_slider_step() const override { return 1.0; }
	_ALWAYS_INLINE_ virtual String get_slider_label(int idx) const override { return labels[CLAMP(idx, 0, 3)]; }
	_ALWAYS_INLINE_ virtual float get_slider_max(int idx) const override { return slider_max[CLAMP(idx, 0, 3)]; }

	virtual float get_slider_value(int idx) const override;
	virtual Color get_color() const override;
	virtual void _value_changed() override;
	virtual void slider_update(int p_which) override;

	ColorModeHSV(ColorPicker *p_color_picker) :
			ColorMode(p_color_picker) {}
};

class ColorModeRGB : public ColorMode {
public:
	String labels[4] = { "R", "G", "B", "A" };

	_ALWAYS_INLINE_ virtual String get_name() const override { return "RGB"; }
	_ALWAYS_INLINE_ virtual float get_slider_step() const override { return 1; }
	_ALWAYS_INLINE_ virtual String get_slider_label(int idx) const override { return labels[CLAMP(idx, 0, 3)]; }
	_ALWAYS_INLINE_ virtual float get_slider_max(int idx) const override { return 255; }
	_ALWAYS_INLINE_ virtual bool get_allow_greater(int idx) const override { return idx < 3; }

	virtual float get_slider_value(int idx) const override;
	virtual Color get_color() const override;
	virtual void _greater_value_inputted() override;

	ColorModeRGB(ColorPicker *p_color_picker) :
			ColorMode(p_color_picker) {}
};

class ColorModeLinear : public ColorMode {
public:
	String labels[4] = { "R", "G", "B", "A" };

	_ALWAYS_INLINE_ virtual String get_name() const override { return "Linear"; }
	_ALWAYS_INLINE_ virtual float get_slider_step() const override { return 0.001; }
	_ALWAYS_INLINE_ virtual float get_spinbox_arrow_step() const override { return 0.01; }
	_ALWAYS_INLINE_ virtual String get_slider_label(int idx) const override { return labels[CLAMP(idx, 0, 3)]; }
	_ALWAYS_INLINE_ virtual float get_slider_max(int idx) const override { return 1; }
	_ALWAYS_INLINE_ virtual bool get_allow_greater(int idx) const override { return idx < 3; }

	virtual float get_slider_value(int idx) const override;
	virtual Color get_color() const override;
	virtual void _greater_value_inputted() override;

	ColorModeLinear(ColorPicker *p_color_picker) :
			ColorMode(p_color_picker) {}
};

class ColorModeOKHSL : public ColorMode {
public:
	String labels[4] = { "H", "S", "L", "A" };
	float slider_max[4] = { 359, 100, 100, 255 };
	float cached_hue = 0.0;
	float cached_saturation = 0.0;

	_ALWAYS_INLINE_ virtual String get_name() const override { return "OKHSL"; }
	_ALWAYS_INLINE_ virtual float get_slider_step() const override { return 1.0; }
	_ALWAYS_INLINE_ virtual String get_slider_label(int idx) const override { return labels[CLAMP(idx, 0, 3)]; }
	_ALWAYS_INLINE_ virtual float get_slider_max(int idx) const override { return slider_max[CLAMP(idx, 0, 3)]; }

	virtual float get_slider_value(int idx) const override;
	virtual Color get_color() const override;
	virtual void _value_changed() override;
	virtual void slider_update(int p_which) override;

	ColorModeOKHSL(ColorPicker *p_color_picker) :
			ColorMode(p_color_picker) {}
};
