#pragma once
#include <JuceHeader.h>

#include <functional>

namespace UrlJobs {
  using Callback = std::function<void(const juce::String &)>;
  // for more info check this out B^)
  // https://www.subsonic.org/pages/api.jsp

  // system
  void ping(Callback callback);
  // Browsing
  void getMusicFolders(Callback callback);
  void getIndexes(Callback callback, std::string musicFolderId = "", std::string
                                                                 ifModifiedSince = "");
  void getMusicDirectory(Callback callback, std::string_view id);
  void getGenres(Callback callback);
  void getArtists(Callback callback, std::string musicFolderId = "");
  void getArtist(Callback callback, std::string id);
  void getAlbum(Callback callback, std::string id);
  void getSong(Callback callbacki, std::string id);
  void getArtistInfo2(Callback callback, std::string_view id, int64_t count = 0, bool includeNotPresent = false);
  // Album/song lists
  void getRandomSongs(Callback callback, int numberOfSongs);
  // Media retrieval
  void stream(Callback callback, std::string id, int maxBitRate = -1, std::string format = "");
}

