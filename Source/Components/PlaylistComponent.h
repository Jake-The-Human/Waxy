#pragma once

#include <JuceHeader.h>

#include "NowPlayingComponent.h"
#include "PlaylistBoxModel.h"

class PlaylistComponent : public juce::Component
{
public:
    virtual ~PlaylistComponent() = default;
    PlaylistComponent(std::shared_ptr<WaxyState> waxyState);

    // juce::Component
    void paint(juce::Graphics &g) final;
    void resized() final;

private:

    NowPlayingComponent nowPlayingView_;
    PlayListBoxModel playlistBoxModel_;
    juce::ListBox playlistListBox_;
    juce::Label playlistViewTitle_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
