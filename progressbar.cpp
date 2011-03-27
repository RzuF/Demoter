#include "progressbar.h"
#include "ui_progressbar.h"
#include "demotywator.h"

extern demotywator w;

progressbar::progressbar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::progressbar)
{
    ui->setupUi(this);
}

progressbar::~progressbar()
{
    delete ui;
}

void progressbar::closeEvent(QCloseEvent *event)
{
    //if(!demotywator::isEnabled()) demotywator::setEnabled(true);
    event->accept();
}
