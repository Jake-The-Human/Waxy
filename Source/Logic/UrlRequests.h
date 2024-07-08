#pragma once

#include <JuceHeader.h>
#include "Song.h"
#include <functional>
#include <vector>

// for more info check this out B^)
// https://www.subsonic.org/pages/api.jsp
namespace UrlRequests
{
  // system
  bool ping();
  // Browsing
  juce::String getMusicFolders();
  SubsonicIndexes getIndexes(std::string musicFolderId = "", std::string ifModifiedSince = "");
  juce::var getMusicDirectory(std::string_view id);
  std::vector<Genre> getGenres();
  Artists getArtists(std::string musicFolderId = "");
  Artist getArtist(std::string id);
  Album getAlbum(std::string id);
  Song getSong(std::string id);
  ArtistInfo getArtistInfo2(std::string_view id, int64_t count = 0, bool includeNotPresent = false);
  // Album/song lists
  std::vector<Song> getRandomSongs(int numberOfSongs);
  // Media retrieval
  void stream(std::string id, int maxBitRate = 0, std::string format = "");
}

// seprate the responce and request. bellow will be the class that makes the responce
class URLFetcher : public juce::ThreadPoolJob
{
  public:
    virtual ~URLFetcher() = default;
    URLFetcher(const juce::String& request, const juce::StringPairArray& queryParams, std::function<void(const juce::String&)> callback) : 
    juce::ThreadPoolJob("URLFetcher"),
    requestType(request),
    queryParamsInternal(queryParams),
    callbackInternal(callback) 
    {
        queryParamsInternal.set("u", "admin");
        queryParamsInternal.set("p", "admin");
        queryParamsInternal.set("c", "Waxy"); // A unique string identifying the client application.
        queryParamsInternal.set("f", "json");
    }

    juce::ThreadPoolJob::JobStatus runJob() override
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

        juce::URL::InputStreamOptions options(
            juce::URL::ParameterHandling::inAddress);
        
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

  private:
   juce::String requestType;
   juce::StringPairArray queryParamsInternal;
   std::function<void(const juce::String&)> callbackInternal;

   JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (URLFetcher)
};
