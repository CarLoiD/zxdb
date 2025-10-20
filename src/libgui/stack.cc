// ---------------------------------------------------------------------------
//   Copyright 2025 Carlos Gurgel
//
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.
// ---------------------------------------------------------------------------
// File: stack.cc
// ---------------------------------------------------------------------------

#include "stack.hpp"

namespace UI {

Stack::Stack()
    : Widget(gtk_stack_new())
{
    m_stack = GTK_STACK(m_handle);
    SetExpand(true, true);
}

void Stack::AddNamed(Widget& child, std::string_view name) {
    gtk_stack_add_named(
        m_stack, 
        child.GetHandle(), 
        name.data());

    // Ensure the widget can be visible
    child.ShowAll();
}

void Stack::SetVisible(std::string_view name) {
    gtk_stack_set_visible_child_full(
        m_stack,
        name.data(),
        GTK_STACK_TRANSITION_TYPE_CROSSFADE);
}

} // namespace UI
