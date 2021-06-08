// отдельный поток для печати сообщений и печати в файл

#include "print_controller.h"

Print_Controller::Print_Controller()
{
    Printer *worker = new Printer;
    worker->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &Print_Controller::operate, worker, &Printer::doPrint);
    connect(worker, &Printer::resultReady, this, &Print_Controller::handleResults);
    workerThread.start();
}

Print_Controller::~Print_Controller() {
    workerThread.quit();
    workerThread.wait();
}

void Printer::doPrint(const int &marshrut, const int &reis, int type_msg)
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

    QString str3="Дата:\n"+
                 dateToday.toString()+"\n"+
                 "Время:\n"+
                 timeNow.toString()+"\n\n"+
                 QString("Текущий Маршрут: №%1!\n").arg(marshrut) +
                 QString("Номер рейса: %1!\n\n").arg(reis)+
                 "Стоимость проезда 2 ₽\n"+
                 "Оплата проезда прошла успешно, счастливого пути!";

    if(type_msg==1)
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

    else if(type_msg==2){

        if(fileOut.open(QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream writeStream(&fileOut);
            writeStream << str;
            fileOut.close();

            QMessageBox msgBox1(QMessageBox::Information,
                                  "Печать чека об оплате!",
                                  str3,
                                  QMessageBox::Ok);
            msgBox1.exec();

            }
            else{
                QMessageBox msgBox1(QMessageBox::Warning,
                                   "Печать чека об оплате!",
                                    str2,
                                    QMessageBox::Ok);
                msgBox1.exec();
            }

    }

    emit resultReady(result);
}

void Print_Controller::handleResults(const QString &)
{
    /*Обработка результата*/
}
