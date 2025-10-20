#include "editor.h"

#include "game/game.h"
#include "scene/gui/panel.h"
#include "scene/gui/split_container.h"
#include "scene/gui/subviewport_container.h"
#include "scene/main/viewport.h"

void Editor::_notification(int p_what) {
	if (p_what == NOTIFICATION_DRAW) {
	}
}

Editor::Editor() {
	singleton = this;

	set_anchors_and_offsets_preset(Control::PRESET_FULL_RECT);

	top_menu = memnew(Panel);
	top_menu->set_custom_minimum_size(Size2(0, 16));
	add_child(top_menu);

	left_split = memnew(HSplitContainer);
	left_split->set_v_size_flags(SIZE_EXPAND_FILL);
	add_child(left_split);

	left_panel = memnew(Panel);
	left_panel->set_custom_minimum_size(Size2(200, 0));
	left_split->add_child(left_panel);

	right_split = memnew(HSplitContainer);
	right_split->set_h_size_flags(SIZE_EXPAND_FILL);
	left_split->add_child(right_split);

	center_split = memnew(VSplitContainer);
	center_split->set_h_size_flags(SIZE_EXPAND_FILL);
	right_split->add_child(center_split);

	SubViewportContainer *svc = memnew(SubViewportContainer);
	svc->set_custom_minimum_size(VEC2S(200));
	svc->set_stretch(true);
	svc->set_v_size_flags(SIZE_EXPAND_FILL);
	center_split->add_child(svc);

	game_viewport = memnew(SubViewport);
	game_viewport->add_child(memnew(Game));

	svc->add_child(game_viewport);

	bottom_panel = memnew(Panel);
	bottom_panel->set_custom_minimum_size(Size2(0, 200));
	center_split->add_child(bottom_panel);

	right_panel = memnew(Panel);
	right_panel->set_custom_minimum_size(Size2(200, 0));
	right_split->add_child(right_panel);
}
