#include "screen/qcharacterpdf_screen.h"

#include <QPdfWriter>
#include <QPainter>

namespace qt {
    namespace screen {

        qcharacterpdf_screen::qcharacterpdf_screen(std::shared_ptr<character::character> character,
                                                   QWidget *parent): QWidget(parent), _character(character)
        {
            //Cast Character name from string to char* array
            std::string charname = character->name();
            char * namearray = new char [charname.length()+1];
            strcpy_s (namearray, charname.length()+1, charname.c_str());

            QString charName(namearray);
            QPdfWriter character_pdf("C:/Users/franc/Desktop/test.pdf");
            character_pdf.setPageSize(QPageSize(QPageSize::A4));
            QPainter painter(&character_pdf);
            painter.drawText(0,0, charName);
            painter.end();
        }

    }
}
