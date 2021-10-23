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

    static const juce::Font& getGiraffeyFont()
    {
        static juce::Font giraffey(juce::Font(juce::Typeface::createSystemTypefaceFor(BinaryData::Giraffey_otf,
            BinaryData::Giraffey_otfSize)));
        return giraffey;
    }

private:
    juce::Rectangle<float> rect{ 50.f, 50.f, 400.f, 300.f };
    juce::Slider volumeSlider;
    juce::Slider driveSlider;
    juce::Slider rangeSlider;
    juce::Slider blendSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> driveAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> rangeAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> blendAttachment;

    juce::CustomLNF myLNF;
    juce::DropShadowEffect ds;
    juce::DropShadow dsStruct;
    juce::Font giraffey;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    FirstDistortionAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FirstDistortionAudioProcessorEditor)
};
