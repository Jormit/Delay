/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Delay1AudioProcessorEditor::Delay1AudioProcessorEditor (Delay1AudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    addAndMakeVisible (delaySlider);
    delaySlider.setRange (0.0, 2000.0f, 100.0f);
    delaySlider.setTextValueSuffix ("ms");
    delaySlider.setValue (processor.mDelay);
    delaySlider.addListener (this);
    
    addAndMakeVisible(delayLabel);
    delayLabel.setText ("Delay", dontSendNotification);
    delayLabel.attachToComponent (&delaySlider, true);
    
    // Presence Slider setup.
    addAndMakeVisible (feedbackSlider);
    feedbackSlider.setRange (0.0, 1.0f, 0.01f);
    feedbackSlider.setValue (processor.mFeedback);
    feedbackSlider.addListener (this);
    
    addAndMakeVisible(feedbackLabel);
    feedbackLabel.setText ("Feedback", dontSendNotification);
    feedbackLabel.attachToComponent (&feedbackSlider, true);    
    
    setSize (500, 90);
}

Delay1AudioProcessorEditor::~Delay1AudioProcessorEditor()
{
}

//==============================================================================
void Delay1AudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
}

void Delay1AudioProcessorEditor::resized()
{
    auto margin = 20;
    auto labelSpace = 50;
    delaySlider.setBounds (margin + labelSpace, 20, getWidth() - 2 * margin - labelSpace, 20);   
    feedbackSlider.setBounds (margin + labelSpace, 50, getWidth() - 2 * margin - labelSpace, 20);      
}

void Delay1AudioProcessorEditor::sliderValueChanged(Slider *slider) 
{    
    processor.mFeedback = feedbackSlider.getValue();
    
    if (processor.mDelay != delaySlider.getValue())
    {
        processor.mDelay = delaySlider.getValue();
        processor.delayLine[0].updateSize((int) ((processor.mDelay / 1000.0f) * (processor.sampleRate)));
        processor.delayLine[1].updateSize((int) ((processor.mDelay / 1000.0f) * (processor.sampleRate)));
    }
    

}
