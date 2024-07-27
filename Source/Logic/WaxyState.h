#pragma once

#include <JuceHeader.h>

#include "Song.h"

#include <deque>
#include <memory>

enum TransportState
{
    Stopped,
    Starting,
    Playing,
    Stopping
};

// will need to start thinking about threading soon
class WaxyState :
    public juce::ChangeListener,
    public juce::ChangeBroadcaster
{
public:
    virtual ~WaxyState();
    WaxyState();

    // juce::ChangeListener
    void changeListenerCallback(juce::ChangeBroadcaster *source) override;

    void releaseTransportResources() { transportSource.releaseResources(); }
    void changeState(TransportState newState);

    bool isPlaying() const { return transportSource.isPlaying(); }
    Song getCurrentSong() const { return currentSong_; }

    juce::AudioTransportSource &getTransportSource() { return transportSource; }
    std::unique_ptr<juce::AudioFormatReaderSource> &getReaderSource() { return readerSource; }

    void updateSongQ(std::unique_ptr<juce::InputStream> stream);
private:
    Song currentSong_;
    std::deque<Song> songQueue;

    TransportState state{TransportState::Stopped};
    juce::AudioFormatManager formatManager;
    std::unique_ptr<juce::MemoryAudioSource> audioSource;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioTransportSource transportSource;
};
