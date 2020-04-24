#include "managers/equipment_manager.h"

#include "json_constants.h"

namespace manager {
  const std::string equipment_manager::EQUIPMENT_SAVE_FILE = "equip.json";

  equipment_manager::equipment_manager()
  {
    load(EQUIPMENT_SAVE_FILE);
  }

  void equipment_manager::serialisation()
  {
    if (saving())
      {
        auto weps = weapons();
        auto wprojs = projects();
        auto mats = materials();
        synch(serialisation::json_constants::SLOT_WEAPONS, weps);
        synch(serialisation::json_constants::SLOT_WEAPON_PROJECTS, wprojs);
        synch(serialisation::json_constants::SLOT_MATERIALS, mats);
      }
    else
      {
        std::vector<craft::material> mats;
        std::vector<craft::weapon_project> wep_proj;
        std::vector<class weapon> weps;
        synch(serialisation::json_constants::SLOT_WEAPONS, weps);
        synch(serialisation::json_constants::SLOT_WEAPON_PROJECTS, wep_proj);
        synch(serialisation::json_constants::SLOT_MATERIALS, mats);

        for (auto m: mats)
          add_material(m);
        for (auto w: weps)
          add_weapon(w);
        for (auto wp: wep_proj)
          add_project(wp);
      }
  }

  std::vector<craft::weapon_project> equipment_manager::projects() const
  {
    std::vector<craft::weapon_project> result;
    for (auto project: _projects)
      result.push_back(project.second);
    return result;
  }

  std::vector<craft::material> equipment_manager::materials() const
  {
    std::vector<craft::material> result;
    for (auto material: _materials)
      result.push_back(material.second);
    return result;
  }

  std::vector<class weapon> equipment_manager::weapons() const
  {
    std::vector<class weapon> result;
    for (auto weap: _weapons)
      result.push_back(weap.second);
    return result;
  }


  craft::weapon_project equipment_manager::project(const std::string& name) const
  {
    return _projects.at(name);
  }

  craft::material equipment_manager::material(const std::string& name) const
  {
    return _materials.at(name);
  }

  weapon equipment_manager::weapon(const std::string& name) const
  {
    return _weapons.at(name);
  }


  void equipment_manager::add_material(const craft::material& m)
  {
    _materials[m.name()] = m;
    save(EQUIPMENT_SAVE_FILE);
  }

  void equipment_manager::add_project(const craft::weapon_project& p)
  {
    _projects[p.name()] = p;
    save(EQUIPMENT_SAVE_FILE);
  }

  void equipment_manager::add_weapon(const class weapon& w)
  {
    _weapons[w.name()] = w;
    save(EQUIPMENT_SAVE_FILE);
  }

}
