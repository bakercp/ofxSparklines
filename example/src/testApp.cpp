#include "testApp.h"


testApp::~testApp() {
}

//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    
    ofxSparkline::Settings settings;
    for(int i = 0; i < 152; i++) {
        x.push_back(ofRandom(100));
        settings.axes.x.invert = ((int)ofRandom(100) % 2 == 0); 
        sparkLines.push_back(ofxSparkline(settings,100));
    }

    // ----
    settings = ofxSparkline::Settings();
    settings.annotations.label.display = true;
    settings.annotations.label.text = "{V} Data w/ High Precision";
    settings.annotations.label.precision = 5;
    customized.push_back(ofxSparkline(settings,100));
    x2.push_back(ofRandom(100));
    
    // ----
    settings.annotations.label.text = "{V} Data w/ Smoothing";
    settings.annotations.label.precision = 2;
    settings.styles.curve.line.smoothing = true;
    customized.push_back(ofxSparkline(settings,100));
    x2.push_back(ofRandom(100));

    
    // ----
    settings.annotations.label.text = "{V} With Normal Range Defined";
    settings.annotations.normalRange.display = true;
    settings.styles.curve.line.smoothing = false;
    settings.annotations.normalRange.range.min = .5;
    settings.annotations.normalRange.range.max = .75;
    customized.push_back(ofxSparkline(settings,100));
    x2.push_back(ofRandom(100));
    
    // ----
    settings.annotations.label.text = "{V} w/ First Data Point Marker";
    settings.annotations.markers.first.display = true;  
    customized.push_back(ofxSparkline(settings,100));
    x2.push_back(ofRandom(100));

    // ----
    settings.annotations.label.text = "{V} w/ Local Min Marker";
    settings.annotations.markers.min.display   = true;  
    customized.push_back(ofxSparkline(settings,100));
    x2.push_back(ofRandom(100));

    // ----
    settings.annotations.label.text = "{V} w/ Local Max Marker";
    settings.annotations.markers.max.display   = true;  
    customized.push_back(ofxSparkline(settings,100));
    x2.push_back(ofRandom(100));

    // ----
    settings = ofxSparkline::Settings();
    settings.annotations.label.display = true;
    settings.annotations.label.text = "{V} w/ Curve Area";
    settings.styles.curve.area.display = true;
    customized.push_back(ofxSparkline(settings,100));
    x2.push_back(ofRandom(100));

    // ----
    settings = ofxSparkline::Settings();
    settings.annotations.label.display = true;
    settings.annotations.label.text = "{V} w/ A Buffer Longer Than Box (clipped)";
    settings.styles.curve.area.display = true;
    customized.push_back(ofxSparkline(settings,200));
    x2.push_back(ofRandom(100));

    // ----
    settings = ofxSparkline::Settings();
    settings.width = 200;
    settings.annotations.label.display = true;
    settings.annotations.label.text = "{V} w/ A Longer Buffer w/ Wider Box";
    settings.styles.curve.area.display = true;
    customized.push_back(ofxSparkline(settings,200));
    x2.push_back(ofRandom(100));

    // ----
    settings = ofxSparkline::Settings();
    settings.width = 200;
    settings.axes.x.autoScale = true;
    settings.annotations.markers.max.display = true;
    settings.annotations.label.display = true;
    settings.annotations.label.text = "{V} w/ An even Longer Buffer w/ AutoScaling";
    settings.styles.curve.area.display = true;
    customized.push_back(ofxSparkline(settings,600));
    x2.push_back(ofRandom(100));

    // ----
    settings = ofxSparkline::Settings();
    settings.annotations.label.display = true;
    settings.annotations.label.text = "Other Colors";
    settings.annotations.label.precision = 2;
    settings.styles.box.fill.display = true;
    settings.styles.box.fill.color = ofColor(0);
    settings.styles.curve.line.color = ofColor(255);
    customized.push_back(ofxSparkline(settings,100));
    x2.push_back(ofRandom(100));

    
    // ----
    settings.annotations.markers.last.display = false;
    settings.styles.curve.area.display = true;
    settings.styles.curve.line.smoothing = true;
    settings.styles.curve.line.color = ofColor(255,100);
    settings.styles.curve.area.color = ofColor(255,80);
    customized.push_back(ofxSparkline(settings,100));
    x2.push_back(ofRandom(100));

    // ----
    settings.width = 400;
    settings.height = 50;
    settings.annotations.label.text = "Big x/y inverted";
    settings.axes.x.invert = true;
    settings.axes.y.invert = true;
    customized.push_back(ofxSparkline(settings,400));
    x2.push_back(ofRandom(100));

    settings.width = 400;
    settings.height = 50;
    settings.axes.y.invert = false;
    settings.axes.x.invert = false;
    settings.axes.x.autoScale = true;
    settings.axes.y.autoScale = true;
    settings.annotations.label.text = "Big x/y Autoscale";
    customized.push_back(ofxSparkline(settings,800));
    x2.push_back(ofRandom(100));

    // ----
    settings.axes.x.autoScale = false;
    settings.axes.y.autoScale = false;
    settings.axes.y.range.min = -1;
    settings.annotations.label.text = "Y range -1 -> 1";
    customized.push_back(ofxSparkline(settings,400));
    x2.push_back(ofRandom(100));

    settings.axes.x.autoScale = false;
    settings.axes.y.autoScale = false;
    settings.axes.y.range.min = -1;
    settings.annotations.label.text = "Variations";
    settings.styles.box.fill.display = false;
    settings.styles.box.stroke.display = true;
    settings.axes.y.range.min = 0;
    settings.styles.curve.line.color = ofColor(255,0,0,80);
    settings.styles.curve.area.color = ofColor(255,255,0,80);
    customized.push_back(ofxSparkline(settings,400));
    x2.push_back(ofRandom(100));
    
    settings.annotations.label.text = "Small Databuffer";
    settings.width = 400;
    settings.height = 300;
    settings.styles.box.stroke.display = false;
    settings.axes.x.autoScale = true;
    customized.push_back(ofxSparkline(settings,20));
    x2.push_back(ofRandom(100));

}

//--------------------------------------------------------------
void testApp::update() {
    for(int i = 0; i < x.size(); i++) {
        x[i]+=ofRandom(.001,.1);
        float f = ofNoise(x[i]);
        sparkLines[i].push_back(f);
    }
    
    for(int i = 0; i < x2.size(); i++) {
        x2[i]+=ofRandom(.001,.1);
        float f = ofNoise(x2[i]);
        customized[i].push_back(f);
    }

}

//--------------------------------------------------------------
void testApp::draw(){
    
    
    
    ofBackground(255);
    float padX = 5;
    float padY = 5;
    float currentX = padY;
    float currentY = padY;

    ofPushMatrix();
    ofTranslate(0,0);
    currentX = padY;
    currentY = padY;
    
    // draw customized
    for(int i = 0; i < customized.size(); i++) {
        customized[i].draw(currentX,currentY);
        currentY += customized[i].getHeight() + padY;;
        if((currentY + customized[i].getHeight())> ofGetHeight()) {
            currentY = padY;
            currentX += customized[i].getWidth() + padX;
        }
    }
    ofPopMatrix();
    
    
    // draw fleet
    ofPushMatrix();
    ofTranslate(ofGetWidth() / 2 + 80, 0);
    currentX = padY;
    currentY = padY;
    for(int i = 0; i < sparkLines.size(); i++) {
        sparkLines[i].draw(currentX,currentY);
        currentY += sparkLines[i].getHeight() + padY;;
        if((currentY + sparkLines[i].getHeight())> ofGetHeight()) {
            currentY = padY;
            currentX += sparkLines[i].getWidth() + padX;
        }
    }
    ofPopMatrix();
}
//--------------------------------------------------------------
void testApp::keyPressed  (int key){
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){ 
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::resized(int w, int h){

}
