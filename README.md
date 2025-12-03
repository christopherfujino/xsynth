A cross-platform software synthesizer.

## Building

On Ubuntu:

```bash
apt install \
    libcurl4-openssl-dev \
    ladspa
```

## Setup

The following paths are actually source directories:

`~/JUCE`
`~/JUCE/modules`

## Development

The following CMake scaffold will allow bootstrapping a new JUCE project:

```cmake
cmake_minimum_required(VERSION 4.0)

project(xsynth-cmake-no-projucer
  LANGUAGES CXX
  VERSION 0.1)

# Generate a compile_commands.json file
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(
  # This is relative to CMakeLists.txt
  ../ignore/JUCE
  # This is relative to build dir
  JUCE/cmake-build
  # Do not include these targets to ALL target
  EXCLUDE_FROM_ALL)

juce_add_console_app(main)

target_sources(main PRIVATE main.cpp)

juce_generate_juce_header(main)

target_compile_definitions(main PRIVATE JUCE_WEB_BROWSER=0 JUCE_USE_CURL=0)

target_link_libraries(main PRIVATE
  juce::juce_core
  juce::juce_audio_devices
  juce::juce_audio_formats

  PUBLIC
  juce::juce_recommended_config_flags
  juce::juce_recommended_warning_flags)
```
