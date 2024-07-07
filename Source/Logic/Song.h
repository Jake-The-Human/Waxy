#pragma once

#include <JuceHeader.h>

#include <cstdint>
#include <ctime>
#include <string_view>

struct SongData {
    std::string_view id{};
    std::string_view albumId{};
    std::string_view artistId{};
    std::string_view parent{};
    std::int64_t coverArt{-1};
    std::int64_t duration{-1};
    std::int64_t bitRate{-1};
    std::int64_t size{-1};
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

using Song = SongData;
