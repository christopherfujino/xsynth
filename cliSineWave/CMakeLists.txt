cmake_minimum_required(VERSION 3.30)

project(animations LANGUAGES CXX)

## allow 
#add_subdirectory(../ignore/JUCE)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB LIB_SRC "JuceLibraryCode/*.cpp")

find_package(Freetype REQUIRED)

add_executable(main Source/Main.cpp ${LIB_SRC})

# TODO: should this be private?
target_include_directories(main PRIVATE JuceLibraryCode)

target_include_directories(main PRIVATE ../ignore/JUCE/modules)

target_compile_definitions(main PRIVATE
  JUCE_WEB_BROWSER=0
  JUCE_USE_CURL=0
  JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED=1
)

target_link_libraries(main PRIVATE Freetype::Freetype)

#target_link_libraries(main raylib)

#target_compile_options(main PRIVATE -Wall -Wextra -Wunreachable-code -Wpedantic -Werror)
