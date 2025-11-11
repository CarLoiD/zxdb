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
// File: main_area.hpp
// ---------------------------------------------------------------------------

#ifndef APP_MAIN_AREA_HPP_
#define APP_MAIN_AREA_HPP_

#include <libgui/libgui.hpp>

enum class StatusMode {
    kNormal     = 0,
    kWarning    = 1,
    kError      = 2,
};

struct MainArea {
    static constexpr int kProjSrcInitDivPos = 300;
    static constexpr int kMemInitDivPos = 940;
    static constexpr int kBottomInitDivPos = 480;
    static constexpr int kBottomPanedInitDivPos = 625;

    UI::Notebook project_views;
    UI::Notebook source_views;
    UI::Notebook memory_views;
    UI::Notebook watch_views;
    UI::Notebook trace_views;
    UI::PanedContainer view_container;
    UI::StatusBar status_bar;

    // Main area box that should contain 
    UI::VBox box;

    void Initialize();
    void SetStatus(std::string_view text, const StatusMode& mode);
};

#endif // APP_MAIN_AREA_HPP_
