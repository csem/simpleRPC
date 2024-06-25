#pragma once

#include <Arduino.h>
#include <vector>
#include <algorithm> // for std::min

template <class T>
void swap_(T& a, T& b) noexcept {
  T tmp{a};
  a = b;
  b = tmp;
}

/*!
 * Generic Vector.
 */
template <class T>
class Vector {
public:
  Vector() = default;
  Vector(Vector const& v);

  /*! Create a Vector with `size` elements.
  *
  * \param size Vector size.
  */
  Vector(size_t const);

  /*!
  * Create a Vector with `size` elements from a C array.
  *
  * \param arr C array.
  */
  template <size_t n>
  Vector(T const (&arr)[n]);

  /*!
  * Create a Vector with `size` elements from a block of raw memory.
  *
  * \param ptr Pointer to data, Vector takes ownership.
  * \param size Vector size.
  */
  Vector(T* const, size_t const);

  ~Vector() = default;

  Vector& operator=(Vector);
  T& operator[](size_t const);
  T const& operator[](size_t const) const;

  T* begin();
  T* end();
  T const* begin() const;
  T const* end() const;

  /*!
  * Get the underlying data.
  *
  * \return data.
  */
  T* data();

  /*!
  * Get the number of elements.
  *
  * \return Vector size.
  */
  size_t size() const;

  /*!
  * Set the number of elements.
  *
  * \param size Vector size.
  */
  void resize(size_t const);

  /*! Clear the contents. */
  void clear();

  /*!
  * Add an element to the back.
  *
  * \param el Element.
  */
  void push_back(T const&);

  /*!
  * Add an element to the back.
  *
  * \param el Element.
  */
  void push_back(T&&);

  /*!
  * Remove an element from the back.
  *
  * \return Element.
  */
  T pop_back();

  template <class U>
  friend void swap(Vector<U>&, Vector<U>&) noexcept;

private:
  void copy_(T const* const, size_t const size);

  std::vector<T> data_;
};

template <class T>
Vector<T>::Vector(Vector const& other)
  : data_{other.data_} {}

template <class T>
Vector<T>::Vector(size_t const size)
  : data_(size) {}

template <class T>
Vector<T>::Vector(T* const ptr, size_t const size)
  : data_(ptr, ptr + size) {}

template <class T>
template <size_t n>
Vector<T>::Vector(T const (&arr)[n])
  : data_(arr, arr + n) {}

template <class T>
Vector<T>& Vector<T>::operator=(Vector<T> other) {
  swap(*this, other);
  return *this;
}

template <class T>
T& Vector<T>::operator[](size_t const idx) {
  return data_[idx];
}

template <class T>
T const& Vector<T>::operator[](size_t const idx) const {
  return data_[idx];
}

template <class T>
T* Vector<T>::begin() {
  return data_.data();
}

template <class T>
T* Vector<T>::end() {
  return data_.data() + data_.size();
}

template <class T>
T const* Vector<T>::begin() const {
  return data_.data();
}

template <class T>
T const* Vector<T>::end() const {
  return data_.data() + data_.size();
}

template <class T>
T* Vector<T>::data() {
  return data_.data();
}

template <class T>
size_t Vector<T>::size() const {
  return data_.size();
}

template <class T>
void Vector<T>::resize(size_t const size) {
  data_.resize(size);
}

template <class T>
void Vector<T>::clear() {
  data_.clear();
}

template <class T>
void Vector<T>::push_back(T const& el) {
  data_.push_back(el);
}

template <class T>
void Vector<T>::push_back(T&& el) {
  data_.push_back(std::move(el));
}

template <class T>
T Vector<T>::pop_back() {
  T el = std::move(data_.back());
  data_.pop_back();
  return el;
}

template <class T>
void Vector<T>::copy_(T const* const data, size_t const size) {
  std::copy(data, data + size, data_.data());
}

template <class U>
void swap(Vector<U>& a, Vector<U>& b) noexcept {
  using std::swap;
  swap(a.data_, b.data_);
}
