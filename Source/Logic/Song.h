#pragma once

#include <JuceHeader.h>

#include <cstdint>
#include <string_view>
#include <vector>

struct Song
{
    struct Helper
    {
        std::string_view id;
        juce::String name;
    };
    std::string_view id;
    juce::String album;
    std::string_view albumId;
    juce::String artist;
    std::string_view artistId;
    std::vector<Helper> artists;
    juce::String displayArtist;
    std::vector<Helper> albumArtists;
    juce::String displayAlbumArtist;
    int64_t bitRate;
    std::string_view contentType;
    std::string_view coverArt;
    std::string_view created;
    int64_t duration;
    bool isDir;
    bool isVideo;
    std::string_view parent;
    std::string_view path;
    int64_t size;
    std::string_view suffix;
    juce::String title;
    int64_t track;
    std::string_view type;
    int64_t year;
    std::string_view musicBrainzId;
};

struct Album
{
    struct AlbumHeader
    {
        std::string_view id;
        juce::String name;
        std::string_view coverArt;
        std::string_view created;
        int64_t duration;
        juce::String artist;
        std::string_view artistId;
    } header;
    std::vector<Song> trackList;
    uint64_t songCount() const { return trackList.size(); }
};

struct Artist
{
    struct ArtistHeader
    {
        std::string_view id;
        juce::String name;
        std::string_view converArt;
        std::string_view created;
        int64_t duration;
        juce::String artist;
        std::string_view artistId;
    } header;
    std::vector<Album::AlbumHeader> albums;
    uint64_t albumCount() const { return albums.size(); }
};

struct Genre
{
    juce::String value;
    int64_t songCount;
    int64_t albumCount;
};

struct SimilarArtist
{
    std::string_view id;
    std::string_view coverArt;
    juce::String name;
    int64_t albumCount;
};

struct ArtistInfo
{
    juce::String biography;
    juce::String musicBrainzId;
    juce::String lastFmUrl;
    juce::String smallImageUrl;
    juce::String mediumImageUrl;
    juce::String largeImageUrl;
    std::vector<SimilarArtist> similarArtist;
};

struct SubsonicIndexes
{
    struct SubsonicIndex
    {
        struct Artist
        {
            std::string_view id;
            juce::String name;
            int64_t albumCount;
        };
        std::string_view name;
        std::vector<Artist> artist;
    };
    int64_t lastModified;
    std::string_view ignoredArtilcles;
    std::vector<SubsonicIndex> index;
};
