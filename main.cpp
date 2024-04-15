#include "mainwindow.h"
#include "errorwindow.h"
#include <QApplication>
//#include <windows.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SYSTEM_POWER_STATUS lpSysPwrStatus;
    if(GetSystemPowerStatus(&lpSysPwrStatus)==false || lpSysPwrStatus.BatteryFlag ==128 || lpSysPwrStatus.BatteryFlag == 255 || lpSysPwrStatus.ACLineStatus == 255)
    {
        ErrorWindow error;
        error.setWindowFlags(Qt::WindowCloseButtonHint);                              //logika błędów
        error.show();
//
        return a.exec();
    }
    else
    {
        MainWindow w;

        w.show();
        return a.exec();
    }






}
