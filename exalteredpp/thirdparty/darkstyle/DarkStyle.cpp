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

void DarkStyle::setMainColor(const QColor &color)
{
  main_color = color;
  link = color;
}

void DarkStyle::setDark(bool isDark)
{
  if (isDark)
    {
      darkest =  dark20;
      darker  =  dark35;
      middle  =  dark42;
      lighter =  dark53;
      light   =  dark66;
    }
  else
    {
      darkest =  light20;
      darker  =  light35;
      middle  =  light42;
      lighter =  light53;
      light   =  light66;
    }
}

void DarkStyle::foreground(QPushButton *button)
{
  auto palette = button->palette();
  polish(palette);
  palette.setColor(QPalette::Button,          main_color);
  palette.setColor(QPalette::Disabled, QPalette::Button,           dark127);
  button->setPalette(palette);
}

QStyle *DarkStyle::baseStyle() const { return styleBase(); }

void DarkStyle::polish(QPalette &palette) {
  // modify palette to dark
  palette.setColor(QPalette::Window,          lighter);
  palette.setColor(QPalette::WindowText,      text);
  palette.setColor(QPalette::Base,            middle);
  palette.setColor(QPalette::AlternateBase,   light);
  palette.setColor(QPalette::ToolTipBase,     text);
  palette.setColor(QPalette::ToolTipText,     lighter);
  palette.setColor(QPalette::Text,            text);
  palette.setColor(QPalette::Dark,            darker);
  palette.setColor(QPalette::Shadow,          darkest);
  palette.setColor(QPalette::Button,          lighter);
  palette.setColor(QPalette::ButtonText,      text);
  palette.setColor(QPalette::BrightText,      text_bright);
  palette.setColor(QPalette::Link,            link);
  palette.setColor(QPalette::Highlight,       link);
  palette.setColor(QPalette::HighlightedText, text);

  palette.setColor(QPalette::Disabled, QPalette::Button,           dark127);
  palette.setColor(QPalette::Disabled, QPalette::WindowText,       dark127);
  palette.setColor(QPalette::Disabled, QPalette::Text,             dark127);
  palette.setColor(QPalette::Disabled, QPalette::ButtonText,       dark127);
  palette.setColor(QPalette::Disabled, QPalette::Highlight,        dark80);
  palette.setColor(QPalette::Disabled, QPalette::HighlightedText,  dark127);
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
    for (auto toReplace: QSSReplacer.keys())
      qsStylesheet = qsStylesheet.replace(toReplace, QSSReplacer[toReplace]);

    app->setStyleSheet(qsStylesheet);
    qfDarkstyle.close();
  }
}
