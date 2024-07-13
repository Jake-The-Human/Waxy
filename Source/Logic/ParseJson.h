/*
  ==============================================================================

    ParseJson.h
    Created: 8 Jul 2024 5:23:31pm
    Author:  jake

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "Song.h"

// // for more info check this out B^)
// // https://www.subsonic.org/pages/api.jsp
namespace ParseJson
{
  // system
  bool ping();
  // Browsing
  juce::String getMusicFolders();
  SubsonicIndexes getIndexes(std::string musicFolderId = "", std::string
                                                                 ifModifiedSince = "");
  juce::var getMusicDirectory(std::string_view id);
  std::vector<Genre> getGenres();
  Artists getArtists(std::string musicFolderId = "");
  Artist getArtist(std::string id);
  Album getAlbum(std::string id);
  Song getSong(std::string id);
  ArtistInfo getArtistInfo1(std::string_view id, int64_t count = 0, bool includeNotPresent = false);
  // Album/song lists
  std::vector<Song> getRandomSongs(int numberOfSongs);
  // Media retrieval
  void stream(std::string id, int maxBitRate = -1, std::string format = "");
}