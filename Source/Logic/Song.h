#pragma once

#include <JuceHeader.h>

#include <cstdint>
#include <ctime>
#include <string_view>
#include <vector>

struct Song {
    std::string_view id{};
    std::string_view albumId{};
    std::string_view artistId{};
    std::string_view parent{};
    int64_t coverArt{-1};
    int64_t duration{-1};
    int64_t bitRate{-1};
    int64_t size{-1};
    bool isDir{false};
    bool isVideo{false};
    juce::String title{};
    juce::String album{};
    juce::String artist{};
    juce::String suffix{};
    juce::String contentType{};
    juce::String path{};
    std::time_t created{}; // use std::time_t for storing date and time
};

struct Album {
    std::vector<Song> trackList;
    juce::String getTilte() { return trackList.empty() ? "" : trackList.front().album; }
    juce::String getArtist() { return trackList.empty() ? "" : trackList.front().artist; }
    uint64_t size() { return trackList.size(); }
};

struct Artist {
    std::vector<Album> albums;
    juce::String getName() { return albums.empty() ? "" : albums.front().getArtist(); }
    uint64_t size() { return albums.size(); }
};

struct Genre {
    int64_t songCount{0};
    int64_t albumCount{0};
    juce::String genre;
};

struct SimilarArtist {
    std::string_view id;
    std::string_view coverArt;
    juce::String name;
    int64_t albumCount;
};

struct ArtistInfo {
    juce::String biography;
    juce::String musicBrainzId;
    juce::String lastFmUrl;
    juce::String smallImageUrl;
    juce::String mediumImageUrl;
    juce::String largeImageUrl;
    std::vector<SimilarArtist> similarArtist;
};
