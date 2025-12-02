#include <JuceHeader.h>

using namespace juce;

AudioDeviceManager devmgr;
AudioFormatManager fmgr;

int main(void) {
  fmgr.registerBasicFormats();
  ScopedPointer<ToneGeneratorAudioSource> source =
      new ToneGeneratorAudioSource();

  // 0 in, 2 out
  devmgr.initialiseWithDefaultDevices(0, 2);
  AudioIODevice *device = devmgr.getCurrentAudioDevice();
  if (device && source) {
    source->prepareToPlay(device->getDefaultBufferSize(),
                          device->getCurrentSampleRate());
    ScopedPointer<AudioSourcePlayer> player = new AudioSourcePlayer();
    player->setSource(source);
    devmgr.addAudioCallback(player);
    Thread::sleep(1000);
    source->releaseResources();
    return 0;
  }
  return -1;
}
