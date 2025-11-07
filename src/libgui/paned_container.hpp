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
// File: paned_container.hpp
// ---------------------------------------------------------------------------

#ifndef LIBGUI_PANED_CONTAINER_HPP_
#define LIBGUI_PANED_CONTAINER_HPP_

#include <libgui/paned.hpp>

namespace UI {

class PanedContainer final {
public:
    PanedContainer() : m_root(nullptr) {}
    ~PanedContainer() {}

    Paned* Append(Widget& child, const PanedOrientation& orientation) {
        if (!m_root) {
            m_root = &child;
            return nullptr;
        }

        // TODO: Find some way to not leak memory, maybe track allocations
        // and free on destructor?
        Paned* paned = nullptr;
        if (orientation == PanedOrientation::kHorizontal) {
            paned = new HPaned();
        } else {
            paned = new VPaned();
        }
        
        // Pack old root + new widget
        paned->Add(*m_root);
        paned->Add(child);

        // Update root
        m_root = paned;
        return paned;
    }

    Widget& GetRoot() const {
        return *m_root;
    }

private:
    Widget* m_root;
};

} // namespace UI

#endif // LIBGUI_PANED_CONTAINER_HPP_
