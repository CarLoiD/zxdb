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
// File: paned.hpp
// ---------------------------------------------------------------------------

#ifndef LIBGUI_PANED_HPP_
#define LIBGUI_PANED_HPP_

#include <libgui/widget.hpp>

namespace UI {

enum class PanedOrientation {
    kHorizontal,
    kVertical,
};

class Paned : public Widget {
public:
    Paned() = delete;
    Paned(const PanedOrientation& orientation);
    
    void SetOpt(const bool resize, const bool shrink);
    void SetDivPosition(int position);
    void Add(Widget& child) override;

private:
    GtkPaned* m_paned;

    int m_packed;

    bool m_resize;
    bool m_shrink;
};

class HPaned final : public Paned {
public:
    HPaned() : Paned(PanedOrientation::kHorizontal) {}
};

class VPaned final : public Paned {
public:
    VPaned() : Paned(PanedOrientation::kVertical) {}
};

} // namespace UI

#endif // LIBGUI_PANED_HPP_
