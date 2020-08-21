//
//  RingBuffer.hpp
//
//  Created by Kyle Price on 8/20/20.
//

#ifndef RingBuffer_hpp
#define RingBuffer_hpp

#include <stdio.h>
#include <deque>
#include <memory>
#include <ostream>
#include <algorithm>
#include "IRingBuffer.hpp"

namespace Pricetec {
    template<typename T>
    class SimpleRingBuffer : public IRingBuffer<T> {
        public:
            class iterator;
        
        private:
            std::deque<T> buffer;
            size_t bufferSize;
            
        public:
            SimpleRingBuffer(size_t size) : bufferSize(size) { }
        
            SimpleRingBuffer(const SimpleRingBuffer &other) = delete;
            SimpleRingBuffer &operator=(const SimpleRingBuffer &other) = delete;
        
            iterator begin() {
                return iterator(0, *this);
            }
        
            iterator end() {
                return iterator(this->bufferSize, *this);
            }
            
            void add(T newVal) override {
                if (this->buffer.size() == this->bufferSize) {
                    this->buffer.pop_front();
                }
                
                this->buffer.push_back(newVal);
            }
        
            T &getAt(size_t idx) override {
                return this->buffer[idx];
            }
        
            std::vector<T> getFirst(int numElements) override {
                numElements = std::min(numElements, static_cast<int>(this->buffer.size()));
                std::vector<T> values;
                
                for (int i = 0; i < numElements; i++) {
                    values.push_back(this->buffer[i]);
                }
                
                return values;
            }
        
            size_t size() override {
                return this->bufferSize;
            }
        
            bool empty() override {
                return this->buffer.empty();
            }
        
            bool operator==(SimpleRingBuffer &other) {
                return this->buffer == other.buffer;
            }
    };
    
    
    template<typename T>
    class SimpleRingBuffer<T>::iterator {
        private:
            size_t curPosition;
            SimpleRingBuffer &buffer;
        
        public:
            iterator(size_t startingPos, SimpleRingBuffer &buffer) :
                curPosition(startingPos), buffer(buffer) {};
            
            iterator &operator++(int) {
                this->curPosition++;
                
                return *this;
            }
            
            iterator &operator++() {
                this->curPosition++;
                
                return *this;
            }
            
            iterator &operator--(int) {
                this->curPosition--;
                
                return *this;
            }
            
            iterator &operator--() {
                this->curPosition--;
                
                return *this;
            }
            
            iterator &operator+=(int incVal) {
                this->curPosition += incVal;
                
                return *this;
            }
            
            bool operator==(iterator &other) {
                if (this->buffer == other.buffer) {
                    return this->curPosition == other.curPosition;
                }
                
                return false;
            }
            
            bool operator!=(iterator &other) {
                return !(*this == other);
            }
            
            T &operator*() {
                return this->buffer.getAt(this->curPosition);
            }
    };
}

#endif
