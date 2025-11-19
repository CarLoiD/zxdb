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
// File: main_window.cc
// ---------------------------------------------------------------------------

#include "main_window.hpp"
#include "setup_menu.hpp"

constexpr u32 kInitWidth = 1280;
constexpr u32 kInitHeight = 720;

void MainWindow::OnMenuCommand(s32 id) {
    MenuOpt opt = static_cast<MenuOpt>(id);
    s32 ret = -1;

    switch (opt) {
        case MenuOpt::kSessionNew:
            ret = m_session.New();
            if (ret >= 0) {

            }
        break;

        case MenuOpt::kSessionOpen:
            ret = m_session.Open();
            if (ret >= 0) {

            }
        break;

        case MenuOpt::kSessionExit:
            Close();
        break;

        default: break;
    }
}

void MainWindow::SetupMenuBar() {
    // Setup menu bar and it's actions
    m_mb.SetOnCommandCallback(this, &MainWindow::OnMenuCommand);

    SetupSessionMenu(m_mb);
    SetupViewMenu(m_mb);
    SetupDebugMenu(m_mb);
    SetupHelpMenu(m_mb);
}

void MainWindow::SetupHeaderBar() {
    // Default title while no session is loaded
    m_header_bar.SetTitle("zx-debugger"); 

    UI::Image app_icon("res/icon/app.png");
    app_icon.SetMargin(UI::MarginOpt::kStart, 8);

    m_header_bar.Add(app_icon);
    m_header_bar.Add(m_mb);
    SetHeaderBar(m_header_bar);
}

void MainWindow::SetupCustomStyle() {
    // TODO: Detect dark/light mode switch
    // TODO: Reuse this function when switching dark/light mode
    Widget::GlobalEvalCSSFromFile("res/style/dark.css");
}

void MainWindow::SetupArea() {
    UI::Label workspace("WORKSPACE VIEW.");
    UI::Label symbols("SYMBOLS VIEW.");
    UI::Label functions("FUNCTIONS VIEW.");
    m_area.project_views.AddTab(workspace, "Workspace");
    m_area.project_views.AddTab(symbols, "Symbols");
    m_area.project_views.AddTab(functions, "Functions");

    UI::Label disasm("DISASSEMBLY VIEW.");
    m_area.source_views.AddTab(disasm, "Disassembly");

    UI::Label registers("REGISTERS VIEW.");
    UI::Label memory("MEMORY VIEW.");
    m_area.memory_views.AddTab(registers, "Registers");
    m_area.memory_views.AddTab(memory, "Memory");

    UI::Label watch("WATCH VIEW.");
    m_area.watch_views.AddTab(watch, "Watch");

    UI::Label trace("TRACE VIEW.");
    m_area.trace_views.AddTab(trace, "Call Stack");

    // Initialize icon toolbar, views and status bar
    m_area.Initialize();
}

MainWindow::MainWindow() {
    Resize(kInitWidth, kInitHeight);
    //Maximize();

    // Setup no-session label
    m_empty.SetTextColor(UI::Color(0xa0a0a0));
    m_empty.SetText(
        "No active session. "
        "Open an existing session (Ctrl+O) or create a new one to start debugging."
    );
    
    m_current_view.AddNamed(m_empty, "empty");
    m_current_view.AddNamed(m_area.box, "main");
    m_current_view.SetVisible("empty");

    Add(m_current_view);

    SetupMenuBar();
    SetupHeaderBar();
    SetupCustomStyle();
    SetupArea();

    m_session.Initialize(this);
}

bool MainWindow::Close() {
    // TODO: Implement ConfirmShutdownDialog
    return Window::Close();
}
