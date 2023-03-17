#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ElevatorControlSystem.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_startSimBtn_clicked();

    void on_closeBtn_clicked();

    void on_openBtn_pressed();

    void on_openBtn_released();

    void on_upBtn_clicked();

    void on_flrNumDropDown_currentTextChanged(const QString &arg1);

    void on_downBtn_clicked();

    void on_elevNumDropDown_currentTextChanged(const QString &arg1);

    void on_fireBtn_clicked();

    void on_pwroutBtn_clicked();



    void on_doorBlockBtn_clicked();

    void on_pushBtn_clicked();

    void on_overldBtn_clicked();

    void on_helpBtn_clicked();

private:
    Ui::MainWindow *ui;
    ElevatorControlSystem* ecs;
};
#endif // MAINWINDOW_H
