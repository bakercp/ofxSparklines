#include "testApp.h"


testApp::~testApp() {
}

//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(60);
    ofSetVerticalSync(true);

//    ofRange floatRange0(-10.9,99.9);
//    ofRange floatRange1(-99.9,10.9);
//    
//    cout << floatRange0 << endl;
//    cout << floatRange1 << endl;
//    
//    cout << (floatRange0 - floatRange1) << endl;
//    cout << (floatRange0 + floatRange1) << endl;
//    
//    ofRange r = floatRange0;
//    r+= floatRange1;
//    cout << (r) << endl;
//    
//    vector<float> nums;
//    nums.push_back(-11);
//    nums.push_back(-22);
//    nums.push_back(22);
//    nums.push_back(33);
//    nums.push_back(-33);
//    nums.push_back(-33);
//    nums.push_back(-44);
//    nums.push_back(44);
//    nums.push_back(11);
//    
//    ofxDataBuffer db0(nums);
//    cout << "Count    : " << db0.getSize() << endl;
//    cout << "Sum      : " << db0.getSum() << endl;
//    cout << "Median   : " << db0.getMedian() << endl;
//    cout << "Mean     : " << db0.getMean() << endl;
//    cout << "Max      : " << db0.getMax() << endl;
//    cout << "Min      : " << db0.getMin() << endl;
//    cout << "Product  : " << db0.getProduct() << endl;
//    cout << "Geo Mean : " << db0.getGeometricMean() << endl;
//    cout << "Harm Mean: " << db0.getHarmonicMean() << endl;
//    cout << "Var      : " << db0.getVariance() << endl;
//    cout << "StdDev   : " << db0.getStdDev() << endl;
//    cout << "PopVar   : " << db0.getPopulationVariance() << endl;
//    cout << "PopStdDev: " << db0.getPopulationStdDev() << endl;
//
//    
    
    
//    ofRange_<double> doubleRange;
//   ofRange_<int> intRange;

    
    
//    intBuffer.setSize(100);
//    intBuffer.push_back(-3);
//    intBuffer.push_back(4);
//    intBuffer.push_back(2);
//    intBuffer.push_back(1);
//    intBuffer.push_back(7);
//    intBuffer.push_back(3);
//    intBuffer.push_back(5);
//    intBuffer.push_back(0);
//    intBuffer.push_back(8);
//    intBuffer.push_back(6);
//    intBuffer.push_back(9);
//    intBuffer.push_back(33);
//
//    cout << "  Max:" << intBuffer.getMax() << endl;
//    cout << "  Min:" << intBuffer.getMin() << endl;
//    cout << " Mean:" << intBuffer.getMean() << endl;
//    cout << "  Med:" << intBuffer.getMedian() << endl;
//    cout << "Stdev:" << intBuffer.getStdDev() << endl;
//    cout << "  Var:" << intBuffer.getVariance() << endl;
//    
    
//    floatBuffer;
//    doubleBuffer;

    //ofImage_<int> image;
    
    ofxSparkline::Settings settings;
    settings.height = 15;
        
    settings.xInvert = false;
    
    settings.yRange.set(0,1);
    settings.yAutoScale = false;
    settings.yClip = false;//true;
    settings.yInvert = false;
    settings.styles.box.fill.render= false;//true;
    settings.styles.box.fill.color = ofColor(0,30);

    settings.styles.line.smoothing = false;
    
    settings.styles.normalRangeBox.fill.render = true;
    
    settings.styles.label.render = true;
    settings.styles.label.bFill = false;
    settings.styles.label.color = ofColor(0);
    
    //settings.styles.underLine.render = true;
    
    settings.styles.localMinPoint.render = true;
    settings.styles.localMinPoint.stroke.render = true;

    settings.styles.firstPoint.render = false;
    settings.styles.firstPoint.stroke.render = true;
    settings.styles.lastPoint.render = true;
    settings.styles.lastPoint.stroke.render = true;
    //settings.styles.line.bFill = true;
    //settings.styles.line.smoothing = false;
    
    
    
    for(int i = 0; i < 266; i++) {
        x.push_back(ofRandom(100));
        settings.normalRange = ofRange(ofRandom(1),ofRandom(1)); 
        sparkLines.push_back(ofxSparkline(settings,100));
    }
}

//--------------------------------------------------------------
void testApp::update() {
    for(int i = 0; i < x.size(); i++) {
        x[i]+=ofRandom(.001,.1);
        
        float f = ofNoise(x[i]);
        
        sparkLines[i].push_back(f);
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(255);
    float padX = 46;
    float padY = 5;
    float currentX = padY;
    float currentY = padY;
    for(int i = 0; i < sparkLines.size(); i++) {
        sparkLines[i].draw(currentX,currentY);

        currentY += sparkLines[i].getHeight() + padY;;
        if((currentY + sparkLines[i].getHeight())> ofGetHeight()) {
            currentY = padY;
            currentX += sparkLines[i].getWidth() + padX;
        }
    }
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
