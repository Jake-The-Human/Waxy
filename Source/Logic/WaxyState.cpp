#include "WaxyState.h"
#include "Logic/UrlJobs.h"

WaxyState::~WaxyState()
{
    formatManager.clearFormats();
    transportSource.removeAllChangeListeners();
};

WaxyState::WaxyState()
{
    formatManager.registerBasicFormats();
    transportSource.addChangeListener(this);
}

void WaxyState::changeListenerCallback(juce::ChangeBroadcaster *source)
{
    if (source == &transportSource)
    {
        if (transportSource.isPlaying())
        {
            changeState(Playing);
        }
        else
            changeState(Stopped);
    }

    sendChangeMessage();
}

void WaxyState::changeState(TransportState newState)
{
    if (state != newState)
    {
        state = newState;

        switch (state)
        {
        case Stopped:
            transportSource.setPosition(0.0);
            break;

        case Starting:

            UrlJobs::stream([this](std::unique_ptr<juce::BufferedInputStream> stream){
                updateSongQ(std::move(stream));
                transportSource.start();
            }, "tr-32");

            break;

        case Playing:
            break;
        case Pausing:
            transportSource.stop();
            break;

        case Paused:
            break;

        case Stopping:
            transportSource.stop();
            break;
        }
    }
}

void WaxyState::updateSongQ(std::unique_ptr<juce::BufferedInputStream> stream) {
    auto* reader = formatManager.createReaderFor(std::move(stream));
    if (reader != nullptr)
    {
        DBG("Playing a " + reader->getFormatName());
        auto newSource = std::make_unique<juce::AudioFormatReaderSource> (reader, true);
        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
        readerSource.reset (newSource.release());
    }
}
