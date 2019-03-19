#pragma once

#include "db_abstraction.h"

namespace serialisation {
  class filesystem_db : public db_abstraction
  {
  public:
    filesystem_db() = default;

    // db_abstraction interface
    QSharedPointer<character::character> load_character() override;
    bool has_characters() const override;
    void save_character(const QSharedPointer<character::character> character) override;

  private:
    static QString FILE_EXT;
  };
}
