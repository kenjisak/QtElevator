#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//just testing commit

void MainWindow::on_startSimBtn_clicked()
{
    QString flrnuminput = ui->flrNuminit->text();
    QString elevnuminput = ui->elevNuminit->text();

    if (flrnuminput != "" || elevnuminput != ""){
        ui->outputBox->append("Number of Floors created: " + flrnuminput);
        ui->outputBox->append("Number of Elevators created: " + elevnuminput);
    }


}
