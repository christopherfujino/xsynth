/*
  ==============================================================================

    This file contains the basic startup code for a JUCE application.

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include <stdio.h>

//==============================================================================
int main(int argc, char *argv[]) {
  printf("Your project name: %s\n", ProjectInfo::projectName);
  // ..your code goes here!

  return 42;
}
