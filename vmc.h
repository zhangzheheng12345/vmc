#pragma once

namespace vmc {

template<class T> class PtrBox {
public:
    PtrBox(T* ptr) {
        data = ptr;
    }
    void Add() {
        count++;
    }
    void Sub() {
        if(count){
            count--;
            if(count == 0) delete data;
        }
    }
    bool Destroyed() {
        return !count;
    }
private:
    T* data;
    unsigned int count;
};

template<class T> class LinearBox {
public:
    LinearBox(int);
    LinearBox(const LinearBox&);
    ~LinearBox();
    T& at(unsigned int);
    unsigned int len();
private:
    PtrBox<T>* data;
    unsigned int length;
};

template<class T> class Vec {
public:
    Vec() {}
    ~Vec() {}
private:
    LinearBox<T> data;
};

} // namespace end
