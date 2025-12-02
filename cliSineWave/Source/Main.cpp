#include <JuceHeader.h>

#include "pitches.h"

using namespace juce;

// TODO figure out assertions in
// JUCE Assertion failure in juce_MidiDeviceListConnectionBroadcaster.cpp:48
// JUCE Assertion failure in juce_AsyncUpdater.cpp:78
//
// To do with JUCE_ASSERT_MESSAGE_THREAD

int main(void) {
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
  source->setFrequency(Pitches::A4);
  const auto sleep = 200;

  devmgr.addAudioCallback(player.get());
  Thread::sleep(sleep);
  source->setFrequency(Pitches::C5);
  Thread::sleep(sleep);
  source->setFrequency(Pitches::E5);
  Thread::sleep(sleep);
  source->setFrequency(Pitches::G5);
  Thread::sleep(sleep);
}
