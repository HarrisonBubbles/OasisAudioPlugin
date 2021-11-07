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
    juce::Colour orange = juce::Colour(252, 176, 69);
    juce::ColourGradient gradient = juce::ColourGradient(red, 0.0f, 0.0f, orange, 0.0f, 500.0f, false);

    g.setGradientFill(gradient);
    g.fillAll();

    g.setColour(juce::Colour(237, 74, 79));
    //dsStruct.drawForRectangle(g, juce::Rectangle<int>::Rectangle<int>(50, 50, 400, 300));
    g.fillRoundedRectangle(rect, 10.f);

    g.setColour(juce::Colours::black);
    g.drawRoundedRectangle(rect, 10.f, 4.f);

    g.setColour (juce::Colours::white);
    g.setFont (juce::Font(getGiraffeyFont()));
    g.setFont(50.0f);
    g.drawFittedText ("DISTORTION", getLocalBounds(), juce::Justification::centred, 1);
    
    g.setFont(20.0f);
    g.drawText("VOLUME", 50, rect.getHeight() - 105, 100, 100, juce::Justification::centred, false);
    g.drawText("DRIVE", rect.getWidth() - 50, rect.getHeight() - 105, 100, 100, juce::Justification::centred, false);
    g.drawText("RANGE", 50, 20, 100, 100, juce::Justification::centred, false);
    g.drawText("BLEND", rect.getWidth() - 50, 20, 100, 100, juce::Justification::centred, false);


}

void FirstDistortionAudioProcessorEditor::resized()
{
    volumeSlider.setBounds(50,rect.getHeight() - 50,100,100);
    driveSlider.setBounds(rect.getWidth() - 50, rect.getHeight() - 50, 100, 100);
    rangeSlider.setBounds(50, 75, 100, 100);
    blendSlider.setBounds(rect.getWidth() - 50, 75, 100, 100);
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
