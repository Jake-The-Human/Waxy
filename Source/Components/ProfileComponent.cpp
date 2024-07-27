#include "ProfileComponent.h"
#include "GuiConstants.h"
#include "Logic/Client/UrlJobs.h"
#include "Logic/Client/ParseJson.h"

ProfileComponent::ProfileComponent() {
  searchBox_.setEditable(true);
  searchBox_.setTooltip("Let get waxy with it.");
  searchBox_.setColour(juce::Label::backgroundColourId, juce::Colours::black);
  searchBox_.setHelpText("Search");
  // addAndMakeVisible(searchBox_);
  UrlJobs::ping([this](const juce::String& json){urlCallback(json);});
  // checkConnection.onClick = [this](){UrlJobs::stream([this](const juce::String& json){
  //                                                      DBG(json);
  //                                                    }, "tr-1");};
  addAndMakeVisible(checkConnection);
}

void ProfileComponent::paint(juce::Graphics &g) {
  auto area = getLocalBounds();
  area.reduce(4, 4);
  g.setColour(juce::Colours::ivory);
  g.fillRoundedRectangle(area.toFloat(), GuiConstant::CORNER_RADIUS);
  if (isGonicConnected) {
    checkConnection.setButtonText("Connected to GONIC!!!!! Know matter how are "
                                  "you try you can't stop us now....");
  } else {
    checkConnection.setButtonText(
        "NOT connected to GONIC!!!!! O shit you stopped us............. =(");
  }
}

void ProfileComponent::resized() {
  auto area = getLocalBounds();
  area.reduce(32, 16); // padding
  searchBox_.setBounds(area);

  checkConnection.setBounds(area);
}

void ProfileComponent::urlCallback(const juce::String& json) {
  isGonicConnected = ParseJson::ping(json);
  juce::MessageManager::callAsync([this]()
  {
      // Update or access GUI components here
    checkConnection.repaint(checkConnection.getScreenX(), checkConnection.getScreenY(), checkConnection.getWidth(), checkConnection.getHeight());
  });
}
