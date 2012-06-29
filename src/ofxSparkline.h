//
//  ofxSparklines.h
//  ofxSparklines
//
//  Created by Christopher Baker on 6/15/12.
//  Copyright (c) 2012 School of the Art Institute of Chicago. All rights reserved.
//
//  TODO: refactor into generic ofxPlot type?

#pragma once

#include "ofMain.h"
#include "ofxDataBuffer.h"
#include "ofRange.h"

enum ofxSparklineType {
	OFX_SPARKLINE_TYPE_LINE,
	OFX_SPARKLINE_TYPE_GRADIENT,
};

enum ofxPointType {
    OFX_POINT_TYPE_ELLIPSE    = 0,
    OFX_POINT_TYPE_RECT       = 1,
};

class ofxStyle : public ofStyle {
public:
    ofxStyle() { render = true; }
    bool render;
};

class ofxStrokeFillStyle {
public:
    ofxStrokeFillStyle() {
        stroke.bFill = false;
        fill.bFill   = true;
    }
    ofxStyle   stroke;
    ofxStyle   fill;
};


class ofxPointStyle : public ofxStrokeFillStyle {
public:
    ofxPointStyle() : ofxStrokeFillStyle() {
        width            = 3;
        height           = 3;
        type             = OFX_POINT_TYPE_RECT;
        
        stroke.render    = true;
        stroke.rectMode  = OF_RECTMODE_CENTER;
        fill.render      = true;
        fill.rectMode    = OF_RECTMODE_CENTER;
        render           = true;
    }
    
    virtual ~ofxPointStyle() {}
    
    void draw(const ofPoint& p) {
        draw(p.x,p.y);
    }
    
    void draw(float x, float y) {
        if(!render || (!stroke.render && !fill.render)) return;

        ofPushStyle();
        
        if(type == OFX_POINT_TYPE_ELLIPSE) {
            ofPushStyle();
            if(fill.render) {
                ofSetStyle(fill);
                ofEllipse(x,y,width,height);
            }
            if(stroke.render) {
                ofSetStyle(stroke);
                ofEllipse(x,y,width,height);
            }
            ofPopStyle();
        } else if(type == OFX_POINT_TYPE_RECT) {
            ofPushStyle();
            if(fill.render) {
                ofSetStyle(fill);
                ofRect(x,y,width,height);
            }
            if(stroke.render) {
                ofSetStyle(stroke);
                ofRect(x,y,width,height);
            }
            ofPopStyle();
        }

        ofPopStyle();
    }
    
    float width;
    float height;
    
    bool render;
    
    ofxPointType type;
};


class ofxSparkline : public ofxDataBuffer, public ofBaseDraws {
public:
    
    struct Settings;

    ofxSparkline();
    ofxSparkline(size_t size);
    ofxSparkline(Settings settings, size_t size = 100);
    virtual ~ofxSparkline();

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
        ofRange             normalRange;
        
        bool                xInvert;
        
        bool                yAutoScale;
        ofRange             yRange;
        bool                yClip;
        bool                yInvert;
        
        
        
        struct ofxSparkLineStyles {
            ofxStyle            line;
            ofxStyle            underLine;
            
            ofxStrokeFillStyle  box;
            ofxStrokeFillStyle  normalRangeBox;
            
            ofxPointStyle       lastPoint;        
            ofxPointStyle       firstPoint;        
            ofxPointStyle       localMaxPoint;        
            ofxPointStyle       localMinPoint;
            
            ofxStyle            label;

        };

        ofxSparkLineStyles styles;
        
    };
    
    Settings settings;

protected:
    
    ofPoint bufferToScreen(float x, float y);
    float   bufferXToScreenX(float x);
    float   bufferYToScreenY(float y);
    
private:
};
