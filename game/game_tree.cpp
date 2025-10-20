#include "game_tree.h"

#include "core/config/engine.h"
#include "core/config/project_settings.h"
#include "core/io/file_access.h"
#include "game/editor.h"
#include "game/game.h"
#include "game/res/texture_packer.h"
#include "scene/main/window.h"

void GameTree::initialize() {
	SceneTree::initialize();

	get_root()->set_min_size(Size2i(640, 480));

	ProjectSettings::get_singleton()->set("debug/settings/stdout/print_fps", true);

	print_line(Engine::get_singleton()->get_version_info());
	print_line(OS::get_singleton()->get_current_rendering_driver_name());
	print_line(OS::get_singleton()->get_current_rendering_method());
	// OS::get_singleton()->shell_show_in_file_manager(OS::get_singleton()->get_user_data_dir(), true);

	if (!FileAccess::exists(OS::get_singleton()->get_user_data_dir().path_join("settings.game"))) {
		ProjectSettings::get_singleton()->save();
	}

	print_line("Packed textures:");
	for (String texture_name : TexturePacker::get_images()) {
		print_line(texture_name);
	}

	Window *window = get_root();

#ifdef DEBUG_ENABLED
	window->add_child(memnew(Editor));
#else
	window->add_child(memnew(Game));
#endif // DEBUG_ENABLED
	window->print_tree_pretty();
}

bool GameTree::physics_process(double p_time) {
	return SceneTree::physics_process(p_time);
}

bool GameTree::process(double p_time) {
	return SceneTree::process(p_time);
}

void GameTree::finalize() {
	TexturePacker::clear();
	SceneTree::finalize();
}

GameTree::GameTree() {
	TexturePacker::create();

	singleton = this;
}
