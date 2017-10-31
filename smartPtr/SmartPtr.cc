#include "SmartPtr.h"

template <typename T>
SmartPtr<T>::SmartPtr() :instance_(nullptr), reference_num_(new int(1)){};

template <typename T>
SmartPtr<T>::SmartPtr(T *instance) :instance_(instance), reference_num_(new int(1)){};

template <typename T>
SmartPtr<T>::SmartPtr(const SmartPtr &ptr) : instance_(ptr.instance_), reference_num_(ptr.reference_num_){
  (*reference_num_)++;
}

template <typename T>
SmartPtr<T>& SmartPtr<T>::operator=(const SmartPtr &ptr) {
  if (this != &ptr) {
    if (--*reference_num_ == 0) {
      delete instance_;
      delete reference_num_;
    }
    instance_ = ptr.instance_;
    reference_num_ = ptr.reference_num_;
    (*reference_num_)++;
  }
  return *this;
}

template <typename T>
SmartPtr<T>::~SmartPtr() {  // may have bug
  if (--*reference_num_ == 0) {
    delete instance_;
    delete reference_num_;
    instance_ = nullptr;
    reference_num_ = nullptr;
  }
}

template <typename T, typename ...Args>
SmartPtr<T>& make_share(Args &&args) {
  SmartPtr<T> smartPtr(new T(std::forward<Args>(args)...));
  return smartPtr;
};

template <typename T>
T& SmartPtr<T>::operator*() const {
  return *instance_;
}

template <typename T>
T* SmartPtr<T>::operator->() const {
  return instance_;
}

template <typename T>
T* SmartPtr<T>::get() const {
  return instance_;
}

template <typename T>
int SmartPtr<T>::use_count() const {
  return *reference_num_;
}

template <typename T>
bool SmartPtr<T>::unique() const {
  return use_count() == 1;
}
