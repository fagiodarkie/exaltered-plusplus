#include "widget/add_ability_declination_dialog.h"

#include "layout/qborderlayout.h"

#include <QLabel>

namespace qt { namespace widget {

    add_ability_declination_dialog::add_ability_declination_dialog(QWidget *parent) : QDialog(parent)
    {
      submit_declination = new QPushButton("Submit");
      submit_declination->setEnabled(false);
      connect(submit_declination, &QPushButton::clicked, this, &add_ability_declination_dialog::submit);

      declination_text = new QLineEdit;
      connect(declination_text, &QLineEdit::textEdited, this, &add_ability_declination_dialog::validate);

      auto outer = new layout::QBorderLayout;

      outer->addWidget(new QLabel("New Subability name:"), layout::QBorderLayout::North);
      outer->addWidget(declination_text, layout::QBorderLayout::Center);
      outer->addWidget(submit_declination, layout::QBorderLayout::South);
      setLayout(outer);
    }

    void add_ability_declination_dialog::set_prohibited_declinations(QList<QString> declinations)
    {
      prohibited_declinations = declinations;
    }

    void add_ability_declination_dialog::validate()
    {
      auto text = declination_text->text();

      bool invalid = text.trimmed().isEmpty()
          || prohibited_declinations.contains(text)
          || prohibited_declinations.contains(text.trimmed());

      submit_declination->setEnabled(!invalid);
    }

    void add_ability_declination_dialog::submit()
    {
      emit declination_selected(declination_text->text().trimmed());
    }
}}
