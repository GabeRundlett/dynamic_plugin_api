#include "plugin.hpp"

int main() {
    std::filesystem::path plugin_path;
    std::string           line_str;

    std::getline(std::cin, line_str);
    std::stringstream line_ss(line_str);

    std::vector<std::thread> threads;

    auto load_plugin = [](std::filesystem::path plugin_path) {
        DynamicPlugin test_plugin(plugin_path);
        std::cout << std::format("Calling plugin main of {}\n",
                                 plugin_path.string());
        test_plugin.exec();
        std::cout << "Finished\n";
    };

    while (line_ss >> plugin_path) {
        if (plugin_path == "test_plugin2.dll") load_plugin(plugin_path);
        else
            threads.emplace_back(load_plugin, plugin_path);
    }

    for (auto & thread : threads) thread.join();
}
