#include "screen/qhealth_screen.h"

#include "label/interfacelabels.h"
#include "layout/qborderlayout.h"

namespace qt { namespace screen {

    using namespace labels::health_labels;

    /*std::shared_ptr<character::character> _character;
    std::shared_ptr<manager::character_manager> _manager;

    QPushButton *deal_heal_button;
    QRadioButton *deal_radio, *heal_radio;
    QSpinBox *_amount_box;
    QLabel *_status_label;

    void on_deal_heal_switched();
    void on_deal_heal_issued();
    void heal_issued();
    void deal_issued(); */
    qhealth_screen::qhealth_screen(std::shared_ptr<character::character> character,
                                                 std::shared_ptr<manager::character_manager> manager,
                                                 QWidget *parent)
      : QWidget(parent),
      _character(character),
      _manager(manager)
    {
      deal_heal_button = new QPushButton;
      deal_radio = new QRadioButton(this);
      heal_radio = new QRadioButton(this);
      heal_radio->setChecked(true);

      _summary_label = new QLabel;
      _amount_box = new QSpinBox;



      on_deal_heal_switched();
    }

}}
