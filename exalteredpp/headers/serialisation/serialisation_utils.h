#ifndef SERIALISATION_UTILS_H
#define SERIALISATION_UTILS_H

#define SYNCH_ENUM_VECTOR(type, name, parameter)  if (saving())\
{\
  std::vector<std::underlying_type_t<type>> tmp;\
  for (auto n: parameter)\
    tmp.emplace_back(static_cast<std::underlying_type_t<type>>(n));\
  synch(name, tmp);\
}\
else\
{\
  std::vector<std::underlying_type_t<type>> tmp;\
  synch(name, tmp);\
  for (auto n: tmp)\
    parameter.emplace_back(static_cast<type>(n));\
}

#endif // SERIALISATION_UTILS_H
