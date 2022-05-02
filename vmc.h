#pragma once

#include <iostream> // Just for std

namespace vmc {

// A ptr wrapper, make GC easier & prettier for LinearBox
template<class T> class PtrBox {
public:
    PtrBox(T* ptr) {
        data = ptr;
        count = 1;
    }
    T* Get() { return data; }
    void Add() { count++; }
    void Sub() {
        if(count){
            count--;
            if(count == 0) { delete data; data = nullptr; }
        }
    }
    bool Destroyed() { return !count; }
private:
    T* data;
    unsigned int count;
};

// A basic 1D linear data container
template<class T> class LinearBox {
public:
    LinearBox(unsigned int size);
    LinearBox(unsigned int size, T* ptr);
    LinearBox(const LinearBox&);
    LinearBox(std::initializer_list<T>);
    ~LinearBox();
    T at(unsigned int index);
    void set(unsigned int index, const T& value);
    LinearBox<T> clone();
    unsigned int len() { return length; }
    bool operator==(const LinearBox<T>&);
private:
    PtrBox<T>* data = nullptr;
    unsigned int length;
};

// 1D data container
template<class T> class Vec {
public:
    Vec() {}
    ~Vec() {}
private:
    LinearBox<T> data;
};

// TODO: 2D Mat, 3D Cube

} // namespace end

#include "vmc.cpp"