cmake_minimum_required(VERSION 4.0)

project(xsynth-cli
  # Some JUCE module libs require C
  LANGUAGES C CXX
  # JUCEUtils.cmake requires a version
  VERSION 0.1)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# If JUCE is installed on system, we'd use find_package(JUCE REQUIRED)
add_subdirectory(
  # source
  ../ignore/JUCE
  # binary out
  ../ignore/JUCE/cmake-build
  # Don't include these targets when building "ALL"
  EXCLUDE_FROM_ALL)

juce_add_console_app(main
  PRODUCT_NAME "xsynth-cli binary")

target_sources(main PRIVATE
  Source/Main.cpp)

juce_generate_juce_header(main)

target_compile_definitions(main PRIVATE
  JUCE_WEB_BROWSER=0
  JUCE_USE_CURL=0)

target_link_libraries(main PRIVATE
  juce::juce_audio_devices
  juce::juce_audio_formats

  # transitive
  #juce::juce_audio_basics
  #juce::juce_audio_processors
  #juce::juce_core
  #juce::juce_events

  # Needed?
  #juce::juce_audio_utils
  #juce::juce_data_structures
  #juce::juce_graphics
  #juce::juce_gui_basics
  #juce::juce_gui_extra

  PUBLIC
  juce::juce_recommended_config_flags
  juce::juce_recommended_warning_flags)
