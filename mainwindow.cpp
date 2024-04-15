#include "mainwindow.h"
#include <QMessageBox>
#include "ui_mainwindow.h"
//#include <windows.h>
#include <QCloseEvent>
#include <QTimer>
#include <QSystemTrayIcon>
#include <QMenu>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


        timer = new QTimer(this);
        connect (timer, SIGNAL(timeout()),this,SLOT(MySlot()));
        timer->start(1000);



    QMenu *menu = new QMenu(this);
    QAction * quitAction = new QAction(("Zamknij"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    menu->addAction(quitAction);


    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/ikona_traya/batterylovericon.ico"));
    trayIcon->setToolTip("BatteryLover");
    trayIcon->setContextMenu(menu);
    trayIcon->show();
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this, SLOT(IkonaAktywowana(QSystemTrayIcon::ActivationReason)));


    LoadSettings();

}
MainWindow::~MainWindow()
{

    SaveSettings();
    delete ui;
}

void MainWindow::MySlot()
{

    if(zasilanie(0)==255 || zasilanie(0) ==111)
    {
        ErrorBox();
        timer->stop();
    }
    else
    {
       ui->PrNal->display(zasilanie(0));
    }
    if(zasilanie(1)==1)
    {
        ui->Status->setText("Podłączony");
    }
    else if(zasilanie(1) == 255 || zasilanie(1) ==111)
    {
        ErrorBox();
        timer->stop();
    }
    else
    {
        ui->Status->setText("Nie podłączony");
    }
    if(zasilanie(2) == 255 || zasilanie(2) == 128 || zasilanie(2) ==111)
    {
        ErrorBox();
        timer->stop();
    }
    else if(zasilanie(2) == 8 || zasilanie(2) == 10 || zasilanie(2) == 9 || zasilanie(2) ==14)
    {
        ui->Ladowanie->setText("Ładuje");
    }
    else
    {
        ui->Ladowanie->setText("Nie ładuje");
    }

       if(zasilanie(0)==min && flaga_min==true && zasilanie(2) != 8 && zasilanie(2) != 10 && zasilanie(2) != 9 && zasilanie(2) !=14 && ui->checkBox->isChecked()==true)
        {
            trayIcon->showMessage("Podłącz ładowarkę","Dolny poziom naładowania baterii został osiągnięty.",QSystemTrayIcon::Information,5000);
            flaga_min=false;

        }
       if(zasilanie(0)!=min && ui->checkBox->isChecked()==true)
       {
           flaga_min=true;
       }
       if(ui->checkBox->isChecked()==true &&zasilanie(0)==max && flaga_max==true && (zasilanie(2) == 8 || zasilanie(2) == 10 || zasilanie(2) == 9 || zasilanie(2) ==14))
        {
            trayIcon->showMessage("Odłącz ładowarkę","Górny poziom naładowania baterii został osiągnięty.",QSystemTrayIcon::Information,5000);
            flaga_max=false;

        }
       if(zasilanie(0)!=max && ui->checkBox->isChecked()==true)
       {
           flaga_max=true;
       }

}
BYTE MainWindow::zasilanie (short zwracana)
{
   SYSTEM_POWER_STATUS bateria;
   if(GetSystemPowerStatus(&bateria) == true)
     {
       if(zwracana == 0)
         {
           return bateria.BatteryLifePercent;
         }
       else if(zwracana == 1)
         {
           return bateria.ACLineStatus;
         }
       else if(zwracana == 2)
         {
           return bateria.BatteryFlag;
         }
     }
   return 111;
}

void MainWindow::on_checkBox_clicked()
{
    if(ui->checkBox->isChecked())
    {
        ui->Ustawienia->setEnabled(true);
    }
    else
    {
         ui->Ustawienia->setEnabled(false);
    }
}

void MainWindow::on_Ustawienia_clicked()
{
    oknopowiadomien = new OknoPowiadomien(this);
    oknopowiadomien->setModal(true);
    oknopowiadomien->setWindowFlags(oknopowiadomien->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    connect(oknopowiadomien,SIGNAL(PobierzWartosci(int,int)),this,SLOT(OdbierzWartosci(int,int)));

    oknopowiadomien->show();
}
void MainWindow::SaveSettings()
{
    QSettings setting("MT","BatteryLover");
    setting.beginGroup("MainWindow");
    setting.setValue("polozenie",this->geometry());
    setting.setValue("checkbox",ui->checkBox->isChecked());
    setting.setValue("ustawienia",ui->Ustawienia->isEnabled());
    setting.setValue("minimum",min);
    setting.setValue("maksimum",max);
    setting.endGroup();

}
void MainWindow::LoadSettings()
{
    QSettings setting("MT","BatteryLover");
    setting.beginGroup("MainWindow");
    QRect polozenie = setting.value("polozenie").toRect();
    bool checkbox = setting.value("checkbox",true).toBool();
    bool ustawienia = setting.value("ustawienia",true).toBool();
    int minimum = setting.value("minimum",50).toInt();
    int maksimum = setting.value("maksimum",80).toInt();
    min = minimum;
    max = maksimum;
    ui->checkBox->setChecked(checkbox);
    ui->Ustawienia->setEnabled(ustawienia);
    setGeometry(polozenie);
    setting.endGroup();

}

void MainWindow::OdbierzWartosci(int mi,int ma)
{
   min = mi;
   max = ma;
   SaveSettings();
}
void MainWindow::closeEvent(QCloseEvent * event)
{
    event->ignore();
    this->hide();
}
void MainWindow::IkonaAktywowana(QSystemTrayIcon::ActivationReason reason)
{
    if(reason==QSystemTrayIcon::Trigger)
    {
        this->showNormal();
        this->activateWindow();
    }
}

void MainWindow::on_Wyjscie_clicked()
{
    qApp->quit();
}
void MainWindow::ErrorBox()
{
    QMessageBox MsgBox;
    MsgBox.setWindowTitle("Błąd");
    MsgBox.setText("Aplikacja napotkała błąd, wciśnij <i>Ok</i> aby zakończyć jej działanie.");
    MsgBox.setWindowIcon(QIcon(":/ikona_bledu/erroricon.ico"));
    MsgBox.addButton(QMessageBox::Ok);
    if(MsgBox.exec() == QMessageBox::Ok)
    {
        qApp->quit();
    }
}
