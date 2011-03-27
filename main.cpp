#include <QtGui/QApplication>
#include "demotywator.h"
#include "progressbar.h"

extern progressbar x;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    demotywator w;
    w.show();

    return a.exec();
}
