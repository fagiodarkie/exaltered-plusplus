#ifndef WEAPON_PROJECT_STAT_WIDGET_H
#define WEAPON_PROJECT_STAT_WIDGET_H

#include <QCheckBox>
#include <QComboBox>
#include <QSpinBox>
#include <QWidget>

#include "equipment/craft/weapon_project.h"

namespace qt {
  namespace wizard {
    class weapon_project_stat_widget : public QWidget
    {
      Q_OBJECT
    public:
      explicit weapon_project_stat_widget(QWidget *parent = nullptr);

      equipment::craft::attack_stat stat() const;

    private:

      QSpinBox *weapon_precision_spin, *weapon_damage_spin, *weapon_drill_spin, *weapon_min_spin, *weapon_im_spin, *weapon_range_spin, *weapon_cadence_spin;
      QComboBox *weapon_damage_box, *weapon_precision_attr_box, *weapon_damage_attr_box;
      QVector<QCheckBox*> note_checkboxes;
    };

  }
}
#endif // WEAPON_PROJECT_STAT_WIDGET_H
