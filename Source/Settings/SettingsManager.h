#pragma once

#include <JuceHeader.h>
#include <memory>

class SettingsManager
{
public:
    SettingsManager() : propertiesFile(std::make_unique<juce::PropertiesFile>(juce::PropertiesFile::Options()))
    {
    }

    void saveSettings(const juce::String& key, const juce::var& value)
    {
        propertiesFile->setValue(key, value);
        propertiesFile->save();
    }

    juce::var loadSettings(const juce::String& key)
    {
        return propertiesFile->getValue(key);
    }

private:
    std::unique_ptr<juce::PropertiesFile> propertiesFile;
};
