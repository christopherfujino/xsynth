#include <JuceHeader.h>

class MainComponent final : public Component {
public:
  //==============================================================================
  MainComponent() {
    addAndMakeVisible(helloWorldLabel);

    helloWorldLabel.setFont(FontOptions(40.00f, Font::bold));
    helloWorldLabel.setJustificationType(Justification::centred);
    helloWorldLabel.setEditable(false, false, false);
    helloWorldLabel.setColour(Label::textColourId, Colours::black);
    helloWorldLabel.setColour(TextEditor::textColourId, Colours::black);
    helloWorldLabel.setColour(TextEditor::backgroundColourId,
                              Colour(0x00000000));

    addAndMakeVisible(quitButton);
    quitButton.onClick = [] { JUCEApplication::quit(); };

    setSize(600, 300);
  }

  //==============================================================================
  void paint(Graphics &g) override {
    g.fillAll(Colour(0xffc1d0ff));

    g.setColour(Colours::white);
    g.fillPath(internalPath);

    g.setColour(Colour(0xff6f6f6f));
    g.strokePath(internalPath, PathStrokeType(5.200f));
  }

  void resized() override {
    helloWorldLabel.setBounds(152, 80, 296, 48);
    quitButton.setBounds(getWidth() - 176, getHeight() - 60, 120, 32);

    internalPath.clear();
    internalPath.startNewSubPath(136.0f, 80.0f);
    internalPath.quadraticTo(176.0f, 24.0f, 328.0f, 32.0f);
    internalPath.quadraticTo(472.0f, 40.0f, 472.0f, 104.0f);
    internalPath.quadraticTo(472.0f, 192.0f, 232.0f, 176.0f);
    internalPath.lineTo(184.0f, 216.0f);
    internalPath.lineTo(200.0f, 168.0f);
    internalPath.quadraticTo(96.0f, 136.0f, 136.0f, 80.0f);
    internalPath.closeSubPath();
  }

private:
  //==============================================================================
  Label helloWorldLabel{{}, TRANS("Hello World!")};
  TextButton quitButton{TRANS("Quit")};
  Path internalPath;

  //==============================================================================
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
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
      setContentOwned(new MainComponent(), true);
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
