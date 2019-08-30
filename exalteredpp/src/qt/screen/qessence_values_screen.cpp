#include "screen/qessence_values_screen.h"

#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QScrollArea>
#include "layout/qborderlayout.h"
#include "label/interfacelabels.h"

namespace qt {
  namespace screen {

    using namespace labels::essence_labels;

    qessence_values_screen::qessence_values_screen(const std::shared_ptr<character::character> c,
                                                   QWidget *parent)
      : QWidget(parent)
    {

      QWidget *form_widget = new QWidget, *essence_widget = new QWidget;
      QGroupBox *essence_form_widget = new QGroupBox(ESSENCE_TITLE);
      QFormLayout* essence_form = new QFormLayout;
      QVBoxLayout *v_layout = new QVBoxLayout;

      auto essence = c->get_essence();

      essence_form->addRow(PERMANENT_ESSENCE,   new QLabel(QString::number(essence.permanent_essence())));
      essence_form->addRow(KHAN,                new QLabel(QString::number(essence.khan())));
      essence_form->addRow(LOGOS,               new QLabel(QString::number(c->get_logos().get_logos())));
      essence_form->addRow(CELESTIAL_PORTION,   new QLabel(QString::number(essence.get_celestial_portion_percentage())));
      essence_form->addRow(TERRESTRIAL_PORTION, new QLabel(QString::number(essence.get_terrestrial_portion_percentage())));
      essence_form->addRow(PERSONAL_ESSENCE,    new QLabel(labels::AVAILABLE_OVER_TOTAL(essence.available_personal_essence(), essence.total_personal_essence())));
      essence_form->addRow(COMMITTED_SUBSCRIPT, new QLabel(QString::number(essence.committed_personal_essence())));
      essence_form->addRow(PERIPHERAL_ESSENCE,  new QLabel(labels::AVAILABLE_OVER_TOTAL(essence.available_peripheral_essence(), essence.total_peripheral_essence())));
      essence_form->addRow(COMMITTED_SUBSCRIPT, new QLabel(QString::number(essence.committed_peripheral_essence())));
      essence_form->addRow(SPIRITUAL_ESSENCE,   new QLabel(labels::AVAILABLE_OVER_TOTAL(essence.available_spiritual_essence(), essence.total_spiritual_essence())));
      essence_form->addRow(COMMITTED_SUBSCRIPT, new QLabel(QString::number(essence.committed_spiritual_essence())));
      essence_form_widget->setLayout(essence_form);

      QScrollArea *scroll_area = new QScrollArea;
      scroll_area->setWidgetResizable(true);
      scroll_area->setWidget(essence_form_widget);

      v_layout->addWidget(scroll_area);
      setLayout(v_layout);
    }
  }
}
