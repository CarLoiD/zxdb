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
// File: main_window.hpp
// ---------------------------------------------------------------------------

#ifndef CLIENT_MAIN_WINDOW_HPP_
#define CLIENT_MAIN_WINDOW_HPP_

#include <libgui/libgui.hpp>
#include <vector>

class MainWindow : public UI::Window {
private:
    void OnMenuCommand(s32 id);
    void SetupMenuBar();
    void SetupHeaderBar();
    void SetupCustomStyle();
    void SetupArea();
    void SetupStatusBar();

public:
    MainWindow();
    
    // Overwrite so that confirm shutdown dialog can be called
    bool Close() override;

private:
    UI::MenuBar m_mb;
    UI::VBox m_vbox;
    UI::StatusBar m_status;

    // Main area widgets & views
    UI::Stack m_source_stack;
    UI::Notebook m_project_views;
    UI::Notebook m_source_views;
    UI::Notebook m_memory_views;
    UI::Notebook m_trace_views;
    UI::Notebook m_watch_views;

    UI::PanedContainer m_view_container;
};

#endif // CLIENT_MAIN_WINDOW_HPP_
