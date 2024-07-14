#include "ParseJson.h"

#include "Song.h"
#include "ThirdParty/simdjson.h"
#include "juce_core/juce_core.h"
#include "juce_core/system/juce_PlatformDefs.h"
#include <string_view>

juce::String stringViewToJuceString(const std::string_view &sv)
{
  return {static_cast<juce::CharPointer_UTF8>(sv.data()), sv.size()};
}

bool ParseJson::ping(const juce::String &json)
{
  simdjson::dom::parser parser;
  simdjson::dom::object object;
  auto error = parser.parse(json.toStdString()).get(object);
  if (error)
  {
    jassertfalse;
  }

  simdjson::dom::object responceObject;
  error = object["subsonic-response"].get(responceObject);
  if (error)
  {
    jassertfalse;
  }

  std::string_view status;
  error = responceObject["status"].get(status);
  if (error)
  {
    jassertfalse;
  }

  return status == "ok";
}

juce::String ParseJson::getMusicFolders(const juce::String &json)
{
  simdjson::dom::parser parser;
  simdjson::dom::object object;

  auto error = parser.parse(json.toStdString());
  if (error)
  {
    jassertfalse;
  }

  simdjson::dom::object responceObject;
  error = object["subsonic-response"].get(responceObject);
  if (error)
  {
    jassertfalse;
  }

  std::string_view id;
  error = responceObject["id"].get(id);
  if (error)
  {
    jassertfalse;
  }
  return juce::String(id.data());
}

SubsonicIndexes ParseJson::getIndexes(const juce::String &json)
{
  simdjson::dom::parser parser;
  simdjson::dom::object object;
  auto error = parser.parse(json.toStdString()).get(object);
  if (error)
  {
    jassertfalse;
  }

  simdjson::dom::object responceObject;
  error = object["subsonic-response"].get(responceObject);
  if (error)
  {
    jassertfalse;
  }

  simdjson::dom::object indexesObject;
  error = responceObject["indexes"].get(indexesObject);
  if (error)
  {
    jassertfalse;
  }

  SubsonicIndexes result;
  result.lastModified = indexesObject["lastModified"].get_int64();
  result.ignoredArticles = indexesObject["ignoredArticles"].get_string();

  simdjson::dom::array indexArray;
  error = indexesObject["index"].get(indexArray);
  if (error)
  {
    jassertfalse;
  }

  for (auto obj : indexArray)
  {
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
          .name = stringViewToJuceString(artist["name"].get_string()),
          .albumCount = artist["albumCount"].get_int64()});
    }
    result.index.push_back(index);
  }

  return result;
}

void ParseJson::getMusicDirectory(const juce::String &json)
{
  simdjson::dom::parser parser;
  simdjson::dom::object object;
  auto error = parser.parse(json.toStdString()).get(object);
  if (error)
  {
    jassertfalse;
  }

  simdjson::dom::object responceObject;
  error = object["subsonic-response"].get(responceObject);
  if (error)
  {
    jassertfalse;
  }
}

std::vector<Genre> ParseJson::getGenres(const juce::String &json)
{
  simdjson::dom::parser parser;
  simdjson::dom::object object;

  auto error = parser.parse(json.toStdString()).get(object);
  if (error)
  {
    jassertfalse;
  }

  simdjson::dom::object responceObject;
  error = object["subsonic-response"].get(responceObject);
  if (error)
  {
    jassertfalse;
  }

  simdjson::dom::object genresObject;
  error = responceObject["genres"].get(genresObject);
  if (error)
  {
    jassertfalse;
  }

  simdjson::dom::array genreArray;
  error = genresObject["genre"].get(genreArray);
  if (error)
  {
    jassertfalse;
  }

  std::vector<Genre> result;
  for (auto obj : genreArray)
  {
    result.push_back(
        Genre{.value = stringViewToJuceString(obj["value"].get_string()),
              .songCount = obj["songCount"].get_int64(),
              .albumCount = obj["albumCount"].get_int64()});
  }

  return result;
}

Artists ParseJson::getArtists(const juce::String &json)
{
  simdjson::dom::parser parser;
  simdjson::dom::object object;
  auto error = parser.parse(json.toStdString()).get(object);
  if (error)
  {
    jassertfalse;
  }

  simdjson::dom::object responceObject;
  error = object["subsonic-response"].get(responceObject);
  if (error)
  {
    jassertfalse;
  }

  simdjson::dom::object artistsObject;
  error = responceObject["artists"].get(artistsObject);
  if (error)
  {
    jassertfalse;
  }

  Artists artists;
  artists.ignoredArticles = artistsObject["ignoredArticles"].get_string();

  simdjson::dom::array indexArray;
  error = artistsObject["index"].get(indexArray);
  if (error)
  {
    jassertfalse;
  }

  artists.index.resize(indexArray.size());
  for (int i = 0; auto obj : indexArray)
  {
    artists.index[i++].name = obj["name"].get_string();
  }

  return artists;
}

Artist ParseJson::getArtist(const juce::String &json)
{
  simdjson::dom::parser parser;
  simdjson::dom::object object;

  auto error = parser.parse(json.toStdString()).get(object);
  if (error)
  {
    jassertfalse;
  }

  simdjson::dom::object responceObject;
  error = object["subsonic-response"].get(responceObject);
  if (error)
  {
    jassertfalse;
  }

  simdjson::dom::object artistObject;
  error = responceObject["artist"].get(artistObject);
  if (error)
  {
    jassertfalse;
  }

  simdjson::dom::array albumArray;
  error = artistObject["album"].get(albumArray);
  if (error)
  {
    jassertfalse;
  }

  Artist::ArtistHelper artistHelper;

  return {};
}

Album ParseJson::getAlbum(const juce::String &json)
{
  simdjson::dom::parser parser;
  simdjson::dom::object object;

  auto error = parser.parse(json.toStdString()).get(object);
  if (error)
  {
    jassertfalse;
  }

  // Album result;
  // result.id = artistObject["id"].get_string();
  // result.created = artistObject["created"].get_string();
  // result.artistId = artistObject["artistId"].get_string();
  // result.artist =
  // stringViewToJuceString(artistObject["artist"].get_string());
  return {};
}

Song ParseJson::getSong(const juce::String &json)
{
  // Create the URL object
  simdjson::dom::parser parser;
  simdjson::dom::object object;
  auto error = parser.parse(json.toStdString()).get(object);
  if (error)
  {
    jassertfalse;
  }

  simdjson::dom::object responceObject;
  error = object["subsonic-response"].get(responceObject);
  if (error)
  {
    jassertfalse;
  }

  simdjson::dom::object songObject;
  error = responceObject["song"].get(songObject);
  if (error)
  {
    jassertfalse;
  }

  simdjson::dom::array artistsArray;
  error = songObject["artists"].get(artistsArray);
  if (error)
  {
    jassertfalse;
  }

  std::vector<IdName> artists;
  for (auto a : artistsArray)
  {
    artists.push_back(
        IdName{.id = a["id"].get_string(),
               .name = stringViewToJuceString(a["name"].get_string())});
  }

  simdjson::dom::array albumArtistsArray;
  error = songObject["albumArtists"].get(albumArtistsArray);
  if (error)
  {
    jassertfalse;
  }

  std::vector<IdName> albumArtists;
  for (auto a : albumArtistsArray)
  {
    albumArtists.push_back(
        IdName{.id = a["id"].get_string(),
               .name = stringViewToJuceString(a["name"].get_string())});
  }

  return Song{
      .id = songObject["id"].get_string(),
      .album = stringViewToJuceString(songObject["album"].get_string()),
      .albumId = songObject["albumId"].get_string(),
      .artist = stringViewToJuceString(songObject["artist"].get_string()),
      .artistId = songObject["artistId"].get_string(),
      .artists = artists,
      .displayArtist =
          stringViewToJuceString(songObject["displayArtist"].get_string()),
      .albumArtists = albumArtists,
      .displayAlbumArtist =
          stringViewToJuceString(songObject["displayAlbumArtist"].get_string()),
      .bitRate = songObject["bitRate"].get_int64(),
      .contentType = songObject["contentType"].get_string(),
      .duration = songObject["duration"].get_int64(),
      .isDir = songObject["isDir"].get_bool(),
      .isVideo = songObject["isVideo"].get_bool(),
      .parent = songObject["parent"].get_string(),
      .path = songObject["path"].get_string(),
      .size = songObject["size"].get_int64(),
      .suffix = songObject["suffix"].get_string(),
      .title = stringViewToJuceString(songObject["title"].get_string()),
      .track = songObject["track"].get_int64(),
      .type = songObject["type"].get_string(),
      .year = songObject["year"].get_int64(),
      .musicBrainzId = songObject["musicBrainzId"].get_string()};
}

ArtistInfo ParseJson::getArtistInfo2(const juce::String &json)
{
  simdjson::dom::parser parser;
  simdjson::dom::object object;

  auto error = parser.parse(json.toStdString()).get(object);
  if (error)
  {
    jassertfalse;
  }

  return {};
}

void ParseJson::getAlbumInfo2(const juce::String &json)
{
}

void ParseJson::getSimilarSongs2(const juce::String &json)
{
}

void ParseJson::getTopSongs(const juce::String &json)
{
}

void ParseJson::getAlbumList2(const juce::String &json)
{
}

// Searching
void ParseJson::search(const juce::String &json)
{
}

void ParseJson::search2(const juce::String &json)
{
}

void ParseJson::search3(const juce::String &json)
{
}

std::vector<Song> ParseJson::getRandomSongs(const juce::String &json)
{
  simdjson::dom::parser parser;
  simdjson::dom::object object;

  auto error = parser.parse(json.toStdString()).get(object);
  if (error)
  {
    jassertfalse;
  }

  simdjson::dom::object responceObject;
  error = object["subsonic-response"].get(responceObject);
  if (error)
  {
    jassertfalse;
  }

  simdjson::dom::object randomSongObject;
  error = responceObject["randomSongs"].get(randomSongObject);
  if (error)
  {
    jassertfalse;
  }

  simdjson::dom::array songList;
  error = randomSongObject["song"].get(songList);
  if (error)
  {
    jassertfalse;
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
          .title = stringViewToJuceString(songObject["title"].get_string())};
    }
  }
  return resultList;
}

// void ParseJson::stream(std::string id, int maxBitRate, std::string format)
// {
//   juce::StringPairArray queryParams;
//   queryParams.set("id", id);
//   if (maxBitRate > 0)
//   {
//     queryParams.set("maxBitRate", std::to_string(maxBitRate));
//   }
//   if (!format.empty())
//   {
//     queryParams.set("format", format);
//   }

//   makeRequest("stream", queryParams);
// }
