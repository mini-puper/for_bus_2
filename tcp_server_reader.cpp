// Виджет "Сервер" выполняет роль картридера: встраивается в виджет "Оплата" (Pay_bus)
// Принимает карту, подтверждает оплату

#include "tcp_server_reader.h"

Tcp_server_reader::Tcp_server_reader(int n_potr) : m_nNextBlockSize(0)
{
    p_tcpServ = new QTcpServer(this);

    if (!p_tcpServ->listen(QHostAddress::Any, n_potr)) {
        QMessageBox::critical(0,
                              "Server Error",
                              "Unable to start the server:"
                              + p_tcpServ->errorString()
                             );
        p_tcpServ->close();
        return;
    }

    connect(p_tcpServ, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));

    m_ptxt = new QTextEdit();
    m_ptxt->setReadOnly(true);
    m_ptxt->setMinimumSize(200,400);

    //настройка layout
    QVBoxLayout* pvbxLayout = new QVBoxLayout;
    pvbxLayout->addWidget(new QLabel("<H1>Картридер</H1>"));
    pvbxLayout->addWidget(m_ptxt);
    this->setLayout(pvbxLayout);
}

// слот обработки нового  соединения, выделение сокета
void Tcp_server_reader::slotNewConnection()
{
    QTcpSocket  *pClientSocket = p_tcpServ->nextPendingConnection();

    connect(pClientSocket, SIGNAL(disconnected()), pClientSocket, SLOT(deleteLater()));

    connect(pClientSocket, SIGNAL(readyRead()), this, SLOT(slotReadClient()));

    sendToClient(pClientSocket, "Ответ сервера: Клиент подключен!");
    m_ptxt->append("Подключен новый клиент!");

}

// приём от клиента
void Tcp_server_reader::slotReadClient()
{
    QTcpSocket* pClientSocket = (QTcpSocket*)sender();
    QDataStream in(pClientSocket);
    in.setVersion(QDataStream::Qt_5_15);
    for (;;) {
        if (!m_nNextBlockSize) {
            if (pClientSocket->bytesAvailable() < (int)sizeof(quint16)) {
                break;
            }
            in >> m_nNextBlockSize;
        }

        if (pClientSocket->bytesAvailable() < m_nNextBlockSize) {
            break;
        }
        QTime   time;
        QString str;
        in >> time >> str;

        QString strMessage =
            time.toString() + " " + "Клиент отправил - " + str;
        m_ptxt->append(strMessage);

        m_nNextBlockSize = 0;

        sendToClient(pClientSocket,
                     "Ответ сервера: Получил \"" + str + " - операция выполнена!" +"\""
                    );
    }
}

// отпрвка клиенту
void Tcp_server_reader::sendToClient(QTcpSocket* pSocket, const QString& str)
{
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_15);
    out << quint16(0) << QTime::currentTime() << str;

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    pSocket->write(arrBlock);
}
