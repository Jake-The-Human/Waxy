#include "NowPlayingComponent.h"
#include "Logic/WaxyState.h"
#include "GuiConstants.h"
#include "Logic/UrlRequests.h"

constexpr auto PLAY = "Play";
constexpr auto PAUSE = "Pause";

NowPlayingComponent::NowPlayingComponent(std::shared_ptr<WaxyState> waxyState)
    : waxyState_(waxyState)
{
    waxyState_->addChangeListener(this);
    nowPlayingLabel_.setText("Now Playing", juce::dontSendNotification);
    nowPlayingLabel_.setJustificationType(juce::Justification::topLeft);
    addAndMakeVisible(nowPlayingLabel_);

    currentSongLabel_.setText("Curent Song:", juce::dontSendNotification);
    currentSongLabel_.setJustificationType(juce::Justification::topLeft);
    addAndMakeVisible(currentSongLabel_);

    playButton_.setButtonText(PLAY);
    playButton_.addListener(this);
    addAndMakeVisible(playButton_);

    nextButton_.setButtonText("Next");
    addAndMakeVisible(nextButton_);

    prevButton_.setButtonText("Prev");
    addAndMakeVisible(prevButton_);
}

void NowPlayingComponent::paint(juce::Graphics &g)
{
    auto area = getLocalBounds();
    g.setColour(juce::Colours::green);
    g.fillRoundedRectangle(area.toFloat(), GuiConstant::CORNERN_RADIUS);
    SongData curSong = waxyState_->getCurrentSong();
    currentSongLabel_.setText("Curent Song:" + curSong.title, juce::dontSendNotification);
}

void NowPlayingComponent::resized()
{
    auto area = getLocalBounds();
    area.reduce(8, 8); // padding
    auto fourthHeight= area.getHeight() / 4;
    auto thirdWidth = area.getWidth() / 3;
    nowPlayingLabel_.setBounds(area.removeFromTop(fourthHeight));
    currentSongLabel_.setBounds(area.removeFromTop(fourthHeight));
    nextButton_.setBounds(area.removeFromLeft(thirdWidth));
    playButton_.setBounds(area.removeFromLeft(thirdWidth));
    prevButton_.setBounds(area.removeFromLeft(thirdWidth));
}

void NowPlayingComponent::changeListenerCallback(juce::ChangeBroadcaster *source)
{
    if (source == waxyState_.get()) {
        currentSongLabel_.repaint();
    }
}

void NowPlayingComponent::buttonClicked(juce::Button *button)
{
    UrlRequests::allAlbums();
    auto id = UrlRequests::getIndexes();
    auto t = UrlRequests::getMusicDirectory("c");
  
    if (button == &playButton_)
    {
        if (playButton_.getButtonText().compare(PLAY) && waxyState_->isPlaying())
        {
            playButton_.setButtonText(PAUSE);
            waxyState_->changeState(TransportState::Stopping);
        }
        else if (playButton_.getButtonText().compare(PAUSE))
        {
            playButton_.setButtonText(PLAY);
            waxyState_->changeState(TransportState::Starting);
        }
    }
}
