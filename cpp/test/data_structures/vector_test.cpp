#include <gtest/gtest.h>
#include "../../src/data_structures/vector.h"
#include <string>

class VectorTest : public ::testing::Test {
protected:
    dev::vector<int> intVector;
    dev::vector<std::string> stringVector;
};

TEST_F(VectorTest, InitialCapacity) {
    EXPECT_EQ(intVector.capacity(), 4);
    EXPECT_EQ(intVector.size(), 0);
    EXPECT_FALSE(intVector.is_full());
}

TEST_F(VectorTest, PushBackIntegers) {
    intVector.push_back(1);
    intVector.push_back(2);
    intVector.push_back(3);
    
    EXPECT_EQ(intVector.size(), 3);
    EXPECT_EQ(intVector[0], 1);
    EXPECT_EQ(intVector[1], 2);
    EXPECT_EQ(intVector[2], 3);
}

TEST_F(VectorTest, Resize) {
    // Fill the vector to capacity
    for (int i = 0; i < 4; i++) {
        intVector.push_back(i);
    }
    
    EXPECT_EQ(intVector.size(), 4);
    EXPECT_EQ(intVector.capacity(), 4);
    EXPECT_TRUE(intVector.is_full());
    
    // Add one more to trigger resize
    intVector.push_back(4);
    
    EXPECT_EQ(intVector.size(), 5);
    EXPECT_EQ(intVector.capacity(), 8); // Doubled
    EXPECT_FALSE(intVector.is_full());
    
    // Verify all values are still correct
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(intVector[i], i);
    }
}

TEST_F(VectorTest, Clear) {
    intVector.push_back(1);
    intVector.push_back(2);
    
    EXPECT_EQ(intVector.size(), 2);
    
    intVector.clear();
    
    EXPECT_EQ(intVector.size(), 0);
    EXPECT_FALSE(intVector.is_full());
    // Capacity should remain unchanged
    EXPECT_EQ(intVector.capacity(), 4);
}

TEST_F(VectorTest, Reserve) {
    EXPECT_EQ(intVector.capacity(), 4);

	intVector.push_back(0);
    intVector.reserve(10);
    
    EXPECT_EQ(intVector.capacity(), 10);
    EXPECT_EQ(intVector.size(), 1);
}

TEST_F(VectorTest, StringVector) {
    stringVector.push_back("Hello");
    stringVector.push_back("World");
    
    EXPECT_EQ(stringVector.size(), 2);
    EXPECT_EQ(stringVector[0], "Hello");
    EXPECT_EQ(stringVector[1], "World");
}

// Test with a class that tracks construction/destruction
class Counter {
public:
    static int instances;
    
    Counter() { instances++; }
    Counter(const Counter&) { instances++; }
    Counter(Counter&&) noexcept { instances++; }
    ~Counter() { instances--; }
};

int Counter::instances = 0;

TEST(VectorCounterTest, ProperDestruction) {
    Counter::instances = 0;
    {
        dev::vector<Counter> counterVec;
        counterVec.push_back(Counter{});
        counterVec.push_back(Counter{});
        counterVec.push_back(Counter{});
        
        EXPECT_EQ(Counter::instances, 3);
        
        counterVec.clear();
        EXPECT_EQ(Counter::instances, 0);
        
        // Add more and make sure they're destroyed with the vector
        counterVec.push_back(Counter{});
        EXPECT_EQ(Counter::instances, 1);
    }
    // Vector is destroyed, all counters should be destroyed
    EXPECT_EQ(Counter::instances, 0);
}
