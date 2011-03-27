#include "demotywator.h"
#include "progressbar.h"

demotywator::demotywator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::demotywator)
{
    ui->setupUi(this);

    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(nextPage()));
    //connect(ui->pushButton_4, SIGNAL(clicked()), ui->webView, SLOT(reload()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(gotowe()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(nextDemot()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(prevDemot()));

    connect(&nvm, SIGNAL(finished(QNetworkReply*)), this, SLOT(connector(QNetworkReply*)));

    //connect(webpage.mainFrame(), SIGNAL(loadFinished(bool)), &loop, SLOT(quit()));

    strona = 0;
    demot = 0;

    currentUrl.setUrl("http://demotywatory.pl/page/");
    mainUrl.setUrl("http://demotywatory.pl/page/1");

}

demotywator::~demotywator()
{
    delete ui;
}

void demotywator::enable()
{
    this->setEnabled(true);
}

void demotywator::gotowe()
{
    int wys = 200;

    ui->webView->setMinimumHeight(wys);
    ui->webView->setMaximumHeight(wys);

    QWebElement img = ui->webView->page()->mainFrame()->findFirstElement("img");
    wys = img.geometry().height();
    QString wysx;
    wysx.setNum(wys);

    QMessageBox::information(this, "Wymiar", "Wysokosc: " + wysx);
}

void demotywator::nextPage()
{
    strona++;
    ui->lcdNumber->display(strona);

    lol.show();
    this->setEnabled(false);

    connect(&lol, SIGNAL(destroyed()), this, SLOT(enable()));

    QWidget::setCursor(Qt::WaitCursor);

    QString url;
    url.setNum(strona);

    czytaj("http://demotywatory.pl/page/" + url);

    QMessageBox::information(this, "Sukces!","Ładowanie zakończono pomyślnie :)");

    zczytaj_tytuly();

    QWidget::setCursor(Qt::ArrowCursor);
    this->setEnabled(true);
    lol.hide();

}

void demotywator::prevPage()
{
    if(strona==1) return;

    strona--;

    QString url;
    url.setNum(strona);
    currentUrl.setUrl("http://demotywatory.pl/page/" + url);

}

void demotywator::zczytaj_tytuly()
{
    int k;
    QWebElementCollection tytuly_e;
    QWebElementCollection obrazki_e;

    do
    {

    QWebFrame *frame = webpage.mainFrame();
    QWebElement document = frame->documentElement();

    tytuly_e = document.findAll("h1.demot");
    obrazki_e = document.findAll("img.demot");

    //===

    k = tytuly_e.count();
    }
    while(k!=10);

    for(int i=0 ; i<k ; i++)
    {
        QWebElement test = tytuly_e.at(i);
        QWebElement test2 = obrazki_e.at(i);

        tytuly << test.toPlainText();
        obrazki << test2.attribute("src");
        wysokosc << test2.attribute("height");
        if(wysokosc.at(i)==0) { }
    }
    if(k!=0) pokaz();
}

void demotywator::pokaz()
{
    QUrl curDem(obrazki.at(demot));
    int wys = wysokosc.at(demot).toInt();

    ui->label->setText(tytuly.at(demot));
    ui->webView->setUrl(curDem);
    ui->webView->setMinimumHeight(wys);
    ui->webView->setMaximumHeight(wys);
}

void demotywator::nextDemot()
{
    if(demot==(tytuly.count()-1)) nextPage();

    demot++;

    pokaz();
}

void demotywator::prevDemot()
{
    if(demot==0) return;

    demot--;

    pokaz();
}

void demotywator::connector(QNetworkReply * reply)
{
    HTMLpage = reply->readAll();

    emit connectorFinished();
}

void demotywator::czytaj(QString url)
{
    QUrl urlx(url);

    QNetworkRequest request(urlx);
    request.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::PreferCache);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    QByteArray data;

    nvm.post(request, data);

    connect(this, SIGNAL(connectorFinished()), &loop, SLOT(quit()));
    loop.exec();
    this->disconnect(&loop);

    webpage.mainFrame()->setHtml(HTMLpage);
    HTMLpage.clear();
}
