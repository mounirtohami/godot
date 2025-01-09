/**************************************************************************/
/*  color_button.h                                                        */
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

/**************************************************************************/
/*                             PIXEL ENGINE                               */
/* Copyright (c) 2024-present Pixel Engine contributors (see AUTHORS.md). */
/**************************************************************************/
/* NOTICE:                                                                */
/* This file contains modifications and additions specific to the Pixel   */
/* Engine project. While these changes are licensed under the MIT license */
/* for compatibility, we request proper attribution if reused in any      */
/* derivative works, including meta-forks.                                */
/**************************************************************************/

#ifndef COLOR_BUTTON_H
#define COLOR_BUTTON_H

#include "scene/gui/base_button.h"

class ColorButton : public BaseButton {
	GDCLASS(ColorButton, BaseButton);

	bool flat = false;
	Color color = Color(1, 1, 1);

	struct ThemeCache {
		Ref<StyleBox> normal;
		Ref<StyleBox> pressed;
		Ref<StyleBox> hover;
		Ref<StyleBox> hover_pressed;
		Ref<StyleBox> disabled;
		Ref<StyleBox> focus;

		Ref<Texture2D> background_icon;
		Ref<Texture2D> overbright_indicator;
	} theme_cache;

protected:
	void _notification(int);
	static void _bind_methods();

public:
	virtual Size2 get_minimum_size() const override;
	void set_color_no_signal(const Color &p_color);
	void set_color(const Color &p_color);
	Color get_color() const;
	void set_flat(bool p_enabled);
	bool is_flat() const;

	ColorButton(const Color &p_color = Color(1, 1, 1));
};

#endif // COLOR_BUTTON_H
