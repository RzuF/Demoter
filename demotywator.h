#ifndef DEMOTYWATOR_H
#define DEMOTYWATOR_H

#include <QMainWindow>
#include <QtGui>
#include <QUrl>
#include <QtWebKit>
#include <QWebElement>
#include <QWebFrame>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

#include "demotywator.h"
#include "ui_demotywator.h"
#include "progressbar.h"

namespace Ui {
    class demotywator;
}

class demotywator : public QMainWindow
{
    Q_OBJECT

public:
    explicit demotywator(QWidget *parent = 0);
    ~demotywator();

private:
    Ui::demotywator *ui;

    QDataStream out;
    QDataStream in;
    QString curDem;

    QString HTMLpage;

    QWebPage webpage;
    QStringList obrazki, tytuly, wysokosc, obrazki_f, tytuly_f;
    QUrl currentUrl, mainUrl;
    int strona, demot;
    QEventLoop loop;

    QNetworkAccessManager nvm;

    progressbar lol;

public slots:

    void zczytaj_tytuly();
    void gotowe();
    void pokaz();
    void enable();

    void nextDemot();
    void prevDemot();

    void nextPage();
    void prevPage();

    void czytaj(QString);
    void connector(QNetworkReply*);

signals:

    void connectorFinished();

};
#endif // DEMOTYWATOR_H
