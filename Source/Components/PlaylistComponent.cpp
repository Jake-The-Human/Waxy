#include "PlaylistComponent.h"

#include "Components/PlaylistBoxModel.h"
#include "GuiConstants.h"
#include "Logic/UrlRequests.h"

PlaylistComponent::PlaylistComponent(std::shared_ptr<WaxyState> waxyState) : nowPlayingView_(waxyState), playlistBoxModel_(UrlRequests::getRandomSongs(10)) {
    playlistViewTitle_.setText("Whats up next", juce::dontSendNotification);
    addAndMakeVisible(playlistViewTitle_);
    playlistListBox_.setModel(&playlistBoxModel_);
    addAndMakeVisible(playlistListBox_);
    addAndMakeVisible(nowPlayingView_);
}

void PlaylistComponent::paint(juce::Graphics& g) {
    auto area = getLocalBounds();
    area.reduce(4, 4);
    g.setColour(juce::Colours::tan);
    g.fillRoundedRectangle(area.toFloat(), GuiConstant::CORNERN_RADIUS);
    g.resetToDefaultState();
}
void PlaylistComponent::resized() {
    auto area = getLocalBounds();
    area.reduce(8, 8);  // padding
    playlistViewTitle_.setBounds(area.removeFromTop(area.getHeight() / 6));
    nowPlayingView_.setBounds(area.removeFromBottom(area.getHeight() / 3));
    playlistListBox_.setBounds(area);
}
