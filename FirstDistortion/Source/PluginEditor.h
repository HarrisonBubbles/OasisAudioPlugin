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
class FirstDistortionAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    FirstDistortionAudioProcessorEditor (FirstDistortionAudioProcessor&);
    ~FirstDistortionAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    CustomLNF myLNF;
    juce::Slider volumeSlider;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    FirstDistortionAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FirstDistortionAudioProcessorEditor)
};
