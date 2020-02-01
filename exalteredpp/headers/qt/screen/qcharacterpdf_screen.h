#ifndef QCHARACTERPDF_SCREEN_H
#define QCHARACTERPDF_SCREEN_H

#include <QWidget>
#include "character.h"

namespace qt { namespace screen {

    class qcharacterpdf_screen : public QWidget
    {
        Q_OBJECT
        public:
          explicit qcharacterpdf_screen(std::shared_ptr<character::character> character,
                                        QWidget *parent = nullptr);

        signals:

        public slots:

        private:
            std::shared_ptr<character::character> _character;
    };

} }

#endif // QCHARACTERPDF_SCREEN_H
