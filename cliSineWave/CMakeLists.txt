cmake_minimum_required(VERSION 3.30)

project(animations
  # Some JUCE module libs require C
  LANGUAGES C CXX
  VERSION 0.1
)

# If JUCE is installed on system, we'd use find_package(JUCE REQUIRED)
add_subdirectory(
  # source
  ../ignore/JUCE
  # binary out
  ../ignore/JUCE/cmake-build
  # Don't include these targets when building "ALL"
  EXCLUDE_FROM_ALL
)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

juce_add_console_app(main
  PRODUCT_NAME "Yolo"
)
  # The name of the final executable, which can differ from the target name

file(GLOB LIB_SRC "JuceLibraryCode/*.cpp")

target_sources(main PRIVATE
  Source/Main.cpp
  #${LIB_SRC}
)

#find_package(Freetype REQUIRED)

#add_executable(main Source/Main.cpp ${LIB_SRC})

# TODO: should this be private?
target_include_directories(main PRIVATE JuceLibraryCode)

target_include_directories(main PRIVATE ../ignore/JUCE/modules)
#
target_compile_definitions(main PRIVATE
  JUCE_WEB_BROWSER=0
  JUCE_USE_CURL=0
  #JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED=1
)

target_link_libraries(main PRIVATE
  juce::juce_audio_basics
  juce::juce_audio_devices
  juce::juce_audio_formats
  juce::juce_audio_processors
  juce::juce_audio_utils
  juce::juce_core
  juce::juce_data_structures
  juce::juce_events
  juce::juce_graphics
  juce::juce_gui_basics
  juce::juce_gui_extra

  PUBLIC
  juce::juce_recommended_config_flags
  juce::juce_recommended_warning_flags
)
