// Главный виджет управляет тремя виджетами - Инфо, Оплата, Настройка

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSharedPointer>

#include "pay_bus.h"
#include "info_bus.h"
#include "settings_bus.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // слот по клику кнопки "Инфо"
    void on_btn_info_clicked();
    // слот по клику кнопки "Оплата"
    void on_btn_pay_clicked();
    // слот по клику кнопки "Настройки"
    void on_btn_settings_clicked();

    void on_test(int m, int r);//


private:
    Ui::MainWindow *ui;

    // три виджета в главном окне
    // виджет Инфо
    //QSharedPointer<Info_bus> p_info2( new Info_bus() );
    /*Info_bus* p_info;
    // виджет Оплаты
    Pay_bus* p_pay;
    // виджет Настроек
    Settings_bus* p_settings;*/

    QSharedPointer<Pay_bus> p_pay;
    QSharedPointer<Info_bus> p_info;
    QSharedPointer<Settings_bus> p_settings;


};
#endif // MAINWINDOW_H
