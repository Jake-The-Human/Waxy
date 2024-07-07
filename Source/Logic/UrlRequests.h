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
  Artists getArtists(std::string musicFolderId = "");
  Artist getArtist(std::string id);
  Album getAlbum(std::string id);
  Song getSong(std::string id);
  ArtistInfo getArtistInfo2(std::string_view id, int64_t count = 0, bool includeNotPresent = false);
  // Album/song lists
  std::vector<Song> getRandomSongs(int numberOfSongs);
  // Media retrieval
  void stream(std::string id, int maxBitRate = 0, std::string format = "");
}

// seprate the responce and request. bellow will be the class that makes the responce
class URLFetcher : public juce::ThreadPoolJob
{
  public:
    virtual ~URLFetcher() = default;
    URLFetcher() : juce::ThreadPoolJob("URLFetcher") {}
    juce::ThreadPoolJob::JobStatus runJob() override
    {
      return {};
    }
  private:
   juce::String url;
   std::function<void(const juce::String&)> callback;
};
