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
    volumeSlider.setRange(0.0f, 10.0f);
    volumeSlider.setValue(5.0f);
    volumeSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 100, 25);
    addAndMakeVisible(volumeSlider);

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

    g.setColour (juce::Colours::orange);
    g.setFont (25.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void FirstDistortionAudioProcessorEditor::resized()
{
    volumeSlider.setBounds(0,getHeight() - 100,100,100);
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
