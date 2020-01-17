#pragma once

#include "character.h"
#include <QSharedPointer>

namespace serialisation {

  class db_abstraction
  {
  public:
    virtual std::shared_ptr<character::character> load_character(const std::string& character_id) = 0;
    virtual bool has_characters() const = 0;
    virtual std::vector<std::string> character_list() = 0;
    virtual std::string character_name(const std::string& character_id) const = 0;
    virtual void remove_character(const std::string& character_id) = 0;
    virtual void remove_character(unsigned int character_id) = 0;
    virtual void save_character(std::shared_ptr<character::character>& character) = 0;
    virtual std::shared_ptr<character::character> create_character( const std::string& name,
                                                        const character::creation::character_type type,
                                                        const character::exalt::caste& caste,
                                                        const attribute::attributes& attribute,
                                                        const ability::abilities& abilities,
                                                        const virtues::virtues& virtues,
                                                        const power::essence&   essence,
                                                        const power::willpower& willpower,
                                                        const power::health&    health,
                                                        const power::logos&     logos) = 0;

    virtual ~db_abstraction() {}
  };
}
