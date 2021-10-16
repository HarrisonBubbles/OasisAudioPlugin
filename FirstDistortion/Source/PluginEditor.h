/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "StyleSheet.h"

//==============================================================================
/**
*/
class FirstDistortionAudioProcessorEditor  : public juce::AudioProcessorEditor,
    public juce::Slider::Listener
{
public:
    FirstDistortionAudioProcessorEditor (FirstDistortionAudioProcessor&);
    ~FirstDistortionAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(juce::Slider* slider) override;

private:
    juce::Slider volumeSlider;
    juce::Slider driveSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;

    juce::CustomLNF myLNF;
    juce::DropShadowEffect ds;
    juce::Font giraffey;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    FirstDistortionAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FirstDistortionAudioProcessorEditor)
};
