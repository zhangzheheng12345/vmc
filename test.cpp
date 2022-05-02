#include "vmc.h"
#include "lightest.h"
using namespace vmc;

MAIN

DEFTEST(TestPtrBox) {
    PtrBox<int> ptr(new int(0));
    CHECK(*ptr.Get() == 0);
    ptr.Add();
    CHECK(!ptr.Destroyed());
    ptr.Sub(); ptr.Sub();
    CHECK(ptr.Destroyed());
}

DEFTEST(TestLinearBox) {
    const unsigned int box1Len = 5;
    vmc::LinearBox<int> box1(box1Len, new int[box1Len] {1, 2, 3, 4, 5});
    vmc::LinearBox<int> box2 = box1;
    vmc::LinearBox<int> box3{1, 2, 3, 4, 5};
    // at & len
    CHECK(box1.at(1) == 2);
    CHECK(box1.len() == box1Len);
    CHECK(box2.at(1) == 2);
    CHECK(box2.len() == box1.len());
    CHK_OP(2, box3.at(1), ==);
    CHECK(box2.len() == 5);
    // set & clone
    box2.set(1, 3);
    LinearBox<int> box4 = box2.clone();
    box4.set(1, 4);
    CHK_OP(3, box1.at(1), ==);
    CHK_OP(3, box2.at(1), ==);
    CHK_OP(4, box4.at(1), ==);
    // operator==
    CHECK(box1==box2);
    box1.set(1, 2);
    CHECK(box2==box3);
}
