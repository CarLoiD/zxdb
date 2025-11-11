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
    switch (opt) {
        case MenuOpt::kSessionNew:
        break;

        case MenuOpt::kSessionOpen:
        break;

        case MenuOpt::kSessionRecentExec1:
        case MenuOpt::kSessionRecentExec2:
        case MenuOpt::kSessionRecentExec3:
        case MenuOpt::kSessionRecentExec4:
        case MenuOpt::kSessionRecentExec5:
        break;
        
        case MenuOpt::kSessionRecentSession1:
        case MenuOpt::kSessionRecentSession2:
        case MenuOpt::kSessionRecentSession3:
        case MenuOpt::kSessionRecentSession4:
        case MenuOpt::kSessionRecentSession5:
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
    m_header_bar.SetTitle("zx-debugger"); // Default title while no session is loaded

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

    UI::HPaned bottom;
    bottom.Add(m_area.watch_views);
    bottom.Add(m_area.trace_views);
    bottom.SetDivPosition(MainArea::kBottomPanedInitDivPos);

    UI::Paned* p = nullptr;
    UI::PanedContainer* container = &m_area.view_container;

    p = container->Append(m_area.project_views, UI::PanedOrientation::kHorizontal);
    p = container->Append(m_area.source_views, UI::PanedOrientation::kHorizontal);
    p->SetDivPosition(MainArea::kProjSrcInitDivPos);
    p = container->Append(m_area.memory_views, UI::PanedOrientation::kHorizontal);
    p->SetDivPosition(MainArea::kMemInitDivPos);
    p = container->Append(bottom, UI::PanedOrientation::kVertical);
    p->SetDivPosition(MainArea::kBottomInitDivPos);
    
    // Fill the area with the stack
    m_vbox.SetOpt(true, true);
    m_vbox.Add(container->GetRoot());
}

void MainWindow::SetupStatusBar() {
    m_area.status_bar.AddColor(UI::Color(0x007acc)); // Color 0 -> Normal Status
    m_area.status_bar.AddColor(UI::Color(0xfa0000)); // Color 1 -> Error Status
    m_area.status_bar.AddColor(UI::Color(0xf55505)); // Color 2 -> Warning Status
    m_area.status_bar.SetText("Ready", 0);

    m_vbox.Add(m_area.status_bar);
}

MainWindow::MainWindow() {
    Resize(kInitWidth, kInitHeight);
    Maximize();
    
    // Attach main vertical container
    Add(m_vbox);

    SetupMenuBar();
    SetupHeaderBar();
    SetupCustomStyle();
    SetupArea();
    SetupStatusBar();
}

bool MainWindow::Close() {
    // TODO: Implement ConfirmShutdownDialog
    return Window::Close();
}
