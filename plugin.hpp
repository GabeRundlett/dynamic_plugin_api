#include <filesystem>
#include <sstream>
#include <iostream>
#include <thread>
#include <format>
#include <stdexcept>

// Windows specific implementation throughout whole codebase
#include <Windows.h>

constexpr bool USE_EXCEPTIONS = true;

class DynamicPlugin {
  private:
    HMODULE dll_handle;

  public:
    DynamicPlugin(const std::filesystem::path & path) {
        // This is very cursed. I don't know much about unicode, so this is a
        // 'hack' that allows me to get a single byte c-string from the filepath
        dll_handle = LoadLibrary(path.string().c_str());
        if constexpr (USE_EXCEPTIONS) {
            if (!dll_handle)
                throw std::runtime_error("Failed to 'LoadLibrary'");
        }
    }

    ~DynamicPlugin() { FreeLibrary(dll_handle); }

    auto get_main() const {
        if constexpr (USE_EXCEPTIONS) {
            auto plugin_main_ptr = reinterpret_cast<void (*)()>(
                GetProcAddress(dll_handle, "plugin_main"));
            if (!plugin_main_ptr)
                throw std::runtime_error("Failed to 'GetProcAddress'");
            return plugin_main_ptr;
        } else {
            return reinterpret_cast<void (*)()>(
                GetProcAddress(dll_handle, "plugin_main"));
        }
    }

    void exec() { get_main()(); }
};