#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "oknopowiadomien.h"
#include <QMainWindow>
#include <QSystemTrayIcon>
#include <windows.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTimer *timer;


public slots:
    void OdbierzWartosci(int mi,int ma);
    void MySlot();
private slots:
    void on_checkBox_clicked();
    void IkonaAktywowana(QSystemTrayIcon::ActivationReason reason);
    void on_Wyjscie_clicked();
    void on_Ustawienia_clicked();

protected:
    void closeEvent(QCloseEvent * event);


private:
    QSystemTrayIcon *trayIcon;
    Ui::MainWindow *ui;
    OknoPowiadomien *oknopowiadomien;

    void SaveSettings();
    void LoadSettings();
    void ErrorBox();
    BYTE zasilanie (short zwracana);
    int min=0;
    int max=0;
    bool flaga_min = true;
    bool flaga_max = true;

};


#endif // MAINWINDOW_H
