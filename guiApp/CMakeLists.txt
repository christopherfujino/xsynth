cmake_minimum_required(VERSION 4.0)

project(guiApp
  LANGUAGES C CXX
  VERSION 0.1)

# Generate a compile_commands.json file
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(
  # This is relative to CMakeLists.txt
  ../ignore/JUCE
  # This is relative to build dir
  # TODO can this be shared? Prob not, would have to account for release mode
  JUCE/cmake-build
  # Do not include these targets to ALL target
  EXCLUDE_FROM_ALL)

juce_add_gui_app(main)

target_sources(main PRIVATE main.cpp)

juce_generate_juce_header(main)

target_compile_definitions(main PRIVATE JUCE_WEB_BROWSER=0 JUCE_USE_CURL=0)

target_link_libraries(main PRIVATE
  juce::juce_core
  juce::juce_audio_devices
  juce::juce_audio_formats

  juce::juce_graphics
  juce::juce_gui_basics

  # ? juce_data_structures
  # ? juce_events

  PUBLIC
  juce::juce_recommended_config_flags
  juce::juce_recommended_warning_flags)
