/**************************************************************************/
/*  pixel_default_theme.h                                                 */
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

#ifndef DEFAULT_THEME_H
#define DEFAULT_THEME_H

#include "scene/resources/theme.h"

void finalize_default_theme();
void update_theme_icons(Ref<Theme> &p_theme, Color p_font_color, Color p_accent_color);
void update_font_color(Ref<Theme> &p_theme, Color p_color);
void update_font_outline_color(Ref<Theme> &p_theme, Color p_color);
void update_theme_margins(Ref<Theme> &p_theme, int p_margin);
void update_theme_padding(Ref<Theme> &p_theme, int p_padding);
void update_theme_corner_radius(Ref<Theme> &p_theme, int p_corner_radius);
void update_theme_border_width(Ref<Theme> &p_theme, int p_border_width);
void update_font_outline_size(Ref<Theme> &p_theme, int p_outline_size);
void update_font_size(Ref<Theme> &p_theme, int p_font_size);
void update_theme_border_padding(Ref<Theme> &p_theme, int p_border_padding);
void update_theme_scale(Ref<Theme> &p_theme);
void update_theme_colors(Ref<Theme> &p_theme, Color p_base_color, Color p_accent_color, float p_contrast, float p_base2_contrast, float p_base3_contrast, float p_base4_contrast, float p_accent2_contrast, float p_bg_contrast);
void update_font_embolden(float p_embolden);
void update_font_spacing_glyph(int p_spacing);
void update_font_spacing_space(int p_spacing);
void update_font_spacing_top(int p_spacing);
void update_font_spacing_bottom(int p_spacing);
void update_theme_font(Ref<Theme> &p_theme, Ref<Font> p_font);
void update_font_subpixel_positioning(TextServer::SubpixelPositioning p_font_subpixel_positioning);
void update_font_antialiasing(TextServer::FontAntialiasing p_font_antialiasing);
void update_font_lcd_subpixel_layout(TextServer::FontLCDSubpixelLayout p_font_lcd_subpixel_layout);
void update_font_hinting(TextServer::Hinting p_font_hinting);
void update_font_msdf(bool p_font_msdf);
void update_font_generate_mipmaps(bool p_font_generate_mipmaps);
void make_default_theme(Ref<Font> p_font, float p_scale = 1.f, TextServer::SubpixelPositioning p_font_subpixel = TextServer::SUBPIXEL_POSITIONING_AUTO, TextServer::Hinting p_font_hinting = TextServer::HINTING_LIGHT, TextServer::FontAntialiasing p_font_antialiased = TextServer::FONT_ANTIALIASING_GRAY, TextServer::FontLCDSubpixelLayout p_font_lcd_subpixel_layout = TextServer::FontLCDSubpixelLayout::FONT_LCD_SUBPIXEL_LAYOUT_HRGB, bool p_font_msdf = false, bool p_font_generate_mipmaps = false, Color p_base_color = Color(0.131, 0.152, 0.234), Color p_secondary_color = Color(0.226, 0.478, 0.921), Color p_font_color = Color(0.8, 0.8, 0.8), Color p_font_outline_color = Color(0, 0, 0, 0), float p_contrast = 0.2f, float p_base2_contrast = 0.6f, float p_base3_contrast = 0.4f, float p_base4_contrast = 0.2, float p_accent2_contrast = 0.6, float p_bg_contrast = 0.8, int p_margin = 4, int p_padding = 4, int p_border_width = 2, int p_corner_radius = 6, int p_font_size = 16, int p_font_outline_size = 0, float p_font_embolden = 0.f, int p_font_spacing_glyph = 0, int p_font_spacing_space = 0, int p_font_spacing_top = 0, int p_font_spacing_bottom = 0);

#endif // DEFAULT_THEME_H
