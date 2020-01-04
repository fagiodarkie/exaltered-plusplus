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

    signals:
      void purchased(const character::narrative::experience_purchase& purchase);

    private:
      void purchase_type_selected();
      void compute_purchase() const;
      void compute_cost() const;
      int selected_purchase_type() const;
      void validate() const;
      void redraw(const QList<QWidget*> widgets_in_list);

      QComboBox *attribute_dropdown, *virtue_dropdown, *purchase_type_dropdown;
      widget::ability_declination_selector *ability_selector;
      QLineEdit *specialty_freetext;
      QLabel *cost_label;
      QPushButton *purchase_submit;
      std::shared_ptr<character::character> _character;
    };

}}

#endif // EXPERIENCE_PURCHASE_WIDGET_H
