/*
  ==============================================================================

    AudioStream.h
    Created: 14 Jul 2024 7:19:18pm
    Author:  jake

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class AudioStream {
public:

private:
  juce::AudioFormatManager formatManager;
  std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
 };
