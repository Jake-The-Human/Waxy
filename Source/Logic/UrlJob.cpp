/*
  ==============================================================================

    UrlJob.cpp
    Created: 13 Jul 2024 10:11:02am
    Author:  jake

  ==============================================================================
*/

#include "UrlJob.h"

UrlJob::UrlJob(const juce::String &jobName, const juce::String &request, const juce::StringPairArray &queryParams, std::function<void(const juce::String &)> callback) : juce::ThreadPoolJob(jobName),
                                                                                                                                                                         requestType(request),
                                                                                                                                                                         queryParamsInternal(queryParams),
                                                                                                                                                                         callbackInternal(callback)
{
  queryParamsInternal.set("u", "admin");
  queryParamsInternal.set("p", "admin");
  queryParamsInternal.set("c", "Waxy"); // A unique string identifying the client application.
  queryParamsInternal.set("f", "json");
}

juce::ThreadPoolJob::JobStatus UrlJob::runJob()
{
  juce::URL urlObj("http://localhost:4747/rest/" + requestType);
  urlObj = urlObj.withParameters(queryParamsInternal);

  // Not sure if we need this so i put here before i start remove prev impl
  // Add POST data if provided
  // if (!postData.isEmpty())
  // {
  //   url = url.withPOSTData(postData);
  // }

  juce::String headers = "Content-Type: application/json";
  int timeOutMs = 30000; // Timeout in milliseconds
  juce::StringPairArray responseHeaders;
  int statusCode = 0;
  int numRedirectsToFollow = 5; // Number of redirects to follow

  juce::URL::InputStreamOptions options(juce::URL::ParameterHandling::inAddress);

  std::unique_ptr<juce::InputStream> stream = urlObj.createInputStream(options);
  juce::String response;

  if (stream != nullptr)
  {
    response = stream->readEntireStreamAsString();
    DBG("Response: " + response);
    DBG("Status code: " + juce::String(statusCode));

    // Print response headers
    for (int i = 0; i < responseHeaders.size(); ++i)
    {
      DBG(responseHeaders.getAllKeys()[i] + ": " +
          responseHeaders.getAllValues()[i]);
    }
  }
  else
  {
    DBG("Failed to create input stream!");
  }

  if (response.isEmpty())
  {
    juce::Logger::writeToLog("Failed to fetch URL: " + requestType);
  }
  else
  {
    callbackInternal(response);
  }

  return juce::ThreadPoolJob::JobStatus::jobHasFinished;
}