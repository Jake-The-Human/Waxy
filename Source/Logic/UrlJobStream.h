/*
  ==============================================================================

    UrlJobStream.h
    Created: 25 Jul 2024 6:47:27pm
    Author:  jake

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

#include <functional>

class UrlJobStream : public juce::ThreadPoolJob
{
public:
  virtual ~UrlJobStream() = default;
  UrlJobStream(const juce::String &jobName, const juce::String &request, const juce::StringPairArray &queryParams, std::function<void(std::unique_ptr<juce::InputStream>)> callback);
  juce::ThreadPoolJob::JobStatus runJob() override;

private:
  juce::String requestType;
  juce::StringPairArray queryParamsInternal;
  std::function<void(std::unique_ptr<juce::InputStream>)> callbackInternal;
  juce::AudioFormatManager formatManager;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UrlJobStream)
};
