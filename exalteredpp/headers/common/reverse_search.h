#pragma once

#include <map>
#include <string>
#include <list>
#include <algorithm>

namespace commons {
  template<class T>
  T reverse_search_in_map(std::list<T> iterable, std::map<T, std::string> names_map, std::string name)
  {
    return *std::find_if(iterable.begin(), iterable.end(), [names_map, name](T iterator) {
      return names_map.at(iterator) == name;
    });
  }

  template<class T>
  bool contains(std::list<T> iterable, T item)
  {
    return std::find(iterable.begin(), iterable.end(), item) != iterable.end();
  }
}
