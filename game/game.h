#pragma once

#include "scene/2d/node_2d.h"

class Camera2D;
class ImageTexture;
class Control;
class CanvasLayer;
class Editor;

class Game : public Node2D {
	GDCLASS(Game, Node2D)

	friend class Editor;

	static inline Game *singleton;

#ifdef DEBUG_ENABLED
	const PackedFloat32Array zoom_levels = { 0.25, 0.5, 0.75, 1, 2, 3, 4, 8, 16, 32, 64, 128 };

	short edit_zoom = 3;
	bool is_panning = false;
	bool edit_mode = false;
	Vector2 edit_position;
#endif // DEBUG_ENABLED

	short game_zoom = 4;
	Vector2 player_pos;

	Ref<ImageTexture> texture;

	CanvasLayer *canvas = nullptr;
	Editor *editor = nullptr;
	Camera2D *camera = nullptr;

private:
	void _draw_rect_unfilled(RID p_canvas_item, const Rect2 &p_rect, const Color &p_color, real_t p_width = -1.0, bool p_antialiased = false) const;
	void _reset_camera();

#ifdef DEBUG_ENABLED
	void _zoom(int p_amount);
	bool _edit_input(const Ref<InputEvent> &p_event);
#endif // DEBUG_ENABLED

	_ALWAYS_INLINE_ Vector2 _get_zoom() {
#ifdef DEBUG_ENABLED
		if (edit_mode) {
			return VEC2S(zoom_levels[edit_zoom]);
		}
#endif
		return VEC2S(zoom_levels[game_zoom]);
	}

protected:
	void _notification(int p_what);
	virtual void input(const Ref<InputEvent> &p_event) override;

public:
	static Game *get_singleton() { return singleton; }
	Camera2D *get_camera() const { return camera; }

	Game();
};
