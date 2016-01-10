#include <iostream>
#include <stddef.h>

template <class T>
class SharedPtr {
  private:
    bool debug;
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
    void set_debug(bool);
    void set_use_count(int);
    bool unique();
};

template <class T>
SharedPtr<T>::SharedPtr() {
  set_debug(true);
  use_count = new int(-1);
  set_ptr(nullptr);
}

template <class T>
SharedPtr<T>::SharedPtr(T* ptr) {
  set_debug(true);
  use_count = new int(1);
  set_ptr(ptr);
}

template <class T>
SharedPtr<T>::SharedPtr(SharedPtr<T>& shared_ptr) {
  set_debug(true);
  use_count = new int(-1);
  //use_count = shared_ptr.use_count;
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
  //set_use_count(get_use_count() + shared_ptr.get_use_count());
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
  set_debug(true);
  set_ptr(nullptr);
  use_count = new int(0);
}

template <class T>
void SharedPtr<T>::free() {
  if (debug) {
    std::cout << "Delete pointer " << ptr << "?" << std::endl;
    std::cout << "Use count: " << get_use_count() << std::endl;
  }

  if (get_use_count() == 1) {
    if (debug) {
      std::cout << "Deleting pointer " << ptr << std::endl;
    }

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
void SharedPtr<T>::set_debug(bool debug) {
  this->debug = debug;
}

template <class T>
void SharedPtr<T>::set_ptr(T* ptr) {
  if (debug) {
    if (ptr) {
      std::cout << "Setting pointer to " << ptr << std::endl;
    }
  }

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
