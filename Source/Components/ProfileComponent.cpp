#include "ProfileComponent.h"
#include "GuiConstants.h"
#include "Logic/UrlRequests.h"
#include <Logic/Song.h>

ProfileComponent::ProfileComponent() {
  searchBox_.setEditable(true);
  searchBox_.setTooltip("Let get waxy with it.");
  searchBox_.setColour(juce::Label::backgroundColourId, juce::Colours::black);
  searchBox_.setHelpText("Search");
  // addAndMakeVisible(searchBox_);

  addAndMakeVisible(checkConnection);
}

void ProfileComponent::paint(juce::Graphics &g) {
  auto area = getLocalBounds();
  area.reduce(4, 4);
  g.setColour(juce::Colours::ivory);
  g.fillRoundedRectangle(area.toFloat(), GuiConstant::CORNERN_RADIUS);
}

void ProfileComponent::resized() {
  auto area = getLocalBounds();
  area.reduce(32, 16); // padding
  searchBox_.setBounds(area);

  checkConnection.setBounds(area);
  if (UrlRequests::ping()) {
    checkConnection.setButtonText("Connected to GONIC!!!!! Know matter how are "
                                  "you try you can't stop us now....");
  } else {
    checkConnection.setButtonText(
        "NOT connected to GONIC!!!!! O shit you stopped us............. =(");
  }
}
