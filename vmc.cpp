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
}
template<class T> LinearBox<T>::LinearBox(std::initializer_list<T> li) {
    if(data) {
        data->Sub();
        if(data->Destroyed()) delete data;
    }
    data = new PtrBox<T>(new T[li.size()]);
    length = li.size();
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
    data->Get()[index] = value;
}
template<class T> LinearBox<T> LinearBox<T>::clone() {
    T* res = new T[length];
    T* src = data->Get();
    for(unsigned int i = 0; i < length; i++) res[i] = src[i];
    return LinearBox(length, res);
}
template<class T> bool LinearBox<T>::operator==(const LinearBox<T>& operand) {
    if(operand.length != length) return false;
    if(operand.data->Get() == data->Get()) return true;
    T* operandPtr = operand.data->Get(), *thisPtr = data->Get();
    for(unsigned int i = 0; i < length; i++) if(operandPtr[i] != thisPtr[i]) return false;
    return true;
}

} // namespace end
