#pragma once

#include <QMap>

namespace commons {
  template<class T>
  T reverse_search_in_map(QList<T> iterable, QMap<T, QString> names_map, QString name)
  {
    return *std::find_if(iterable.begin(), iterable.end(), [names_map, name](T iterator) {
      return names_map.value(iterator) == name;
    });
  }
}
