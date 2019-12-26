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
      ability_declination_selector(detailed_ability ability, bool is_editable, QWidget *parent = nullptr);

      void set_ability(detailed_ability ability);

      detailed_ability value() const;

      QWidget* widget() const;

    signals:
      void on_ability_selected(detailed_ability ability);

    public slots:
      void signal_taken_abilities(const QList<detailed_ability>& taken_abilities);

    private:

      QHBoxLayout *declination_sublayout;
      QVBoxLayout *ability_and_declination_layout, *widget_layout;
      QComboBox *ability_selection, *declination_selection;
      QWidget *outer_widget;
      QPushButton *create_declination, *submit_declination;
      QTextLine *new_declination_name;
      QDialog *new_declination_dialog;
      detailed_ability _ability;
      bool _valid_selection, _is_editable, _is_caste;
      QList<detailed_ability> _prohibited_abilities;
      QList<std::string> possible_declinations;

      QStringList generate_available_abilities() const;
      QStringList generate_available_declinations() const;

      void generate_widget();

      static std::string ability_text(detailed_ability ability);
    };
} }

#endif // ABILITY_DECLINATION_SELECTOR_H
