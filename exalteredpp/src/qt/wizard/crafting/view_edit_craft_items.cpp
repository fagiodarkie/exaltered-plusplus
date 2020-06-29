#include "wizard/crafting/view_edit_craft_items.h"

#include "label/interfacelabels.h"
#include "layout/qborderlayout.h"
#include "QFormLayout"
#include "QLabel"
#include "QScrollArea"
#include "QHBoxLayout"

namespace qt {
  namespace wizard {

    constexpr char view_edit_craft_items::DATA[];

    view_edit_craft_items::view_edit_craft_items(QWidget *parent) : QWidget(parent)
    {
      back = new QPushButton(labels::BACK_LABEL);
      connect(back, &QPushButton::clicked, [this] { emit back_issued(); });
    }

    void view_edit_craft_items::update_items(const QList<QString>& item_names, item_mode new_mode)
    {
      mode = new_mode;
      delete layout();
      layout::QBorderLayout* outer = new layout::QBorderLayout;

      /*
       * TODO:
       * if possible, at a later stage, make it so that the items passed are not strings but widgets, put in a list. Each widget would consist of a "header row"
       * and a "hidden body" with the item details, to be shown when the user clicks on the headers. Double click on the header would instead fire the "edit" event.
       */

      QFormLayout* list_layout = new QFormLayout;
      for (QString item: item_names)
        {
          QPushButton* edit = new QPushButton(labels::EDIT_LABEL);
          edit->setProperty(DATA, item);
          connect(edit, &QPushButton::clicked, this, &view_edit_craft_items::on_row_click);
          list_layout->addRow(item, edit);
        }
      QWidget *list_widget = new QWidget;
      list_widget->setLayout(list_layout);
      QScrollArea *scroll = new QScrollArea;
      scroll->setWidget(list_widget);

      QHBoxLayout* buttons = new QHBoxLayout;
      buttons->addWidget(back);
      QWidget* buttons_w = new QWidget;
      buttons_w->setLayout(buttons);

      outer->addWidget(scroll, layout::QBorderLayout::Center);
      outer->addWidget(buttons_w, layout::QBorderLayout::South);
      setLayout(outer);
    }

    void view_edit_craft_items::on_row_click()
    {
      QString selected_item = sender()->property(DATA).toString();
      emit edit_request(selected_item, mode);
    }
  }
}
