#include <QLabel>

#pragma once

namespace qt {
  static QLabel* label(const std::string& text)
  {
    return new QLabel(text.c_str());
  }
}
