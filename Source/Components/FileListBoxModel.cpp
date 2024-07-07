#include "FileListBoxModel.h"

FileListBoxModel::FileListBoxModel(const std::vector<Song> &songs) : songs_(songs)
{
}

int FileListBoxModel::getNumRows()
{
    return songs_.size();
}

void FileListBoxModel::paintRowBackground(juce::Graphics &g, int rowNumber, int width, int height, bool rowIsSelected)
{
    if (rowIsSelected)
        g.fillAll(juce::Colours::lightblue);
    else if (rowNumber % 2)
        g.fillAll(juce::Colours::lightgrey);
    else
        g.fillAll(juce::Colours::white);
}

void FileListBoxModel::paintCell(juce::Graphics &g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    g.setColour(juce::Colours::black);
    g.setFont(height * 0.7f);

    juce::String text;
    if (rowNumber < songs_.size())
    {
        const Song &song = songs_[rowNumber];
        if (columnId == 1) // Title column
            text = song.title;
        else if (columnId == 2) // Artist column
            text = song.artist;
    }
    else
    {
        text = "";
    }

    g.drawText(text, 2, 0, width - 4, height, juce::Justification::centredLeft, true);
    g.setColour(juce::Colours::black);
    g.drawRect(0, 0, width, height); // cell border
}
