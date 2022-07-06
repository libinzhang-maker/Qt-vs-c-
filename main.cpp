#pragma execution_character_set("utf-8")
#include "WaKAwaka.h"
#include <QtWidgets/QApplication>
#include    <QPixmap>
#include    <QSplashScreen>
#include    "qdlgLogin.h"

#include    <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDlgLogin* dlgLogin = new QDlgLogin; //创建对话框

    if (dlgLogin->exec() == QDialog::Accepted)
    {
        //        delete dlgLogin;
        WaKAwaka w;

        w.show();
        return a.exec();
    }
    else
        return  0;

}
