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

            UrlJobs::stream([this](std::unique_ptr<juce::InputStream> stream){ updateSongQ(std::move(stream)) ;}, "tr-32");


            // transportSource.start();


            break;

        case Playing:
            break;

        case Stopping:
            transportSource.stop();
            break;
        }
    }
}

void WaxyState::updateSongQ(std::unique_ptr<juce::InputStream> stream) {
    DBG(formatManager.getWildcardForAllFormats());
    DBG(stream->getPosition());
    auto t = std::make_unique<juce::BufferedInputStream>(stream.get(), stream->getNumBytesRemaining(), false);
    auto* reader = formatManager.createReaderFor(std::move(t));
    if (reader != nullptr)
    {
    DBG(reader->getFormatName());
    const int numChannels = (int)reader->numChannels;
    const int64_t numSamples = reader->lengthInSamples;
    auto newSource = std::make_unique<juce::AudioFormatReaderSource> (reader, true);
    transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
    transportSource.start();
    readerSource.reset (newSource.release());

    }
}
