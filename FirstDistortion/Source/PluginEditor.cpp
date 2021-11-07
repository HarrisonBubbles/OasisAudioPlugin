/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "BinaryData.h"

//==============================================================================
FirstDistortionAudioProcessorEditor::FirstDistortionAudioProcessorEditor (FirstDistortionAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    addAndMakeVisible(inputMeterL);
    addAndMakeVisible(inputMeterR);
    
    startTimerHz(24);
    
    juce::LookAndFeel::setDefaultLookAndFeel(&myLNF);

    volumeSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    //volumeSlider.setRange(-60.0f, 5.0f, 0.01f);
    //volumeSlider.setValue(0.0f);
    volumeSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 100, 25);
    volumeSlider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::orange);
    volumeSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::orange);
    volumeSlider.addListener(this);
    //volumeSlider.setComponentEffect(&ds);

    driveSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    driveSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 100, 25);
    driveSlider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::orange);
    driveSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::orange);
    driveSlider.addListener(this);

    rangeSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    rangeSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 100, 25);
    rangeSlider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::orange);
    rangeSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::orange);
    rangeSlider.addListener(this);

    blendSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    blendSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 100, 25);
    blendSlider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::orange);
    blendSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::orange);
    blendSlider.addListener(this);

    addAndMakeVisible(volumeSlider);
    addAndMakeVisible(driveSlider);
    addAndMakeVisible(rangeSlider);
    addAndMakeVisible(blendSlider);

    gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "Gain", volumeSlider);
    driveAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "Drive", driveSlider);
    blendAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "Blend", blendSlider);
    rangeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "Range", rangeSlider);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (500, 400);
}

FirstDistortionAudioProcessorEditor::~FirstDistortionAudioProcessorEditor()
{
    juce::LookAndFeel::setDefaultLookAndFeel(nullptr);
}

//==============================================================================
void FirstDistortionAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    //g.fillAll (juce::Colours::black);

    //const auto myDrawable = juce::Drawable::createFromImageData(BinaryData::background_svg, BinaryData::background_svgSize);
    //myDrawable->draw(g, 1.0f);

    juce::Colour red = juce::Colour(253, 29, 29);
    juce::Colour burntOrange = juce::Colour(191, 87, 0);
    juce::Colour UTBlue = juce::Colour(51, 63, 72);
    juce::Colour pretentious = juce::Colour(12, 50, 78);
//    juce::ColourGradient gradient = juce::ColourGradient(red, 0.0f, 0.0f, peach, 0.0f, 300.0f, false);

    //g.setGradientFill(gradient);
    g.setColour(burntOrange);
    g.fillAll();
    
    g.setColour(UTBlue);
    g.fillRoundedRectangle(rect, 10.f);

    //g.setColour(juce::Colours::black);
    //g.fillRoundedRectangle(<#float x#>, <#float y#>, <#float width#>, <#float height#>, <#float cornerSize#>)
    //g.fillCheckerBoard(rect, 2, 1, juce::Colours::maroon, juce::Colours::black);
    //dsStruct.drawForRectangle(g, juce::Rectangle<int>::Rectangle<int>(50, 50, 400, 300));

    //g.setColour (juce::Colours::white);
    g.setColour(juce::Colours::white);
    g.setFont (juce::Font(getAGFont()));
    g.setFont(40.0f);
//    g.drawFittedText ("OASIS CUSTOM", getLocalBounds(), juce::Justification::horizontallyCentred, 1);
    
    g.drawText("oasis custom", 50, -25, 400, 300,juce::Justification::centred, false);
    
    g.setFont (juce::Font(getAGFont()));
    g.setFont(15.0f);
    g.drawText("range", 50, rect.getHeight() - 105, 100, 100, juce::Justification::centred, false);
    g.drawText("volume", 150, rect.getHeight() - 105, 100, 100, juce::Justification::centred, false);
    g.drawText("drive", 250, rect.getHeight() - 105, 100, 100, juce::Justification::centred, false);
    g.drawText("blend", 350, rect.getHeight() - 105, 100, 100, juce::Justification::centred, false);
    
//    g.drawText("blend", 350, rect.getHeight() - 150, 100, 100, juce::Justification::centred, false);
    
//    g.setFont(5.0f);
//    g.drawText("MADE IN BOSTON, MA 2021", rect.getWidth() / 2, rect.getHeight() - 5, 100, 100, juce::Justification::centred, false);


}

void FirstDistortionAudioProcessorEditor::resized()
{
    // input meter
    inputMeterL.setBounds(150, 170, 200, 15);
    inputMeterR.setBounds(150, 190, 200, 15);
    
    rangeSlider.setBounds(50, rect.getHeight() - 50, 100, 100);
    volumeSlider.setBounds(150,rect.getHeight() - 50,100,100);
    driveSlider.setBounds(250, rect.getHeight() - 50, 100, 100);
    blendSlider.setBounds(350, rect.getHeight() - 50, 100, 100);
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void FirstDistortionAudioProcessorEditor::sliderValueChanged(juce::Slider *slider) 
{
    if (slider == &volumeSlider) {
        *audioProcessor.apvts.getRawParameterValue("Gain") = volumeSlider.getValue();
    }

    if (slider == &driveSlider) {
        *audioProcessor.apvts.getRawParameterValue("Drive") = driveSlider.getValue();
    }

    if (slider == &blendSlider) {
        *audioProcessor.apvts.getRawParameterValue("Blend") = blendSlider.getValue();
    }

    if (slider == &rangeSlider) {
        *audioProcessor.apvts.getRawParameterValue("Range") = rangeSlider.getValue();
    }
}

void FirstDistortionAudioProcessorEditor::timerCallback()
{
    inputMeterL.setLevel(audioProcessor.getRmsValue(0));
    inputMeterR.setLevel(audioProcessor.getRmsValue(1));
    inputMeterL.repaint();
    inputMeterR.repaint();
}
