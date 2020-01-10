/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class Delay1AudioProcessorEditor  : public AudioProcessorEditor,
                                    private Slider::Listener
{
public:
    Delay1AudioProcessorEditor (Delay1AudioProcessor&);
    ~Delay1AudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Delay1AudioProcessor& processor;
    
    void sliderValueChanged (Slider* slider) override;
    
    Slider delaySlider;
    Slider feedbackSlider;
    
    Label delayLabel;
    Label feedbackLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Delay1AudioProcessorEditor)
};
