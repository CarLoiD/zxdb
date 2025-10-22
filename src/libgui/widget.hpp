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
// File: widget.hpp
// ---------------------------------------------------------------------------

#ifndef LIBGUI_WIDGET_HPP_
#define LIBGUI_WIDGET_HPP_

#include <base/types.hpp>
#include <gtk/gtk.h> 

namespace UI {

class Widget {
public:
    enum class Align {
        kFill       = GTK_ALIGN_FILL,
        kStart      = GTK_ALIGN_START,
        kEnd        = GTK_ALIGN_END,
        kCenter     = GTK_ALIGN_CENTER,
        kBaseLine   = GTK_ALIGN_BASELINE,
    };

    struct MarginMask {
        enum Options : u16 {
            kStart      = (1 << 0),
            kEnd        = (1 << 1),
            kTop        = (1 << 2),
            kBottom     = (1 << 3),
        };
    };

    // GDK screen is used as context for the style eval
    static void GlobalEvalCSS(std::string_view expression);

public:
    Widget() = delete; // Force wrappers to be impl. using Widget(GtkWidget*) constructor
    Widget(GtkWidget* handle);
    virtual ~Widget();

    void SetAlignH(const Align& alignment);
    void SetAlignV(const Align& alignment);
    void SetMarginX(const int offset);
    void SetMarginY(const int offset);
    void SetMargin(const MarginMask::Options& mask, const int offset);
    void SetMargin(const int offset);
    void SetExpand(const bool h_expand, const bool v_expand);
    void RequestSize(const s32 req_width, const s32 req_height);
    void SetTooltipText(std::string_view text);

    void SetVisible(const bool visible);
    void Show();
    void Hide();

    void SetEnabled(const bool enabled);
    void Enable();
    void Disable();

    void ShowAll();

    // Widget instance is used as context
    void LocalEvalCSS(std::string_view expression);

    // Non-pure virtual function, when not overwritten by a subclass it triggers a failure on debug builds
    virtual void Add(Widget& child);

    GtkWidget* GetHandle() const { return m_handle; }

protected:
    GtkWidget* m_handle;
};

using MarginOpt = Widget::MarginMask::Options;

inline MarginOpt operator|(const MarginOpt& lhe, const MarginOpt& rhe) {
    const u16 op = static_cast<u16>(lhe) | static_cast<u16>(rhe);
    return static_cast<MarginOpt>(op);
}

} // namespace UI

#endif // LIBGUI_WIDGET_HPP_
