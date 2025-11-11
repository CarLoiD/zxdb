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
// File: main_area.cc
// ---------------------------------------------------------------------------

#include "main_area.hpp"

void MainArea::Initialize() {
    UI::Paned* p = nullptr;
    UI::PanedContainer* container = &view_container;

    UI::HPaned bottom;
    bottom.Add(watch_views);
    bottom.Add(trace_views);
    bottom.SetDivPosition(kBottomPanedInitDivPos);

    p = container->Append(project_views, UI::PanedOrientation::kHorizontal);
    p = container->Append(source_views, UI::PanedOrientation::kHorizontal);
    p->SetDivPosition(MainArea::kProjSrcInitDivPos);
    p = container->Append(memory_views, UI::PanedOrientation::kHorizontal);
    p->SetDivPosition(kMemInitDivPos);
    p = container->Append(bottom, UI::PanedOrientation::kVertical);
    p->SetDivPosition(kBottomInitDivPos);
    
    box.SetOpt(true, true);
    box.Add(container->GetRoot());

    // Status Bar settings
    // TODO: Colors should be defined somewhere else, to support light/dark theme
    status_bar.AddColor(UI::Color(0x007acc)); // Color 0 -> Normal Status
    status_bar.AddColor(UI::Color(0xf55505)); // Color 1 -> Warning Status
    status_bar.AddColor(UI::Color(0xfa0000)); // Color 2 -> Error Status
    
    box.Add(status_bar);
    
    // Initial status
    SetStatus("Ready", StatusMode::kNormal);
}

void MainArea::SetStatus(std::string_view text, const StatusMode& mode) {
    const size_t col_index = static_cast<size_t>(mode);
    status_bar.SetText(text, col_index);
}
