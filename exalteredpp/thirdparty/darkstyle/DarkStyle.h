/*
###############################################################################
#                                                                             #
# The MIT License                                                             #
#                                                                             #
# Copyright (C) 2017 by Juergen Skrotzky (JorgenVikingGod@gmail.com)          #
#               >> https://github.com/Jorgen-VikingGod                        #
#                                                                             #
# Sources: https://github.com/Jorgen-VikingGod/Qt-Frameless-Window-DarkStyle  #
#                                                                             #
###############################################################################
*/

#ifndef DARKSTYLE_HPP
#define DARKSTYLE_HPP

#include <QApplication>
#include <QFile>
#include <QFont>
#include <QProxyStyle>
#include <QPushButton>
#include <QStyleFactory>

class DarkStyle : public QProxyStyle {
  Q_OBJECT

 public:
  DarkStyle();
  explicit DarkStyle(QStyle *style);

  QStyle *baseStyle() const;

  void polish(QPalette &palette) override;
  void polish(QApplication *app) override;

  void setMainColor(const QColor& color);
  void setDark(bool isDark);
  void foreground(QPushButton* button);

 private:
  QStyle *styleBase(QStyle *style = Q_NULLPTR) const;

  QColor  dark20      = QColor(20 , 20 , 20 ),
          dark35      = QColor(35 , 35 , 35 ),
          dark42      = QColor(42 , 42 , 42 ),
          dark53      = QColor(53 , 53 , 53 ),
          dark66      = QColor(66 , 66 , 66 ),
          dark80      = QColor(80 , 80 , 80 ),
          dark127     = QColor(127, 127, 127),
          light20     = QColor(30 , 21 , 21 ),
          light35     = QColor(96 , 96 , 100),
          light42     = QColor(115, 115, 119),
          light53     = QColor(144, 144, 149),
          light66     = QColor(180, 180, 186),
          light80     = QColor(80 , 80 , 80 ),
          light127    = QColor(127, 127, 127),
          text        = Qt::white,
          text_bright = Qt::red,
          link        = QColor(170, 122, 73),
          main_color  = link;

  QColor darkest =  light20,
         darker  =  light35,
         middle  =  light42,
         lighter =  light53,
         light   =  light66;

  QMap<QString, QString> QSSReplacer = {
    { "%TOOLTIP%"       , "#ffffff"                 },
    { "%GRAY25_75%"     , "rgba(25,25,25,75)"       },
    { "%GRAY25_127%"    , "rgba(25,25,25,127)"      },
    { "%GRAY25_50%%"    , "rgba(25,25,25,50%)"      },
    { "%GRAY25_255%"    , "rgba(25,25,25,255)"      },
    { "%GRAY35_127%"    , "rgba(35,35,35,127)"      },
    { "%GRAY53_75%"     , "rgba(53,53,53,75)"       },
    { "%GRAY53_127%"    , "rgba(53,53,53,127)"      },
    { "%GRAY66_50%%"    , "rgba(66,66,66,50%)"      },
    { "%GRAY66_75%%"    , "rgba(66,66,66,75%)"      },
    { "%GRAY80%"        , "rgb(80,80,80)"           },
    { "%GRAY106%"       , "rgba(106,106,106,255)"   },
    { "%GRAY106_75%"    , "rgba(106,106,106,75)"    },
    { "%GRAY106_127%"   , "rgba(106,106,106,127)"   },
    // light blue
    { "%MENU_SEL%"      , "rgba(147,191,236,127)"   },
    { "%GRAY127%"       , "rgb(127,127,127)"        },

    //
  };
};

#endif  // DARKSTYLE_HPP
