#pragma once
#include <JuceHeader.h>

#include <cstdint>
#include <string>
#include <functional>

namespace UrlJobs {
using Callback = std::function<void(const juce::String &)>;
// for more info check this out B^)
// https://www.subsonic.org/pages/api.jsp

// system
void ping(Callback callback);
// Browsing
void getMusicFolders(Callback callback);
void getIndexes(Callback callback, std::string musicFolderId = "",
                std::string ifModifiedSince = "");
void getMusicDirectory(Callback callback, std::string_view id);
void getGenres(Callback callback);
void getArtists(Callback callback, std::string musicFolderId = "");
void getArtist(Callback callback, std::string id);
void getAlbum(Callback callback, std::string id);
void getSong(Callback callbacki, std::string id);
void getArtistInfo2(Callback callback, std::string_view id, int64_t count = 20,
                    bool includeNotPresent = false);
void getAlbumInfo2(Callback callback, std::string id);
void getSimilarSongs2(Callback callback, std::string id, int count = 50);
void getTopSongs(Callback callback, std::string artistName, int count = 50);
void getAlbumList2(Callback callback, std::string type,
                   std::string fromYear = "", std::string toYear = "",
                   int size = 10, int offset = 0,
                   std::string musicFolderId = ""); // size: max is 500
// Searching
void search(Callback callback, std::string artist, std::string album,
            std::string title, std::string any, int count = 20, int offset = 0,
            std::string newerThen = "Not sure what type to make this");
void search2(Callback callback, std::string query, int artistCount = 20,
             int artistOffset = 0, int albumCount = 20, int songCount = 20,
             int songOffset = 0, std::string musicFilderId = "");
void search3(Callback callback, int artistCount = 20, int artistOffset = 0,
             int albumCount = 20, int albumOffset = 0, int songCount = 20,
             int songOffset = 0, std::string musicFolderId = "");
// Album/song lists
void getRandomSongs(Callback callback, int numberOfSongs);
// Media retrieval
void stream(Callback callback, std::string id, int maxBitRate = -1,
            std::string format = "");
} // namespace UrlJobs
