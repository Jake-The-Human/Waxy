#include "PlaylistBoxModel.h"

PlayListBoxModel::PlayListBoxModel(const std::deque<Song> &songs) : songs_(songs)
{
}

int PlayListBoxModel::getNumRows()
{
    return songs_.size();
}

void PlayListBoxModel::paintListBoxItem(int rowNumber, juce::Graphics &g, int width, int height, bool rowIsSelected)
{
    if (rowIsSelected)
        g.fillAll(juce::Colours::lightblue);

    g.setColour(juce::Colours::black);
    g.setFont(height * 0.7f);
    auto songTitle = rowNumber < songs_.size() ? std::get<SongData>(songs_.at(rowNumber)).title : "";
    g.drawText("Item " + std::string(songTitle), 5, 0, width, height, juce::Justification::centredLeft, true);
}
