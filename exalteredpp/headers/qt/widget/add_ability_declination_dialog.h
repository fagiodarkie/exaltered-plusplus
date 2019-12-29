#pragma once

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>

namespace qt { namespace widget {
    class add_ability_declination_dialog : public QDialog
    {
      Q_OBJECT
    public:
      explicit add_ability_declination_dialog(QWidget *parent = nullptr);

      void set_prohibited_declinations(QList<QString> declinations);

    signals:
      void declination_selected(const QString& declination_name);

    public slots:

    private:
      QPushButton *submit_declination;
      QLineEdit *declination_text;
      QList<QString> prohibited_declinations;

      void validate();
      void submit();
    };
} }


