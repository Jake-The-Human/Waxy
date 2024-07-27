/*
  ==============================================================================

    UrlJobStream.cpp
    Created: 25 Jul 2024 6:47:27pm
    Author:  jake

  ==============================================================================
*/

#include "UrlJobStream.h"

UrlJobStream::UrlJobStream(const juce::String &jobName, const juce::String &request, const juce::StringPairArray &queryParams, std::function<void(std::unique_ptr<juce::InputStream>)> callback) : juce::ThreadPoolJob(jobName),
                                                                                                                                                                                                 requestType(request),
                                                                                                                                                                                                 queryParamsInternal(queryParams),
                                                                                                                                                                                                 callbackInternal(callback)
{
  queryParamsInternal.set("u", "admin");
  queryParamsInternal.set("p", "admin");
  queryParamsInternal.set("c", "Waxy"); // A unique string identifying the client application.

    if (!formatManager.getNumKnownFormats())
    {
        formatManager.registerBasicFormats();
    }

}

juce::ThreadPoolJob::JobStatus UrlJobStream::runJob()
{
  juce::URL urlObj("http://localhost:4747/rest/" + requestType);
  urlObj = urlObj.withParameters(queryParamsInternal);

  juce::URL::InputStreamOptions options(juce::URL::ParameterHandling::inAddress);

  auto stream = urlObj.createInputStream(options);

  if (stream != nullptr)
  {

    // auto* reader = formatManager.createReaderFor(std::move(stream));
    // if (reader != nullptr)
    // {
    //   DBG(reader->getFormatName());
    //   const int numChannels = (int)reader->numChannels;
    //   const int64_t numSamples = reader->lengthInSamples;
    //   juce::AudioBuffer<float> buffer(numChannels, (int)numSamples);

    //   if (reader->read(&buffer, 0, (int)numSamples, 0, true, true))
    //   {
    //     callbackInternal(buffer);
    //   }
    // }
    callbackInternal(std::move(stream));
  }
  else
  {
    DBG("Failed to create input stream!");
  }

  return juce::ThreadPoolJob::JobStatus::jobHasFinished;
}
