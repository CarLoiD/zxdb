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
// File: dbg_session.hpp
// ---------------------------------------------------------------------------

#ifndef APP_DBG_SESSION_HPP_
#define APP_DBG_SESSION_HPP_

#include <libgui/libgui.hpp>
#include <string>

class DbgSession final {
public:
    DbgSession();
    ~DbgSession();

    void Initialize(UI::Window* window);
    void Close();

    s32  New();
    s32  Open();

    bool IsInitialized() const { return m_initialized; }

private:
    bool m_initialized;

    UI::Window* m_wnd;
    std::string m_elf_path;
};

#endif // APP_DBG_SESSION_HPP_
