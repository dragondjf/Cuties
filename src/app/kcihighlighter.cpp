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

#include "kcihighlighter.h"

static char charNeedParentheses[]="{}[]()";

kciHighlighter::kciHighlighter(QObject *parent) :
    QSyntaxHighlighter(parent)
{
}

void kciHighlighter::highlightBlock(const QString &text)
{
    /* This function is used to associate kciTextBlockData with QTextBlock.
     * And then call kciHighlightBlock() which highlight the source code.
     */
    kciTextBlockData* data=(kciTextBlockData*)currentBlockUserData();
    if(data==NULL)
    {
        data=new kciTextBlockData;
        setCurrentBlockUserData(data);
    }

    data->beginUsingSearchDatas();
    data->onBlockChanged();
    data->endUsingSearchDatas();

    data->resetParentheseInfos();
    for(int i=0,l=strlen(charNeedParentheses);
        i<l;
        i++)
    {
        parseParenthesesInfo(text,data,charNeedParentheses[i]);
    }

    kciHighlightBlock(text);
}

void kciHighlighter::parseParenthesesInfo(const QString &text,
                                          kciTextBlockData *data,
                                          char character)
{
    int index=text.indexOf(character);
    while(index!=-1)
    {
        data->insertParenthesesInfo(index,character);
        index=text.indexOf(character,index+1);
    }
}
