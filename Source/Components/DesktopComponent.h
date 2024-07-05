#pragma once

#include <JuceHeader.h>

#include "ProfileComponent.h"
#include "FileListComponent.h"
#include "PlaylistComponent.h"

class DesktopComponent : public juce::Component
{
public:
    virtual ~DesktopComponent() = default;
    DesktopComponent(std::shared_ptr<WaxyState> waxyState);

    // juce::Component
    void paint(juce::Graphics &g) final;
    void resized() final;

private:
    ProfileComponent profileView_;
    FileListComponent fileListView_;
    PlaylistComponent playlistView_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DesktopComponent)
};
