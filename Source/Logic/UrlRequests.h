#pragma once

#include <JuceHeader.h>

#include "UrlJob.h"

class UrlRequests
{
public:
  JUCE_DECLARE_SINGLETON(UrlRequests, true) // true means the singleton will be created on demand
  ~UrlRequests() { clearSingletonInstance(); }
  UrlRequests() = default;

  void addJob(UrlJob *job, bool deleteJobWhenFinished);

private:
  static constexpr auto NUM_THREADS = 2;
  juce::ThreadPool threadPool{NUM_THREADS};
};
