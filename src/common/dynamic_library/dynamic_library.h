// Copyright 2023 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include <sstream>
#include <string>
#if defined(_WIN32)
#include <windows.h>
#else
#include <dlfcn.h>
#endif
#include "common/common_types.h"

namespace DynamicLibrary {

class DynamicLibrary {
public:
    explicit DynamicLibrary(const std::string& name, u32 version = 0) {
        const auto full_name = GetLibraryName(name, version);
#if defined(_WIN32)
        handle = LoadLibraryA(full_name.c_str());
        if (!handle) {
            DWORD error_message_id = GetLastError();
            LPSTR message_buffer = nullptr;
            size_t size =
                FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
                                   FORMAT_MESSAGE_IGNORE_INSERTS,
                               nullptr, error_message_id, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                               reinterpret_cast<LPSTR>(&message_buffer), 0, nullptr);
            std::string message(message_buffer, size);
            load_error = message;
        }
#else
        handle = dlopen(full_name.c_str(), RTLD_LAZY);
        if (!handle) {
            load_error = dlerror();
        }
#endif // defined(_WIN32)
    }

    ~DynamicLibrary() {
        if (handle) {
#if defined(_WIN32)
            FreeLibrary(handle);
#else
            dlclose(handle);
#endif // defined(_WIN32)
            handle = nullptr;
        }
    }

    bool IsLoaded() {
        return handle != nullptr;
    }

    const std::string& GetLoadError() {
        return load_error;
    }

    template <typename T>
    struct _symbol_type_helper {
        using type = T;
    };

    template <typename T>
    typename _symbol_type_helper<T>::type GetSymbol(const std::string& name) {
#if defined(_WIN32)
        return reinterpret_cast<T>(GetProcAddress(handle, name.c_str()));
#else
        return reinterpret_cast<T>(dlsym(handle, name.c_str()));
#endif // defined(_WIN32)
    }

private:
#if defined(_WIN32)
    HMODULE handle;
#else
    void* handle;
#endif // defined(_WIN32)
    std::string load_error;

#if defined(_WIN32)
    static constexpr std::string_view lib_prefix = "";
    static constexpr std::string_view lib_suffix = ".dll";
    static constexpr std::string_view lib_version_separator = "-";
    static constexpr bool version_before_suffix = true;
#elif defined(__APPLE__)
    static constexpr std::string_view lib_prefix = "lib";
    static constexpr std::string_view lib_suffix = ".dylib";
    static constexpr std::string_view lib_version_separator = ".";
    static constexpr bool version_before_suffix = true;
#else
    static constexpr std::string_view lib_prefix = "lib";
    static constexpr std::string_view lib_suffix = ".so";
    static constexpr std::string_view lib_version_separator = ".";
    static constexpr bool version_before_suffix = false;
#endif

    static std::string GetLibraryName(const std::string& name, u32 version) {
        std::stringstream lib_name;
        lib_name << lib_prefix << name;
        if (version > 0 && version_before_suffix) {
            lib_name << lib_version_separator << version;
        }
        lib_name << lib_suffix;
        if (version > 0 && !version_before_suffix) {
            lib_name << lib_version_separator << version;
        }
        return lib_name.str();
    }
};

} // namespace DynamicLibrary
