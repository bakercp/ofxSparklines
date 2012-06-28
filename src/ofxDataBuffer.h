//
//  ofxDataQueue.h
//  ofxSparklines
//
//  Created by Christopher Baker on 6/15/12.
//  Copyright (c) 2012 School of the Art Institute of Chicago. All rights reserved.
//
#pragma once

#include <vector>
#include <set>

template<typename T>
class ofxDataBuffer_ {
public:
    ofxDataBuffer_();
    ofxDataBuffer_(size_t maxSize);
    ofxDataBuffer_(const vector<T>& data);
    ofxDataBuffer_(T* data, int length);
	
	virtual ~ofxDataBuffer_();
    
    deque<T>& getBuffer();
    
    void push_back(const T& data,      bool expand = false);
    void push_back(const vector<T>& v, bool expand = false);
    void push_back(T* v, int length,   bool expand = false);
 
    void   setMaxSize(size_t _maxSize);
    size_t getMaxSize();
    
    size_t getSize();
    
    // buffer statistics
    void calcStats();
    bool statsValid;
    
    T      getMin();
	T      getMax();
    
    double getSum();
    double getProduct();
    double getMean();
    double getHarmonicMean();
    double getGeometricMean();
    double getVariance();
    double getStdDev();
    double getPopulationVariance();
    double getPopulationStdDev();
    
    double getMedian();
    
protected:

    deque<T> buffer;

    size_t maxSize;

    // statistics
    double sum;
    double product;
    double variance;
    double variancePopulation;
    
    double mean;
    double harmMean;
    double geoMean;
    double stdDev;
    double stdDevPopulation;
    
    T minimum;
    T maximum;
    
};

template<typename T>
ofxDataBuffer_<T>::ofxDataBuffer_(){
    maxSize        = 1;
    statsValid     = false;
}

template<typename T>
ofxDataBuffer_<T>::ofxDataBuffer_(size_t _maxSize){
    maxSize        = _maxSize;
    statsValid     = false;
}

template<typename T>
ofxDataBuffer_<T>::ofxDataBuffer_(const vector<T>& data){
    maxSize        = data.size();
    statsValid     = false;
    push_back(data,true);
}

template<typename T>
ofxDataBuffer_<T>::ofxDataBuffer_(T* data, int length){
    maxSize        = length;
    statsValid     = false;
    push_back(data,length,true);
}

template<typename T>
ofxDataBuffer_<T>::~ofxDataBuffer_(){}


template<typename T>
deque<T>& ofxDataBuffer_<T>::getBuffer(){
    return buffer;
}

template<typename T>
void ofxDataBuffer_<T>::calcStats(){
    
    if(statsValid) {
        return;
    } else {
        statsValid = true;
    }
    
    sum         = 0.0;
    product     = 0.0;
    variance    = 0.0;
    mean        = 0.0;
    harmMean    = 0.0;
    geoMean     = 0.0;
    stdDev      = 0.0;
    minimum     = 0.0;
    maximum     = 0.0;

    
    if(buffer.empty()) return;
    
    bool hasNegativeValues = false;
    
    int    n      = 0;
    double delta  = 0.0;
    double M2     = 0.0;
    double invSum = 0.0;
    
    for(size_t i = 0; i < buffer.size(); ++i) {
        T         value = buffer[i];
        double invValue = 1.0 / value;
        if(value < 0) hasNegativeValues = true;

        n = n+1;
        
        if(i == 0) {
            sum       = value;
            product   = value;
            invSum    = invValue;
            minimum   = value;
            maximum   = value;
        } else {
            sum      += value;
            product  *= value;
            invSum   += invValue;
            minimum  = MIN(minimum, value);
            maximum  = MAX(maximum, value);
        }

        
        delta = value - mean;
        mean  = mean + delta/n;
        M2    = M2 + delta * (value - mean);

    }
    
    harmMean           = hasNegativeValues ? -1 : (n / invSum);
    geoMean            = hasNegativeValues ? -1 : pow(product, 1.0 / n);

    variancePopulation = M2 / (n);
    variance           = M2 / (n - 1);

    stdDevPopulation   = sqrt(variancePopulation);
    stdDev             = sqrt(variance);
}

template<typename T>
void ofxDataBuffer_<T>::push_back(const T& data, bool expand){
    
    buffer.push_back(data); // buffer it

    if(buffer.size() > maxSize) {
        buffer.erase(buffer.begin()); // remove the last one
    }
    
    statsValid = false;
}

template<typename T>
void ofxDataBuffer_<T>::push_back(const vector<T>& data, bool expand) {
    for(int i = 0; i < (int)data.size(); i++) push_back(data[i], expand);
}


template<typename T>
void ofxDataBuffer_<T>::push_back(T* data, int length, bool expand) {
    for(int i = 0; i < length; i++) push_back(data[i], expand);
}

template<typename T>
void ofxDataBuffer_<T>::setMaxSize(size_t _maxSize) {
    maxSize = _maxSize;

    // will remove values on next
    while(buffer.size() > maxSize) {
        buffer.erase(buffer.begin()); // remove the last one
        statsValid = false;
    }
}

template<typename T>
size_t ofxDataBuffer_<T>::getMaxSize() {
    return maxSize;
}

template<typename T>
size_t ofxDataBuffer_<T>::getSize() {
    return buffer.size();
}

template<typename T>
T ofxDataBuffer_<T>::getMin(){
    calcStats();
    return minimum;
}

template<typename T>
T ofxDataBuffer_<T>::getMax(){
    calcStats();
    return maximum;
}

template<typename T>
double ofxDataBuffer_<T>::getSum(){
    calcStats();
    return sum;
}

template<typename T>
double ofxDataBuffer_<T>::getProduct(){
    calcStats();
    return product;
}

template<typename T>
double ofxDataBuffer_<T>::getMean(){
    calcStats();
    return mean;
}

template<typename T>
double ofxDataBuffer_<T>::getHarmonicMean(){
    calcStats();
    return harmMean;
}

template<typename T>
double ofxDataBuffer_<T>::getGeometricMean(){
    calcStats();
    return geoMean;
}

template<typename T>
double ofxDataBuffer_<T>::getMedian(){
    // median is not cached
     
    deque<T> bufferCopy = buffer;
    size_t size = bufferCopy.size();
    int    n    = size / 2;

    std::nth_element(bufferCopy.begin(), bufferCopy.begin()+n, bufferCopy.end());
    double med = bufferCopy[n];
    
    if(size % 2 != 0) { // odd
        return med;
    } else { // even
        std::nth_element(bufferCopy.begin(), bufferCopy.begin()+(n - 1), bufferCopy.end());
        return (med + bufferCopy[n - 1]) / 2.0;
    }
}

template<typename T>
double ofxDataBuffer_<T>::getVariance(){
    calcStats();
    return variance;
}

template<typename T>
double ofxDataBuffer_<T>::getStdDev(){
    calcStats();
    return stdDev;
}

template<typename T>
double ofxDataBuffer_<T>::getPopulationVariance(){
    calcStats();
    return variancePopulation;
}

template<typename T>
double ofxDataBuffer_<T>::getPopulationStdDev(){
    calcStats();
    return stdDevPopulation;
}


typedef ofxDataBuffer_<char>   ofxCharDataBuffer;
typedef ofxDataBuffer_<float>  ofxFloatDataBuffer;
typedef ofxDataBuffer_<float>  ofxDataBuffer;
typedef ofxDataBuffer_<double> ofxDoubleDataBuffer;
typedef ofxDataBuffer_<int>    ofxIntDataBuffer;
typedef ofxDataBuffer_<long>   ofxLongDataBuffer;

// http://stackoverflow.com/questions/3903538/online-algorithm-for-calculating-absolute-deviation
// http://www.johndcook.com/standard_deviation.html
// http://stackoverflow.com/questions/1058813/on-line-iterator-algorithms-for-estimating-statistical-median-mode-skewnes
// http://en.wikipedia.org/wiki/Algorithms_for_calculating_variance
// http://www.codecogs.com/code/statistics/moments/statistics.php //rt
// http://www.codecogs.com/code/statistics/moments/index.php

