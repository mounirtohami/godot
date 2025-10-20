#include "game.h"

#include "game/editor.h"
#include "game/game_tree.h"
#include "game/res/texture_packer.h"
#include "scene/2d/camera_2d.h"
#include "scene/gui/control.h"
#include "scene/main/canvas_layer.h"
#include "scene/main/viewport.h"
#include "scene/main/window.h"
#include "scene/resources/image_texture.h"

void Game::_notification(int p_what) {
	if (p_what == NOTIFICATION_DRAW) {
		if (texture.is_valid()) {
			draw_texture(texture, Vector2());
		}
	}
}

void Game::input(const Ref<InputEvent> &p_event) {
	ERR_FAIL_COND(p_event.is_null());

#ifdef DEBUG_ENABLED
	if (edit_mode) {
		if (_edit_input(p_event)) {
			get_viewport()->set_input_as_handled();
			return;
		}
	}

	Ref<InputEventKey> key = p_event;
	if (key.is_valid() && key->is_pressed() && !key->is_echo()) {
		if (key->get_keycode() == Key::TAB) {
			edit_mode = !edit_mode;
			is_panning = false;
			edit_position = camera->get_position();
			_reset_camera();
		}
	}
#endif // DEBUG_ENABLED
}

#ifdef DEBUG_ENABLED
bool Game::_edit_input(const Ref<InputEvent> &p_event) {
	Ref<InputEventMouseButton> mb = p_event;
	if (mb.is_valid()) {
		if (mb->get_button_index() == MouseButton::MIDDLE) {
			is_panning = mb->is_pressed();
			return true;
		}

		if (mb->is_pressed()) {
			if (mb->get_button_index() == MouseButton::WHEEL_UP) {
				_zoom(1);
				return true;
			}
			if (mb->get_button_index() == MouseButton::WHEEL_DOWN) {
				_zoom(-1);
				return true;
			}
		}
	}

	if (is_panning) {
		Ref<InputEventMouseMotion> mm = p_event;

		if (mm.is_valid()) {
			camera->set_position(camera->get_position() - (mm->get_relative() / camera->get_zoom()));
			return true;
		}
	}

	return false;
}

void Game::_zoom(int p_amount) {
	if (CLAMP(edit_zoom + p_amount, 0, zoom_levels.size() - 1) == edit_zoom) {
		return;
	}
	float old_zoom = zoom_levels[edit_zoom];
	edit_zoom += p_amount;
	float new_zoom = zoom_levels[edit_zoom];
	Point2 mpos = get_viewport()->get_mouse_position();
	Point2 cur_pos = (-get_viewport_rect().size / 2) + mpos;
	camera->set_position(camera->get_position() - (cur_pos / new_zoom - cur_pos / old_zoom));
	camera->set_zoom(VEC2S(new_zoom));
}
#endif // DEBUG_ENABLED

void Game::_draw_rect_unfilled(RID p_canvas_item, const Rect2 &p_rect, const Color &p_color, real_t p_width, bool p_antialiased) const {
	Rect2 rect = p_rect.abs();

	if (p_width >= rect.size.width || p_width >= rect.size.height) {
		RS::get_singleton()->canvas_item_add_rect(p_canvas_item, rect.grow(0.5f * p_width), p_color, p_antialiased);
	} else {
		Vector<Vector2> points;
		points.resize(5);
		points.write[0] = rect.position;
		points.write[1] = rect.position + Vector2(rect.size.x, 0);
		points.write[2] = rect.position + rect.size;
		points.write[3] = rect.position + Vector2(0, rect.size.y);
		points.write[4] = rect.position;

		Vector<Color> colors = { p_color };

		RS::get_singleton()->canvas_item_add_polyline(p_canvas_item, points, colors, p_width, p_antialiased);
	}
}

void Game::_reset_camera() {
#ifdef DEBUG_ENABLED
	if (edit_mode) {
		camera->set_zoom(VEC2S(zoom_levels[edit_zoom]));
		camera->set_position(edit_position);
	} else {
#endif // DEBUG_ENABLED
		camera->set_zoom(VEC2S(zoom_levels[game_zoom]));
		camera->set_position(player_pos);
#ifdef DEBUG_ENABLED
	}
#endif // DEBUG_ENABLED
	camera->set_offset(Vector2());
}

Game::Game() {
	singleton = this;
	set_process_input(true);
	set_texture_filter(TEXTURE_FILTER_NEAREST);

	Ref<Image> img = TexturePacker::get_image("ground_1");
	if (img.is_valid()) {
		texture = ImageTexture::create_from_image(img);
	}

	camera = memnew(Camera2D);
	_reset_camera();
	add_child(camera);

	// canvas = memnew(CanvasLayer);
	// GameTree::get_singleton()->get_root()->add_child(canvas);

	// editor = memnew(Editor);
	// editor->set_anchors_and_offsets_preset(Control::PRESET_FULL_RECT);
	// canvas->add_child(editor);
}
