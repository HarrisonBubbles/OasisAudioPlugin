/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FirstDistortionAudioProcessorEditor::FirstDistortionAudioProcessorEditor (FirstDistortionAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    juce::LookAndFeel::setDefaultLookAndFeel(&myLNF);

    volumeSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    //volumeSlider.setRange(-60.0f, 5.0f, 0.01f);
    //volumeSlider.setValue(0.0f);
    volumeSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 100, 25);
    volumeSlider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::orange);
    volumeSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::orange);
    volumeSlider.addListener(this);
    //volumeSlider.setComponentEffect(&ds);

    driveSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    driveSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 100, 25);
    driveSlider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::orange);
    driveSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::orange);
    driveSlider.addListener(this);

    rangeSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    rangeSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 100, 25);
    rangeSlider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::orange);
    rangeSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::orange);
    rangeSlider.addListener(this);

    blendSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
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
    setSize (400, 300);
}

FirstDistortionAudioProcessorEditor::~FirstDistortionAudioProcessorEditor()
{
    juce::LookAndFeel::setDefaultLookAndFeel(nullptr);
}

//==============================================================================
void FirstDistortionAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::darkgrey);

    g.setColour (juce::Colours::white);
    g.setFont (juce::Font("Giraffey", "Black", 50.0f));
    g.drawFittedText ("DISTORTION", getLocalBounds(), juce::Justification::centred, 1);

}

void FirstDistortionAudioProcessorEditor::resized()
{
    volumeSlider.setBounds(0,getHeight() - 100,100,100);
    driveSlider.setBounds(getWidth() - 100, getHeight() - 100, 100, 100);
    rangeSlider.setBounds(0, 100, 100, 100);
    blendSlider.setBounds(getWidth() - 100, 100, 100, 100);
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
