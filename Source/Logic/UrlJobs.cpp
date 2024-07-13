#include "UrlJobs.h"

#include "UrlJob.h"
#include "UrlRequests.h"

void UrlJobs::ping(Callback callback) {
  UrlRequests::getInstance()->addJob(new UrlJob("ping", "ping", {}, callback),
                                     true);
}

void UrlJobs::getMusicFolders(Callback callback) {
  UrlRequests::getInstance()->addJob(
      new UrlJob("getMusicFolders", "getMusicFolders", {}, callback), true);
}

void UrlJobs::getIndexes(Callback callback, std::string musicFolderId,
                         std::string ifModifiedSince) {
  juce::StringPairArray queryParams;
  if (!musicFolderId.empty()) {
    queryParams.set("musicFolderId", musicFolderId);
  }

  if (!ifModifiedSince.empty()) {
    queryParams.set("ifModifiedSince", ifModifiedSince);
  }
  UrlRequests::getInstance()->addJob(
      new UrlJob("getIndexes", "getIndexes", queryParams, callback), true);
}

void UrlJobs::getMusicDirectory(Callback callback, std::string_view id) {
  juce::StringPairArray queryParams;
  queryParams.set("id", std::string(id));

  UrlRequests::getInstance()->addJob(new UrlJob("getMusicDirectory",
                                                "getMusicDirectory",
                                                queryParams, callback),
                                     true);
}

void UrlJobs::getGenres(Callback callback) {
  UrlRequests::getInstance()->addJob(
      new UrlJob("getGenres", "getGenres", {}, callback), true);
}

void UrlJobs::getArtists(Callback callback, std::string musicFolderId) {
  juce::StringPairArray queryParams;
  if (!musicFolderId.empty()) {
    queryParams.set("musicFolderId", musicFolderId);
  }
  UrlRequests::getInstance()->addJob(
      new UrlJob("getArtists", "getArtists", queryParams, callback), true);
}

void UrlJobs::getArtist(Callback callback, std::string id) {
  juce::StringPairArray queryParams;
  queryParams.set("id", std::string(id));

  UrlRequests::getInstance()->addJob(
      new UrlJob("getArtist", "getArtist", queryParams, callback), true);
}

void UrlJobs::getAlbum(Callback callback, std::string id) {
  juce::StringPairArray queryParams;
  queryParams.set("id", std::string(id));

  UrlRequests::getInstance()->addJob(
      new UrlJob("getAlbum", "getAlbum", queryParams, callback), true);
}

void UrlJobs::getSong(Callback callback, std::string id) {
  juce::StringPairArray queryParams;
  queryParams.set("id", std::string(id));

  UrlRequests::getInstance()->addJob(
      new UrlJob("getSong", "getSong", queryParams, callback), true);
}

void UrlJobs::getArtistInfo2(Callback callback, std::string_view id,
                             int64_t count, bool includeNotPresent) {
  juce::StringPairArray queryParams;
  queryParams.set("id", std::string(id));
  if (count > 0) {
    queryParams.set("count", std::to_string(count));
  }

  if (includeNotPresent) {
    queryParams.set("includeNotPresent", "true");
  }
  UrlRequests::getInstance()->addJob(
      new UrlJob("getArtistInfo2", "getArtistInfo2", queryParams, callback),
      true);
}

void UrlJobs::getRandomSongs(Callback callback, int numberOfSongs) {
  juce::StringPairArray queryParams;
  if (numberOfSongs > 0 && numberOfSongs <= 500) {
    queryParams.set("size", std::to_string(numberOfSongs));
  }
  UrlRequests::getInstance()->addJob(
      new UrlJob("getRandomSongs", "getRandomSongs", queryParams, callback),
      true);
}

void UrlJobs::stream(Callback callback, std::string id, int maxBitRate,
                     std::string format) {}
