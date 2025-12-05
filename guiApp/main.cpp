#include <JuceHeader.h>

class AudioAppDemo final : public AudioAppComponent {
public:
  AudioAppDemo() {
    setAudioChannels(0, 2);
    setSize(800, 600);
  }

  ~AudioAppDemo() override { shutdownAudio(); }

  void prepareToPlay(int samplesPerBlockExpected,
                     double newSampleRate) override {
    sampleRate = newSampleRate;
    expectedSamplesPerBlock = samplesPerBlockExpected;
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

  void paint(Graphics &g) override {
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));

    float radius = amplitude * 200.0f;

    if (radius >= 0.0f) {
      // Draw an ellipse based on the mouse position and audio volume
      g.setColour(Colours::lightgreen);

      g.fillEllipse(jmax(0.0f, lastMousePosition.x) - radius / 2.0f,
                    jmax(0.0f, lastMousePosition.y) - radius / 2.0f, radius,
                    radius);
    }

    g.drawSingleLineText(String::formatted("Freq: %0.1f", frequency), 50, 100);
  }

  // Mouse handling..
  void mouseDown(const MouseEvent &e) override { mouseDrag(e); }

  void mouseDrag(const MouseEvent &e) override {
    lastMousePosition = e.position;

    frequency = (float)(getHeight() - e.y) * 2.0f;
    amplitude = jmin(0.9f, 0.2f * e.position.x / (float)getWidth());

    phaseDelta = (float)(MathConstants<double>::twoPi * frequency / sampleRate);

    repaint();
  }

  void mouseUp(const MouseEvent &) override {
    amplitude = 0.0f;
    repaint();
  }

  void resized() override {
    // This is called when the component is resized.
    // If you add any child components, this is where you should
    // update their positions.
  }

private:
  float phase = 0.0f;
  float phaseDelta = 0.0f;
  float frequency = 5000.0f;
  float amplitude = 0.2f;

  double sampleRate = 0.0;
  int expectedSamplesPerBlock = 0;
  Point<float> lastMousePosition;

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
