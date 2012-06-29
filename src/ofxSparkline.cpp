#include "ofxSparkline.h"

void ofxDrawStyledRect(ofxStrokeFillStyle style, float x, float y, float w, float h) {
    ofPushStyle();
    if(style.fill.render) {
        ofSetStyle(style.fill);
        ofRect(x,y,w,h);
    }
    if(style.stroke.render) {
        ofSetStyle(style.stroke);
        ofRect(x,y,w,h);
    }
    ofPopStyle();
};

void ofxDrawStyledEllipse(ofxStrokeFillStyle style, float x, float y, float w, float h) {
    ofPushStyle();
    if(style.fill.render) {
        ofSetStyle(style.fill);
        ofEllipse(x,y,w,h);
    }
    if(style.stroke.render) {
        ofSetStyle(style.stroke);
        ofEllipse(x,y,w,h);
    }
    ofPopStyle();
};


ofxSparkline::Settings::Settings() {
    width  = 100;
    height = 15;
    title  = "";
    font   = NULL;
    
    xInvert          = false;
    yAutoScale       = false;
    yRange           = ofRange(0,1.0);
    yClip            = true;
    yInvert          = false;
    
    normalRangeSet   = false;
    normalRange      = ofRange(0,1.0);

    styles.normalRangeBox.fill.render              = true;
    styles.normalRangeBox.fill.color               = ofColor(0,20);
    styles.normalRangeBox.fill.blendingMode        = OF_BLENDMODE_ALPHA;
    styles.normalRangeBox.stroke.render            = false;
    styles.normalRangeBox.stroke.color             = ofColor(0,30);
    styles.normalRangeBox.stroke.blendingMode      = OF_BLENDMODE_ALPHA;
    
    // turn on alpha
    styles.box.fill.render              = false;
    styles.box.fill.color               = ofColor(255,0);
    styles.box.fill.blendingMode        = OF_BLENDMODE_ALPHA;
    styles.box.stroke.render            = false;
    styles.box.stroke.color             = ofColor(0,30);
    styles.box.stroke.blendingMode      = OF_BLENDMODE_ALPHA;

    styles.line.render                  = true;
    styles.line.bFill                   = false;
    styles.line.color                   = ofColor(0);
    styles.line.blendingMode            = OF_BLENDMODE_ALPHA;
    styles.line.smoothing               = true;

    styles.underLine.render             = false;
    styles.underLine.bFill              = true;
    styles.underLine.color              = ofColor(0,80);
    styles.underLine.blendingMode       = OF_BLENDMODE_ALPHA;
    styles.underLine.smoothing          = false;
    
    styles.localMaxPoint.render         = false;
    styles.localMaxPoint.fill.render    = true;
    styles.localMaxPoint.fill.color     = ofColor(0,0,255,100);
    styles.localMaxPoint.stroke.render  = true;
    styles.localMaxPoint.stroke.color   = ofColor(0,0,255,200);
    
    styles.localMinPoint.render         = false;
    styles.localMinPoint.fill.render    = true;
    styles.localMinPoint.fill.color     = ofColor(0,0,255,100);
    styles.localMinPoint.stroke.render  = false;
    styles.localMinPoint.stroke.color   = ofColor(0,0,255,200);

    styles.firstPoint.render            = false;
    styles.firstPoint.fill.render       = true;
    styles.firstPoint.fill.color        = ofColor(255,0,0,100);
    styles.firstPoint.stroke.render     = false;
    styles.firstPoint.stroke.color      = ofColor(255,0,0,200);
    
    styles.lastPoint.render             = false;
    styles.lastPoint.fill.render        = true;
    styles.lastPoint.fill.color         = ofColor(255,0,0,100);
    styles.lastPoint.stroke.render      = false;
    styles.lastPoint.stroke.color       = ofColor(255,0,0,200);
    
    
    //normalRangeStyle = ofColor(0,80);
    
    //displayRangeType = 
    
    //    bool displayRangeSet;
    //    ofRange_<T> displayRange;
    
    //    lineStyle;
    //    frameStyle;
    
    //    lastPointDef;        
    //    firstPointDef;        
    //    maxPointDef;        
    //    minPointDef;        
    
}


ofxSparkline::ofxSparkline() {
}

ofxSparkline::ofxSparkline(size_t v) : ofxDataBuffer(v){
}

ofxSparkline::ofxSparkline(Settings _settings, size_t v) : ofxDataBuffer(v){
    settings = _settings;
}

ofxSparkline::~ofxSparkline() {
}

void ofxSparkline::setSettings(Settings _settings) {
    settings = _settings;
}

void ofxSparkline::draw(float x, float y) {
    draw(x,y,getWidth(),getHeight());
}

void ofxSparkline::draw(float x, float y, float w, float h) {
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(x,y);
    
    ofxDrawStyledRect(settings.styles.box,0,0,w,h);
    
    float fMax = bufferYToScreenY(settings.normalRange.max);
    float fMin = bufferYToScreenY(settings.normalRange.min);
    
    ofxDrawStyledRect(settings.styles.normalRangeBox,
                      0,fMin,w,fMax - fMin);
    
    if(settings.styles.underLine.render) {
        
        ofPushStyle();
        ofSetStyle(settings.styles.underLine);
        ofBeginShape();
        
        if(settings.styles.underLine.bFill) {
            ofPoint p = bufferToScreen(0,0);
            ofVertex(p);
        }
        
        for(int i = 0; i < buffer.size(); i++) {
            ofPoint p = bufferToScreen(i,buffer[i]);
            ofVertex(p);
        }
        
        if(settings.styles.underLine.bFill) {
            ofPoint p = bufferToScreen(getSize(),0);
            ofVertex(p);
        }
        
        ofEndShape(settings.styles.underLine.bFill);
        
        ofEndShape();
        ofPopStyle();
    }

    if(settings.styles.line.render) {
        
        ofPushStyle();
        ofSetStyle(settings.styles.line);
        ofBeginShape();
        
        if(settings.styles.line.bFill) {
            ofPoint p = bufferToScreen(0,0);
            ofVertex(p);
        }
        
        for(int i = 0; i < buffer.size(); i++) {
            ofPoint p = bufferToScreen(i,buffer[i]);
            ofVertex(p);
        }

        if(settings.styles.line.bFill) {
            ofPoint p = bufferToScreen(getSize(),0);
            ofVertex(p);
        }

        ofEndShape(settings.styles.line.bFill);

        ofEndShape();
        ofPopStyle();
    
    }
    
    // first point
    settings.styles.firstPoint.draw(bufferToScreen(0,buffer[0]));

    // first point
    settings.styles.lastPoint.draw(bufferToScreen(getSize()-1,buffer[getSize()-1]));
    
    // local min point
    settings.styles.localMinPoint.draw(bufferToScreen(getMinIndex(),getMin()));
    
    // local max point
    settings.styles.localMaxPoint.draw(bufferToScreen(getMaxIndex(),getMax()));
    
    
    // TODO : use non bitmap font if provided
    ofPushStyle();
    ofSetStyle(settings.styles.label);
    
    ofDrawBitmapString(ofToString(getNewest(),2) + " " + settings.title, getWidth() + 3, getHeight() / 2 + 6);
    
    ofPopStyle();
    
    ofPopMatrix();
    ofPopStyle();
}

float ofxSparkline::getWidth() {
    return settings.width;
}

float ofxSparkline::getHeight() {
    return settings.height;
}

ofPoint ofxSparkline::bufferToScreen(float x, float y) {
    return ofPoint(bufferXToScreenX(x),bufferYToScreenY(y));
}


float ofxSparkline::bufferXToScreenX(float x) {
    if(settings.xInvert) {
        return ofMap(x, 0, getMaxBufferSize(), getWidth(), 0);
    } else {
        return ofMap(x, 0, getMaxBufferSize(), 0, getWidth());
    }
}

float ofxSparkline::bufferYToScreenY(float y) {

    if(settings.yAutoScale) {
        settings.yRange.set(getMin(),getMax());
    }

    if(settings.yInvert) {
        return ofMap(y,settings.yRange.min,settings.yRange.max,0,getHeight(),settings.yClip);
    } else {
        return ofMap(y,settings.yRange.min,settings.yRange.max,getHeight(),0,settings.yClip);
    }
}


