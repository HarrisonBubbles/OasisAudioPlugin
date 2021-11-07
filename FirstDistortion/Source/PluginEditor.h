/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "StyleSheet.h"
#include "InputMeter.h"

//==============================================================================
/**
*/
class FirstDistortionAudioProcessorEditor  : public juce::AudioProcessorEditor,
public juce::Slider::Listener, public juce::Timer
{
public:
    void timerCallback() override;
    
    FirstDistortionAudioProcessorEditor (FirstDistortionAudioProcessor&);
    ~FirstDistortionAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(juce::Slider* slider) override;

//    static const juce::Font& getGiraffeyFont()
//    {
//        static juce::Font giraffey(juce::Font(juce::Typeface::createSystemTypefaceFor(BinaryData::Giraffey_otf,
//            BinaryData::Giraffey_otfSize)));
//        return giraffey;
//    }
//
//    static const juce::Font& getGaramondFont()
//    {
//        static juce::Font garamond(juce::Font(juce::Typeface::createSystemTypefaceFor(BinaryData::GaramondMed_ttf,
//            BinaryData::GaramondMed_ttfSize)));
//        return garamond;
//    }
//
//    static const juce::Font& getDisengagedFont()
//    {
//        static juce::Font disengaged(juce::Font(juce::Typeface::createSystemTypefaceFor(BinaryData::Disengaged_ttf,
//            BinaryData::Disengaged_ttfSize)));
//        return disengaged;
//    }
//
//    static const juce::Font& getStringsTheoryFont()
//    {
//        static juce::Font stringsTheory(juce::Font(juce::Typeface::createSystemTypefaceFor(BinaryData::StringsTheory_ttf,
//            BinaryData::StringsTheory_ttfSize)));
//        return stringsTheory;
//    }
//
//    static const juce::Font& getMicrogrammaFont()
//    {
//        static juce::Font microgramma(juce::Font(juce::Typeface::createSystemTypefaceFor(BinaryData::Microgramma_ttf,
//            BinaryData::Microgramma_ttfSize)));
//        return microgramma;
//    }
//
//    static const juce::Font& getRobotoFont()
//    {
//        static juce::Font roboto(juce::Font(juce::Typeface::createSystemTypefaceFor(BinaryData::RobotoMedium_ttf,
//            BinaryData::RobotoMedium_ttfSize)));
//        return roboto;
//    }
    
    static const juce::Font& getAGFont()
    {
        static juce::Font ag(juce::Font(juce::Typeface::createSystemTypefaceFor(BinaryData::Akzidenzgroteskroman_ttf,
            BinaryData::Akzidenzgroteskroman_ttfSize)));
        return ag;
    }
    
//    static const juce::Font& getEurostileFont()
//    {
//        static juce::Font eurostile(juce::Font(juce::Typeface::createSystemTypefaceFor(BinaryData::EuroStyle_Normal_ttf,
//            BinaryData::EuroStyle_Normal_ttfSize)));
//        return eurostile;
//    }

private:
    // input meter
    
    Gui::InputMeter inputMeterL, inputMeterR;
    
    juce::Rectangle<float> rect{ 50.f, 50.f, 400.f, 300.f};
    juce::Rectangle<float> rect2{ 35.f, 35.f, 430.f, 330.f};
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
