#pragma once

#include "juce_gui_basics/juce_gui_basics.h"
#include <JuceHeader.h>

class ProfileComponent : public juce::Component
{
public:
    virtual ~ProfileComponent() = default;
    ProfileComponent();

    // juce::Component
    void paint(juce::Graphics &g) final;
    void resized() final;

private:
    juce::Label searchBox_{"Search"};
     juce::TextButton checkConnection;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ProfileComponent)
};
