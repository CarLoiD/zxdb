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
// File: file.cc
// ---------------------------------------------------------------------------

#include "file.hpp"
#include <cstdio>

namespace Base::File {

size_t GetSize(std::string_view file_path) {
    size_t ret = -1;

    FILE* fp = fopen(file_path.data(), "r");
    if (!fp) return -1;

    fseek(fp, 0, SEEK_END);
    ret = ftell(fp);
    fclose(fp);

    return ret;
}

std::string ReadToString(std::string_view file_path) {
    const size_t sz = GetSize(file_path);
    if (!sz) return "!INVALID FILE SIZE!";

    std::string ret(sz + 1, '\0');
    
    FILE* fp = fopen(file_path.data(), "r");
    if (!fp) return "!INVALID FILE PATH!";

    fseek(fp, 0, SEEK_SET);
    fread(&ret[0], sizeof(char), sz, fp);
    fclose(fp);

    return ret;
}

}
