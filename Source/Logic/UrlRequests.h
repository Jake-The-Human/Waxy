#pragma once

#include <JuceHeader.h>
#include "Song.h"
#include <vector>

// for more info check this out B^)
// https://www.subsonic.org/pages/api.jsp
namespace UrlRequests
{
  // system
  bool ping();
  // Browsing
  juce::String getMusicFolders();
  SubsonicIndexes getIndexes(std::string musicFolderId = "", std::string ifModifiedSince = "");
  juce::var getMusicDirectory(std::string_view id);
  std::vector<Genre> getGenres();
  std::vector<Artist> getArtists(std::string musicFolderId = "");
  Artist getArtist(std::string id);
  Album getAlbum(std::string id);
  Song getSong(std::string id);
  ArtistInfo getArtistInfo2(std::string_view id, int64_t count = 0, bool includeNotPresent = false);
  // Album/song lists
  std::vector<Song> getRandomSongs(int numberOfSongs);
  // Media retrieval
  void stream(std::string id, int maxBitRate = 0, std::string format = "");
}
