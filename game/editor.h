#pragma once

#include "scene/gui/box_container.h"

class Panel;
class HSplitContainer;
class VSplitContainer;
class SubViewport;

class Editor : public VBoxContainer {
	GDCLASS(Editor, VBoxContainer)

	static inline Editor *singleton;

#ifdef DEBUG_ENABLED
	Panel *top_menu;
	HSplitContainer *left_split;
	Panel *left_panel;
	HSplitContainer *right_split;
	VSplitContainer *center_split;
	Panel *bottom_panel;
	Panel *right_panel;
	Panel *bottom_menu;
	SubViewport *game_viewport;
#endif // DEBUG_ENABLED

public:
	void _notification(int p_what);

	Editor();
};
