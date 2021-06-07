// Виджет "Сервер" выполняет роль картридера: встраивается в виджет "Оплата" (Pay_bus)
// Принимает карту, подтверждает оплату

#ifndef MY_SERVER_H
#define MY_SERVER_H
#include <QtNetwork>
#include <QTextEdit>
#include <QGridLayout>
#include <QBoxLayout>
#include <QLabel>
#include <QWidget>
#include <QMessageBox>



class Tcp_server_reader : public QWidget
{
    Q_OBJECT
public:
    explicit Tcp_server_reader(QObject *parent = nullptr);
    Tcp_server_reader(int n_potr);

public slots:
    virtual void slotNewConnection();
    void slotReadClient();

private:
    QTcpServer* p_tcpServ;
    QTextEdit* m_ptxt;

    quint16 m_nNextBlockSize;

    void sendToClient(QTcpSocket* pSoctket, const QString& str);
};

#endif // MY_SERVER_H
