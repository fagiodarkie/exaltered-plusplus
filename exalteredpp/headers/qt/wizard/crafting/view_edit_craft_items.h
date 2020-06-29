#pragma once

#include <QWidget>
#include <QMap>
#include <QList>
#include <QString>
#include <QPushButton>

namespace qt {
  namespace wizard {

    class view_edit_craft_items : public QWidget
    {
      Q_OBJECT
    public:

      enum class item_mode {
        weapon_project, armor_project, material, weapon, armor
      };

      explicit view_edit_craft_items(QWidget *parent = nullptr);

      void update_items(const QList<QString>& item_names, item_mode set_mode);

    signals:
      void edit_request(const QString& item_name, item_mode item_type);
      void back_issued();

    public slots:

    private:
       void on_row_click();

       item_mode mode;
       QPushButton* back;
       static constexpr char DATA[9] = "itemname";
    };

  }
}
