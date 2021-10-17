/*
  ==============================================================================

    StyleSheet.cpp
    Created: 9 Oct 2021 12:23:53am
    Author:  harri

  ==============================================================================
*/

#include "StyleSheet.h"

namespace juce
{
    void CustomLNF::drawRotarySlider(Graphics& g, int x, int y, int width, int height,
        float sliderPos, float rotaryStartAngle, float rotaryEndAngle, Slider& slider) {
        
        auto outline = slider.findColour(Slider::rotarySliderOutlineColourId);
        auto fill = slider.findColour(Slider::rotarySliderFillColourId);

        auto bounds = Rectangle<int>(x, y, width, height).toFloat().reduced(10);

        auto radius = jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f;
        auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        auto lineW = jmin(8.0f, radius * 0.5f);
        auto arcRadius = radius - lineW * 0.5f;

        // dial background path
        Path backgroundArc;
        backgroundArc.addCentredArc(bounds.getCentreX(),
            bounds.getCentreY(),
            arcRadius,
            arcRadius,
            0.0f,
            rotaryStartAngle,
            rotaryEndAngle,
            true);

        g.setColour(outline);
        g.strokePath(backgroundArc, PathStrokeType(lineW / 2, PathStrokeType::curved, PathStrokeType::rounded));

        if (slider.isEnabled())
        {
            // fill path
            Path valueArc;
            valueArc.addCentredArc(bounds.getCentreX(),
                bounds.getCentreY(),
                arcRadius,
                arcRadius,
                0.0f,
                rotaryStartAngle,
                toAngle,
                true);

            g.setColour(fill);
            g.strokePath(valueArc, PathStrokeType(lineW / 2 + 1, PathStrokeType::curved, PathStrokeType::rounded));
        }

        // thumb
        auto thumbWidth = lineW * 2.0f;
        Point<float> thumbPoint(bounds.getCentreX() + (arcRadius - 10.0f) * std::cos(toAngle - MathConstants<float>::halfPi),
            bounds.getCentreY() + (arcRadius - 10.0f) * std::sin(toAngle - MathConstants<float>::halfPi));

        g.setColour(slider.findColour(Slider::thumbColourId));
        //g.fillEllipse(Rectangle<float>(thumbWidth, thumbWidth).withCentre(thumbPoint));
        g.drawLine(backgroundArc.getBounds().getCentreX(), backgroundArc.getBounds().getCentreY(),
            thumbPoint.getX(), thumbPoint.getY(), lineW / 2);
    }
}