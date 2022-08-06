#ifndef WINDOWADDTRANSISTOR_H
#define WINDOWADDTRANSISTOR_H
#include <QMainWindow>
namespace Ui {
    class windowAddTransistor;
}

class windowAddTransistor : public QMainWindow
{
    Q_OBJECT
public:
    MW_ADD_TRANSISTOR
    explicit windowAddTransistor(QWidget *parent = 0);
            ~windowAddTransistor();

private:
    Ui::windowAddTransistor *Ui;
};

#endif // WINDOWADDTRANSISTOR_H
