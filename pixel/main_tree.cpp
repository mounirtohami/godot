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

#include "core/os/os.h"

#include "scene/gui/button.h"
#include "scene/main/window.h"

void MainTree::initialize() {
	SceneTree::initialize();

	Button *button = memnew(Button);
	button->set_text("Hello");
	button->set_anchors_and_offsets_preset(Control::PRESET_CENTER);

	get_root()->add_child(button);
}

MainTree::MainTree() {
	print_line(OS::get_singleton()->get_current_rendering_driver_name());
	print_line(OS::get_singleton()->get_current_rendering_method());
	print_line("HELLO PIXEL Engine");
}
