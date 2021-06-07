// Виджет "Инфо": отображает html страницу
#include "info_bus.h"
#include "ui_info_bus.h"

#include <QFile>

Info_bus::Info_bus(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Info_bus)
{
    ui->setupUi(this);
    ui->textBrowser->setSource(QUrl("qrc:/res/for_info_bus_wiki.html"));
    ui->textBrowser->setOpenLinks(0);
}

Info_bus::~Info_bus()
{
    delete ui;
}
