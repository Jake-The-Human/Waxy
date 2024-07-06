#pragma once

#include <JuceHeader.h>
#include "Song.h"

namespace UrlRequests
{
  void allAlbums();
  Song getSong(int id);
  auto getRandomSongs(int numberOfSongs);
  
}
