#pragma once

#include <JuceHeader.h>

class UrlRequests
{
public:
  JUCE_DECLARE_SINGLETON(UrlRequests, true) // true means the singleton will be created on demand
  ~UrlRequests() { clearSingletonInstance(); }
  UrlRequests() = default;

  void addJob(juce::ThreadPoolJob *job, bool deleteJobWhenFinished);

private:
  static constexpr auto NUM_THREADS = 4;
  juce::ThreadPool threadPool{NUM_THREADS};
};
