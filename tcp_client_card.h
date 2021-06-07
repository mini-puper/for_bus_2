// Виджет "Клиент" выполняет роль карты: встраивается в виджет "Оплата" (Pay_bus)
// Связывается с сервером (картридереом), отправляет запрос на оплату

#ifndef _Tcp_client_card_h_
#define _Tcp_client_card_h_

#include <QWidget>
#include <QTcpSocket>

class QTextEdit;
class QLineEdit;

// ======================================================================
class Tcp_client_card : public QWidget {
Q_OBJECT
private:
    QTcpSocket* m_pTcpSocket;
    QTextEdit*  m_ptxtInfo;
    QLineEdit*  m_ptxtInput;

    quint16     m_nNextBlockSize;

public:
    Tcp_client_card(const QString& strHost, int nPort, QWidget* pwgt = 0) ;

private slots:
    void slotReadyRead   ();
    void slotError       (QAbstractSocket::SocketError);
    void slotSendToServer();
    void slotConnected   ();
};
#endif  //_Tcp_client_card_h_
