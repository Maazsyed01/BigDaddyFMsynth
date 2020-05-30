/*
  ==============================================================================

    KnobSection.cpp
    Created: 26 May 2020 1:58:38pm
    Author:  daveg

  ==============================================================================
*/

#include <JuceHeader.h>
#include "KnobSection.h"

//==============================================================================

KnobSection::KnobSection()
{
    xPos = 0;
    yPos = 0;
    height = 40;
    width = 40;
    checkDirection();

}

KnobSection::KnobSection(int x, int y, int w, int h) : xPos{ x }, yPos{ y }, width{ w }, height{ h }{
    checkDirection();
    sender = new MySender(tSection::matrix);
}

KnobSection::KnobSection(int x, int y, int w, int h, int nKnob) : xPos{ x }, yPos{ y }, width{ w }, height{ h }{
    checkDirection();
    sender = new MySender(tSection::matrix);
    addKnobs(nKnob);
}

KnobSection::KnobSection(int x, int y, int w, int h, int nKnob, tSection type) : xPos{ x }, yPos{ y }, width{ w }, height{ h }
{
    checkDirection();
    sender = new MySender(type);
    addKnobs(nKnob);
}

KnobSection::KnobSection(int x, int y, int w, int h, int nKnob, tSection type, int row) : xPos{ x }, yPos{ y }, width{ w }, height{ h }
{
    checkDirection();
    sender = new MySender(type);
    addKnobs(nKnob, row);
}

KnobSection::~KnobSection(){
    for (auto& knob : knobs) {
        delete knob;
    }
    delete sender;
}


void KnobSection::setMyBounds() {
    this->setBounds(xPos, yPos, width, height);
}


void KnobSection::addKnobs(int nKnob)
{
    addKnobs(nKnob, -1);
}

void KnobSection::addKnobs(int nKnob, int row)
{
    Slider* temp;
    String knobName;

    for (size_t i = 0; i < nKnob; ++i) {
        temp = new Slider(Slider::RotaryHorizontalVerticalDrag, Slider::TextBoxBelow);
        temp->setTextBoxIsEditable(true);
        if (row < 0) {
            knobName = sender->getSocketName() + ">=" + std::to_string(i);
        }
        else {
            knobName = sender->getSocketName() + ">=" + std::to_string(row) + ">=" + std::to_string(i);
        }
        
        std::string stdName = knobName.toStdString();
        temp->setName(knobName); //set name to send to socket
        temp->addListener(this);
        temp->setLookAndFeel(&KnobLAF);
        addAndMakeVisible(temp); // makes visible each knob
        knobs.push_back(temp);
    }
    arrange();
}



//TODO IMPLEMENT AUTOMATIC AND SCALABLE SETBOUND FOR KNOBS 
void KnobSection::arrange() {
    if (knobs.size() == 0){
        return;
    }
    int i = 0;
    float individualWidth, individualHeight;

    switch (dir)
    {
    case direction::horizontal:
        individualHeight = height;
        individualWidth = width / knobs.size();
        for (auto& knob : knobs) {
            knob->setBounds(i * individualWidth, 0, individualWidth, individualHeight);
            i++;
        }
        break;

    case direction::vertical:
        individualHeight = height/knobs.size();
        individualWidth = width;
        for (auto& knob : knobs) {
            knob->setBounds(0, i * individualHeight, individualWidth, individualHeight);
            i++;
        }
        break;
    default:
        break;
    }


}


void KnobSection::checkDirection() {
    if (height > width) {
        dir = direction::vertical;
    }
    else
    {
        dir = direction::horizontal;
    }
}




void KnobSection::paint (Graphics& g)
{

}

void KnobSection::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void KnobSection::sliderDragStarted(Slider*)
{
}

void KnobSection::sliderDragEnded(Slider*)
{
}


void KnobSection::sliderValueChanged(Slider* slider)
{
    sender->mySend(slider->getName(), slider->getValue());
}

void KnobSection::setMyOscillatorRange() 
{
    int max = 100;
    int min = 10;
    int step = 1;
 
    knobs[0]->setRange(min/100, max/100, step/100); // AMP
    knobs[1]->setRange(min/10, max/10, step/10);                   // FREQRATIO
    knobs[1]->setSkewFactorFromMidPoint(max/50);
    knobs[2]->setRange(0, double_Pi, step/100);           //PHASE      
}

void KnobSection::setMyLFORange()
{
    int max = 20 ;
    int min = 0.002 ;
    int step = 0.1;

    knobs[0]->setRange( min, max / 20 , step/10 ); // LFOA amp
    knobs[1]->setRange(min, max/4, step/10);
    knobs[2]->setRange(min, max, step);
    knobs[2]->setSkewFactorFromMidPoint(max / 10);
    knobs[3]->setRange(0, double_Pi,step/10);
}

