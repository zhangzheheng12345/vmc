#include "lightest.h"
#define _VMC_LOG_ 0
#include "vmc.h"
using namespace vmc;

MAIN

DEFTEST(TestPtrBox) {
    PtrBox<int> ptr(new int(0));
    REQUIRE(*ptr.Get() == 0);
    ptr.Add();
    REQUIRE(!ptr.Destroyed());
    ptr.Sub(); ptr.Sub();
    REQUIRE(ptr.Destroyed());
}

DEFTEST(TestLinearBox) {
    const unsigned int boxLen = 5;
    vmc::LinearBox<int> box1(boxLen, new int[boxLen] {1, 2, 3, 4, 5});
    vmc::LinearBox<int> box2 = box1;
    vmc::LinearBox<int> box3{1, 2, 3, 4, 5};
    // at & len
    REQUIRE(box1.at(1) == 2);
    REQUIRE(box1.len() == boxLen);
    REQUIRE(box2.at(1) == 2);
    REQUIRE(box2.len() == box1.len());
    REQ_OP(2, box3.at(1), ==);
    REQUIRE(box2.len() == 5);
    // set & clone
    box2.set(1, 3);
    LinearBox<int> box4 = box2.clone();
    box4.set(1, 4);
    REQ_OP(3, box1.at(1), ==);
    REQ_OP(3, box2.at(1), ==);
    REQ_OP(4, box4.at(1), ==);
    // operator== & !=
    REQUIRE(box1 == box2);
    REQUIRE(box2 != box3);
    box1.set(1, 2);
    REQUIRE(box2 == box3);
}

DEFTEST(TestVec) {
    const unsigned int boxLen = 5;
    vmc::Vec<int> box1(boxLen, new int[boxLen] {1, 2, 3, 4, 5});
    vmc::Vec<int> box2 = box1;
    vmc::Vec<int> box3{1, 2, 3, 4, 5};
    vmc::Vec<int> box4 = LinearBox<int>{1, 2, 3, 4, 5};
}
