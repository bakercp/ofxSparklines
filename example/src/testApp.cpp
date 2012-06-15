#include "testApp.h"


testApp::~testApp() {
}

//--------------------------------------------------------------
void testApp::setup(){
    
    cout << "Minimum value for int: " << numeric_limits<int>::min() << endl;
    cout << "Maximum value for int: " << numeric_limits<int>::max() << endl;

    cout << "Maximum value for int: " << -(numeric_limits<int>::max()) << endl;

    cout << "Minimum value for float: " << numeric_limits<float>::min() << endl;
    cout << "Maximum value for float: " << numeric_limits<float>::max() << endl;

    cout << "Minimum value for double: " << numeric_limits<double>::min() << endl;
    cout << "Maximum value for double: " << numeric_limits<double>::max() << endl;
    
    
    intBuffer.setSize(100);
    intBuffer.add(-3);
    intBuffer.add(4);
    intBuffer.add(2);
    intBuffer.add(1);
    intBuffer.add(7);
    intBuffer.add(3);
    intBuffer.add(5);
    intBuffer.add(0);
    intBuffer.add(8);
    intBuffer.add(6);
    intBuffer.add(9);
    intBuffer.add(33);

    cout << "  Max:" << intBuffer.getMax() << endl;
    cout << "  Min:" << intBuffer.getMin() << endl;
    cout << " Mean:" << intBuffer.getMean() << endl;
    cout << "  Med:" << intBuffer.getMedian() << endl;
    cout << "Stdev:" << intBuffer.getStdDev() << endl;
    cout << "  Var:" << intBuffer.getVariance() << endl;
    
    
//    floatBuffer;
//    doubleBuffer;

    
    
}

//--------------------------------------------------------------
void testApp::update() {
}

//--------------------------------------------------------------
void testApp::draw(){
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
