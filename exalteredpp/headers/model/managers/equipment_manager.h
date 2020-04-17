#ifndef EQUIPMENT_MANAGER_H
#define EQUIPMENT_MANAGER_H

#include "equipment/craft/weapon_project.h"
#include "equipment/craft/material.h"
#include "equipment/craft/improvement.h"
#include "equipment/weapon.h"

#include "../thirdparty/serialisable/serialisable.hpp"

#include <vector>
#include <string>
#include <map>

namespace manager {

  using namespace equipment;

  class equipment_manager : Serialisable
  {

  public:
    equipment_manager();

    std::vector<craft::weapon_project> projects() const;
    std::vector<craft::material> materials() const;
    std::vector<weapon> weapons() const;

    craft::weapon_project project(const std::string& name) const;
    craft::material material(const std::string& name) const;
    weapon weapon(const std::string& name) const;

    void add_material(const craft::material& m);
    void add_project(const craft::weapon_project& p);
    void add_weapon(const class weapon& w);

    void serialisation() override;

  private:
    static const std::string EQUIPMENT_SAVE_FILE;

    std::map<std::string, craft::weapon_project> _projects;
    std::map<std::string, craft::material> _materials;
    std::map<std::string, class weapon> _weapons;
  };
}

#endif // EQUIPMENT_MANAGER_H
