#include "kcisettinglistitemlanguageitem.h"

kciSettingListItemLanguageItem::kciSettingListItemLanguageItem(QWidget *parent) :
    kciSettingListItemBase(parent)
{
    MainLayout=new QHBoxLayout(this);
    MainLayout->setContentsMargins(0,0,0,0);
    MainLayout->setSpacing(0);
    setLayout(MainLayout);

    lblLanguageIcon=new QLabel(this);
    MainLayout->addWidget(lblLanguageIcon);

    MainLayout->addWidget(Caption);
    MainLayout->addStretch();

    blnSel=false;
}
