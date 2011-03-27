#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <QWidget>

namespace Ui {
    class progressbar;
}

class progressbar : public QWidget
{
    Q_OBJECT

public:
    explicit progressbar(QWidget *parent = 0);
    ~progressbar();

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::progressbar *ui;
};

extern progressbar w2;

#endif // PROGRESSBAR_H
