/*
  ==============================================================================

    UrlJob.h
    Created: 13 Jul 2024 10:11:02am
    Author:  jake

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include <functional>

// seprate the responce and request. bellow will be the class that makes the responce
class URLJob : public juce::ThreadPoolJob
{
public:
  virtual ~URLJob() = default;
  URLJob(const juce::String &jobName, const juce::String &request, const juce::StringPairArray &queryParams, std::function<void(const juce::String &)> callback);
  juce::ThreadPoolJob::JobStatus runJob() override;

private:
  juce::String requestType;
  juce::StringPairArray queryParamsInternal;
  std::function<void(const juce::String &)> callbackInternal;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(URLJob)
};
