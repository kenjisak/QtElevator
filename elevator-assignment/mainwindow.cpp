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
    QString maxweightinput = ui->maxlbsInput->text();

    if (flrnuminput != "" && elevnuminput != "" && maxweightinput != ""){
        this->ecs = new ElevatorControlSystem(elevnuminput.toInt(),flrnuminput.toInt(),maxweightinput.toInt());

        for (int i = 0;i < flrnuminput.toInt();i++){
            ui->outputBox->append("Test flr num through ECS: " + QString::number(this->ecs->getflrarr()[i]->getflrnum()));
        }

        for (int i = 0;i < elevnuminput.toInt();i++){
            ui->outputBox->append("Test elev num through ECS: " + QString::number(this->ecs->getelevarr()[i]->getElevNum()));
        }


        ui->outputBox->append("Number of Floors created: " + flrnuminput);
        ui->outputBox->append("Number of Elevators created: " + elevnuminput);

        for (int i = 0;i < flrnuminput.toInt();i++){
            ui->flrNumDropDown->addItem(QString::number(i+1));
            ui->flrNumDropDown_2->addItem(QString::number(i+1));
        }

        for (int i = 0;i < elevnuminput.toInt();i++){
            ui->elevNumDropDown->addItem(QString::number(i+1));
        }

        ui->elevNuminit->setReadOnly(true);
        ui->flrNuminit->setReadOnly(true);
        ui->maxlbsInput->setReadOnly(true);

        ui->startSimBtn->setEnabled(false);

        ui->upBtn->setEnabled(true);

        ui->pushBtn->setEnabled(true);
        ui->helpBtn->setEnabled(true);
        ui->openBtn->setEnabled(true);
        ui->closeBtn->setEnabled(true);

        ui->fireBtn->setEnabled(true);
        ui->overldBtn->setEnabled(true);
        ui->pwroutBtn->setEnabled(true);
        ui->doorBlockBtn->setEnabled(true);
    }
}

void MainWindow::on_closeBtn_clicked()
{
    QString elevnuminput = ui->elevNumDropDown->currentText();
    this->ecs->getelevarr()[elevnuminput.toInt()-1]->closeDoor();
    ui->outputBox->append("Elevator " + elevnuminput + " Door is now Closed.");
}

void MainWindow::on_openBtn_clicked()
{
    QString elevnuminput = ui->elevNumDropDown->currentText();
    this->ecs->getelevarr()[elevnuminput.toInt()-1]->openDoor();
    ui->outputBox->append("Elevator " + elevnuminput + " Door is now Open.");
}


void MainWindow::on_upBtn_clicked()
{
    QString flrnuminput = ui->flrNumDropDown->currentText();
    this->ecs->flrreq("up",flrnuminput.toInt());

}

void MainWindow::on_flrNumDropDown_currentTextChanged(const QString &flrnum)
{
    if (flrnum == "1"){//if floor 1 is selected in drop down then disable the down button
        ui->downBtn->setEnabled(false);
    }else{
        ui->downBtn->setEnabled(true);
    }
}
