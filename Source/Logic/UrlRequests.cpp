#include "UrlRequests.h"
#include "Logic/Song.h"
#include "ThirdParty/simdjson.h"

juce::String
makeRequest(const juce::String &requestType,
            juce::StringPairArray queryParams = juce::StringPairArray(),
            const juce::String &postData = "")
{
  juce::StringPairArray queryParamsInternal(queryParams);
  queryParamsInternal.set("u", "admin");
  queryParamsInternal.set("p", "admin");
  queryParamsInternal.set(
      "c", "Waxy"); // A unique string identifying the client application.
  queryParamsInternal.set("f", "json");

  juce::URL url("http://localhost:4747/rest/" + requestType);

  // Add query parameters to the URL
  for (int i = 0; i < queryParamsInternal.size(); ++i)
  {
    url = url.withParameter(queryParamsInternal.getAllKeys()[i],
                            queryParamsInternal.getAllValues()[i]);
  }

  // Add POST data if provided
  if (!postData.isEmpty())
  {
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

  if (stream != nullptr)
  {
    response = stream->readEntireStreamAsString();
    DBG("Response: " + response);
    DBG("Status code: " + juce::String(statusCode));

    // Print response headers
    for (int i = 0; i < responseHeaders.size(); ++i)
    {
      DBG(responseHeaders.getAllKeys()[i] + ": " +
          responseHeaders.getAllValues()[i]);
    }
  }
  else
  {
    DBG("Failed to create input stream!");
  }

  return response;
}

bool UrlRequests::ping()
{
  simdjson::dom::parser parser;
  simdjson::dom::object object;
  auto error = parser.parse(makeRequest("ping").toStdString()).get(object);
  if (error)
  {
    return false;
  }

  simdjson::dom::object responceObject;
  error = object["subsonic-response"].get(responceObject);
  if (error)
  {
    return {};
  }

  std::string_view status;
  error = responceObject["status"].get(status);
  if (error)
  {
    return false;
  }

  return status == "ok";
}

juce::String UrlRequests::getMusicFolders()
{
  simdjson::dom::parser parser;
  simdjson::dom::object object;

  auto error = parser.parse(makeRequest("getMusicFolders").toStdString());
  if (error)
  {
    return "";
  }

  simdjson::dom::object responceObject;
  error = object["subsonic-response"].get(responceObject);
  if (error)
  {
    return {};
  }

  std::string_view id;
  error = responceObject["id"].get(id);
  if (error)
  {
    return "";
  }
  return juce::String(id.data());
}

SubsonicIndexes UrlRequests::getIndexes(std::string musicFolderId,
                                     std::string ifModifiedSince)
{
  juce::StringPairArray queryParams;
  if (!musicFolderId.empty())
  {
    queryParams.set("musicFolderId", musicFolderId);
  }

  if (!ifModifiedSince.empty())
  {
    queryParams.set("ifModifiedSince", ifModifiedSince);
  }

  simdjson::dom::parser parser;
  simdjson::dom::object object;
  auto error =
      parser.parse(makeRequest("getIndexes", queryParams).toStdString())
          .get(object);
  if (error)
  {
    return {};
  }

  simdjson::dom::object responceObject;
  error = object["subsonic-response"].get(responceObject);
  if (error)
  {
    return {};
  }

  simdjson::dom::object indexesObject;
  error = responceObject["indexes"].get(indexesObject);
  if (error) {
    return {};
  }

  SubsonicIndexes result;
  result.lastModified = indexesObject["lastModified"].get_int64();
  result.ignoredArtilcles = indexesObject["ignoredArticles"].get_string();

  simdjson::dom::array indexArray;
  error = indexesObject["index"].get(indexArray);
  if (error)
  {
    return {};
  }

  for (auto obj : indexArray) {
    SubsonicIndexes::SubsonicIndex index;
    index.name = obj["name"].get_string();
    simdjson::dom::array artistsArray;
    error = obj["artist"].get(artistsArray);
    if (error)
    {
      continue;
    }
    for (auto artist : artistsArray)
    {
      index.artist.emplace_back(SubsonicIndexes::SubsonicIndex::Artist{
                                  .id = artist["id"].get_string(),
                                  .name = juce::String(artist["name"].get_c_str()),
                                  .albumCount = artist["albumCount"].get_int64()
                                });
    }
    result.index.push_back(index);
  }

  return result;
}

juce::var UrlRequests::getMusicDirectory(std::string_view id)
{
  juce::StringPairArray queryParams;
  queryParams.set("id", std::string(id));
  
  simdjson::dom::parser parser;
  simdjson::dom::object object;
  auto error =
      parser.parse(makeRequest("getMusicDirectory", queryParams).toStdString())
          .get(object);
  if (error)
  {
    return {};
  }
  
  simdjson::dom::object responceObject;
  error = object["subsonic-response"].get(responceObject);
  if (error)
  {
    return {};
  }
  // not sure what to do with the results.
  return {};
}

Song UrlRequests::getSong(std::string id)
{
  juce::StringPairArray queryParams;
  queryParams.set("id", id);

  // Create the URL object
  simdjson::dom::parser parser;
  simdjson::dom::object object;
  auto error =
      parser.parse(makeRequest("getSong", queryParams).toStdString())
          .get(object);
  if (error)
  {
    return {};
  }
  
  simdjson::dom::object responceObject;
  error = object["subsonic-response"].get(responceObject);
  if (error)
  {
    return {};
  }

  return {};
}

std::vector<Genre> UrlRequests::getGenres()
{
  simdjson::dom::parser parser;
  simdjson::dom::object object;

  auto error =
      parser.parse(makeRequest("getGenres").toStdString())
          .get(object);
  if (error)
  {
    return {};
  }
  return {};
}

std::vector<Artist> UrlRequests::getArtists(std::string musicFolderId)
{
  juce::StringPairArray queryParams;
  if (!musicFolderId.empty())
  {
    queryParams.set("musicFolderId", musicFolderId);
  }
  
  simdjson::dom::parser parser;
  simdjson::dom::object object;

  auto error =
      parser.parse(makeRequest("getArtists", queryParams).toStdString())
          .get(object);
  if (error)
  {
    return {};
  }
  return {};
}

Artist UrlRequests::getArtist(std::string id)
{
  juce::StringPairArray queryParams;
  queryParams.set("id", id);
  simdjson::dom::parser parser;
  simdjson::dom::object object;

  auto error =
      parser.parse(makeRequest("getArtist", queryParams).toStdString())
          .get(object);
  if (error)
  {
    return {};
  }
  return {};
}

Album UrlRequests::getAlbum(std::string id)
{
  juce::StringPairArray queryParams;
  queryParams.set("id", id);
  simdjson::dom::parser parser;
  simdjson::dom::object object;

  auto error =
      parser.parse(makeRequest("getAlbum", queryParams).toStdString())
          .get(object);
  if (error)
  {
    return {};
  }
  return {};
}

  ArtistInfo UrlRequests::getArtistInfo2(std::string_view id, int64_t count, bool includeNotPresent)
  {
    juce::StringPairArray queryParams;
    queryParams.set("id", std::string(id));
    if (count > 0)
    {
      queryParams.set("count", std::to_string(count));
    }

    if (includeNotPresent)
    {
      queryParams.set("includeNotPresent", "true");
    }
    
    simdjson::dom::parser parser;
    simdjson::dom::object object;

    auto error =
        parser.parse(makeRequest("getArtistInfo2", queryParams).toStdString())
            .get(object);
    if (error)
    {
      return {};
    }
    return {};
  }

std::vector<Song> UrlRequests::getRandomSongs(int numberOfSongs)
{
  juce::StringPairArray queryParams;
  if (numberOfSongs > 0 && numberOfSongs <= 500)
  {
    queryParams.set("size", std::to_string(numberOfSongs));
  }

  simdjson::dom::parser parser;
  simdjson::dom::object object;

  auto error =
      parser.parse(makeRequest("getRandomSongs", queryParams).toStdString())
          .get(object);
  if (error)
  {
    return {};
  }

  simdjson::dom::object responceObject;
  error = object["subsonic-response"].get(responceObject);
  if (error)
  {
    return {};
  }

  simdjson::dom::object randomSongObject;
  error = responceObject["randomSongs"].get(randomSongObject);
  if (error)
  {
    return {};
  }

  simdjson::dom::array songList;
  error = randomSongObject["song"].get(songList);
  if (error)
  {
    return {};
  }

  std::vector<Song> resultList(songList.size());
  for (int i = 0; auto song : songList)
  {
    simdjson::dom::object songObject;
    auto songError = song.get(songObject);
    if (!error)
    {
      resultList[i++] = Song{
          .id = songObject["id"].get_string(),
          .albumId = songObject["albumId"].get_string(),
          .artistId = songObject["artistId"].get_string(),
          .title = juce::String(songObject["title"].get_c_str())};
    }
  }
  return resultList;
}

void UrlRequests::stream(std::string id, int maxBitRate, std::string format)
{
  juce::StringPairArray queryParams;
  queryParams.set("id", id);
  if (maxBitRate > 0)
  {
    queryParams.set("maxBitRate", std::to_string(maxBitRate));
  }
  if (!format.empty())
  {
    queryParams.set("format", format);
  }

  makeRequest("stream", queryParams);
}
