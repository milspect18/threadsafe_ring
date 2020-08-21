//
//  IRingBuffer.hpp
//
//  Created by Kyle Price on 8/21/20.
//

#ifndef IRingBuffer_hpp
#define IRingBuffer_hpp

#include <vector>

namespace Pricetec
{
    template <typename T>
    class IRingBuffer {
        public:
            class iterator;

        public:
            virtual ~IRingBuffer(){};

            virtual void add(T newVal) = 0;
            virtual T &getAt(size_t idx) = 0;
            virtual std::vector<T> getFirst(int numElements) = 0;
            virtual size_t size() = 0;
            virtual bool empty() = 0;
    };
}

#endif
