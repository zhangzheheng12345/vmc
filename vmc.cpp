#include "vmc.h"

namespace vmc {

template<class T> LinearBox<T>::LinearBox(int size) {
    data = PtrBox(new T[size]);
    length = size;
}
template<class T> LinearBox<T>::LinearBox(const LinearBox& origin) {
    data = origin.data;
    data->Add();
    length = origin.length;
}

} // namespace end