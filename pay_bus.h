// Виджет "Оплата": предлагает варианты оплаты: по карте (Tcp/Ip: Client - Server)
//                                             наличными, в виде диалога
#ifndef PAY_BUS_H
#define PAY_BUS_H

#include <QWidget>

//#include <QBoxLayout>
//#include <QMessageBox>

#include "tcp_client_card.h"
#include "tcp_server_reader.h"

namespace Ui {
class Pay_bus;
}

class Pay_bus : public QWidget
{
    Q_OBJECT

public:
    explicit Pay_bus(QWidget *parent = nullptr);
    ~Pay_bus();

signals:
    void click_pay();

private slots:
    // слот на клик по кнопке "Оплата картой"
    void on_btn_pay_card_clicked();
    // слот на клик по кнопке "Оплата наличными"
    void on_btn_pay_cash_clicked();
    // слот скрывает клиент-сервер после нажатию на кнп "Оплата" главного виджета
    void pay_show();

private:
    Ui::Pay_bus *ui;
    // Указатель на Tcp сервер
    /*Tcp_server_reader* p_serv;
    // Указатель на Tcp клиент
    Tcp_client_card* p_client;*/

    QSharedPointer<Tcp_server_reader> p_serv;
    QSharedPointer<Tcp_client_card> p_client;

    QVBoxLayout* pvbxLayout;


};

#endif // PAY_BUS_H
