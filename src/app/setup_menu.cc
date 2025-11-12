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
// File: setup_menu.cc
// ---------------------------------------------------------------------------

#include "setup_menu.hpp"

// TODO: Edit submenu

void SetupSessionMenu(UI::MenuBar& bar) {
    UI::MenuItem session_new("_New...", "Ctrl+N");
    UI::MenuItem session_open("_Open...", "Ctrl+O");
    UI::MenuItem session_save("_Save", "Ctrl+S");
    UI::MenuItem session_save_as("Save _As...");
    UI::MenuItem session_settings("Settin_gs...");
    UI::MenuItem session_exit("E_xit", "Alt+F4");

    bar.PushSubmenu("_Session");
        bar.AppendItem(session_new, MenuOpt::kSessionNew);
        bar.AppendItem(session_open, MenuOpt::kSessionOpen);

        bar.AppendSeparator();
        bar.AppendItem(session_save, MenuOpt::kSessionSave);
        bar.AppendItem(session_save_as, MenuOpt::kSessionSaveAs);
        
        bar.AppendSeparator();
        bar.PushSubmenu("Recent _Executables");
            // TODO: Implement MainWindow::FillRecentExecItems()
        bar.PopSubmenu();
        bar.PushSubmenu("Recent Saved _Sessions");
            // TODO: Implement MainWindow::FillRecentSessionItems()
        bar.PopSubmenu();

        bar.AppendSeparator();
        bar.AppendItem(session_settings, MenuOpt::kSessionSettings);

        bar.AppendSeparator();
        bar.AppendItem(session_exit, MenuOpt::kSessionExit);
    bar.PopSubmenu();

    bar.DisableItem(0, MenuOpt::kSessionSave);
    bar.DisableItem(0, MenuOpt::kSessionSaveAs);
    bar.DisableItem(0, MenuOpt::kSessionRecentExecs);
    bar.DisableItem(0, MenuOpt::kSessionRecentSessions);
}

void SetupViewMenu(UI::MenuBar& bar) {
    UI::MenuItem view_breakpoints("_Breakpoints", "Ctrl+Shift+B");
    UI::MenuItem view_disassembly("_Disassembly", "Ctrl+Shift+D");
    UI::MenuItem view_memory("_Memory", "Ctrl+Shift+M");
    UI::MenuItem view_log_console("_Log Console", "Ctrl+Shift+L");
    UI::MenuItem view_registers("_Registers", "Ctrl+Shift+R");
    UI::MenuItem view_watch("_Watch", "Ctrl+Shift+W");
    UI::MenuItem view_fullscreen("_Full Screen", "Shift+Alt+Enter");

    bar.PushSubmenu("_View");
        bar.AppendItem(view_breakpoints, MenuOpt::kViewBreakpoints);
        bar.AppendItem(view_disassembly, MenuOpt::kViewDisassembly);
        bar.AppendItem(view_memory, MenuOpt::kViewMemory);
        bar.AppendItem(view_log_console, MenuOpt::kViewLogConsole);
        bar.AppendItem(view_registers, MenuOpt::kViewRegisters);
        bar.AppendItem(view_watch, MenuOpt::kViewWatch);

        bar.AppendSeparator();
        bar.PushSubmenu("Appearance");
            bar.AppendItem(view_fullscreen, MenuOpt::kViewAppearanceFullScreen);
        bar.PopSubmenu();

        bar.PushSubmenu("Layout");
            // TODO: Layout related functions
        bar.PopSubmenu();
    bar.PopSubmenu();
    
    const auto offset = MenuOpt::kViewBreakpoints;
    bar.DisableItem(1, MenuOpt::kViewBreakpoints - offset);
    bar.DisableItem(1, MenuOpt::kViewDisassembly - offset);
}

void SetupDebugMenu(UI::MenuBar& bar) {
    UI::MenuItem debug_start("Start _Debugging", "F5");
    UI::MenuItem debug_start_nodbg("Start _Without Debugging", "Ctrl+F5");
    UI::MenuItem debug_continue("_Continue", "Shift+F5");
    UI::MenuItem debug_break("Brea_k", "Ctrl+B");
    UI::MenuItem debug_restart("_Restart", "Ctrl+Shift+F5");
    UI::MenuItem debug_step_over("_Step Over", "F10");
    UI::MenuItem debug_step_in("Step _In", "F11");
    UI::MenuItem debug_step_out("Step _Out", "Shift+F11");
    UI::MenuItem debug_toggle_breakpoint("_Toggle Breakpoint", "F9");
    UI::MenuItem debug_new_bpt_func("At _Function...");
    UI::MenuItem debug_new_bpt_addr("At _Address...");
    UI::MenuItem debug_delete_all_bpt("Delete _All Breakpoints", "Ctrl+Shift+F9");
    UI::MenuItem debug_export_dump("E_xport Dump...");

    bar.PushSubmenu("_Debug");
        bar.AppendItem(debug_start, MenuOpt::kDebugRun);
        bar.AppendItem(debug_start_nodbg, MenuOpt::kDebugRunWithoutDebugging);

        bar.AppendSeparator();
        bar.AppendItem(debug_continue, MenuOpt::kDebugContinue);
        bar.AppendItem(debug_break, MenuOpt::kDebugBreak);
        bar.AppendItem(debug_restart, MenuOpt::kDebugRestart);

        bar.AppendSeparator();
        bar.AppendItem(debug_step_over, MenuOpt::kDebugStepOver);
        bar.AppendItem(debug_step_in, MenuOpt::kDebugStepIn);
        bar.AppendItem(debug_step_out, MenuOpt::kDebugStepOut);

        bar.AppendSeparator();
        bar.AppendItem(debug_toggle_breakpoint, MenuOpt::kDebugToggleBreakpoint);
        bar.PushSubmenu("New Breakpoint");
            bar.AppendItem(debug_new_bpt_func, MenuOpt::kDebugNewBptFunc);
            bar.AppendItem(debug_new_bpt_addr, MenuOpt::kDebugNewBptAddr);
        bar.PopSubmenu();
        bar.AppendItem(debug_delete_all_bpt, MenuOpt::kDebugDeleteAllBrkpts);

        bar.AppendSeparator();
        bar.AppendItem(debug_export_dump, MenuOpt::kDebugExportDump);
    bar.PopSubmenu();
}

void SetupHelpMenu(UI::MenuBar& bar) {
    UI::MenuItem help_user_manual("User _Manual", "Ctrl+F1");
    UI::MenuItem help_about("_About");

    bar.PushSubmenu("_Help");
        bar.AppendItem(help_user_manual, MenuOpt::kHelpDebuggerManual);
        
        bar.AppendSeparator();
        bar.AppendItem(help_about, MenuOpt::kHelpAbout);
    bar.PopSubmenu();
}
