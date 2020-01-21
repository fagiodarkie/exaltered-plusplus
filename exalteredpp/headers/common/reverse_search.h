#pragma once

#include <map>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <exception>

namespace commons {
  template<class T>
  T reverse_search_in_map(std::list<T> iterable, std::map<T, std::string> names_map, std::string name)
  {
    auto result = std::find_if(iterable.begin(), iterable.end(), [names_map, name](T iterator) {
        return names_map.at(iterator) == name;
      });
    if (result != iterable.end()) return *result;
    throw std::runtime_error("item not in map");
  }

  template<class T>
  bool contains(std::list<T> iterable, T item)
  {
    return std::find(iterable.begin(), iterable.end(), item) != iterable.end();
  }

  template<class T>
  T reverse_search_in_map(std::vector<T> iterable, std::map<T, std::string> names_map, std::string name)
  {
    auto result = std::find_if(iterable.begin(), iterable.end(), [names_map, name](T iterator) {
        return names_map.at(iterator) == name;
      });
    if (result != iterable.end()) return *result;
    throw std::runtime_error("item not in map");
  }

  template<class T>
  bool contains(std::vector<T> iterable, T item)
  {
    return std::find(iterable.begin(), iterable.end(), item) != iterable.end();
  }

  template <class K, class T>
  typename std::map<K, T>::iterator find(std::map<K, T> m, K key)
  {
    for (auto pair = m.begin(); pair != m.end(); ++pair)
      if (pair->first == key)
        return pair;
    return m.end();
  }
}
