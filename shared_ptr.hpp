#include <stddef.h>

template <class T>
class SharedPtr {
  private:
    T* ptr;

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

// Empty constructor
template <class T>
SharedPtr<T>::SharedPtr() {
  use_count = new int(-1);
  set_ptr(nullptr);
}

// Contructor for explicit pointer
template <class T>
SharedPtr<T>::SharedPtr(T* ptr) {
  use_count = new int(1);
  set_ptr(ptr);
}

// Constructor for SharedPtr
template <class T>
SharedPtr<T>::SharedPtr(SharedPtr<T>& shared_ptr) {
  use_count = new int(-1);
  *this = shared_ptr;
}

// Destructor, freeing up pointers and use count
template <class T>
SharedPtr<T>::~SharedPtr() {
  if (get_use_count() == 1) {
    delete use_count;
    delete ptr;
  } else if (get_use_count() == -1) {
    delete use_count;
  } else {
    set_use_count(get_use_count() - 1);
  }
}

// Reassignment operator
template <class T>
void SharedPtr<T>::operator=(SharedPtr<T>& shared_ptr) {
  set_ptr(shared_ptr.get());
  delete use_count;
  use_count = shared_ptr.use_count;
  set_use_count(get_use_count() + 1);
}

// Comparison operator for regular pointer
template <class T>
bool SharedPtr<T>::operator==(T* cmpPtr) {
  if (ptr == cmpPtr) {
    return true;
  }

  return false;
}

// Comparison operator for SharedPtr
template <class T>
bool SharedPtr<T>::operator==(SharedPtr<T>& shared_ptr) {
  if (ptr == shared_ptr.get()) {
    return true;
  }

  return false;
}

// Comparison operator, is less, for regular pointer
template <class T>
bool SharedPtr<T>::operator<(T* cmpPtr) {
  if (ptr < cmpPtr) {
    return true;
  }

  return false;
}

// Comparison operator, is less, for SharedPtr
template <class T>
bool SharedPtr<T>::operator<(SharedPtr<T>& shared_ptr) {
  if (ptr < shared_ptr.get()) {
    return true;
  }

  return false;
}

// Boolean operator. Used in e.g. if statements or asserts
template <class T>
SharedPtr<T>::operator bool() {
  if (ptr != nullptr) {
    return true;
  }

  return false;
}

// Get the dereferenced value of the pointer
template <class T>
T& SharedPtr<T>::operator*() {
  return *ptr;
}

// Get the pointer
template <class T>
T* SharedPtr<T>::operator->() {
  return ptr;
}

// Get the pointer
template <class T>
T* SharedPtr<T>::get() {
  return ptr;
}

// Get the use count
template <class T>
int SharedPtr<T>::get_use_count() {
  return *use_count;
}

// Reset the current pointer and replace it with a new pointer
template <class T>
void SharedPtr<T>::reset(T* newPtr) {
  delete use_count;
  use_count = new int(1);
  delete ptr;
  set_ptr(newPtr);
}

// Set pointer
template <class T>
void SharedPtr<T>::set_ptr(T* ptr) {
  this->ptr = ptr;
}

// Set the current use count
template <class T>
void SharedPtr<T>::set_use_count(int count) {
  *use_count = count;
}

// Check if this SharedPtr is the only SharedPtr pointing at the object
template <class T>
bool SharedPtr<T>::unique() {
  if (get_use_count() == 1) {
    return true;
  }

  return false;
}
