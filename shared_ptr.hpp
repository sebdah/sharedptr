#include <stddef.h>

template <class T>
class SharedPtr {
  private:
    T* ptr;

    void common_init();
    void free();
    bool has_ptr();
    void set_ptr(T*);
  public:
    int* use_count;
    SharedPtr<T>();
    SharedPtr<T>(T*);
    SharedPtr<T>(SharedPtr&);
    ~SharedPtr<T>();

    void operator=(SharedPtr&);
    bool operator==(T*);
    bool operator==(SharedPtr&);
    bool operator<(T*);
    bool operator<(SharedPtr&);
    T& operator*();
    T* operator->();
    explicit operator bool();

    T* get();
    int get_use_count();
    void reset(T*);
    void set_use_count(int);
    bool unique();
};

template <class T>
SharedPtr<T>::SharedPtr() {
  use_count = new int(-1);
  set_ptr(nullptr);
}

template <class T>
SharedPtr<T>::SharedPtr(T* ptr) {
  use_count = new int(1);
  set_ptr(ptr);
}

template <class T>
SharedPtr<T>::SharedPtr(SharedPtr<T>& shared_ptr) {
  use_count = new int(-1);
  *this = shared_ptr;
}

template <class T>
SharedPtr<T>::~SharedPtr() {
  free();
}

template <class T>
void SharedPtr<T>::operator=(SharedPtr<T>& shared_ptr) {
  set_ptr(shared_ptr.get());
  delete use_count;
  use_count = shared_ptr.use_count;
  set_use_count(get_use_count() + 1);
}

template <class T>
bool SharedPtr<T>::operator==(T* cmpPtr) {
  if (ptr == cmpPtr) {
    return true;
  }

  return false;
}

template <class T>
bool SharedPtr<T>::operator==(SharedPtr<T>& shared_ptr) {
  if (ptr == shared_ptr.get()) {
    return true;
  }

  return false;
}

template <class T>
bool SharedPtr<T>::operator<(T* cmpPtr) {
  if (ptr < cmpPtr) {
    return true;
  }

  return false;
}

template <class T>
SharedPtr<T>::operator bool() {
  if (ptr != nullptr) {
    return true;
  }

  return false;
}

template <class T>
bool SharedPtr<T>::operator<(SharedPtr<T>& shared_ptr) {
  if (ptr < shared_ptr.get()) {
    return true;
  }

  return false;
}

template <class T>
T& SharedPtr<T>::operator*() {
  return *ptr;
}

template <class T>
T* SharedPtr<T>::operator->() {
  return ptr;
}

template <class T>
void SharedPtr<T>::common_init() {
  set_ptr(nullptr);
  use_count = new int(0);
}

template <class T>
void SharedPtr<T>::free() {
  if (get_use_count() == 1) {
    delete use_count;
    delete ptr;
  } else if (get_use_count() == -1) {
    delete use_count;
  } else {
    set_use_count(get_use_count() - 1);
  }
}

template <class T>
T* SharedPtr<T>::get() {
  return ptr;
}

template <class T>
int SharedPtr<T>::get_use_count() {
  return *use_count;
}

template <class T>
bool SharedPtr<T>::has_ptr() {
  if (ptr) {
    return true;
  }

  return false;
}

template <class T>
void SharedPtr<T>::reset(T* newPtr) {
  delete use_count;
  use_count = new int(1);
  delete ptr;
  set_ptr(newPtr);
}

template <class T>
void SharedPtr<T>::set_ptr(T* ptr) {
  this->ptr = ptr;
}

template <class T>
void SharedPtr<T>::set_use_count(int count) {
  *use_count = count;
}

template <class T>
bool SharedPtr<T>::unique() {
  if (get_use_count() == 1) {
    return true;
  }

  return false;
}
