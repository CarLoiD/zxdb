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
// File: paned.cc
// ---------------------------------------------------------------------------

#include "paned.hpp"

namespace UI {

Paned::Paned(const PanedOrientation& orientation)
    : Widget(gtk_paned_new(static_cast<GtkOrientation>(orientation)))
{
    m_paned = GTK_PANED(m_handle);

    m_resize = false;
    m_shrink = false;

    m_packed = 0;
}

void Paned::SetOpt(const bool resize, const bool shrink) {
    m_resize = resize;
    m_shrink = shrink;
}

void Paned::SetDivPosition(int position) {
    gtk_paned_set_position(m_paned, position);
}

void Paned::Add(Widget& child) {
    if (m_packed >= 2) {
        return;
    }

    if (m_packed) {
        gtk_paned_pack2(m_paned, child.GetHandle(), m_resize, m_shrink);
    } else {
        gtk_paned_pack1(m_paned, child.GetHandle(), m_resize, m_shrink);
    }

    SetOpt(false, false);
    ++m_packed;
}

} // namespace UI
