// Виджет "Настройки": закрывает приложение, вводит номер маршрута,
//                     считает кол-во рейсов за смену,
//                     в отдельном потоке c помощью контроллера печатает отчёт на экран и в файл
//                     переходить к "Инфо"

#include "settings_bus.h"
#include "ui_settings_bus.h"

Settings_bus::Settings_bus(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings_bus), p_print_control(new Print_Controller)
{
    ui->setupUi(this);

    ui->lineEdit->hide();
    ui->label_2->hide();

    connect(ui->lineEdit, SIGNAL(returnPressed()),
            this,        SLOT(slotEditMarsh())
           );
    marshrut=1;
    reis=0;

//     p_print_control = new Print_Controller();
}

Settings_bus::~Settings_bus()
{
    delete ui;
    //delete p_print_control;
}

// слот на клик по кнопке "Закрыть смену"
void Settings_bus::on_pushButton_clicked()
{

    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setText("Внимание!");
    msgBox.setInformativeText("Приложение будет закрыто!");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    int ret = msgBox.exec();

    switch (ret) {
      case QMessageBox::Ok:
          emit destroyed();
          break;
      case QMessageBox::Cancel:
          break;
      default:
          break;
    }
}

// слот на кнопку смены маршрута
void Settings_bus::on_pushButton_2_clicked()
{
    ui->lineEdit->show();
    ui->label_2->setText("Введите номер маршрута:");
    ui->label_2->show();
}


// слот на кнопку нового рейса
void Settings_bus::on_pushButton_3_clicked()
{
    ++reis;

    QMessageBox msgBox1(QMessageBox::Information,
                        "Новый рейс!",
                        QString("Начат рейс №%1!").arg(reis),
                        QMessageBox::Ok);
    msgBox1.exec();

}

// слот на кнопку печати промежуточного маршрута
// печать запускаетя в отдельном
void Settings_bus::on_pushButton_4_clicked()
{
    emit p_print_control->operate(marshrut, reis);
/*    QDate dateToday = QDate::currentDate();
    QTime timeNow = QTime::currentTime();
    QString path = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    qDebug() << +" Exists? " << QFile::exists(path + "/printer.txt");
    QFile fileOut(path+"/printer.txt");


    QString str="Дата:\n"+
                 dateToday.toString()+"\n"+
                 "Время:\n"+
                 timeNow.toString()+"\n\n"+
                 QString("Текущий Маршрут: №%1!\n").arg(marshrut) +
                 QString("Количество рейсов за смену: %1!\n\n").arg(reis)+
                 "Успешно создан файл для печати printer.txt в директории:\n"+
                 path;

    QString str2="Дата:\n"+
                 dateToday.toString()+"\n"+
                 "Время:\n"+
                 timeNow.toString()+"\n\n"+
                 QString("Текущий Маршрут: №%1!\n").arg(marshrut) +
                 QString("Количество рейсов за смену: %1!\n\n").arg(reis)+
                 "Ошибка!!! Не удалось создатьфайл для печати printer.txt в директории:\n"+
                 path;

    if(fileOut.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream writeStream(&fileOut);
        writeStream << str;
        fileOut.close();

        QMessageBox msgBox1(QMessageBox::Information,
                                "Печать промежуточного отчёта!",
                                str,
                                QMessageBox::Ok);
        msgBox1.exec();

        }
        else{
            QMessageBox msgBox1(QMessageBox::Warning,
                                "Печать промежуточного отчёта!",
                                str2,
                                QMessageBox::Ok);
            msgBox1.exec();
        }
*/
}


// слот на кнопку информации о системе
void Settings_bus::on_pushButton_5_clicked()
{
    emit click_info();
}

// слот на ввод нового маршрута по сигналу от lineEdit
void Settings_bus::slotEditMarsh()
{
    bool ok;
    int m = ui->lineEdit->text().toInt(&ok);

    // проверка на ввод числа
    if(ok){
        marshrut = m;
        QMessageBox msgBox1(QMessageBox::Information,
                            "Изменение маршрута!",
                            QString("Маршрут изменён на №%1!").arg(marshrut),
                            QMessageBox::Ok);
        msgBox1.exec();
    }
    else{
        QMessageBox msgBox1(QMessageBox::Warning,
                            "Изменение маршрута!",
                            QString("Введите верный номер маршрута!"),
                            QMessageBox::Ok);
        msgBox1.exec();
    }



    ui->lineEdit->hide();
    ui->label_2->hide();
}




void Printer::doPrint(const int &marshrut, const int &reis)
{
    QString result="ok";

    QDate dateToday = QDate::currentDate();
    QTime timeNow = QTime::currentTime();
    QString path = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    qDebug() << +" Exists? " << QFile::exists(path + "/printer.txt");
    QFile fileOut(path+"/printer.txt");


    QString str="Дата:\n"+
                 dateToday.toString()+"\n"+
                 "Время:\n"+
                 timeNow.toString()+"\n\n"+
                 QString("Текущий Маршрут: №%1!\n").arg(marshrut) +
                 QString("Количество рейсов за смену: %1!\n\n").arg(reis)+
                 "Успешно создан файл для печати printer.txt в директории:\n"+
                 path;

    QString str2="Дата:\n"+
                 dateToday.toString()+"\n"+
                 "Время:\n"+
                 timeNow.toString()+"\n\n"+
                 QString("Текущий Маршрут: №%1!\n").arg(marshrut) +
                 QString("Количество рейсов за смену: %1!\n\n").arg(reis)+
                 "Ошибка!!! Не удалось создатьфайл для печати printer.txt в директории:\n"+
                 path;

    if(fileOut.open(QIODevice::/*ReadOnly*/WriteOnly | QIODevice::Text)){
        QTextStream writeStream(&fileOut);
        writeStream << str;
        fileOut.close();

        QMessageBox msgBox1(QMessageBox::Information,
                                "Печать промежуточного отчёта!",
                                str,
                                QMessageBox::Ok);
        msgBox1.exec();

        }
        else{
            QMessageBox msgBox1(QMessageBox::Warning,
                                "Печать промежуточного отчёта!",
                                str2,
                                QMessageBox::Ok);
            msgBox1.exec();
        }


    emit resultReady(result);
}

void Print_Controller::handleResults(const QString &)
{
    /*Обработка результата*/
}
