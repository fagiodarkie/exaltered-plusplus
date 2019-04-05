#pragma once

#include "db_abstraction.h"
#include <QMap>

namespace serialisation {
  class filesystem_db : public db_abstraction
  {
  public:
    filesystem_db();

    // db_abstraction interface
    QSharedPointer<character::character> load_character(const QString& character_id) override;
    bool has_characters() const override;
    QList<QString> character_list() override;
    void save_character(const QSharedPointer<character::character> character) override;
    void remove_character(const QString& character_id) override;
    void remove_character(unsigned int character_id) override;
    QString character_name(const QString& character_id) const override;
    QSharedPointer<character::character> create_character(const QString& character_name) override;

  private:
    static QString FILE_EXT, AVAILABLE_CHARACTERS_FILE;
    QMap<QString, QString> id_to_name;

    void save_json_to_file(QJsonObject json, const QString& filename) const;
    void save_character_map();
  };
}
