#pragma once

#include <JuceHeader.h>
#include "Song.h"

namespace UrlRequests
{
  struct UrlResponse
  {
    juce::Result status;
    juce::String response;
  };

  bool ping();
  juce::String getIndexes(std::string musicFolderId, std::string ifModifiedSince);
  juce::var getMusicDirectory(juce::String id);
  juce::String getMusicFolders();
  juce::var allAlbums();
  Song getSong(int id);
  juce::var getRandomSongs(int numberOfSongs);
}
