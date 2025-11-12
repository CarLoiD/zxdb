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
// File: menu_bar.cc
// ---------------------------------------------------------------------------

#include "menu_bar.hpp"
#include "application.hpp"
#include "base/assert.hpp"

namespace {

GtkWidget* GetSubmenuItem(GtkMenu* menu, const size_t at) {
    GtkWidget* ret = nullptr;

    GList* items = gtk_container_get_children(GTK_CONTAINER(menu));
    ret = static_cast<GtkWidget*>(g_list_nth_data(items, at));
    g_list_free(items);
    
    return ret;
}

} // namespace

namespace UI {

MenuBar::MenuBar()
    : Widget(gtk_menu_bar_new())
{
    m_cb = nullptr;
    m_mb = GTK_MENU_BAR(m_handle);
}

void MenuBar::PushSubmenu(std::string_view label) {
    // The normal C api can be confusing, but just to remember:
    // menu_item is the item on the top level menu bar
    // menu is the pop-up list that show up when menu_item is clicked
    GtkWidget* menu_item = gtk_menu_item_new_with_mnemonic(label.data());
    GtkWidget* menu = gtk_menu_new();

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item), menu);
    m_stack.push_back({ menu_item, menu });
    
    // Save top-level submenus
    if (m_stack.size() == 1) {
        m_submenus.push_back({ menu, label });
    }
}

void MenuBar::PopSubmenu() {
    ASSERT(!m_stack.empty(), "Submenu stack underflow");
    
    auto submenu = m_stack.back();
    m_stack.pop_back();

    // Currently on top-level, add to the menu bar handle, else, nested submenu
    if (m_stack.empty()) {
        gtk_menu_shell_append(GTK_MENU_SHELL(m_mb), submenu.menu_item);
    } else {
        GtkWidget* gtk_submenu = m_stack.back().menu;
        gtk_menu_shell_append(GTK_MENU_SHELL(gtk_submenu), submenu.menu_item);
    }

    gtk_widget_show_all(submenu.menu_item);
}

void MenuBar::EnableItem(const size_t submenu, const size_t item) {
    GtkMenu* submenu_instance = GTK_MENU(m_submenus.at(submenu).instance);

    Widget at(GetSubmenuItem(submenu_instance, item));
    at.Enable();
}

void MenuBar::DisableItem(const size_t submenu, const size_t item) {
    GtkMenu* submenu_instance = GTK_MENU(m_submenus.at(submenu).instance);
    
    Widget at(GetSubmenuItem(submenu_instance, item));
    at.Disable();
}

void MenuBar::AppendItem(MenuItem& item, const s32 id) {
    ASSERT(!(id >= 0 && !m_cb), "Trying to append valid id without cmd callback");
    ASSERT(!m_stack.empty(), "Trying to append item to inactive submenu stack");

    // callback should be a pointer to a function of signature void (*)(s32)
    struct Data {
        s32 id;
        std::function<void(s32)> callback;
    };

    auto* udata = new Data;
    udata->id = id;
    udata->callback = m_cb;

    GtkWidget* handle = item.GetHandle();

    g_signal_connect_data(
        handle,
        "activate",
        G_CALLBACK(+[](GtkMenuItem*, gpointer user_data) {
            auto* data = static_cast<Data*>(user_data);
            if (data->callback && data->id >= 0) {
                data->callback(data->id);
            }
        }),
        udata,
        [](gpointer data, GClosure*) { delete static_cast<Data*>(data); },
        static_cast<GConnectFlags>(0));

    gtk_menu_shell_append(GTK_MENU_SHELL(m_stack.back().menu), handle);
    gtk_widget_show(handle);
}

void MenuBar::AppendSeparator() {
    ASSERT(!m_stack.empty(), "Trying to append item to inactive submenu stack");

    GtkWidget* item = gtk_separator_menu_item_new();
    gtk_menu_shell_append(GTK_MENU_SHELL(m_stack.back().menu), item);
    gtk_widget_show(item);
}

} // namespace UI
