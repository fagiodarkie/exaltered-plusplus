#ifndef ABILITY_DECLINATION_SELECTOR_H
#define ABILITY_DECLINATION_SELECTOR_H

#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include "abilities/ability_names.h"
#include "character.h"
#include <memory>

using character::ability_names::detailed_ability;

namespace qt { namespace widget {
    class ability_declination_selector : public QWidget
    {
      Q_OBJECT
    public:
      explicit ability_declination_selector(QWidget *parent = nullptr);
      ability_declination_selector(detailed_ability ability, bool is_ability_editable, bool is_declination_editable, bool is_favored, QWidget *parent = nullptr);
      ability_declination_selector(std::shared_ptr<character::character> character, QWidget *parent = nullptr);

      void set_ability(detailed_ability ability);
      void set_favored(bool favored);

      detailed_ability value() const;

    signals:
      void on_ability_selected(detailed_ability ability);

    private:

      detailed_ability _ability;
      std::shared_ptr<character::character> _character_reference;

      bool _is_declination_editable, _is_ability_editable, _is_favored;
      QGridLayout *ability_and_declination_layout;
      QComboBox *ability_selection, *declination_selection;
      QLabel *ability_name, *declination_name;

      void generate_available_abilities() const;
      void generate_available_declinations() const;

      character::ability_names::ability_enum selected_ability() const;

      void generate_widget();
      void refresh();
      void update_ability();
      void on_ability_change();
      void on_declination_change();
      void repaint(const QList<QWidget*> &widgets_in_layout);
    };
} }

#endif // ABILITY_DECLINATION_SELECTOR_H
