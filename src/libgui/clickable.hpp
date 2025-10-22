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
// File: clickable.hpp
// ---------------------------------------------------------------------------

#ifndef LIBGUI_CLICKABLE_HPP_
#define LIBGUI_CLICKABLE_HPP_

#include <base/assert.hpp>
#include <gtk/gtk.h>
#include <type_traits>

namespace UI {

class Clickable {
public:
    Clickable() : m_clickable_widget(nullptr) {}

    // Pointer to member function (method) version
    template <typename T>
    void SetOnClickCallback(T* instance, void (T::*method)(GtkWidget*)) {
        ASSERT(m_clickable_widget, "m_clickable_widget was nullptr");

        // The callback need non scoped data in order to call the method later
        struct Data {
            T* instance;
            void (T::*method)(GtkWidget*);
        };

        // Alloc such data on the heap
        auto* udata = new Data;
        udata->instance = instance;
        udata->method = method;

        // Pass data and set closure to delete the data when widget is destroyed
        g_signal_connect_data(
            m_clickable_widget,
            "clicked",
            G_CALLBACK(+[](GtkWidget* widget, gpointer user_data) {
                auto* thiz = static_cast<Data*>(user_data);
                (thiz->instance->*(thiz->method))(widget);
            }),
            udata,
            [](gpointer data, GClosure*) { delete static_cast<Data*>(data); },
            static_cast<GConnectFlags>(0));
    }

    // Functor version
    template <typename Callable>
    void SetOnClickCallback(Callable&& cb) {
        ASSERT(m_clickable_widget, "m_clickable_widget was nullptr");

        // Clean functor type that can be allocated
        using Functor = std::decay_t<Callable>;

        // Same as in pointer to member, non local scope data is needed...
        auto* udata = new Functor(std::forward<Callable>(cb));

        g_signal_connect_data(
            m_clickable_widget,
            "clicked",
            G_CALLBACK(+[](GtkWidget* widget, gpointer user_data) {
                auto* f = static_cast<Functor*>(user_data);
                (*f)(widget);
            }),
            udata,
            [](gpointer data, GClosure*) { delete static_cast<Functor*>(data); },
            static_cast<GConnectFlags>(0));
    }

protected:
    GtkWidget* m_clickable_widget;
};

} // namespace UI

#endif // LIBGUI_CLICKABLE_HPP_
