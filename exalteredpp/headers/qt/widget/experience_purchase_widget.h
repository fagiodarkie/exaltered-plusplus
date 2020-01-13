#ifndef EXPERIENCE_PURCHASE_WIDGET_H
#define EXPERIENCE_PURCHASE_WIDGET_H

#include <QDialog>
#include "widget/ability_declination_selector.h"
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>

#include "narrative/experience.h"

namespace qt { namespace widget {

    class experience_purchase_widget : public QDialog
    {
      Q_OBJECT

    public:
      experience_purchase_widget(std::shared_ptr<character::character> character, QWidget* parent = nullptr);
      ~experience_purchase_widget();

      void set_available_experience(unsigned int experience);

    signals:
      void purchased(const character::narrative::experience_purchase& purchase);

    private:
      void purchase_type_selected();
      character::narrative::experience_purchase compute_purchase() const;
      void compute_cost_label() const;
      unsigned int compute_cost(character::narrative::experience_expense_type purchase_type, std::shared_ptr<character::narrative::abstract_purchase> purchase) const;
      int selected_purchase_type() const;
      void submit_purchase();

      character::attribute_names::attribute selected_attribute() const;
      character::ability_names::detailed_ability selected_ability() const;
      character::virtues::virtue_enum selected_virtue() const;

      void validate(unsigned int cost) const;
      void redraw(const QList<QWidget*> widgets_in_list);

      QComboBox *attribute_dropdown, *virtue_dropdown, *purchase_type_dropdown;
      widget::ability_declination_selector *ability_selector;
      QLineEdit *specialty_freetext;
      QLabel *cost_label, *newvalue_label;
      QPushButton *purchase_submit;
      std::shared_ptr<character::character> _character;
      unsigned int available;
    };

}}

#endif // EXPERIENCE_PURCHASE_WIDGET_H
