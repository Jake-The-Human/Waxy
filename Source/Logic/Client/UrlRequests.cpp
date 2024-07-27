#include "UrlRequests.h"

JUCE_IMPLEMENT_SINGLETON(UrlRequests)

void UrlRequests::addJob(juce::ThreadPoolJob *job, bool deleteJobWhenFinished) { threadPool.addJob(job, deleteJobWhenFinished); }
