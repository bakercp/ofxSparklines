//
//  ofxSparklines.h
//  ofxSparklines
//
//  Created by Christopher Baker on 6/15/12.
//  Copyright (c) 2012 School of the Art Institute of Chicago. All rights reserved.
//

#pragma once

#include "ofxDataBuffer.h"
#include "ofRange.h"

//enum ofxSparklineType {
//	OFX_SPARKLINE_TYPE_LINE,
//	OFX_SPARKLINE_TYPE_GRADIENT,
//};
//
//enum ofxSparklineRangeType {
//	OFX_SPARKLINE_RANGE_TYPE_NORMAL     = 0,
//	OFX_SPARKLINE_RANGE_TYPE_CLAMP      = 1,
//    OFX_SPARKLINE_RANGE_TYPE_NORMALIZE  = 2
//};
//
//
//enum ofxPointType {
//    OFX_POINT_TYPE_ELLIPSE    = 0,
//    OFX_POINT_TYPE_RECT       = 1,
//};
//
//class ofxStyle : public ofStyle {
//public:
//    ofxStyle() { render = true; }
//    bool render;
//};
//
//class ofxStrokeFillStyle {
//public:
//    ofxStrokeFillStyle() {
//        stroke.bFill = false;
//        fill.bFill   = true;
//    }
//    ofxStyle   stroke;
//    ofxStyle   fill;
//};
//
//void ofxDrawStyledRect(ofxStrokeFillStyle style, float x, float y, float w, float h) {
//    cout << "in here" << endl;
//    
//    ofPushStyle();
//    if(style.fill.render) {
//        ofSetStyle(style.fill);
//        ofRect(x,y,w,h);
//    }
//    if(style.stroke.render) {
//        ofSetStyle(style.stroke);
//        ofRect(x,y,w,h);
//    }
//    ofPopStyle();
//    cout << "out here" << endl;
//};
//
//void ofxDrawStyledEllipse(ofxStrokeFillStyle style, float x, float y, float w, float h) {
//    ofPushStyle();
//    if(style.fill.render) {
//        ofSetStyle(style.fill);
//        ofEllipse(x,y,w,h);
//    }
//    if(style.stroke.render) {
//        ofSetStyle(style.stroke);
//        ofEllipse(x,y,w,h);
//    }
//    ofPopStyle();
//};
//
//
//class ofxPointStyle : public ofxStrokeFillStyle {
//public:
//    ofxPointStyle() : ofxStrokeFillStyle() {
//        width            = 3;
//        height           = 3;
//        type             = OFX_POINT_TYPE_ELLIPSE;
//        stroke.render    = OF_RECTMODE_CENTER;
//        fill.render      = OF_RECTMODE_CENTER;
//    }
//    
//    virtual ~ofxPointStyle() {}
//    
//    void draw(float x, float y) {
//        if(!stroke.render || !fill.render) return;
//
//        ofPushStyle();
//        
//        if(type == OFX_POINT_TYPE_ELLIPSE) {
//            ofxDrawStyledEllipse(*this,x,y,width,height);
//        } else if(type == OFX_POINT_TYPE_RECT) {
//            ofxDrawStyledRect(*this,x,y,width,height);
//        }
//
//        ofPopStyle();
//    }
//    
//    float width;
//    float height;
//    
//    ofxPointType type;
//};


template<typename T>
class ofxSparkline_ : public ofxDataBuffer_<T> {//, ofBaseDraws {
public:
    
    struct Settings;

    ofxSparkline_();
    ofxSparkline_(size_t size);
    ofxSparkline_(Settings settings, size_t size = 100);
    virtual ~ofxSparkline_();

    void setSettings(Settings _settings);

	void draw(float x, float y);
	void draw(float x, float y, float w, float h);

	float getHeight();
	float getWidth();
    
	struct Settings {
		float   width;				
		float   height;
        
        string title;
        ofTrueTypeFont*     font;
		Settings();
        
        bool                normalRangeSet;
        ofRange_<T>         normalRange;
//        ofxStrokeFillStyle  normalRangeStyle;
        
//        ofxSparklineRangeType   displayRangeType;
        ofRange_<T>             displayRange;
         
//        ofxStyle            lineStyle;
        
//        ofxStrokeFillStyle  frameStyle;
//        
//        ofxPointStyle       lastPointStyle;        
//        ofxPointStyle       firstPointStyle;        
//        ofxPointStyle       maxPointStyle;        
//        ofxPointStyle       minPointStyle;  
        
    };
    
    Settings settings;

protected:
private:
};

template<typename T>
ofxSparkline_<T>::ofxSparkline_() {
    //settings = Settings();
    cout << "init() > settings = " << settings.width << " / " << settings.height << endl;
}

template<typename T>
ofxSparkline_<T>::ofxSparkline_(size_t v) : ofxDataBuffer_<T>(v){
    //settings = Settings();
    cout << "init() > settings = " << settings.width << " / " << settings.height << endl;
}

template<typename T>
ofxSparkline_<T>::ofxSparkline_(Settings _settings, size_t v) : ofxDataBuffer_<T>(v){
    settings = _settings;
    cout << "init() > settings = " << settings.width << " / " << settings.height << endl;
}


template<typename T>
ofxSparkline_<T>::~ofxSparkline_() {
}

template<typename T>
void ofxSparkline_<T>::setSettings(Settings _settings) {
    settings = _settings;
}

//template<typename T>
//void ofxSparkline_<T>::draw(float x, float y) {
//    cout << "in here ==> width = " << getWidth() << "getHeight=" << getHeight() << endl;
//    
//    
//    //draw(x,y,getWidth(),getHeight());
//}

template<typename T>
void ofxSparkline_<T>::draw(float x, float y, float w, float h) {
    
    cout << "in here ==> x=" << x << " y= " << y << " width = " << w << "getHeight=" << h << endl;

    
    
//    ofPushStyle();
//    ofPushMatrix();
//    ofTranslate(x,y);
//    
//    cout << ">>>> in here!!!!!" << endl;
//    ofxDrawStyledRect(settings.frameStyle,0,0,w,h);
//    cout << ">>>> out here!!!!!" << endl;
//    
//    ofPopMatrix();
//    ofPopStyle();
}

template<typename T>
float ofxSparkline_<T>::getWidth() {
    return settings.width;
}

template<typename T>
float ofxSparkline_<T>::getHeight() {
    return settings.height;
}

template<typename T>
ofxSparkline_<T>::Settings::Settings() {
    width  = 20.0;
    height = 50.0;
    title  = "";
    font   = NULL;
    
    normalRangeSet   = false;
//    normalRange      = ofRange_<T>();
//    normalRangeStyle = ofColor(0,80);
    
//    displayRangeType = 
    
//    bool displayRangeSet;
//    ofRange_<T> displayRange;
    
//    lineStyle;
//    frameStyle;
    
//    lastPointDef;        
//    firstPointDef;        
//    maxPointDef;        
//    minPointDef;        

}

typedef ofxSparkline_<char>   ofxCharSparkline;
typedef ofxSparkline_<float>  ofxFloatSparkline;
typedef ofxSparkline_<float>  ofxSparkline;
typedef ofxSparkline_<double> ofxDoubleSparkline;
typedef ofxSparkline_<int>    ofxIntSparkline;
typedef ofxSparkline_<long>   ofxLongSparkline;




