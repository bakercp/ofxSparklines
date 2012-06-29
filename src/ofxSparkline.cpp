#include "ofxSparkline.h"

void ofxDrawStyledRect(const ofxStrokeFillStyle& style, float x, float y, float w, float h) {
    ofPushStyle();
    if(style.fill.display) {
        ofSetStyle(style.fill);
        ofRect(x,y,w,h);
    }
    if(style.stroke.display) {
        ofSetStyle(style.stroke);
        ofRect(x,y,w,h);
    }
    ofPopStyle();
};

void ofxDrawStyledEllipse(const ofxStrokeFillStyle& style, float x, float y, float w, float h) {
    ofPushStyle();
    if(style.fill.display) {
        ofSetStyle(style.fill);
        ofEllipse(x,y,w,h);
    }
    if(style.stroke.display) {
        ofSetStyle(style.stroke);
        ofEllipse(x,y,w,h);
    }
    ofPopStyle();
};

void ofxDrawStyledPoint(const ofxPointStyle& style, float x, float y) {

    if(!style.fill.display && !style.stroke.display) return;

    ofPushStyle();
    if(style.fill.display) {
        ofPushStyle();
        ofSetStyle(style.fill);
        if(style.type == OFX_POINT_TYPE_RECT) {
            ofRect(x,y,style.width,style.height);
        } else if(style.type == OFX_POINT_TYPE_ELLIPSE) {
            ofEllipse(x,y,style.width,style.height);
        }
        ofPopStyle();
    }
    if(style.stroke.display) {
        ofPushStyle();
        ofSetStyle(style.stroke);
        if(style.type == OFX_POINT_TYPE_RECT) {
            ofRect(x,y,style.width,style.height);
        } else if(style.type == OFX_POINT_TYPE_ELLIPSE) {
            ofEllipse(x,y,style.width,style.height);
        }
        ofPopStyle();
    }
    ofPopStyle();
}

ofxSparkline::Settings::Settings() {
    width  = 100;
    height = 15;

    styles.curve.line.display      = true;
    styles.curve.line.bFill        = false;
    styles.curve.line.color        = ofColor(0);
    styles.curve.line.blendingMode = OF_BLENDMODE_ALPHA;
    styles.curve.line.smoothing    = false;
    
    styles.curve.area.display      = false;
    styles.curve.area.bFill        = true;
    styles.curve.area.color        = ofColor(0,40);
    styles.curve.area.blendingMode = OF_BLENDMODE_ALPHA;
    styles.curve.area.smoothing    = false;
    
    styles.box.fill.display        = false;
    styles.box.fill.color          = ofColor(0,30);
    styles.box.fill.blendingMode   = OF_BLENDMODE_ALPHA;
    styles.box.stroke.display      = false;
    styles.box.stroke.color        = ofColor(0,50);
    styles.box.stroke.blendingMode = OF_BLENDMODE_ALPHA;

    // axes
    axes.x.invert      = false;
    axes.x.clip        = true;
    axes.x.autoScale   = false;
    axes.x.range.min   = 0;
    axes.x.range.max   = width;
    
    axes.y.invert      = false;
    axes.y.clip        = true;
    axes.y.autoScale   = false;
    axes.y.range.min   = 0;
    axes.y.range.max   = 1.0f;
    
    // annotations
    StyledRange& normalRange = annotations.normalRange;
    normalRange.display                     = false;
    normalRange.range.min                   = 0.0;
    normalRange.range.max                   = 1.0;
    normalRange.style.fill.display          = true;
    normalRange.style.fill.color            = ofColor(0,20);
    normalRange.style.fill.blendingMode     = OF_BLENDMODE_ALPHA;
    normalRange.style.stroke.display        = false;
    normalRange.style.stroke.color          = ofColor(0,30);
    normalRange.style.stroke.blendingMode   = OF_BLENDMODE_ALPHA;

    Label& label = annotations.label;
    label.style.color = ofColor(0);
    label.display     = false;
    label.text        = "{V}"; // last value, precision = 2
    
    Markers& markers = annotations.markers;

    Marker& first = markers.first;
    Marker& last  = markers.last;
    Marker& min   = markers.min;
    Marker& max   = markers.max;

    max.display                = false;
    max.style.fill.display     = true;
    max.style.fill.color       = ofColor(0,255,0,100);
    max.style.stroke.display   = true;
    max.style.stroke.color     = ofColor(0,255,0,200);
    
    min.display                = false;
    min.style.fill.display     = true;
    min.style.fill.color       = ofColor(0,0,255,100);
    min.style.stroke.display   = true;
    min.style.stroke.color     = ofColor(0,0,255,200);

    first.display              = false;
    first.style.fill.display   = true;
    first.style.fill.color     = ofColor(255,0,0,100);
    first.style.stroke.display = true;
    first.style.stroke.color   = ofColor(255,0,0,200);

    last.display               = true;
    last.style.fill.display    = true;
    last.style.fill.color      = ofColor(255,0,0,100);
    last.style.stroke.display  = true;
    last.style.stroke.color    = ofColor(255,0,0,200);

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
    
    if(settings.annotations.normalRange.display) {
        float fMin = bufferYToScreenY(settings.annotations.normalRange.range.min);
        float fMax = bufferYToScreenY(settings.annotations.normalRange.range.max);
        ofxDrawStyledRect(settings.annotations.normalRange.style,
                          0,fMin,w,fMax - fMin);
    }
    
    
    if(getSize() > 0) {
        if(settings.styles.curve.area.display) {
            
            ofPushStyle();
            ofSetStyle(settings.styles.curve.area);
            ofBeginShape();
            
            if(settings.styles.curve.area.bFill) {
                ofPoint p = bufferToScreen(0,0);
                ofVertex(p);
            }
            
            for(int i = 0; i < buffer.size(); i++) {
                ofPoint p = bufferToScreen(i,buffer[i]);
                ofVertex(p);
            }
            
            if(settings.styles.curve.area.bFill) {
                ofPoint p = bufferToScreen(getSize()-1,0);
                ofVertex(p);
            }
            
            ofEndShape(settings.styles.curve.area.bFill);
            
            ofEndShape();
            ofPopStyle();
        }

        if(settings.styles.curve.line.display) {
            
            ofPushStyle();
            ofSetStyle(settings.styles.curve.line);
            ofBeginShape();
            
            if(settings.styles.curve.line.bFill) {
                ofPoint p = bufferToScreen(0,0);
                ofVertex(p);
            }
            
            for(int i = 0; i < buffer.size(); i++) {
                ofPoint p = bufferToScreen(i,buffer[i]);
                ofVertex(p);
            }

            if(settings.styles.curve.line.bFill) {
                ofPoint p = bufferToScreen(getSize()-1,0);
                ofVertex(p);
            }

            ofEndShape(settings.styles.curve.line.bFill);

            ofEndShape();
            ofPopStyle();
        
        }
        
        // first point
        if(settings.annotations.markers.first.display) {
            ofPoint p = bufferToScreen(0,buffer[0]);
            ofxDrawStyledPoint(settings.annotations.markers.first.style,p.x,p.y);
        }

        // last point
        if(settings.annotations.markers.last.display) {
            ofPoint p = bufferToScreen(getSize()-1,buffer[getSize()-1]);
            ofxDrawStyledPoint(settings.annotations.markers.last.style,p.x,p.y);
        }
        
        // local min point
        if(settings.annotations.markers.min.display) {
            ofPoint p = bufferToScreen(getMinIndex(),getMin());
            ofxDrawStyledPoint(settings.annotations.markers.min.style,p.x,p.y);
        }
        
        // local max point
        if(settings.annotations.markers.max.display) {
            ofPoint p = bufferToScreen(getMaxIndex(),getMax());
            ofxDrawStyledPoint(settings.annotations.markers.max.style,p.x,p.y);
        }
    }    
    
    // TODO : use non bitmap font if provided
    if(settings.annotations.label.display) {
        ofPushStyle();
        ofSetStyle(settings.annotations.label.style);
        string s = settings.annotations.label.text;
        if(getSize() > 0) {
            ofStringReplace(s, "{V}", ofToString(getLast(),settings.annotations.label.precision));
        }
        ofDrawBitmapString(s, getWidth() + 3, getHeight() / 2 + 6);
        ofPopStyle();
    }
    
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
    Settings::Axis&  xAxis  = settings.axes.x;
    ofRange&         xRange = settings.axes.x.range;

    if(xAxis.autoScale) {
        xRange.min = 0;
        xRange.max = getSize() - 1;
    } else {
        xRange.min = 0;
        xRange.max = settings.width;
    }
    
    if(xAxis.invert) {
        return ofMap(x, xRange.min, xRange.max, getWidth(), 0, xAxis.clip);
    } else {
        return ofMap(x, xRange.min, xRange.max, 0, getWidth(), xAxis.clip);
    }
}

float ofxSparkline::bufferYToScreenY(float y) {
    Settings::Axis&  yAxis  = settings.axes.y;
    ofRange&         yRange = settings.axes.y.range;

    if(yAxis.autoScale) {
        yRange.min = getMin();
        yRange.max = getMax();
    }

    if(yAxis.invert) {
        return ofMap(y,yRange.min,yRange.max,0,getHeight(),yAxis.clip);
    } else {
        return ofMap(y,yRange.min,yRange.max,getHeight(),0,yAxis.clip);
    }
}


