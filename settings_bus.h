// Виджет "Настройки": закрывает приложение, вводит номер маршрута,
//                     считает кол-во рейсов за смену,
//                     в отдельном потоке c помощью контроллера печатает отчёт на экран и в файл
//                     переходить к "Инфо"

#ifndef SETTINGS_BUS_H
#define SETTINGS_BUS_H

#include <QWidget>
#include <QMessageBox>
#include <QLineEdit>
#include <QSharedPointer>

#include "print_controller.h"

class Print_Controller;

namespace Ui {
class Settings_bus;
}

class Settings_bus : public QWidget
{
    Q_OBJECT

public:
    explicit Settings_bus(QWidget *parent = nullptr);
    ~Settings_bus();

signals:
    void click_info();
    void marshrutOrReisChange(int mar, int rei);//

public slots:

    // слот на клик по кнопке закрытия смены
    void on_pushButton_clicked();
    // слот на кнопку смены маршрута
    void on_pushButton_2_clicked();
    // слот на кнопку нового рейса
    void on_pushButton_3_clicked();
    // слот на кнопку печати промежуточного маршрута
    void on_pushButton_4_clicked();
    // слот на кнопку информации о системе
    void on_pushButton_5_clicked();
    // слот на ввод нового маршрута по сигналу от lineEdit
    void slotEditMarsh();


private:
    Ui::Settings_bus *ui;
    void sream_print();

    // счётчик кол-ва рейсов за смену
    int reis;
    // номер маршрута
    int marshrut;

    //Print_Controller* p_print_control;

    QSharedPointer<Print_Controller> p_print_control;
};


#endif // SETTINGS_BUS_H
