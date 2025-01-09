/**************************************************************************/
/*  foldable_container.h                                                  */
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

#ifndef FOLDABLE_CONTAINER_H
#define FOLDABLE_CONTAINER_H

#include "scene/gui/container.h"
#include "scene/resources/text_line.h"

class FoldableContainer : public Container {
	GDCLASS(FoldableContainer, Container);

	struct Button {
		int id = -1;
		Ref<Texture2D> icon = nullptr;
		String tooltip;

		bool disabled = false;
		bool hidden = false;
		bool toggle_mode = false;
		bool toggled_on = false;

		Rect2 rect;

		Variant metadata;
	};

	Vector<FoldableContainer::Button> buttons;
	int _hovered = -1;
	int _pressed = -1;
	bool expanded = true;
	String title;
	Ref<TextLine> text_buf;
	String language;
	Control::TextDirection text_direction = Control::TEXT_DIRECTION_INHERITED;
	HorizontalAlignment title_alignment = HORIZONTAL_ALIGNMENT_LEFT;
	TextServer::OverrunBehavior overrun_behavior = TextServer::OVERRUN_TRIM_ELLIPSIS;

	bool is_hovering = false;
	int title_panel_height = 0;

	struct ThemeCache {
		Ref<StyleBox> title_style;
		Ref<StyleBox> title_hover_style;
		Ref<StyleBox> title_collapsed_style;
		Ref<StyleBox> title_collapsed_hover_style;
		Ref<StyleBox> panel_style;
		Ref<StyleBox> focus_style;

		Ref<StyleBox> button_normal_style;
		Ref<StyleBox> button_hovered_style;
		Ref<StyleBox> button_pressed_style;
		Ref<StyleBox> button_disabled_style;

		Color button_icon_normal;
		Color button_icon_hovered;
		Color button_icon_pressed;
		Color button_icon_disabled;

		Color title_font_color;
		Color title_hovered_font_color;
		Color title_collapsed_font_color;
		Color title_font_outline_color;

		Ref<Font> title_font;
		int title_font_size = 0;
		int title_font_outline_size = 0;

		Ref<Texture2D> arrow;
		Ref<Texture2D> arrow_collapsed;
		Ref<Texture2D> arrow_collapsed_mirrored;

		int h_separation = 0;
	} theme_cache;

	Ref<StyleBox> _get_title_style() const;
	Ref<Texture2D> _get_title_icon() const;
	Size2 _get_title_panel_min_size() const;
	void _shape();

protected:
	virtual void gui_input(const Ref<InputEvent> &p_event) override;
	virtual String get_tooltip(const Point2 &p_pos) const override;
	void _notification(int p_what);
	static void _bind_methods();

public:
	void set_expanded(bool p_expanded);
	bool is_expanded() const;

	void set_title(const String &p_title);
	String get_title() const;

	void set_title_alignment(HorizontalAlignment p_alignment);
	HorizontalAlignment get_title_alignment() const;

	void set_language(const String &p_language);
	String get_language() const;

	void set_text_direction(TextDirection p_text_direction);
	TextDirection get_text_direction() const;

	void set_text_overrun_behavior(TextServer::OverrunBehavior p_overrun_behavior);
	TextServer::OverrunBehavior get_text_overrun_behavior() const;

	int add_button(const Ref<Texture2D> &p_icon, int p_position = -1, int p_id = -1);
	void remove_button(int p_index);

	int get_button_count() const;

	void set_button_id(int p_index, int p_id);
	int get_button_id(int p_index) const;

	int set_button_position(int p_index, int p_position);
	int get_button_position(int p_id) const;

	void set_button_toggle_mode(int p_index, bool p_mode);
	int get_button_toggle_mode(int p_index) const;

	void set_button_toggled(int p_index, bool p_toggled_on);
	bool is_button_toggled(int p_index) const;

	void set_button_icon(int p_index, const Ref<Texture2D> &p_icon);
	Ref<Texture2D> get_button_icon(int p_index) const;

	void set_button_tooltip(int p_index, String p_tooltip);
	String get_button_tooltip(int p_index) const;

	void set_button_disabled(int p_index, bool p_disabled);
	bool is_button_disabled(int p_index) const;

	void set_button_hidden(int p_index, bool p_hidden);
	bool is_button_hidden(int p_index) const;

	void set_button_metadata(int p_index, Variant p_metadata);
	Variant get_button_metadata(int p_index) const;

	int get_button_at_position(const Point2 &p_pos) const;

	virtual Size2 get_minimum_size() const override;

	virtual Vector<int> get_allowed_size_flags_horizontal() const override;
	virtual Vector<int> get_allowed_size_flags_vertical() const override;

	FoldableContainer(const String &p_title = String());
};

#endif // FOLDABLE_CONTAINER_H
