/*
  ==============================================================================

    StyleSheet.cpp
    Created: 9 Oct 2021 12:23:53am
    Author:  harri

  ==============================================================================
*/

#include "StyleSheet.h"

//==============================================================================
void juce::CustomLNF::drawRotarySlider(Graphics& g,
    int x, int y, int width, int height, float sliderPos,
    float rotaryStartAngle, float rotaryEndAngle, Slider& slider)
{

    File knobImageFile1 = File::getSpecialLocation
    (File::SpecialLocationType::userDesktopDirectory).getChildFile("knob1.png");
    static juce::Image
        img1(ImageCache::getFromFile(knobImageFile1));

        const double rotation = (slider.getValue()
            - slider.getMinimum())
            / (slider.getMaximum()
                - slider.getMinimum());

        const int frames = img1.getHeight() / img1.getWidth();
        const int frameId = (int)ceil(rotation * ((double)frames - 1.0));
        const float radius = jmin(width / 3.0f, height / 3.0f);
        const float centerX = x + width * 0.5f;
        const float centerY = y + height * 0.5f;
        const float rx = centerX - radius - 1.0f;
        const float ry = centerY - radius;

        g.drawImage(img1,
            (int)rx,
            (int)ry,
            2 * (int)radius,
            2 * (int)radius,
            0,
            frameId*img1.getWidth(),
            img1.getWidth(),
            img1.getWidth());
}


//namespace juce
//{
//    void CustomLNF::drawRotarySlider(Graphics& g, int x, int y, int width, int height,
//        float sliderPos, float rotaryStartAngle, float rotaryEndAngle, Slider& slider) {
//
//        const float radius = jmin (width / 2, height / 2) - 4.0f;
//        const float centreX = x + width * 0.5f;
//        const float centreY = y + height * 0.5f;
//        const float rx = centreX - radius;
//        const float ry = centreY - radius;
//        const float rw = radius * 2.0f;
//        const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
//
//        // fill
//        g.setColour (Colours::orange);
//        g.fillEllipse (rx, ry, rw, rw);
//
//        // outline
//        g.setColour (Colours::red);
//        g.drawEllipse (rx, ry, rw, rw, 1.0f);
//
//        Path p;
//        const float pointerLength = radius * 0.33f;
//        const float pointerThickness = 2.0f;
//        p.addRectangle (-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
//        p.applyTransform (AffineTransform::rotation (angle).translated (centreX, centreY));
//
//        // pointer
//        g.setColour (Colours::yellow);
//        g.fillPath (p);
//    }
//}
