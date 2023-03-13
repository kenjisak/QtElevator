#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ElevatorControlSystem.h>
#include <Door.h>
#include <Floor.h>

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

    void on_openBtn_clicked();

    void on_upBtn_clicked();

    void on_flrNumDropDown_currentTextChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    Door* doortest;
    Floor** floortest;
    ElevatorControlSystem* ecs;
};
#endif // MAINWINDOW_H
