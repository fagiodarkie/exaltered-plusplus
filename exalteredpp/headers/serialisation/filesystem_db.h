#pragma once

#include "db_abstraction.h"
#include <QMap>

namespace serialisation {
  class filesystem_db : public db_abstraction
  {
  public:
    filesystem_db() = default;

    // db_abstraction interface
    QSharedPointer<character::character> load_character(const QString& character_id) override;
    bool has_characters() const override;
    QList<QString> character_list() override;
    void save_character(const QSharedPointer<character::character> character) override;
    QString character_name(const QString& character_id) const override;

  private:
    static QString FILE_EXT, AVAILABLE_CHARACTERS_FILE;
    QMap<QString, QString> id_to_name;

    void save_json_to_file(QJsonObject json, const QString& filename) const;
  };
}
