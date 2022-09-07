cmake_minimum_required(VERSION 3.15)

project(nanofile LANGUAGES CXX)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS 1)

add_library(nanofile SHARED src/nanofile.cpp)

target_include_directories(nanofile PUBLIC deps/module-sdk/include)
target_compile_features(nanofile PRIVATE cxx_std_17)
set_target_properties(nanofile PROPERTIES LINKER_LANGUAGE CXX)

if(WIN32)
    target_link_libraries(nanofile PRIVATE "${CMAKE_SOURCE_DIR}/deps/module-sdk/lib/lua.lib")
elseif(UNIX AND NOT APPLE)
    target_link_libraries(nanofile PRIVATE "${CMAKE_SOURCE_DIR}/deps/module-sdk/lib/liblua.a")
endif()