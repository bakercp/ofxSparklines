#pragma once

#include "ofMain.h"
#include "ofxDataBuffer.h"
#include "ofxSparkline.h"
#include "ofRange.h"
class testApp : public ofBaseApp{

public:

    ~testApp();

    void setup();
    void update();
    void draw();

    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void resized(int w, int h);
    
    vector<float>        x;
    vector<ofxSparkline> sparkLines;
    
};
