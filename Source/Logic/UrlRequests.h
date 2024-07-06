#pragma once

#include <JuceHeader.h>
#include "Song.h"
#include <vector>

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
  std::vector<Song> getRandomSongs(int numberOfSongs);
}
