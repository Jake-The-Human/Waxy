#pragma once
#include <JuceHeader.h>

#include "Logic/Song.h"
#include <deque>
#include <vector>

class PlayListBoxModel : public juce::ListBoxModel
{
public:
    virtual ~PlayListBoxModel() = default;
    PlayListBoxModel() = default;
    PlayListBoxModel(const std::deque<Song> &songs);
    PlayListBoxModel(const std::vector<Song> &songs);

    PlayListBoxModel(const PlayListBoxModel &) = default;
    PlayListBoxModel(PlayListBoxModel &&) = default;

    PlayListBoxModel &operator=(const PlayListBoxModel &) = default;
    PlayListBoxModel &operator=(PlayListBoxModel &&) = default;

    // juce::ListBoxModel
    int getNumRows() override;
    void paintListBoxItem(int rowNumber, juce::Graphics &g, int width, int height, bool rowIsSelected) override;

private:
    std::deque<Song> songs_;
};
