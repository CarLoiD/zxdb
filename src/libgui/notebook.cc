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
// File: notebook.cc
// ---------------------------------------------------------------------------

#include "notebook.hpp"

#include <libgui/box.hpp>
#include <libgui/button.hpp>
#include <libgui/label.hpp>

namespace UI {

Notebook::Notebook()
    : Widget(gtk_notebook_new())
{
    m_notebook = GTK_NOTEBOOK(m_handle);

    // Set a default group name so that detachable tabs can attach to it
    // TODO: In the near future, custom group name will be added so that tabs
    // can be attached only to that specific tooling group, for example,
    // a disassembly view would fit to be on the same group as source view
    // or project/workspace view.
    gtk_notebook_set_group_name(m_notebook, "main-group");

    //SetExpand(true, true); // Making sure notebook expands itself
    ShowTabs();
}

void Notebook::AddTab(Widget& child, std::string_view title) {
    Label text(title);

    struct TabData {
        GtkNotebook* notebook;
        GtkWidget* child;
    };

    Button close;
    close.SetTooltipText("Close Tab");
    close.SetIcon("window-close-symbolic");
    
    close.SetOnClickCallback([]{
    });

    HBox custom_label;
    custom_label.SetOpt(true, true);
    custom_label.Add(text);
    custom_label.Add(close);
    custom_label.ShowAll();

    gtk_notebook_append_page(
        m_notebook, 
        child.GetHandle(),
        custom_label.GetHandle());

    // Enable tab behavior
    gtk_notebook_set_tab_detachable(m_notebook, child.GetHandle(), false);
    gtk_notebook_set_tab_reorderable(m_notebook, child.GetHandle(), true);
}

void Notebook::HideTabs() {
    gtk_notebook_set_show_tabs(m_notebook, false);
}

void Notebook::ShowTabs() {
    gtk_notebook_set_show_tabs(m_notebook, true);
}

} // namespace UI
