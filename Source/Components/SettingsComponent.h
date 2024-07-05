#pragma once

#include <JuceHeader.h>

class SettingsComponent  : public juce::Component
{
public:
    SettingsComponent();
    ~SettingsComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SettingsComponent)
};
