#ifndef SMARTPTR_H
#define SMARTPTR_H

#include <utility>

template <typename T>
class SmartPtr {
 public:
  SmartPtr();
  explicit SmartPtr(T *);
  SmartPtr(const SmartPtr&);
  SmartPtr& operator=(const SmartPtr &);
  ~SmartPtr();

  T* operator->() const;
  T& operator*() const;
  T* get() const;
  int use_count() const;
  bool unique() const;
 private:
  T  *instance_;
  int *reference_num_;
};

#endif //SMARTPTR_H
