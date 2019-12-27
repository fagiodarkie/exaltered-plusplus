#ifndef ABILITY_DECLINATION_SELECTOR_H
#define ABILITY_DECLINATION_SELECTOR_H

#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "abilities/ability_names.h"

using character::ability_names::detailed_ability;

namespace qt { namespace widget {
    class ability_declination_selector : public QWidget
    {
      Q_OBJECT
    public:
      explicit ability_declination_selector(QWidget *parent = nullptr);
      ability_declination_selector(detailed_ability ability, bool is_ability_editable, bool is_declination_editable, QWidget *parent = nullptr);

      void set_ability(detailed_ability ability);

      detailed_ability value() const;

      QWidget* widget() const;

    signals:
      void on_ability_selected(detailed_ability ability);

    private:

      detailed_ability _ability;
      bool _is_declination_editable, _is_ability_editable;
      QHBoxLayout *ability_and_declination_layout;
      QComboBox *ability_selection;
      QWidget *outer_widget;
      QPushButton *create_declination;
      QDialog *new_declination_dialog;
      QList<std::string> possible_declinations;

      QStringList generate_available_abilities() const;
      QStringList generate_available_declinations() const;

      void generate_widget();
    };
} }

#endif // ABILITY_DECLINATION_SELECTOR_H
