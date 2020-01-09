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

#include "DarkStyle.h"

DarkStyle::DarkStyle() : DarkStyle(styleBase()) {}

DarkStyle::DarkStyle(QStyle *style) : QProxyStyle(style) {}

QStyle *DarkStyle::styleBase(QStyle *style) const {
  static QStyle *base =
      !style ? QStyleFactory::create(QStringLiteral("Fusion")) : style;
  return base;
}

QStyle *DarkStyle::baseStyle() const { return styleBase(); }

void DarkStyle::polish(QPalette &palette) {
  // modify palette to dark
  palette.setColor(QPalette::Window,                                      gray53);
  palette.setColor(QPalette::WindowText,                                  text);
  palette.setColor(QPalette::Disabled,        QPalette::WindowText,       gray127);
  palette.setColor(QPalette::Base,                                        gray42);
  palette.setColor(QPalette::AlternateBase,                               gray66);
  palette.setColor(QPalette::ToolTipBase,                                 text);
  palette.setColor(QPalette::ToolTipText,                                 gray53);
  palette.setColor(QPalette::Text,                                        text);
  palette.setColor(QPalette::Disabled,        QPalette::Text,             gray127);
  palette.setColor(QPalette::Dark,                                        gray35);
  palette.setColor(QPalette::Shadow,                                      gray20);
  palette.setColor(QPalette::Button,                                      gray53);
  palette.setColor(QPalette::ButtonText,                                  text);
  palette.setColor(QPalette::Disabled,        QPalette::ButtonText,       gray127);
  palette.setColor(QPalette::BrightText,                                  text_bright);
  palette.setColor(QPalette::Link,                                        link);
  palette.setColor(QPalette::Highlight,                                   link);
  palette.setColor(QPalette::Disabled,        QPalette::Highlight,        gray80);
  palette.setColor(QPalette::HighlightedText,                             text);
  palette.setColor(QPalette::Disabled,        QPalette::HighlightedText,  gray127);
}

void DarkStyle::polish(QApplication *app) {
  if (!app) return;

  // increase font size for better reading,
  // setPointSize was reduced from +2 because when applied this way in Qt5, the
  // font is larger than intended for some reason
  QFont defaultFont = QApplication::font();
  defaultFont.setPointSize(defaultFont.pointSize() + 1);
  app->setFont(defaultFont);

  // loadstylesheet
  QFile qfDarkstyle(QStringLiteral(":/darkstyle/darkstyle.qss"));
  if (qfDarkstyle.open(QIODevice::ReadOnly | QIODevice::Text)) {
    // set stylesheet
    QString qsStylesheet = QString::fromLatin1(qfDarkstyle.readAll());
    app->setStyleSheet(qsStylesheet);
    qfDarkstyle.close();
  }
}
