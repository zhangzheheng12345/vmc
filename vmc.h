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
            if(count == 0) {
                delete data; data = nullptr;
#ifdef _VMC_LOG_
                std::cout << "Data deleted" << std::endl;
#endif
            }
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
    LinearBox() {}
    LinearBox(unsigned int size);
    LinearBox(unsigned int size, T* ptr);
    LinearBox(const LinearBox&);
    LinearBox(std::initializer_list<T>);
    ~LinearBox();
    T& at(unsigned int index);
    LinearBox<T> clone();
    unsigned int len() { return length; }
    bool operator==(const LinearBox<T>&);
    bool operator!=(const LinearBox<T>& operand) { return !(*this == operand); }
private:
    PtrBox<T>* data = nullptr;
    unsigned int length = 0;
};

// 1D data container
template<class T> class Vec {
public:
    Vec(unsigned int size) { data = LinearBox<T>(size); }
    Vec(unsigned int size, T* data) { this->data = LinearBox<T>(size, data); }
    Vec(const Vec& vec) { data = vec.data; }
    Vec(std::initializer_list<T> li) { data = LinearBox<T>(li); }
    Vec(const LinearBox<T>& box) { data = box; }
    ~Vec() {}
    T& at(int);
    unsigned int len() { return data.len(); }
    bool operator==(const Vec<T>& operand) { return data == operand.data; }
    bool operator!=(const Vec<T>& operand) { return data != operand.data; }
private:
    LinearBox<T> data;
};

// TODO: 2D Mat, 3D Cube

} // namespace end

#include "vmc.cpp"