// Виджет "Клиент" выполняет роль карты: встраивается в виджет "Оплата" (Pay_bus)
// Связывается с сервером (картридереом), отправляет запрос на оплату

#include "tcp_client_card.h"

// ----------------------------------------------------------------------
Tcp_client_card::Tcp_client_card(const QString& strHost,
                   int nPort,
                   QWidget* pwgt /*=0*/
                  ) : QWidget(pwgt)
                    , m_nNextBlockSize(0)
{
    m_pTcpSocket = new QTcpSocket(this);

    m_ptxtInfo  = new QTextEdit;
    m_ptxtInfo->setMinimumSize(200,400);
    m_ptxtInfo->setReadOnly(true);

    // связываемся с сервером
    m_pTcpSocket->connectToHost(strHost, nPort);
    m_ptxtInfo->append("Подключение к картридеру: ...");
    // получение сигнала подтверждения связи
    connect(m_pTcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
    // приём сообщение от сервера
    connect(m_pTcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    // обработка сигналов сокета об ошибки
    connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this,         SLOT(slotError(QAbstractSocket::SocketError))
           );

    m_ptxtInput = new QLineEdit("2.00 ₽");

    // отаправка сообщение серверу из поля LineEdit
    connect(m_ptxtInput, SIGNAL(returnPressed()),
            this,        SLOT(slotSendToServer())
           );


    // отаправка сообщение серверу по кнопке оплатить
    pcmd = new QPushButton("&Оплатить");
    connect(pcmd, SIGNAL(clicked()), SLOT(slotSendToServer()));

    //Размещение виджетов
    pvbxLayout = new QVBoxLayout;
    pvbxLayout->addWidget(new QLabel("<H1>Карта</H1>"));
    pvbxLayout->addWidget(m_ptxtInfo);
    pvbxLayout->addWidget(m_ptxtInput);
    pvbxLayout->addWidget(pcmd);
    setLayout(pvbxLayout);
}

Tcp_client_card::~Tcp_client_card()
{
    delete pvbxLayout;
    delete m_pTcpSocket;
    delete m_ptxtInfo;
    delete m_ptxtInput;
    delete pcmd;
}

// ----------------------------------------------------------------------
// приём сообщение от сервера
void Tcp_client_card::slotReadyRead()
{
    QDataStream in(m_pTcpSocket);
    in.setVersion(QDataStream::Qt_5_15);
    for (;;) {
        if (!m_nNextBlockSize) {
            if (m_pTcpSocket->bytesAvailable() < (int)sizeof(quint16)) {
                break;
            }
            in >> m_nNextBlockSize;
        }

        if (m_pTcpSocket->bytesAvailable() < m_nNextBlockSize) {
            break;
        }
        QTime   time;
        QString str;
        in >> time >> str;

        m_ptxtInfo->append(time.toString() + " " + str);
        m_nNextBlockSize = 0;
    }
}

// ----------------------------------------------------------------------
// обработка сигналов сокета об ошибки
void Tcp_client_card::slotError(QAbstractSocket::SocketError err)
{
    QString strError =
        "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                     "The host was not found." :
                     err == QAbstractSocket::RemoteHostClosedError ?
                     "The remote host is closed." :
                     err == QAbstractSocket::ConnectionRefusedError ?
                     "The connection was refused." :
                     QString(m_pTcpSocket->errorString())
                    );
    m_ptxtInfo->append(strError);
}

// ----------------------------------------------------------------------
// отправка на сервер
void Tcp_client_card::slotSendToServer()
{
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_15);
    out << quint16(0) << QTime::currentTime() << m_ptxtInput->text();

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    m_pTcpSocket->write(arrBlock);
    m_ptxtInput->setText("");
}

// ------------------------------------------------------------------
// подтверждение связи
void Tcp_client_card::slotConnected()
{
    m_ptxtInfo->append("Подключение к картридеру: успешно!");
}
