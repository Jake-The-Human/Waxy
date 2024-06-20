/*
  ==============================================================================

    WaxyState.h
    Created: 16 Jun 2024 6:49:48pm
    Author:  jakep

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

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
class WaxyState : public juce::ChangeListener
{
    public:
    virtual ~WaxyState();
    WaxyState();


    void changeListenerCallback(juce::ChangeBroadcaster *source) override;

    void releaseTransportResources() { transportSource.releaseResources(); }
    void changeState(TransportState newState);

    void requestSongBytes(const juce::String &apiEndpoint, const juce::String &apiKey, const juce::String &songId)
    {
        // // Create the URL object
        // juce::URL url(apiEndpoint);

        // // Create the JSON payload
        // juce::DynamicObject::Ptr jsonPayload = new juce::DynamicObject();
        // jsonPayload->setProperty("song_id", songId);

        // juce::String jsonString = jsonPayload->;

        // // Create a memory block for the JSON data
        // juce::MemoryBlock postData;
        // postData.append(jsonString.toRawUTF8(), jsonString.getNumBytesAsUTF8());

        // // Set up the headers
        // juce::StringPairArray headers;
        // headers.set("Authorization", "Bearer " + apiKey);
        // headers.set("Content-Type", "application/json");

        // // Create the POST request
        // auto response = url.withPOSTData(postData);

        // // Successfully retrieved song bytes
        // juce::MemoryBlock songBytes;
        // response.readEntireBinaryStream(songBytes);
    }

    bool isPlaying() const { return transportSource.isPlaying(); }

    juce::AudioTransportSource& getTransportSource() { return transportSource; }
    std::unique_ptr<juce::AudioFormatReaderSource>& getReaderSource() { return readerSource; }
private:

    std::deque<juce::Uuid> songQueue;

    TransportState state{TransportState::Stopped};
    juce::AudioFormatManager formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioTransportSource transportSource;
};