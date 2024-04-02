#pragma once

#include <algorithm>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

template <typename T> class UniqueVector {
public:
  UniqueVector() = default;

  void add(std::unique_ptr<T> &);

  T *find(const std::string &);

  std::unique_ptr<T> pop(const std::string &);

  void remove(const std::string &);

  template <class I> struct DereferenceIterator : public I {
    DereferenceIterator(const I &it) : I(it) {}

    using ValueType = typename I::value_type::element_type;
    using PtrType = ValueType *;
    using RefType = ValueType &;

    RefType operator*() const {
      auto &val = I::operator*();
      return *val;
    }
    PtrType operator->() const { return I::operator*().get(); }
  };

  using ValuesType = typename std::vector<std::unique_ptr<T>>;
  using iterator = DereferenceIterator<typename ValuesType::iterator>;
  using const_iterator =
      DereferenceIterator<typename ValuesType::const_iterator>;

  iterator begin() { return iterator(_data.begin()); }
  iterator end() { return iterator(_data.end()); }
  const_iterator begin() const { return const_iterator(_data.begin()); }
  const_iterator end() const { return const_iterator(_data.end()); }

private:
  ValuesType _data;
};

template <typename T> void UniqueVector<T>::add(std::unique_ptr<T> &ptr) {
  _data.push_back(std::move(ptr));
}

template <typename T> T *UniqueVector<T>::find(const std::string &str) {
  auto d = std::find_if(_data.begin(), _data.end(),
                        [&](auto &d) { return d->name == str; });
  return d->get();
}

template <typename T>
std::unique_ptr<T> UniqueVector<T>::pop(const std::string &str) {
  auto d = std::find_if(_data.begin(), _data.end(),
                        [&](auto &d) { return d->name == str; });
  if (d == _data.end())
    throw std::invalid_argument("Invalid key " + str);
  auto v = std::move(*d);
  _data.erase(d);
  return v;
}

template <typename T> void UniqueVector<T>::remove(const std::string &str) {
  auto d = std::find_if(_data.begin(), _data.end(),
                        [&](auto &d) { return d->name == str; });
  if (d != _data.end())
    _data.erase(d);
}

template <typename T>
std::ostream &operator<<(std::ostream &os, UniqueVector<T> &uv) {
  for (auto it = uv.begin(); it != uv.end(); it++) {
    os << it->name;
    if (it != uv.end() - 1)
      os << ", ";
  }
  return os;
}