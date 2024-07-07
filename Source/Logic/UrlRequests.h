#pragma once

#include <JuceHeader.h>
#include "Song.h"
#include <vector>

namespace UrlRequests
{
  // system
  bool ping();
  // Browsing
  juce::String getMusicFolders();
  juce::String getIndexes(std::string musicFolderId = "", std::string ifModifiedSince = "");
  juce::var getMusicDirectory(juce::String id);
  std::vector<Genre> getGenres();
  std::vector<Artist> getArtists(std::string musicFolderId = "");
  Artist getArtist(std::string id);
  Album getAlbum(std::string id);
  Song getSong(int id);
  // Album/song lists
  std::vector<Song> getRandomSongs(int numberOfSongs);
  // Media retrieval
  void stream(std::string id, int maxBitRate = 0, std::string format = "");
  // idk
  juce::var allAlbums();
}
