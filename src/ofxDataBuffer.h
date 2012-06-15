//
//  ofxDataQueue.h
//  ofxSparklines
//
//  Created by Christopher Baker on 6/15/12.
//  Copyright (c) 2012 School of the Art Institute of Chicago. All rights reserved.
//
#pragma once

#include "ofMain.h"
#include <set>

class ofxAbstractDataBuffer{
public:
	virtual ~ofxAbstractDataBuffer(){};
    
};

template<typename ParameterType>
class ofxDataBuffer: public ofxAbstractDataBuffer{
public:
	ofxDataBuffer();
	ofxDataBuffer(size_t v);
	virtual ~ofxDataBuffer(){};
    
    void add(ParameterType v);
    
    void setSize(size_t size) {count = size;}
    size_t getSize()          {return count;}
    
	ParameterType getMin();
	ParameterType getMax();
    
    double getMean();
    double getMedian();
    double getVariance();
    double getStdDev();

    //    ParameterType getHarmonicMean();
    //    ParameterType getGeometricMean();
    //    ParameterType getCorrectedVariance();
    //    ParameterType getCorrectedStandardDeviation();
    //    ParameterType getCoefficientOfVariation();
    //    ParameterType getMeanDeviation();
    //    ParameterType getMedianDeviation();
    //    ParameterType getSkewness();
    
    
    double smooth(double oldValue, ParameterType newValue, double alpha);
    
    void   setSmoothAlpha(double alpha) {smoothAlpha = alpha;}
    double getAlpha()                   {return smoothAlpha;}
    
private:
    deque<ParameterType>  buffer;
    vector<ParameterType> bufferOrdered;
    deque<double>         bufferSmoothed;

    size_t count;

    bool wasCaclulated;
    void calcStats();

    // statistics
    double sum;
    double meanSum;
    double stdDevSum;
    double variance;
    
    double mean;
    double stdDev;
    
    double median;
    
    ParameterType minimum;
    ParameterType maximum;
    
    double smoothAlpha;
    
};

template<typename ParameterType>
ofxDataBuffer<ParameterType>::ofxDataBuffer(){
    count = 100;
    wasCaclulated = false;
    smoothAlpha = 0.95;
}

template<typename ParameterType>
ofxDataBuffer<ParameterType>::ofxDataBuffer(size_t v){
    count = v;
    wasCaclulated = false;
    smoothAlpha = 0.95;
}

template<typename ParameterType>
void ofxDataBuffer<ParameterType>::calcStats(){
    
    if(wasCaclulated) {
        return;
    } else {
        wasCaclulated = true;
    }
    
    sum                = 0.0;
    meanSum            = 0.0;
    stdDevSum          = 0.0;
    variance           = 0.0;
    
    mean               = 0.0;
    stdDev             = 0.0;
    
    minimum            =  numeric_limits<ParameterType>::max();
    maximum            = -numeric_limits<ParameterType>::max();
    
    if(buffer.empty()) return;
    
    int cnt = buffer.size();
    for(int i = 0; i < cnt; ++i) {
        if(i == 0) {
            meanSum = buffer[i];
        } else {
            double stepSum = buffer[i] - meanSum;
            double stepMean = ((i - 1) * stepSum) / i;
            meanSum   += (stepMean);
            stdDevSum += (stepMean * stepSum);
        }
        
        sum += buffer[i];
        
        minimum = MIN(minimum, buffer[i]);
        maximum = MAX(maximum, buffer[i]);
        
        cout << buffer[i] << " << buff" << endl;
        
    }
    
    
    cout << "minimum=" << minimum << endl;
    cout << "maximum=" << maximum << endl;
    
    cout << " sum: " << sum << " - " << cnt << endl;
    
    mean               = sum / cnt;
    cout << "mean=" << mean << endl;
    
    variance           = stdDevSum / (cnt - 1);
    stdDev             = sqrt(variance);
}



template<typename ParameterType>
double ofxDataBuffer<ParameterType>::smooth(double oldValue, ParameterType newValue, double alpha) {
    return oldValue * (1 - alpha) + newValue * alpha;
}


template<typename ParameterType>
void ofxDataBuffer<ParameterType>::add(ParameterType v){
    
    cout << "adding ->" << v << endl;
    
    buffer.push_back(v); // buffer it
    
    bufferOrdered.push_back(v);
    
    if(!bufferSmoothed.empty()) {
        bufferSmoothed.push_back(smooth(bufferSmoothed[bufferSmoothed.size()-1],v,smoothAlpha));
    } else {
        bufferSmoothed.push_back(v);
    }

    if(buffer.size() > count) {
        bufferOrdered.erase(lower_bound(bufferOrdered.begin(), bufferOrdered.end(), buffer.front())); 
        buffer.erase(buffer.begin()); // remove the last one
        bufferSmoothed.erase(bufferSmoothed.begin());
    }
    wasCaclulated = false;
}

template<typename ParameterType>
ParameterType ofxDataBuffer<ParameterType>::getMin(){
    calcStats();
    return minimum;
}

template<typename ParameterType>
ParameterType ofxDataBuffer<ParameterType>::getMax(){
    calcStats();
    return maximum;
}

template<typename ParameterType>
double ofxDataBuffer<ParameterType>::getMean(){
    calcStats();
    return mean;
}

template<typename ParameterType>
double ofxDataBuffer<ParameterType>::getMedian(){

    sort(bufferOrdered.begin(), bufferOrdered.end()); // sort it
    
    if(bufferOrdered.size() % 2 == 0) { // is even
        // even
        
    } else {
        // odd
        
    }
    
    
    return median;
}

template<typename ParameterType>
double ofxDataBuffer<ParameterType>::getVariance(){
    calcStats();
    return variance;
}

template<typename ParameterType>
double ofxDataBuffer<ParameterType>::getStdDev(){
    calcStats();
    return stdDev;
}

//    ParameterType getHarmonicMean();
//    ParameterType getGeometricMean();
//    ParameterType getCorrectedVariance();
//    ParameterType getCorrectedStandardDeviation();
//    ParameterType getCoefficientOfVariation();
//    ParameterType getMeanDeviation();
//    ParameterType getMedianDeviation();
//    ParameterType getSkewness();