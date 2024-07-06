#pragma once

#include <JuceHeader.h>

#include <cstdint>
#include <ctime>
#include <string>
#include <variant>

struct SongData {
    std::string_view id{};
    std::string_view albumId{};
    std::string_view artistId{};
    std::string_view parent{};
    int32_t coverArt{-1};
    int32_t duration{-1};
    int32_t bitRate{-1};
    int32_t size{-1};
    bool isDir{false};
    bool isVideo{false};
    std::string_view title{};
    std::string album{};
    std::string artist{};
    std::string suffix{};
    std::string contentType{};
    std::string path{};
    std::time_t created{}; // use std::time_t for storing date and time
};

using Song = std::variant<int32_t, SongData>;
