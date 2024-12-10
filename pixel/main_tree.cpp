/**************************************************************************/
/*  main_tree.cpp                                                         */
/**************************************************************************/
/*                             PIXEL ENGINE                               */
/**************************************************************************/
/* Copyright (c) 2024-present Pixel Engine contributors (see AUTHORS.md). */
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

#include "main_tree.h"

#include "core/object/class_db.h"
#include "core/os/os.h"

#include "scene/gui/menu_button.h"
#include "scene/main/window.h"

void MainTree::initialize() {
	SceneTree::initialize();

	get_root()->set_embedding_subwindows(false);

	print_line("Renderer: " + OS::get_singleton()->get_current_rendering_driver_name());

	MenuButton *button = memnew(MenuButton());
	button->set_text("Classes");
	button->set_flat(false);
	button->set_anchors_and_offsets_preset(Control::PRESET_CENTER);
	get_root()->add_child(button);

	List<StringName> class_list;
	ClassDB::get_class_list(&class_list);
	class_list.sort_custom<StringName::AlphCompare>();
	PopupMenu *popup = button->get_popup();
	for (const StringName &E : class_list) {
		popup->add_item(E);
	}

	OS::get_singleton()->shell_show_in_file_manager(OS::get_singleton()->get_data_path().path_join("pixel"));
}

void MainTree::set_renderer(const String & p_renderer) {
	if (renderer != p_renderer) {
		renderer = p_renderer;
		List<String> args;
		args.push_back("--rendering-driver");
		args.push_back(renderer);
		// OS::get_singleton()->set_restart_on_exit(true, args);
		// print_line(vformat("%s", OS::get_singleton()->get_cmdline_args()));
		Error err = OS::get_singleton()->create_instance(args);
		ERR_FAIL_COND(err);
		quit();
	}
}

MainTree::MainTree() {
	print_line("HELLO PIXEL Engine");
}
