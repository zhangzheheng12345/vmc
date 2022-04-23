#include "vmc.h"

namespace vmc {

template<class T> LinearBox<T>::LinearBox(unsigned int size) {
    data = new PtrBox<T>(new T[size]);
    length = size;
}
template<class T> LinearBox<T>::LinearBox(unsigned int size, T* ptr) {
    data = new PtrBox<T>(ptr);
    length = size;
}
template<class T> LinearBox<T>::LinearBox(const LinearBox& origin) {
    if(data) {
        data->Sub();
        if(data->Destroyed()) delete data;
    }
    data = origin.data;
    data->Add();
    length = origin.length;
    copied = false;
}
template<class T> LinearBox<T>::LinearBox(std::initializer_list<T> li) {
    if(data) {
        data->Sub();
        if(data->Destroyed()) delete data;
    }
    data = new PtrBox<T>(new T[li.size()]);
    unsigned int index = 0;
    for(const T& item : li) {
        data->Get()[index] = item;
        index++;
    }
}
template<class T> LinearBox<T>::~LinearBox() {
    data->Sub();
    if(data->Destroyed()) delete data;
}
template<class T> T LinearBox<T>::at(unsigned int index) {
    return data->Get()[index];
}
template<class T> void LinearBox<T>::set(unsigned int index, const T& value) {
    if(copied)
        data->Get()[index] = value;
    else {
        T* tmp = deepCopy();
        tmp[index] = value;
        if(data) {
            data->Sub();
            if(data->Destroyed()) delete data;
        }
        data = new PtrBox<T>(tmp);
    }
}
template<class T> LinearBox<T> LinearBox<T>::clone() {
    return LinearBox(length, deepCopy());
}
template<class T> T* LinearBox<T>::deepCopy() {
    T* res = new T[length];
    T* src = data->Get();
    for(unsigned int i = 0; i < length; i++) res[i] = src[i];
    return res;
}

} // namespace end
