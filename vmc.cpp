#include "vmc.h"

namespace vmc {

template<class T> LinearBox<T>::LinearBox(unsigned int size) {
    data = new PtrBox<T>(new T[size]);
    length = size;
    copied = true;
}
template<class T> LinearBox<T>::LinearBox(unsigned int size, T* ptr) {
    data = new PtrBox<T>(ptr);
    length = size;
    copied = true;
}
template<class T> LinearBox<T>::LinearBox(const LinearBox& origin) {
    data = origin.data;
    data->Add();
    length = origin.length;
    copied = false;
}
template<class T> LinearBox<T>::~LinearBox() {
    data->Sub();
    if(data->Destroyed()) delete data;
}
template<class T> T LinearBox<T>::at(unsigned int index) {
    return data->Get()[index];
}
template<class T> void LinearBox<T>::set(unsigned int index, const T& value) {
    *(data->Get()) = value;
}

} // namespace end