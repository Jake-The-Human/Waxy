#pragma once

#include <JuceHeader.h>

#include "Song.h"

// // for more info check this out B^)
// // https://www.subsonic.org/pages/api.jsp
namespace ParseJson
{
  // system
  bool ping(const juce::String& json);
  // Browsing
  juce::String getMusicFolders(const juce::String& json);
  SubsonicIndexes getIndexes(const juce::String& json);
  void getMusicDirectory(const juce::String& json);
  std::vector<Genre> getGenres(const juce::String& json);
  Artists getArtists(const juce::String& json);
  Artist getArtist(const juce::String& json);
  Album getAlbum(const juce::String& json);
  Song getSong(const juce::String& json);
  ArtistInfo getArtistInfo2(const juce::String& json);
  void getAlbumInfo2(const juce::String& json);
  void getSimilarSongs2(const juce::String& json);
  void getTopSongs(const juce::String& json);
  void getAlbumList2(const juce::String& json);
  // Searching
  void search(const juce::String& json);
  void search2(const juce::String& json);
  void search3(const juce::String& json);
  // Album/song lists
  std::vector<Song> getRandomSongs(const juce::String& json);
  // Media retrieval
  void stream();
}
