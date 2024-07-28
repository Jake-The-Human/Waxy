#pragma once

#include <JuceHeader.h>
#include "Logic/Song.h"

#include <vector>

class FileListBoxModel : public juce::TableListBoxModel
{
public:
    virtual ~FileListBoxModel() = default;
    FileListBoxModel() = default;
    FileListBoxModel(const std::vector<Song> &songs);

    FileListBoxModel(const FileListBoxModel &) = default;
    FileListBoxModel(FileListBoxModel &&) = default;

    FileListBoxModel &operator=(const FileListBoxModel &) = default;
    FileListBoxModel &operator=(FileListBoxModel &&) = default;

    void addSong(Song song) { songs_.push_back(song); }

    // juce::TableListBoxModel
    int getNumRows() override;
    void paintRowBackground(juce::Graphics &g, int rowNumber, int width, int height, bool rowIsSelected) override;
    void paintCell(juce::Graphics &g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;

private:
    std::vector<Song> songs_;
};
