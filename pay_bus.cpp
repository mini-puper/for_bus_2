// Виджет "Оплата": предлагает варианты оплаты: по карте (Tcp/Ip: Client - Server)
//                                             наличными, в виде диалога
#include "pay_bus.h"
#include "ui_pay_bus.h"


Pay_bus::Pay_bus(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Pay_bus),
    p_serv( new Tcp_server_reader(2323) ),
    p_client( new Tcp_client_card("localhost", 2323 )),
    p_print_control(new Print_Controller)
{
    ui->setupUi(this);

    // Создаём сервер и клиента
    //p_serv   = new Tcp_server_reader(2323);
    //p_client = new Tcp_client_card("localhost", 2323);

    marshrut=1;
    reis=0;

    connect(this, SIGNAL(click_pay()), SLOT(pay_show()));
}

Pay_bus::~Pay_bus()
{
    delete ui;
    delete pvbxLayout;
    //delete p_serv;
    //delete p_client;
}

// слот на клик по кнопке "Оплата картой"
void Pay_bus::on_btn_pay_card_clicked()
{
    ui->btn_pay_card->hide();
    ui->btn_pay_cash->hide();

    p_serv->show();
    p_client->show();

    //настройка layout
    pvbxLayout = new QVBoxLayout;

    pvbxLayout->addWidget(p_serv.data());
    pvbxLayout->addWidget(p_client.data());
    ui->verticalLayout->addLayout(pvbxLayout);

}

// слот скрывает клиент-сервер после нажатию на кнп "Оплата" главного виджета
void Pay_bus::pay_show()
{
    if(!p_serv->isHidden()){
      p_serv->hide();
      p_client->hide();
    }


    if(ui->btn_pay_card->isHidden()){
      ui->btn_pay_card->show();
      ui->btn_pay_cash->show();
      delete pvbxLayout;
    }
}

//слот обновления маршрута и рейса по сигналу из настроек
void Pay_bus::setMarshrutOrReis(int m, int r)
{
    marshrut=m;
    reis=r;
}


// слот на клик по кнопке "Оплата наличными"
void Pay_bus::on_btn_pay_cash_clicked()
{

    QMessageBox msgBox1(QMessageBox::Information,
                        " Оплата наличными!",
                        "Вставьте 2.00 ₽ в купюроприёмник",
                        QMessageBox::Ok | QMessageBox::Cancel);
    int ret = msgBox1.exec();



    QMessageBox msgBox2(QMessageBox::Information,
                        " Оплата наличными!",
                        "Оплата прошла успешно, спасибо!",
                        QMessageBox::Ok);

    switch (ret) {
      case QMessageBox::Ok:
          //msgBox2.exec();
          emit p_print_control->operate(marshrut, reis, 2);
          break;
      case QMessageBox::Cancel:
          break;
      default:
          break;
    }
}

