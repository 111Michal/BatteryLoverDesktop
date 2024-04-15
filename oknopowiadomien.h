#ifndef OKNOPOWIADOMIEN_H
#define OKNOPOWIADOMIEN_H

#include <QDialog>
#include <QSettings>

namespace Ui {
class OknoPowiadomien;
}

class OknoPowiadomien : public QDialog
{
    Q_OBJECT

public:

    explicit OknoPowiadomien(QWidget *parent = nullptr);
    ~OknoPowiadomien();
signals:
    void PobierzWartosci(int mi,int ma);

private slots:
    void on_pushButton_clicked();
    void AktywatorPrzycisku(int wartosc);




private:
    Ui::OknoPowiadomien *ui;
    void SaveSettings();
    void LoadSettings();


};

#endif // OKNOPOWIADOMIEN_H
