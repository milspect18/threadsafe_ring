//
//  TSRingBufferDecorator.hpp
//
//  Created by Kyle Price on 8/21/20.
//

#ifndef TSRingBufferDecorator_h
#define TSRingBufferDecorator_h

#include <mutex>
#include <condition_variable>
#include "IRingBuffer.hpp"

namespace Pricetec {
    template<typename T>
    class TSRingBufferDecorator : public IRingBuffer<T> {
        private:
            std::unique_ptr<IRingBuffer<T>> bufPtr;
            mutable std::mutex bufMutex;
            std::condition_variable conditionVariable;
        
        public:
            class iterator;
        
        public:
            explicit TSRingBufferDecorator(IRingBuffer<T> *bufPtr) : bufPtr{bufPtr} {}
        
            TSRingBufferDecorator(const TSRingBufferDecorator &other) = delete;
            TSRingBufferDecorator &operator=(const TSRingBufferDecorator &other) = delete;
        
            iterator begin() {
                return iterator(0, *this);
            }
        
            iterator end() {
                return iterator(this->bufPtr->size(), *this);
            }
        
            void add(T newVal) override {
                std::lock_guard<std::mutex> lock(this->bufMutex);
                this->bufPtr->add(newVal);
                this->conditionVariable.notify_one();
            }
            
            T &getAt(size_t idx) override {
                std::unique_lock lock(this->bufMutex);
                this->conditionVariable.wait(lock, [this]{ return !this->bufPtr->empty(); });
                
                return this->bufPtr->getAt(idx);
            }
            
            std::vector<T> getFirst(int numElements) override {
                std::unique_lock lock(this->bufMutex);
                this->conditionVariable.wait(lock, [this]{ return !this->bufPtr->empty(); });
                
                return this->bufPtr->getFirst(numElements);
            }
            
            size_t size() override {
                std::lock_guard<std::mutex> lock(this->bufMutex);
                
                return this->bufPtr->size();
            }
        
            bool empty() override {
                std::lock_guard<std::mutex> lock(this->bufMutex);
                
                return this->bufPtr->empty();
            }
        
            bool operator==(TSRingBufferDecorator<T> &other) {
                std::lock_guard<std::mutex> lock(this->bufMutex);
                
                return this->bufPtr == other.bufPtr;
            }
    };
    
    template<typename T>
    class TSRingBufferDecorator<T>::iterator {
        private:
            size_t curPosition;
            TSRingBufferDecorator &buffer;
        
        public:
            iterator(size_t startingPos, TSRingBufferDecorator &buffer) :
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
