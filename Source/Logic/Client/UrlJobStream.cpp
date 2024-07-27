/*
  ==============================================================================

    UrlJobStream.cpp
    Created: 25 Jul 2024 6:47:27pm
    Author:  jake

  ==============================================================================
*/

#include "UrlJobStream.h"

UrlJobStream::UrlJobStream(const juce::String &jobName, const juce::String &request, const juce::StringPairArray &queryParams, std::function<void(std::unique_ptr<juce::BufferedInputStream>)> callback) : juce::ThreadPoolJob(jobName),
                                                                                                                                                                                                 requestType(request),
                                                                                                                                                                                                 queryParamsInternal(queryParams),
                                                                                                                                                                                                 callbackInternal(callback)
{
  queryParamsInternal.set("u", "admin");
  queryParamsInternal.set("p", "admin");
  queryParamsInternal.set("c", "Waxy"); // A unique string identifying the client application.
}

juce::ThreadPoolJob::JobStatus UrlJobStream::runJob()
{
  juce::URL urlObj("http://localhost:4747/rest/" + requestType);
  urlObj = urlObj.withParameters(queryParamsInternal);

  juce::URL::InputStreamOptions options(juce::URL::ParameterHandling::inAddress);

  auto stream = urlObj.createInputStream(options);
  if (stream != nullptr)
  {
    // TODO: instead of using a callback probably should use a queue and another thread to deal wil play the audio file.
    callbackInternal(std::make_unique<juce::BufferedInputStream>(stream.get(), stream->getNumBytesRemaining(), false));
  }
  else
  {
    DBG("Failed to create input stream!");
  }

  return juce::ThreadPoolJob::JobStatus::jobHasFinished;
}
