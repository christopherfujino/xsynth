#include <JuceHeader.h>
#include "pitches.h"

using namespace juce;

int main() {
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
}
