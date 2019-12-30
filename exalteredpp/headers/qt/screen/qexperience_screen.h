#ifndef QEXPERIENCE_SCREEN_H
#define QEXPERIENCE_SCREEN_H

#include <QWidget>
#include <QPushButton>

#include "character.h"
#include "widget/session_experience_logger.h"
#include "managers/character_manager.h"

namespace qt { namespace screen {

    class qexperience_screen : public QWidget
    {
      Q_OBJECT
    public:
      explicit qexperience_screen(std::shared_ptr<character::character> character,
                                  manager::character_manager &ch_manager,
                                  unsigned int session_number,
                                  QWidget *parent = nullptr);


    signals:

    public slots:

    private:
      widget::session_experience_logger *_logger;
      QPushButton *open_logger;

      std::shared_ptr<character::character> _character;
      manager::character_manager _character_manager;
      unsigned int _session_number;
    };

} }

#endif // QEXPERIENCE_SCREEN_H
