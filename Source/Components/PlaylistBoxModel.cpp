#include "PlaylistBoxModel.h"

PlayListBoxModel::PlayListBoxModel(const std::deque<Song> &songs) : songs_(songs)
{
}

PlayListBoxModel::PlayListBoxModel(const std::vector<Song> &songs) : songs_(songs.begin(), songs.end())
{
}

int PlayListBoxModel::getNumRows()
{
    auto s = songs_.size();
    return s;
}

void PlayListBoxModel::paintListBoxItem(int rowNumber, juce::Graphics &g, int width, int height, bool rowIsSelected)
{
    if (rowIsSelected)
        g.fillAll(juce::Colours::lightblue);

    g.setColour(juce::Colours::black);
    g.setFont(height * 0.7f);
    auto songTitle = rowNumber < songs_.size() ? songs_.at(rowNumber).title : "";
    g.drawText("Item " + songTitle, 5, 0, width, height, juce::Justification::centredLeft, true);
}
