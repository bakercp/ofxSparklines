//
//  ofxSparkline.h
//  ofxSparklines
//
//  Created by Christopher Baker on 6/15/12.
//  Copyright (c) 2012 School of the Art Institute of Chicago. All rights reserved.
//
//  TODO: refactor into generic ofxPlot type?

/*
	changes JJJ 2016 11 17
		- included ofRange.h into src/ from https://github.com/Flightphase/ofxRange/blob/master/src/ofRange.h
		- commented off public ofBaseDraws it triggers error on VS Win 10:  "cannot instantiate abstract class" error
		- works now on win 10 VS OF097
*/

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
    ofxStyle() { display = true; }
    bool display;
};


class ofxStrokeFillStyle {
public:
    ofxStrokeFillStyle() {
        stroke.display = false;
        stroke.bFill   = false;
        fill.display   = true;
        fill.bFill     = true;
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
        stroke.rectMode  = OF_RECTMODE_CENTER;
        fill.rectMode    = OF_RECTMODE_CENTER;
    }
    float width;
    float height;
    ofxPointType type;
};

class ofxSparkline : public ofxDataBuffer // , public ofBaseDraws  // <<--- JJJ
{
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
        Settings();
        
        struct Axis {
            Axis() {invert = false; autoScale = false; clip = true; range = ofRange();}
            bool    invert;
            bool    autoScale;
            bool    clip;
            ofRange range;
        };
        
        struct Axes {
            Axes() {x = Axis(); y = Axis();}
            Axis x;
            Axis y;
        };
        
        struct Label {
            //ofTrueTypeFont* labelFont;
            Label() {
                display     = true; 
                text        = "";
                style.bFill = true;
                style.color = ofColor(0);
                precision   = 2;
            }
            int      precision;
            bool     display; 
            string   text; // {V} is replaced with the last value, number is precision
            ofxStyle style;
        };
        
        
        struct Marker {
            bool display;
            ofxPointStyle style;
        };
        
        struct Markers {
            Marker first;
            Marker last;
            Marker min;
            Marker max;
        };
        
        struct StyledRange {
            bool    display;
            ofRange range;
            ofxStrokeFillStyle  style;
        };
        
        struct Annotations {
            Label label;
            Markers markers;
            StyledRange normalRange;
        };
        
        struct CurveStyle {
            ofxStyle line;
            ofxStyle area;
        };
        
        struct Style {
            CurveStyle curve;
            ofxStrokeFillStyle box;
        };

        float       width;
        float       height;
        Axes        axes;
        Annotations annotations;
        Style       styles;
    };
    
    Settings settings;

protected:
    
    ofPoint bufferToScreen(float x, float y);
    float   bufferXToScreenX(float x);
    float   bufferYToScreenY(float y);
    
private:
};
