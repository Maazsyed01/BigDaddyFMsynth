/*
  ==============================================================================

    FilterGraph.cpp
    Created: 27 May 2020 11:14:05am
    Author:  daveg

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterGraph.h"


FilterGraph::FilterGraph() {

}
//==============================================================================
FilterGraph::FilterGraph(int x, int y, int width, int height)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    xPos = x;
    yPos = y;
    this->height = height;
    this->width = width;

    addGraphs();
}

FilterGraph::~FilterGraph()
{
    for (int i = 0; i < 4; i++)
        delete myGraphs[i];


}

void FilterGraph::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::white);
    g.setFont (14.0f);
    g.drawText ("FilterGraph", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}

void FilterGraph::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void FilterGraph::setMyBounds()
{
    this->setBounds(xPos, yPos, width, height);

}

void FilterGraph::addGraphs()
{
    this->myGraphs.push_back(new MyLowPass(xPos, yPos, width, height));
    this->myGraphs.push_back(new MyHighPass(xPos, yPos, width, height));
    this->myGraphs.push_back(new MyBandPass(xPos, yPos, width, height));
    this->myGraphs.push_back(new MyNotchFilter(xPos, yPos, width, height));

    for (int i = 0; i < 4; i++)
        myGraphs[i]->setMyBounds();

    addAndMakeVisible(myGraphs[0]);


}
