#include "FileListComponent.h"

#include "GuiConstants.h"

FileListComponent::FileListComponent()
{
    tableModel_ = std::make_unique<FileListBoxModel>(songs_);
    tableListBox_.setModel(tableModel_.get());
    tableListBox_.getHeader().addColumn("Title", 1, 200);
    tableListBox_.getHeader().addColumn("Artist", 2, 200);

    addAndMakeVisible(tableListBox_);
}

void FileListComponent::paint(juce::Graphics &g)
{
    auto area = getLocalBounds();
    area.reduce(4, 4); // padding
    g.setColour(juce::Colours::ivory);
    g.fillRoundedRectangle(area.toFloat(), GuiConstant::CORNER_RADIUS);
}
void FileListComponent::resized()
{
    auto area = getLocalBounds();
    area.reduce(8, 8); // padding
    tableListBox_.setBounds(area);
}
