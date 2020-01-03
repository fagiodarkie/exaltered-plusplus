#include "widget/session_experience_logger.h"

#include <QLabel>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include "layout/qborderlayout.h"
#include "qt/label/interfacelabels.h"

namespace qt { namespace widget {

      session_experience_logger::session_experience_logger(QWidget *parent) : QDialog(parent)
      {
        setWindowTitle("New Session Experience Award");

        submit = new QPushButton(qt::labels::SUBMIT_LABEL);
        connect(submit, &QPushButton::clicked, this, &session_experience_logger::submit_session);

        QFormLayout *form = new QFormLayout;

        {
          QLabel *exp_label = new QLabel("Exp"), *desc_label = new QLabel("Notes");
          exp_label->setFixedWidth(50);
          auto headbox = new QHBoxLayout;
          headbox->addWidget(exp_label);
          headbox->addWidget(desc_label);
          form->addRow("Experience Item", headbox);
        }

        for (auto award: character::narrative::AWARD_TYPES)
          {
            award_fields[award] = new QSpinBox;
            award_fields[award]->setMinimum(0);
            award_fields[award]->setMaximum(MAX_VALUE[award]);
            award_fields[award]->setValue(0);
            award_fields[award]->setFixedWidth(50);

            description_fields[award] = new QLineEdit;

            auto hbox = new QHBoxLayout;
            hbox->addWidget(award_fields[award]);
            hbox->addWidget(description_fields[award]);

            form->addRow(character::narrative::AWARD_NAME.at(award).c_str(), hbox);
          }

        auto form_widget = new QWidget;
        form_widget->setLayout(form);
        QScrollArea *scroll = new QScrollArea(this);
        scroll->setWidget(form_widget);


        layout::QBorderLayout *outer = new layout::QBorderLayout;

        outer->addWidget(scroll, layout::QBorderLayout::Center);
        outer->addWidget(submit, layout::QBorderLayout::South);

        setLayout(outer);
      }

      void session_experience_logger::set_next_session_number(unsigned int session_number)
      {
        _session = session_number;
        refresh();
      }

      void session_experience_logger::refresh()
      {
        for (auto award: character::narrative::AWARD_TYPES)
          {
            award_fields[award]->setValue(0);
            description_fields[award]->setText("");
          }
      }

      void session_experience_logger::submit_session()
      {
        character::narrative::session_awards result;

        for (auto award: character::narrative::AWARD_TYPES)
          {
            auto amount = award_fields[award]->value();
            if (amount == 0)
              continue;

            auto description = description_fields[award]->text();
            character::narrative::experience_award new_award(award, amount);
            if (!description.isEmpty())
              new_award.set_description(description.toStdString());

            result[award] = new_award;
          }

        emit session_logged(result);
      }

} }
