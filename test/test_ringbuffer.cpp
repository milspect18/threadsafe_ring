#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include <vector>
#include "RingBuffer.hpp"

TEST_CASE( "Test single thread operations", "[SimpleRingBuffer]" ) {
    using namespace Pricetec;

    const auto BUFFER_CAPACITY = 5;
    SimpleRingBuffer<int> testSimpleBuffer(BUFFER_CAPACITY);

    SECTION("Test buffer creation") {
        REQUIRE(testSimpleBuffer.empty());
        REQUIRE(testSimpleBuffer.size() == BUFFER_CAPACITY);
    }

    SECTION("Test adding data to buffer") {
        int testIdx = 0;
        std::vector<int> fillerData{1, 2, 3, 4, 5};

        for (const auto &fill : fillerData) {
            testSimpleBuffer.add(fill);
        }

        for (const auto &val : testSimpleBuffer) {
            REQUIRE(val == fillerData[testIdx++]);
        }
    }

    SECTION("Test data wrap") {
        int testIdx = 0;
        std::vector<int> fillerData{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        std::vector<int> wrappedFill{6, 7, 8, 9, 10};

        for (const auto &fill : fillerData) {
            testSimpleBuffer.add(fill);
        }

        for (const auto &val : testSimpleBuffer) {
            REQUIRE(val == wrappedFill[testIdx++]);
        }
    }
}
