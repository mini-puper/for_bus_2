#ifndef PRINT_CONTROLLER_H
#define PRINT_CONTROLLER_H

#include <QWidget>
#include <QThread>

#include <QFile>
#include <QTextStream>
#include <QStandardPaths>
#include <QDebug>

#include <QSharedPointer>
#include <QMessageBox>
#include <QDate>
#include <QTime>

class Printer : public QObject
{
    Q_OBJECT

public slots:
    void doPrint(const int &marshrut, const int &reis, int type_msg=1);

signals:
    void resultReady(const QString &result);
};

class Print_Controller : public QObject
{
    Q_OBJECT
    QThread workerThread;
public:
    Print_Controller();
    ~Print_Controller();
public slots:
    void handleResults(const QString &);
signals:
    void operate(const int &marshrut, const int &reis, int type_msg=1);
};
#endif // PRINT_CONTROLLER_H
