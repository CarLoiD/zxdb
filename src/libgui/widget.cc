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
// File: widget.cc
// ---------------------------------------------------------------------------

#include "widget.hpp"
#include "base/assert.hpp"
#include "base/file.hpp"

namespace UI {

void Widget::GlobalEvalCSS(std::string_view expression) {
    GtkCssProvider* provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider, expression.data(), -1, nullptr);

    gtk_style_context_add_provider_for_screen(
        gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    g_object_unref(provider);
}

void Widget::GlobalEvalCSSFromFile(std::string_view file_path) {
    const std::string css = Base::File::ReadToString(file_path);
    GlobalEvalCSS(css);
}

Widget::Widget(GtkWidget* handle) {
    m_handle = handle;
    g_object_ref_sink(m_handle);
}

Widget::~Widget() {
    if (m_handle) {
        g_object_unref(G_OBJECT(m_handle));
        m_handle = nullptr;
    }
}

void Widget::Add(Widget& child) {
    ASSERT(false, "Unsupported Widget::Add() operation");
}

void Widget::SetAlignH(const Align& alignment) {
    ASSERT_PTR(m_handle);

    const GtkAlign value = static_cast<GtkAlign>(alignment);
    gtk_widget_set_halign(m_handle, value);
}

void Widget::SetAlignV(const Align& alignment) {
    ASSERT_PTR(m_handle);

    const GtkAlign value = static_cast<GtkAlign>(alignment);
    gtk_widget_set_valign(m_handle, value);
}

void Widget::SetMarginX(const int offset) {
    ASSERT_PTR(m_handle);

    gtk_widget_set_margin_start(m_handle, offset);
    gtk_widget_set_margin_end(m_handle, offset);
}

void Widget::SetMarginY(const int offset) {
    ASSERT_PTR(m_handle);

    gtk_widget_set_margin_top(m_handle, offset);
    gtk_widget_set_margin_bottom(m_handle, offset);
}

void Widget::SetMargin(const MarginMask::Options& mask, const int offset) {
    ASSERT_PTR(m_handle);

    if (mask & MarginOpt::kStart)  gtk_widget_set_margin_start(m_handle, offset);
    if (mask & MarginOpt::kEnd)    gtk_widget_set_margin_end(m_handle, offset);
    if (mask & MarginOpt::kTop)    gtk_widget_set_margin_top(m_handle, offset);
    if (mask & MarginOpt::kBottom) gtk_widget_set_margin_bottom(m_handle, offset);
}

void Widget::SetMargin(const int offset) {
    SetMarginX(offset);
    SetMarginY(offset);
}

void Widget::SetExpand(const bool h_expand, const bool v_expand) {
    ASSERT_PTR(m_handle);

    gtk_widget_set_hexpand(m_handle, h_expand);
    gtk_widget_set_vexpand(m_handle, v_expand);
}

void Widget::RequestSize(const s32 req_width, const s32 req_height) {
    ASSERT_PTR(m_handle);
    gtk_widget_set_size_request(m_handle, req_width, req_height);
}

void Widget::SetTooltipText(std::string_view text) {
    ASSERT_PTR(m_handle);
    gtk_widget_set_tooltip_text(m_handle, text.data());
}

void Widget::SetVisible(const bool visible) {
    ASSERT_PTR(m_handle);
    gtk_widget_set_visible(m_handle, visible);
}

void Widget::Show() {
    SetVisible(true);
}

void Widget::Hide() {
    SetVisible(false);
}

void Widget::SetEnabled(const bool enabled) {
    ASSERT_PTR(m_handle);
    gtk_widget_set_sensitive(m_handle, enabled);
}

void Widget::Enable() {
    SetEnabled(true);
}

void Widget::Disable() {
    SetEnabled(false);
}

void Widget::ShowAll() {
    ASSERT_PTR(m_handle);
    gtk_widget_show_all(m_handle);
}

void Widget::LocalEvalCSS(std::string_view expression) {
    ASSERT_PTR(m_handle);

    GtkCssProvider* provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider, expression.data(), -1, nullptr);

    gtk_style_context_add_provider(
        gtk_widget_get_style_context(m_handle),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    g_object_unref(provider);
}

} // namespace UI
