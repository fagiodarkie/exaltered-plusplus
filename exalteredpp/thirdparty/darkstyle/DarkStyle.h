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
#include <QStyleFactory>

class DarkStyle : public QProxyStyle {
  Q_OBJECT

 public:
  DarkStyle();
  explicit DarkStyle(QStyle *style);

  QStyle *baseStyle() const;

  void polish(QPalette &palette) override;
  void polish(QApplication *app) override;

 private:
  QStyle *styleBase(QStyle *style = Q_NULLPTR) const;

  QColor  gray20      = QColor(20 , 20 , 20 ),
          gray35      = QColor(35 , 35 , 35 ),
          gray42      = QColor(42 , 42 , 42 ),
          gray53      = QColor(53 , 53 , 53 ),
          gray66      = QColor(66 , 66 , 66 ),
          gray80      = QColor(80 , 80 , 80 ),
          gray127     = QColor(127, 127, 127),
          text        = Qt::white,
          text_bright = Qt::red,
          link        = QColor(42, 130, 218);
};

#endif  // DARKSTYLE_HPP
