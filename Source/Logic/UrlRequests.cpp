#include "UrlRequests.h"
#include "Logic/Song.h"
#include "ThirdParty/simdjson.h"

juce::String
makeRequest(const juce::String &requestType,
            juce::StringPairArray queryParams = juce::StringPairArray(),
            const juce::String &postData = "") {
  juce::StringPairArray queryParamsInternal(queryParams);
  queryParamsInternal.set("u", "admin");
  queryParamsInternal.set("p", "admin");
  queryParamsInternal.set(
      "c", "test"); // A unique string identifying the client application.
  queryParamsInternal.set("f", "json");

  juce::URL url("http://localhost:4747/rest/" + requestType);

  // Add query parameters to the URL
  for (int i = 0; i < queryParamsInternal.size(); ++i) {
    url = url.withParameter(queryParamsInternal.getAllKeys()[i],
                            queryParamsInternal.getAllValues()[i]);
  }

  // Add POST data if provided
  if (!postData.isEmpty()) {
    url = url.withPOSTData(postData);
  }

  juce::String headers = "Content-Type: application/json";
  int timeOutMs = 30000; // Timeout in milliseconds
  juce::StringPairArray responseHeaders;
  int statusCode = 0;
  int numRedirectsToFollow = 5; // Number of redirects to follow

  juce::URL::InputStreamOptions options(
      juce::URL::ParameterHandling::inAddress);

  std::unique_ptr<juce::InputStream> stream = url.createInputStream(options);
  juce::String response;

  if (stream != nullptr) {
    response = stream->readEntireStreamAsString();
    DBG("Response: " + response);
    DBG("Status code: " + juce::String(statusCode));

    // Print response headers
    for (int i = 0; i < responseHeaders.size(); ++i) {
      DBG(responseHeaders.getAllKeys()[i] + ": " +
          responseHeaders.getAllValues()[i]);
    }
  } else {
    DBG("Failed to create input stream!");
  }

  return response;
}

bool UrlRequests::ping() {
  simdjson::dom::parser parser;
  simdjson::dom::object object;
  auto error = parser.parse(makeRequest("ping").toStdString()).get(object);
  if (error) {
    return false;
  }
  simdjson::dom::object responceObject;
  error = object["subsonic-response"].get(responceObject);
  if (error) {
    return {};
  }

  std::string_view status;
  error = responceObject["status"].get(status);
  if (error) {
    return false;
  }

  return status == "ok";
}

juce::String UrlRequests::getIndexes(std::string musicFolderId,
                                     std::string ifModifiedSince) {
  juce::StringPairArray queryParams;
  if (!musicFolderId.empty()) {
    queryParams.set("musicFolderId", musicFolderId);
  }
  if (!ifModifiedSince.empty()) {
    queryParams.set("ifModifiedSince", ifModifiedSince);
  }
  simdjson::dom::parser parser;
  simdjson::dom::object object;
  auto error =
      parser.parse(makeRequest("getIndexes", queryParams).toStdString())
          .get(object);
  if (error) {
    return "";
  }
  simdjson::dom::object responceObject;
  error = object["subsonic-response"].get(responceObject);
  if (error) {
    return {};
  }
  return "";
}

juce::var UrlRequests::getMusicDirectory(juce::String id) {
  juce::StringPairArray queryParams;
  queryParams.set("id", id);
  return juce::JSON::fromString(makeRequest("getMusicDirectory", queryParams));
}

juce::String UrlRequests::getMusicFolders() {
  simdjson::dom::parser parser;
  simdjson::dom::object object;

  auto error = parser.parse(makeRequest("getMusicFolders").toStdString());
  if (error) {
    return "";
  }
  simdjson::dom::object responceObject;
  error = object["subsonic-response"].get(responceObject);
  if (error) {
    return {};
  }
  std::string_view id;
  error = responceObject["id"].get(id);
  if (error) {
    return "";
  }
  return juce::String(id.data());
}

juce::var UrlRequests::allAlbums() {
  juce::StringPairArray queryParams;
  queryParams.set("type", "newest");

  // Create the URL object
  return juce::JSON::fromString(makeRequest("getAlbumList2", queryParams));
}

Song UrlRequests::getSong(int id) {
  juce::StringPairArray queryParams;
  queryParams.set("id", std::to_string(34));

  // Create the URL object
  makeRequest("song", queryParams);

  return {};
}

std::vector<Song> UrlRequests::getRandomSongs(int numberOfSongs) {
  juce::StringPairArray queryParams;
  if (numberOfSongs > 0 && numberOfSongs <= 500) {
    queryParams.set("size", std::to_string(numberOfSongs));
  }

  simdjson::dom::parser parser;
  simdjson::dom::object object;

  auto error =
      parser.parse(makeRequest("getRandomSongs", queryParams).toStdString())
          .get(object);
  if (error) {
    return {};
  }
  simdjson::dom::object responceObject;
  error = object["subsonic-response"].get(responceObject);
  if (error) {
    return {};
  }

  simdjson::dom::object randomSongObject;
  error = responceObject["randomSongs"].get(randomSongObject);
  if (error) {
    return {};
  }
  simdjson::dom::array songList;
  error = randomSongObject["song"].get(songList);
  if (error) {
    return {};
  }
  std::vector<Song> resultList(songList.size());
  for (int i = 0; auto song : songList) {
    simdjson::dom::object songObject;
    auto songError = song.get(songObject);
    if (!error) {
      // std::cout << song << "\n" << songObject << "\n" << std::endl;
      resultList[i++] = Song(
          SongData{.id = songObject["id"].get_string(),
                   .albumId = songObject["albumId"].get_string(),
                   .artistId = songObject["artistId"].get_string(),
                   .title = juce::String(songObject["title"].get_c_str())});
    }
  }
  return resultList;
}
