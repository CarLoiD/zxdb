# ---------------------------------------------------------------------------
#   Copyright 2025 Carlos Gurgel
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.
# ---------------------------------------------------------------------------
# File: CMakeLists.txt
# ---------------------------------------------------------------------------

set(BASE_LIB base/assert.cc
             base/ascii.cc
             base/file.cc
             base/path.cc)

zx_cc_library(NAME libbase SRCS ${BASE_LIB})

set(GUI_LIB libgui/accelerator_target.cc
            libgui/application.cc
            libgui/box.cc
            libgui/button.cc
            libgui/color.cc
            libgui/header_bar.cc
            libgui/image.cc
            libgui/label.cc
            libgui/menu_bar.cc
            libgui/menu_item.cc
            libgui/notebook.cc
            libgui/paned.cc
            libgui/stack.cc
            libgui/status_bar.cc
            libgui/widget.cc
            libgui/window.cc)

zx_cc_library(
    NAME libgui
    SRCS ${GUI_LIB}
    IDIRS ${GTK3_INCLUDE_DIRS} # src/
    LDIRS ${GTK3_LIBRARY_DIRS}
    LIBS ${GTK3_LIBRARIES} zx::base
    COPTS ${GTK3_CFLAGS_OTHER})

set(ZXDB_BIN app/dbg_session.cc
             app/main.cc
             app/main_area.cc
             app/main_window.cc
             app/setup_menu.cc)

# Set the application icon on windows, by linking a resource file
if (WIN32)
    list(APPEND ZXDB_BIN ../bin/res/icon/app.rc)
endif()

zx_cc_binary(NAME zxdb SRCS ${ZXDB_BIN} LIBS zx::gui) 
