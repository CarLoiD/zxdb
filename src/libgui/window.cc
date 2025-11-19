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
// File: window.cc
// ---------------------------------------------------------------------------

#include "window.hpp"
#include "application.hpp"
#include "header_bar.hpp"
#include "base/assert.hpp"

namespace UI {

Window::Window() 
    : Widget(gtk_application_window_new(Application::GetDefault()))
{
    m_wnd = GTK_WINDOW(m_handle);

    gtk_window_add_accel_group(m_wnd, Application::GetAccelGroup()); // Register
    Resize(300, 200);
}

void Window::SetHeaderBar(HeaderBar& bar) {
    gtk_window_set_titlebar(m_wnd, bar.GetHandle());
}

void Window::SetTitle(std::string_view new_title) {
    gtk_window_set_title(m_wnd, new_title.data());
}

void Window::Resize(int new_width, int new_height) {
    gtk_window_set_default_size(m_wnd, new_width, new_height);
}

void Window::Maximize() {
    gtk_window_maximize(m_wnd);
}

bool Window::Close() {
    gtk_window_close(m_wnd);
    return false;
}

void Window::Add(Widget& child) {
    ASSERT_PTR(child.GetHandle());
    gtk_container_add(GTK_CONTAINER(m_handle), child.GetHandle());
}

std::string Window::GetFileDialog(std::string_view title, const bool folder) {
    std::string ret = "";

    // Abstracting this doesn't make sense to me, instead since it depends on a Window parent, it's
    // easier and simpler to implement a function that handle both file and folder chooser dialog.

    GtkFileChooserAction flag = folder
        ? GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER
        : GTK_FILE_CHOOSER_ACTION_OPEN;

    GtkWidget* chooser = gtk_file_chooser_dialog_new(
        title.data(),
        m_wnd,
        flag,
        "_Cancel", GTK_RESPONSE_CANCEL,
        "_Open", GTK_RESPONSE_ACCEPT,
        nullptr
    );

    // Default current folder is the home directory (useful specially on Linux)
    gtk_file_chooser_set_current_folder(
        GTK_FILE_CHOOSER(chooser),
        g_get_home_dir()
    );
    
    // Default filters for file chooser
    if (!folder) {
        GtkFileFilter* filter = gtk_file_filter_new();
        gtk_file_filter_set_name(filter, "All Files (*.*)");
        gtk_file_filter_add_pattern(filter, "*.*");

        gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(chooser), filter);
    }

    s32 btn_ret = gtk_dialog_run(GTK_DIALOG(chooser));
    if (btn_ret == GTK_RESPONSE_ACCEPT) {
        ret = std::string(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(chooser)));
    }

    gtk_widget_destroy(chooser);
    return ret;
}

} // namespace UI
