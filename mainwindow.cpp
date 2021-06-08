// Главный виджет управляет тремя виджетами - Инфо, Оплата, Настройка
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), p_pay( new Pay_bus() ), p_info( new Info_bus() ), p_settings( new Settings_bus() )
{
    ui->setupUi(this);

    /*p_pay = new Pay_bus();
    p_info = new Info_bus();
    p_settings = new Settings_bus();*/

    //QSharedPointer<Info_bus> p_info2( new Info_bus() );

    ui->scnd_layout->addWidget(p_pay.data());
    ui->scnd_layout->addWidget(p_info.data());
    ui->scnd_layout->addWidget(p_settings.data());

    p_pay->hide();
    //p_info->hide();
    p_settings->hide();

    ui->btn_info->setStyleSheet("background-color:#FFD700");
    ui->btn_pay->setStyleSheet("background-color:#FFFFE0");
    ui->btn_settings->setStyleSheet("background-color:#FFFFE0");

    // Для закрытия приложения
    connect(p_settings.data(), SIGNAL(destroyed()), this, SLOT(close()));

    // Открываем виджет Инфо по клику из настроек
    connect(p_settings.data(),SIGNAL(click_info()), this, SLOT(on_btn_info_clicked()));

    connect(p_settings.data(),&Settings_bus::marshrutOrReisChange,
            p_pay.data(), &Pay_bus::setMarshrutOrReis);

}

MainWindow::~MainWindow()
{
    delete ui;
    //delete p_pay;
    //delete  p_pay;
    //delete  p_settings;

}

// слот на клик по кнопке "Оплата"
void MainWindow::on_btn_pay_clicked()
{
    if (!p_info->isHidden()){
      p_info->hide();
      ui->btn_info->setStyleSheet("background-color:#FFFFE0");}

    if(!p_settings->isHidden()){
      p_settings->hide();
      ui->btn_settings->setStyleSheet("background-color:#FFFFE0");}

    if(p_pay->isHidden()){
      p_pay->show();
      ui->btn_pay->setStyleSheet("background-color:#FFD700");}

    emit p_pay->click_pay();
}

// слот на клик по кнопке "Инфо"
void MainWindow::on_btn_info_clicked()
{
    if(!p_pay->isHidden()){
      p_pay->hide();
      ui->btn_pay->setStyleSheet("background-color:#FFFFE0");}

    if(!p_settings->isHidden()){
      p_settings->hide();
      ui->btn_settings->setStyleSheet("background-color:#FFFFE0");}

    if(p_info->isHidden()){
      p_info->show();
      ui->btn_info->setStyleSheet("background-color:#FFD700");}
}

// слот на клик по кнопке "Настройки"
void MainWindow::on_btn_settings_clicked()
{
    if(!p_pay->isHidden()){
      p_pay->hide();
      ui->btn_pay->setStyleSheet("background-color:#FFFFE0");}

    if(!p_info->isHidden()){
      p_info->hide();
      ui->btn_info->setStyleSheet("background-color:#FFFFE0");}

    if(p_settings->isHidden()){
      p_settings->show();
      ui->btn_settings->setStyleSheet("background-color:#FFD700");}
}

void MainWindow::on_test(int m, int r)
{
     p_pay->setMarshrutOrReis(m,r);
}


