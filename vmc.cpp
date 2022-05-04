#include "vmc.h"

namespace vmc {

template<class T> LinearBox<T>::LinearBox(unsigned int size) {
#ifdef _VMC_LOG_
    std::cout << "Data allocated" << std::endl;
#endif
    data = new PtrBox<T>(new T[size]);
    length = size;
}
template<class T> LinearBox<T>::LinearBox(unsigned int size, T* ptr) {
#ifdef _VMC_LOG_
    std::cout << "Data allocated" << std::endl;
#endif
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
#ifdef _VMC_LOG_
    std::cout << "Data allocated" << std::endl;
#endif
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
template<class T> T& LinearBox<T>::at(unsigned int index) {
    return data->Get()[index];
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
template<class T> T& Vec<T>::at(int index) {
        if(index > 0) {
            if(index < data.len()) return data.at(index);
            // TODO: Use self defined error type
            else throw "Index out of range in Vec";
        } else {
            int absIndex = data.len() + index;
            if(absIndex > 0) return data.at(absIndex);
            else throw "Minus index out of range in Vec";
        }
    }

} // namespace end
