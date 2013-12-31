/*
 *  Copyright 2013 Kreogist Dev Team
 *
 *  This file is part of Kreogist-Cuties.
 *
 *    Kreogist-Cuties is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *    Kreogist-Cuties is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Kreogist-Cuties.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QDebug>

#include "kctextblockdata.h"
#include "kctexteditor.h"

#include "kcsmartpanel.h"

static const int normal_color=120;
static const int curr_line_color=255;

KCSmartPanel::KCSmartPanel(QWidget *parent) :
    KCPanel(parent)
{
    setContentsMargins(0,0,0,0);
    foldMark.load(":/SmartPanel/image/folder.png");
    compileErrorMark.load(":/SmartPanel/image/compile_error.png");
    foldMarkWidth=foldMark.width();
    foldMarkHeight=foldMark.height();
    errorMarkWidth=compileErrorMark.width();
    errorMarkHeight=compileErrorMark.height();
    setAutoAdaptWidth(false);
    setAutoFillBackground(true);
    setFixedWidth(errorMarkWidth+4);
    textColor.setRgb(normal_color,normal_color,normal_color);
    previousLevel=0;
}

void KCSmartPanel::paintEvent(QPaintEvent *event)
{
    startRedraw=true;
    KCPanel::paintEvent(event);
}

void KCSmartPanel::draw(QPainter *painter, QTextBlock *block,
                          int x, int y, int w, int h,
                          bool isCurrentLine)
{
    Q_UNUSED(isCurrentLine);
    heightMove=(lineHeight+foldMarkHeight)/2;
    KCTextBlockData *data=static_cast<KCTextBlockData *>(block->userData());
    if(data!=NULL)
    {
        if(startRedraw)
        {
            //Check previous block data is smaller or the same
            previousLevel=data->getCodeLevel();
            startRedraw=false;
        }
        else
        {
            QPen pen(painter->pen());
            pen.setColor(textColor);
            painter->setPen(pen);

            if(data->getCodeLevel()>previousLevel)
            {
                painter->drawPixmap((w-foldMarkWidth)/2,
                                    y-heightMove,
                                    foldMarkWidth,
                                    foldMarkHeight,
                                    foldMark);
            }
            previousLevel=data->getCodeLevel();

            if(data->getHasError())
            {
                painter->drawPixmap((w-errorMarkWidth)/2,
                                    y+(h-errorMarkHeight)/2,
                                    errorMarkWidth,
                                    errorMarkHeight,
                                    compileErrorMark);
            }
        }
    }
}
