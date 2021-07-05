cmake_minimum_required(VERSION 3.12)

project(plugins)

add_executable(app "app.cpp")
target_compile_features(app PRIVATE cxx_std_20)

add_library(test_plugin1 SHARED "test_plugin1.cpp")
target_compile_features(test_plugin1 PRIVATE cxx_std_20)

add_library(test_plugin2 SHARED "test_plugin2.cpp")
target_compile_features(test_plugin2 PRIVATE cxx_std_20)

add_library(test_plugin3 SHARED "test_plugin3.cpp")
target_compile_features(test_plugin3 PRIVATE cxx_std_20)
