/*
  ==============================================================================

    StyleSheet.h
    Created: 9 Oct 2021 12:23:53am
    Author:  harri

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

namespace juce {

    class CustomLNF : public juce::LookAndFeel_V4
    {
    public:
        // methods go here
        void drawRotarySlider(Graphics& g, int x, int y, int width, int height,
            float sliderPos, float rotaryStartAngle, float rotaryEndAngle, Slider& slider);
    };

}
