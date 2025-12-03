#include "pitches.h"
#include <JuceHeader.h>

using namespace juce;

int main() {
  // This must be called manually if you are not using the
  // START_JUCE_APPLICATION macro, even if you are not using a GUI.
  initialiseJuce_GUI();

  // Create an arbitrary block so that our AudioDeviceManager is deconstructed
  // before we shutdownJuce_GUI()
  {
    AudioDeviceManager devmgr;
    AudioFormatManager fmgr;

    fmgr.registerBasicFormats();
    auto source = std::make_unique<ToneGeneratorAudioSource>();

    // 0 in, 2 out
    devmgr.initialiseWithDefaultDevices(0, 2);
    AudioIODevice *device = devmgr.getCurrentAudioDevice();
    if (!device || !source) {
      return -1;
    }

    source->prepareToPlay(device->getDefaultBufferSize(),
                          device->getCurrentSampleRate());
    auto player = std::make_unique<AudioSourcePlayer>();
    player->setSource(source.get());
    source->setAmplitude(0.5);
    source->setFrequency(Pitches::nameA4);
    const auto sleep = 200;

    devmgr.addAudioCallback(player.get());
    Thread::sleep(sleep);
    source->setFrequency(Pitches::nameC5);
    Thread::sleep(sleep);

    devmgr.closeAudioDevice();
  }
  shutdownJuce_GUI();
}
