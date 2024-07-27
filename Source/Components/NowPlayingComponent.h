#pragma once

#include <JuceHeader.h>
#include <memory>
#include "Logic/WaxyState.h"

class NowPlayingComponent : public juce::Component,
                       public juce::ChangeListener,
                       public juce::Button::Listener
{
public:
    virtual ~NowPlayingComponent() = default;
    NowPlayingComponent(std::shared_ptr<WaxyState> waxyState);

    // juce::Component
    void paint(juce::Graphics &g) final;
    void resized() final;

    // juce::ChangeListener
    void changeListenerCallback(juce::ChangeBroadcaster *source) override;

    // juce::Button::Listener
    void buttonClicked(juce::Button *button) final;

private:
    std::shared_ptr<WaxyState> waxyState_;
    juce::Label nowPlayingLabel_{"Now Playing"};
    juce::Label currentSongLabel_{""};
    juce::TextButton playButton_;
    juce::TextButton nextButton_;
    juce::TextButton prevButton_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NowPlayingComponent)
};
