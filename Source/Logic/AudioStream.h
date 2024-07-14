/*
  ==============================================================================

    AudioStream.h
    Created: 14 Jul 2024 7:19:18pm
    Author:  jake

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <array>

class AudioStream {
public:
  static constexpr int FIFO_SIZE = 41000 * 4;

  // these two func taken from the juce doc.
  void addToFifo (const std::byte* someData, int numItems)
  {
      const auto scope = abstractFifo.write (numItems);

      if (scope.blockSize1 > 0)
          std::memcpy(audioData.data() + scope.startIndex1, someData, scope.blockSize1);

      if (scope.blockSize2 > 0)
          std::memcpy(audioData.data() + scope.startIndex2, someData + scope.blockSize1, scope.blockSize2);
  }

  void readFromFifo (std::byte* someData, int numItems)
  {
      const auto scope = abstractFifo.read (numItems);

      if (scope.blockSize1 > 0)
          std::memcpy(someData, audioData.data() + scope.startIndex1, scope.blockSize1);

      if (scope.blockSize2 > 0)
          std::memcpy(someData + scope.blockSize1, audioData.data() + scope.startIndex2, scope.blockSize2);
  }

private:
  juce::AbstractFifo abstractFifo{FIFO_SIZE};
  std::array<std::byte, FIFO_SIZE> audioData;
};
