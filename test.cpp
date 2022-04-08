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
    CHECK(box1.at(1) == 2);
    CHECK(box1.len() == box1Len);
}