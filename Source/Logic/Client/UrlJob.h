#pragma once

#include <JuceHeader.h>

#include <functional>

class UrlJob : public juce::ThreadPoolJob
{
public:
  virtual ~UrlJob() = default;
  UrlJob(const juce::String &jobName, const juce::String &request, const juce::StringPairArray &queryParams, std::function<void(const juce::String &)> callback);
  juce::ThreadPoolJob::JobStatus runJob() override;

private:
  juce::String requestType;
  juce::StringPairArray queryParamsInternal;
  std::function<void(const juce::String &)> callbackInternal;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UrlJob)
};
