#pragma once
#include <JuceHeader.h>

#include <cstdint>
#include <string>
#include <functional>

// for more info check this out B^)
// https://www.subsonic.org/pages/api.jsp
namespace UrlJobs
{
    using Callback = std::function<void(const juce::String &)>;

    // system
    void ping(Callback callback);
    // Browsing
    void getMusicFolders(Callback callback);
    void getIndexes(Callback callback, const std::string &musicFolderId = "",
                    const std::string &ifModifiedSince = "");
    void getMusicDirectory(Callback callback, const std::string &id);
    void getGenres(Callback callback);
    void getArtists(Callback callback, const std::string &musicFolderId = "");
    void getArtist(Callback callback, const std::string &id);
    void getAlbum(Callback callback, const std::string &id);
    void getSong(Callback callback, const std::string &id);
    void getArtistInfo2(Callback callback, const std::string &id, int64_t count = 20,
                        bool includeNotPresent = false);
    void getAlbumInfo2(Callback callback, const std::string &id);
    void getSimilarSongs2(Callback callback, const std::string &id, int count = 50);
    void getTopSongs(Callback callback, const std::string &artistName, int count = 50);
    void getAlbumList2(Callback callback, const std::string &type,
                       const std::string &fromYear = "", const std::string &toYear = "",
                       int size = 10, int offset = 0,
                       const std::string &musicFolderId = ""); // size: max is 500
    // Searching
    void search(Callback callback, const std::string &artist, const std::string &album,
                const std::string &title, const std::string &any, int count = 20, int offset = 0,
                const std::string &newerThen = "Not sure what type to make this");
    void search2(Callback callback, const std::string &query, int artistCount = 20,
                 int artistOffset = 0, int albumCount = 20, int songCount = 20,
                 int songOffset = 0, const std::string &musicFilderId = "");
    void search3(Callback callback, int artistCount = 20, int artistOffset = 0,
                 int albumCount = 20, int albumOffset = 0, int songCount = 20,
                 int songOffset = 0, const std::string &musicFolderId = "");
    // Album/song lists
    void getRandomSongs(Callback callback, int numberOfSongs);
    // Media retrieval
    void stream(Callback callback, const std::string &id, int maxBitRate = -1,
                const std::string &format = "");
} // namespace UrlJobs
