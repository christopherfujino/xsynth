#include <JuceHeader.h>
#include <cmath>

#include "pitches.h"

class AudioAppDemo final : public AudioAppComponent, juce::Slider::Listener {
public:
  AudioAppDemo() {
    setAudioChannels(0, 2);
    setSize(800, 600);

    frequencySlider.setRange(Pitches::nameA0, Pitches::nameB8);
    frequencySlider.setSliderStyle(juce::Slider::LinearVertical);
    frequencySlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 100);
    frequencySlider.setTextValueSuffix(" HZ");
    frequencySlider.setValue(440);
    frequencySlider.addListener(this);

    addAndMakeVisible(frequencySlider);
  }

  ~AudioAppDemo() override { shutdownAudio(); }
  void sliderValueChanged(juce::Slider *slider) override {
    if (slider == &frequencySlider) {
      frequency = slider->getValue();

      phaseDelta =
          (float)(MathConstants<double>::twoPi * frequency / sampleRate);

      std::printf("Freq = %f Amp = %f\n", frequency, amplitude);
      repaint();
    } else {
      throw std::runtime_error("Yikes");
    }
  }

  void prepareToPlay(int samplesPerBlockExpected,
                     double newSampleRate) override {
    sampleRate = newSampleRate;
    expectedSamplesPerBlock = samplesPerBlockExpected;
    phaseDelta = (float)(MathConstants<double>::twoPi * frequency / sampleRate);
    amplitude = 0.1f; // should be well below 1.0f
  }

  void releaseResources() override {
    // This gets automatically called when audio device parameters change
    // or device is restarted.
  }

  /*  This method generates the actual audio samples.
      In this example the buffer is filled with a sine wave whose frequency and
      amplitude are controlled by the mouse position.
   */
  void getNextAudioBlock(const AudioSourceChannelInfo &bufferToFill) override {
    bufferToFill.clearActiveBufferRegion();
    auto originalPhase = phase;

    for (int chan = 0; chan < bufferToFill.buffer->getNumChannels(); ++chan) {
      phase = originalPhase;

      float *channelData =
          bufferToFill.buffer->getWritePointer(chan, bufferToFill.startSample);

      for (int i = 0; i < bufferToFill.numSamples; ++i) {
        channelData[i] = amplitude * std::sin(phase);

        // increment the phase step for the next sample
        phase = std::fmod(phase + phaseDelta, MathConstants<float>::twoPi);
      }
    }
  }

  // Mouse handling..
  void mouseDown(const MouseEvent &) override {}

  void mouseDrag(const MouseEvent &) override {}

  void mouseUp(const MouseEvent &) override {}

  void resized() override {
    // This is called when the component is resized.
    // If you add any child components, this is where you should
    // update their positions.
    int width = 60;
    int height = getHeight() - 100;
    frequencySlider.setBounds(100, 50, width, height);
  }

private:
  float phase = 0.0f;
  float frequency = 440.0f;
  float phaseDelta = 0.0f;
  float amplitude;

  double sampleRate = 0.0;
  int expectedSamplesPerBlock = 0;
  Point<float> lastMousePosition;
  // Button cButton;

  Slider frequencySlider;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioAppDemo)
};

class App : public JUCEApplication {
public:
  App() {}

  const String getApplicationName() override {
    return ProjectInfo::projectName;
  }

  const String getApplicationVersion() override {
    return ProjectInfo::versionString;
  }

  bool moreThanOneInstanceAllowed() override { return false; }

  void initialise(const String &) override {
    mainWindow.reset(new MainWindow(getApplicationName()));
  }

  void shutdown() override {
    // (deletes the window)
    mainWindow = nullptr;
  }

  void systemRequestedQuit() override {
    // This is called when the app is being asked to quit: you can ignore this
    // request and let the app carry on running, or call quit() to allow the app
    // to close.
    quit();
  }

  void anotherInstanceStarted(const String &) override {
    // When another instance of the app is launched while this one is running,
    // this method is invoked, and the commandLine parameter tells you what
    // the other instance's command-line arguments were.
  }

  // TODO: can this be private?
  class MainWindow : public DocumentWindow {
  public:
    MainWindow(String name)
        : DocumentWindow(
              name,
              Desktop::getInstance().getDefaultLookAndFeel().findColour(
                  ResizableWindow::backgroundColourId),
              DocumentWindow::allButtons) {
      setUsingNativeTitleBar(true);
      setContentOwned(new AudioAppDemo(), true);
      setResizable(true, true);
      centreWithSize(getWidth(), getHeight());
      setVisible(true);
    }

    void closeButtonPressed() override {
      JUCEApplication::getInstance()->systemRequestedQuit();
    }

  private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindow)
  };

private:
  std::unique_ptr<MainWindow> mainWindow = nullptr;
};

START_JUCE_APPLICATION(App)
