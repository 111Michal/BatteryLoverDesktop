#include "oknopowiadomien.h"
#include "ui_oknopowiadomien.h"
#include <QMessageBox>
//#include <QSettings>


OknoPowiadomien::OknoPowiadomien(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OknoPowiadomien)
{
    ui->setupUi(this);
    LoadSettings();
    connect(ui->WartoscMax, SIGNAL(valueChanged(int)),this,SLOT(AktywatorPrzycisku(int)));
    connect(ui->WartoscMin, SIGNAL(valueChanged(int)),this,SLOT(AktywatorPrzycisku(int)));
}

OknoPowiadomien::~OknoPowiadomien()
{
    delete ui;
}

void OknoPowiadomien::SaveSettings()
{
    QSettings setting("MT","BatteryLover");
    setting.beginGroup("OknoPowiadomien");
    setting.setValue("wartoscmin",ui->WartoscMin->value());
    setting.setValue("wartoscmax",ui->WartoscMax->value());
    setting.endGroup();
}
void OknoPowiadomien::LoadSettings()
{
    QSettings setting("MT","BatteryLover");
    setting.beginGroup("OknoPowiadomien");
    int wartoscmin = setting.value("wartoscmin",50).toInt();
    int wartoscmax = setting.value("wartoscmax",80).toInt();
    ui->WartoscMin->setValue(wartoscmin);
    ui->WartoscMax->setValue(wartoscmax);
    setting.endGroup();

}

void OknoPowiadomien::on_pushButton_clicked()
{
  SaveSettings() ;
  emit PobierzWartosci(ui->WartoscMin->value(),ui->WartoscMax->value());
  QMessageBox::information(this,"Informacja","Ustawienia zostały zapisane.");
  ui->pushButton->setEnabled(false);

}
void OknoPowiadomien::AktywatorPrzycisku(int wartosc)
{
   ui->pushButton->setEnabled(true);
   if(wartosc==0)
   {
      ui->EasterText->setStyleSheet("QLabel{color: #DC143C;}");
      ui->EasterText->setText("Śmieszek:)");
   }
   else if(wartosc!=0 && ui->EasterText->text() == "Śmieszek:)")
   {
       ui->EasterText->setText("");
   }

}

