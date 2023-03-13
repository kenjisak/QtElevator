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
    ui->outputBox->append(QString::fromStdString(this->ecs->getelevarr()[elevnuminput.toInt()-1]->closeDoor()));
}

void MainWindow::on_openBtn_clicked()
{
    QString elevnuminput = ui->elevNumDropDown->currentText();
    ui->outputBox->append(QString::fromStdString(this->ecs->getelevarr()[elevnuminput.toInt()-1]->openDoor()));
}

void MainWindow::on_upBtn_clicked()
{
    QString flrnuminput = ui->flrNumDropDown->currentText();
    ui->outputBox->append("Floor " + flrnuminput + " Up Btn pressed(light on)");

    int elevnumsent = this->ecs->flrreq("up",flrnuminput.toInt());//sends a req to ecs to send an elevator to the given floor

    if (elevnumsent == -1){
        ui->outputBox->append("All Elevators in use.");
        ui->outputBox->append("Floor " + flrnuminput + " Up Btn(light off)");
    }else{
        ui->outputBox->append("Elevator " + QString::number(elevnumsent) + " has arrived.");
        ui->outputBox->append("Floor " + flrnuminput + " Up Btn(light off)");
        ui->outputBox->append("Elevator " + QString::number(elevnumsent) + " Bell Rings and Opens Door for 5s");

        for(int i = 1;i <= 5;i++){
            ui->outputBox->append(QString::number(i) + "s");
//            QThread::msleep(200);
        }
        ui->outputBox->append("Elevator " + QString::number(elevnumsent) + " Bell Rings and Closes Door");
    }
}

void MainWindow::on_downBtn_clicked()
{
    QString flrnuminput = ui->flrNumDropDown->currentText();
    ui->outputBox->append("Floor " + flrnuminput + " Down Btn pressed(light on)");

    int elevnumsent = this->ecs->flrreq("down",flrnuminput.toInt());//sends a req to ecs to send an elevator to the given floor

    if (elevnumsent == -1){
        ui->outputBox->append("All Elevators in use.");
        ui->outputBox->append("Floor " + flrnuminput + " Up Btn(light off)");
    }else{
        ui->outputBox->append("Elevator " + QString::number(elevnumsent) + " has arrived.");
        ui->outputBox->append("Floor " + flrnuminput + " Up Btn(light off)");
        ui->outputBox->append("Elevator " + QString::number(elevnumsent) + " Bell Rings and Opens Door for 5s");
        //have the passenger walk in here



        for(int i = 1;i <= 5;i++){
            ui->outputBox->append(QString::number(i) + "s");
        }
        ui->outputBox->append("Elevator " + QString::number(elevnumsent) + " Bell Rings and Closes Door");
    }
}

void MainWindow::on_flrNumDropDown_currentTextChanged(const QString &flrnum)
{
    if (flrnum == "1"){//if floor 1 is selected in drop down then disable the down button
        ui->downBtn->setEnabled(false);
    }else{
        ui->downBtn->setEnabled(true);
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

    //send req to ecs of fire safety should return true when all elevators reached safe floor
    //once returned true, append showing all elevators at main floor: elev 1 at floor 1, elev 2 at floor 2

    ui->outputBox->append("======Fire Safety Actived=======");

    ui->outputBox->append(QString::fromStdString(this->ecs->safetyreq("fire")));
    ui->outputBox->append("All Elevators have safely reached the main floor");

}

void MainWindow::on_pwroutBtn_clicked()
{
    ui->outputBox->append("======Power Out Safety Actived=======");
    ui->outputBox->append("All Elevators Displays and Plays audio of these messages: ");
    ui->outputBox->append("Display: Theres a power out in the building, please disembark the elevator once the elevators reach the main floor.");
    ui->outputBox->append("Audio System: *Theres a power out in the building, please disembark the elevator once the elevators reach the main floor.*");

    ui->outputBox->append(QString::fromStdString(this->ecs->safetyreq("powerout")));
    ui->outputBox->append("All Elevators have safely reached the main floor");

}
