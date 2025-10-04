/**************************************************************************/
/*  split_container.h                                                     */
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

#include "scene/gui/container.h"

class SplitContainer;
class TextureRect;

class SplitContainerDragger : public Control {
	GDCLASS(SplitContainerDragger, Control)

	friend class SplitContainer;

	SplitContainer *sc = nullptr;

protected:
	void _notification(int p_what);
	virtual void gui_input(const Ref<InputEvent> &p_event) override;

#ifdef ACCESSKIT_ENABLED
	void _accessibility_action_inc(const Variant &p_data);
	void _accessibility_action_dec(const Variant &p_data);
	void _accessibility_action_set_value(const Variant &p_data);
#endif // ACCESSKIT_ENABLED

private:
	bool dragging = false;
	int drag_from = 0;
	int drag_ofs = 0;
	bool mouse_inside = false;

public:
	virtual CursorShape get_cursor_shape(const Point2 &p_pos = Point2i()) const override;

	SplitContainerDragger(SplitContainer *p_sc);
};

class SplitContainer : public Container {
	GDCLASS(SplitContainer, Container)

	friend class SplitContainerDragger;

public:
	enum DraggerVisibility {
		DRAGGER_VISIBLE,
		DRAGGER_HIDDEN,
		DRAGGER_HIDDEN_COLLAPSED
	};

	enum CollapseMode {
		COLLAPSE_NONE,
		COLLAPSE_FIRST,
		COLLAPSE_SECOND,
		COLLAPSE_ALL
	};

private:
	int split_offset = 0;
	int computed_split_offset = 0;
	bool vertical = false;
	bool collapsed = false;
	bool child_collapsed = false;
	bool show_drag_area = false;

	CollapseMode collapse_mode = COLLAPSE_NONE;
	DraggerVisibility dragger_visibility = DRAGGER_VISIBLE;
	bool dragging_enabled = true;

	SplitContainerDragger *dragging_area_control = nullptr;

	bool touch_dragger_enabled = false;
	TextureRect *touch_dragger = nullptr;

	struct ThemeCache {
		Color touch_dragger_color;
		Color touch_dragger_pressed_color;
		Color touch_dragger_hover_color;
		Color grabber_icon_normal;
		Color grabber_icon_hovered;
		Color grabber_icon_pressed;

		int separation = 0;
		int minimum_grab_thickness = 0;
		bool draw_grabber_icon = false;
		bool autohide = false;
		bool draw_split_bar = false;
		bool autohide_split_bar = false;

		Ref<Texture2D> touch_dragger_icon;
		Ref<Texture2D> touch_dragger_icon_h;
		Ref<Texture2D> touch_dragger_icon_v;
		Ref<Texture2D> grabber_icon;
		Ref<Texture2D> grabber_icon_h;
		Ref<Texture2D> grabber_icon_v;

		Ref<StyleBox> split_bar_background;
		Ref<StyleBox> h_split_bar_background;
		Ref<StyleBox> v_split_bar_background;

		Ref<StyleBox> split_bar_background_pressed;
		Ref<StyleBox> h_split_bar_background_pressed;
		Ref<StyleBox> v_split_bar_background_pressed;
	} theme_cache;

	_FORCE_INLINE_ Ref<Texture2D> _get_grabber_icon() const { return is_fixed ? theme_cache.grabber_icon : (vertical ? theme_cache.grabber_icon_v : theme_cache.grabber_icon_h); }
	_FORCE_INLINE_ Ref<Texture2D> _get_touch_dragger_icon() const { return is_fixed ? theme_cache.touch_dragger_icon : (vertical ? theme_cache.touch_dragger_icon_v : theme_cache.touch_dragger_icon_h); }
	_FORCE_INLINE_ Ref<StyleBox> _get_split_bar_background() const { return is_fixed ? theme_cache.split_bar_background : (vertical ? theme_cache.v_split_bar_background : theme_cache.h_split_bar_background); }
	_FORCE_INLINE_ Ref<StyleBox> _get_split_bar_pressed_background() const { return is_fixed ? theme_cache.split_bar_background_pressed : (vertical ? theme_cache.v_split_bar_background_pressed : theme_cache.h_split_bar_background_pressed); }

	_FORCE_INLINE_ void _touch_dragger_mouse_exited();
	_FORCE_INLINE_ void _compute_split_offset(bool p_clamp);
	int _get_separation() const;

	void _touch_dragger_gui_input(const Ref<InputEvent> &p_event);
	void _resort();
	Control *_get_sortable_child(int p_idx) const;

protected:
	bool is_fixed = false;

	void _notification(int p_what);
	void _validate_property(PropertyInfo &p_property) const;
	static void _bind_methods();

public:
	void set_split_offset(int p_offset);
	_FORCE_INLINE_ int get_split_offset() const { return split_offset; }

	void clamp_split_offset();

	void set_collapsed(bool p_collapsed);
	_FORCE_INLINE_ bool is_collapsed() const { return collapsed; }

	void set_dragger_visibility(DraggerVisibility p_visibility);
	_FORCE_INLINE_ DraggerVisibility get_dragger_visibility() const { return dragger_visibility; }

	void set_vertical(bool p_vertical);
	_FORCE_INLINE_ bool is_vertical() const { return vertical; }

	void set_dragging_enabled(bool p_enabled);
	_FORCE_INLINE_ bool is_dragging_enabled() const { return dragging_enabled; }

	void set_collapse_mode(CollapseMode p_mode);
	_FORCE_INLINE_ CollapseMode get_collapse_mode() const { return collapse_mode; }

	virtual Size2 get_minimum_size() const override;

	virtual Vector<int> get_allowed_size_flags_horizontal() const override;
	virtual Vector<int> get_allowed_size_flags_vertical() const override;

	void set_show_drag_area_enabled(bool p_enabled);
	_FORCE_INLINE_ bool is_show_drag_area_enabled() const { return show_drag_area; }

	_FORCE_INLINE_ Control *get_drag_area_control() const { return dragging_area_control; }

	void set_touch_dragger_enabled(bool p_enabled);
	_FORCE_INLINE_ bool is_touch_dragger_enabled() const { return touch_dragger_enabled; }

	SplitContainer(bool p_vertical = false);
};

VARIANT_ENUM_CAST(SplitContainer::DraggerVisibility);
VARIANT_ENUM_CAST(SplitContainer::CollapseMode);

class HSplitContainer : public SplitContainer {
	GDCLASS(HSplitContainer, SplitContainer)

public:
	HSplitContainer() :
			SplitContainer(false) { is_fixed = true; }
};

class VSplitContainer : public SplitContainer {
	GDCLASS(VSplitContainer, SplitContainer)

public:
	VSplitContainer() :
			SplitContainer(true) { is_fixed = true; }
};
