#include "wizard/phys_attack/provide_defense_value_page.h"

#include "layout/qborderlayout.h"
#include <QFormLayout>
#include <QGroupBox>
#include <QVBoxLayout>

#include "label/interfacelabels.h"

namespace qt {
  namespace wizard {

    using namespace labels::wizards::physical_attack;

    provide_defense_value_page::provide_defense_value_page(QWidget *parent) : QWidget(parent)
    {
      layout::QBorderLayout *outer = new layout::QBorderLayout;

      vd_value_spin = new QSpinBox;
      vd_value_spin->setMinimum(0);

      natural_soak_spin = new QSpinBox;
      natural_soak_spin->setMinimum(0);

      armored_soak_spin = new QSpinBox;
      armored_soak_spin->setMinimum(0);

      hardness_spin = new QSpinBox;
      hardness_spin->setMinimum(0);

      current_status = new QLabel;
      current_status->setWordWrap(true);

      vd_selection_box = new QComboBox;
      for (auto vd: combat::PHYSICAL_VD_LIST)
        vd_selection_box->addItem(combat::VD_NAME.at(vd).c_str(), static_cast<int>(vd));

      QFormLayout *vd_and_soak = new QFormLayout;
      vd_and_soak->addRow(VD_TYPE     , vd_selection_box);
      vd_and_soak->addRow(VD_VALUE    , vd_value_spin);
      vd_and_soak->addRow(NATURAL_SOAK, natural_soak_spin);
      vd_and_soak->addRow(ARMORED_SOAK, armored_soak_spin);
      vd_and_soak->addRow(HARDNESS    , hardness_spin);
      QGroupBox *vd_box = new QGroupBox(DEFENSE_VALUES_TITLE);
      vd_box->setLayout(vd_and_soak);

      QVBoxLayout *center = new QVBoxLayout;
      center->addWidget(current_status);
      center->addWidget(vd_box);
      center->setAlignment(Qt::AlignTop);
      QWidget* center_widget = new QWidget;
      center_widget->setLayout(center);

      outer->addWidget(_progress_bar, layout::QBorderLayout::North);
      outer->addWidget(center_widget, layout::QBorderLayout::Center);
      outer->addWidget(buttons_layout(), layout::QBorderLayout::South);

      setLayout(outer);

      enable_next();
      on_next_issued([this]() { on_defense_chosen(); });
    }

    void provide_defense_value_page::attack_properties(unsigned int precision_pool, int external_bonus, combat::damage_type_enum damage_type, combat::body_target target)
    {
      QString damage_type_name = combat::DAMAGE_NAME.at(damage_type).c_str();
      QString target_name = combat::BODY_TARGET_NAME.at(target).c_str();

      current_status->setText(DEFENSE_ROLL_RECAP_TEMPLATE
                              .arg(precision_pool)
                              .arg(external_bonus)
                              .arg(damage_type_name)
                              .arg(target_name));
    }

    void provide_defense_value_page::on_defense_chosen()
    {
      auto vd = static_cast<combat::target_vd>(vd_selection_box->currentData().toInt());
      emit defense_chosen(vd, vd_value_spin->value(),
                          natural_soak_spin->value(), armored_soak_spin->value(), hardness_spin->value());
    }
}}
