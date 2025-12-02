#include <JuceHeader.h>

class App : public juce::JUCEApplication {
public:
  virtual const juce::String getApplicationName() { return "cli-xsynth"; }
  virtual const juce::String getApplicationVersion() { return "0.1"; }

  virtual void initialise(const juce::String &commandLineParameters) {}
  virtual void shutdown() {}
};

START_JUCE_APPLICATION(App)
