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
    QString passnuminput = ui->passNuminit->text();
    QString maxweightinput = ui->maxlbsInput->text();

    if (flrnuminput != "" && elevnuminput != "" && maxweightinput != ""){
        this->ecs = new ElevatorControlSystem(elevnuminput.toInt(),flrnuminput.toInt(),maxweightinput.toInt(),passnuminput.toInt());

//        ui->outputBox->setText("");
        ui->outputBox->append("Number of Floors created: " + flrnuminput);
        ui->outputBox->append("Number of Elevators created: " + elevnuminput);
        ui->outputBox->append("Number of Passengers created: " + passnuminput);

        for (int i = 0;i < flrnuminput.toInt();i++){
            ui->flrNumDropDown->addItem(QString::number(i+1));
            ui->flrNumDropDown_2->addItem(QString::number(i+1));
        }

        for (int i = 0;i < elevnuminput.toInt();i++){
            ui->elevNumDropDown->addItem(QString::number(i+1));
        }

        for (int i = 0;i < passnuminput.toInt();i++){
            ui->passNumDropDown->addItem(QString::number(i+1));
        }

        ui->elevNuminit->setReadOnly(true);
        ui->flrNuminit->setReadOnly(true);
        ui->passNuminit->setReadOnly(true);
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
    QString passnuminput = ui->passNumDropDown->currentText();
    ui->outputBox->append(QString::fromStdString(this->ecs->getelevarr()[elevnuminput.toInt()-1]->closeDoor()));
}

//void MainWindow::on_openBtn_clicked()
//{
//    QString elevnuminput = ui->elevNumDropDown->currentText();
//    ui->outputBox->append(QString::fromStdString(this->ecs->getelevarr()[elevnuminput.toInt()-1]->openDoor()));
//}
void MainWindow::on_openBtn_pressed()
{
    QString elevnuminput = ui->elevNumDropDown->currentText();
    ui->outputBox->append(QString::fromStdString(this->ecs->getelevarr()[elevnuminput.toInt()-1]->holdOpenDoor()));
}

void MainWindow::on_openBtn_released()
{
    QString elevnuminput = ui->elevNumDropDown->currentText();
    ui->outputBox->append(QString::fromStdString(this->ecs->getelevarr()[elevnuminput.toInt()-1]->closeDoor()));
}
void MainWindow::on_upBtn_clicked()
{
    QString flrnuminput = ui->flrNumDropDown->currentText();
    QString passnuminput = ui->passNumDropDown->currentText();
    ui->outputBox->append(QString::fromStdString(this->ecs->flrreq("up",flrnuminput.toInt(),passnuminput.toInt())));
    //pass in the pointer of the the elev dropdown and currweight linedit to be able to edit inside of ecs
}

void MainWindow::on_downBtn_clicked()
{
    QString flrnuminput = ui->flrNumDropDown->currentText();
    QString passnuminput = ui->passNumDropDown->currentText();
    ui->outputBox->append(QString::fromStdString(this->ecs->flrreq("down",flrnuminput.toInt(),passnuminput.toInt())));
    //pass in the pointer of the the elev dropdown and currweight linedit to be able to edit inside of ecs
}

void MainWindow::on_flrNumDropDown_currentTextChanged(const QString &flrnum)
{
    if (flrnum == "1"){//if ground floor is selected in drop down then disable the down button
        ui->downBtn->setEnabled(false);
    }else{
        ui->downBtn->setEnabled(true);
    }

    QString topfloor = ui->flrNuminit->text();

    if (flrnum == topfloor){//if top floor is selected in drop down then disable the up button
        ui->upBtn->setEnabled(false);
    }else{
        ui->upBtn->setEnabled(true);
    }
}

void MainWindow::on_elevNumDropDown_currentTextChanged(const QString &elevnum)
{
    ui->currlbsInput->setText(QString::number(this->ecs->getelevarr()[elevnum.toInt()-1]->getcurrweight()));
}

void MainWindow::on_fireBtn_clicked()
{
    //append fire safety activated
    //append these are the messages shown in each elevator
    //append Display: Theres a fire in the building, please disembark the elevator once the elevators reach the main floor.
    //append Audio System: *Theres a fire in the building, please disembark the elevator once the elevators reach the main floor.*

    ui->outputBox->append("\n======Fire Safety Actived=======");
    ui->outputBox->append("All Elevators Displays and Plays audio of these messages: ");

    ui->outputBox->append(QString::fromStdString(this->ecs->safetyreq("fire")));
}

void MainWindow::on_pwroutBtn_clicked()
{
    ui->outputBox->append("\n======Power Out Safety Actived=======");
    ui->outputBox->append("All Elevators Displays and Plays audio of these messages: ");

    ui->outputBox->append(QString::fromStdString(this->ecs->safetyreq("powerout")));
}


void MainWindow::on_doorBlockBtn_clicked()
{
    ui->outputBox->append("\n======Door Block Safety Actived=======");

    ui->outputBox->append(QString::fromStdString(this->ecs->elevsafetyreq("obstacle",0)));//set to just trigger the first elevator

}
