#include "UrlRequests.h"

JUCE_IMPLEMENT_SINGLETON(UrlRequests)

void UrlRequests::addJob(URLJob *job, bool deleteJobWhenFinished) { threadPool.addJob(job, deleteJobWhenFinished); }
