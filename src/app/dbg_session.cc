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
// File: dbg_session.cc
// ---------------------------------------------------------------------------

#include "dbg_session.hpp"

DbgSession::DbgSession()
    : m_initialized(false)
    , m_wnd(nullptr)
{}

DbgSession::~DbgSession() {
    if (m_initialized) {
        Close();
    }
}

void DbgSession::Initialize(UI::Window* window) {
    m_wnd = window;
    m_initialized = true;
}

void DbgSession::Close() {

    m_initialized = false;
}

s32 DbgSession::New() {
    ASSERT_PTR(m_wnd);

    s32 ret = -1;
    m_elf_path = m_wnd->GetFileDialog("Select ELF file to debug", false);    
    if (!m_elf_path.empty()) {

        ret = 0;
    }

    return ret;
}

s32 DbgSession::Open() {
    ASSERT_PTR(m_wnd);

    s32 ret = -1;

    return ret;
}
