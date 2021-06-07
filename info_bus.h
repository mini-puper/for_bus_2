// Виджет "Инфо": отображает html страницу

#ifndef INFO_BUS_H
#define INFO_BUS_H

#include <QWidget>


namespace Ui {
class Info_bus;
}

class Info_bus : public QWidget
{
    Q_OBJECT

public:
    explicit Info_bus(QWidget *parent = nullptr);
    ~Info_bus();

private:
    Ui::Info_bus *ui;
};

#endif // INFO_BUS_H
