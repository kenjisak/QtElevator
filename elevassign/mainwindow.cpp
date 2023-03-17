#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>


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
            ui->destflrNumDropDown->addItem(QString::number(i+1));
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

//        QTimer* timer = new QTimer(this);
//        connect(timer,&QTimer::timeout,this,[&](){
//            ui->currtimeEdit->setTime(QTime::currentTime());
//        });
//        timer->start(1000); //this chunk syncs the current time by seconds, but not needed as wont be able to edit the time
    }
}

void MainWindow::on_closeBtn_clicked()
{
    int elevnuminput = ui->elevNumDropDown->currentText().toInt();
    QString passnuminput = ui->passNumDropDown->currentText();

    QString allactions = "\nPassenger " + passnuminput + " pressed close door button in Car " + QString::number(elevnuminput);//selected passenger pressed close door in selected car
    allactions += QString::fromStdString(this->ecs->getelevarr()[elevnuminput - 1]->closeDoor());//close door in selected elev

    ui->outputBox->append(allactions);
}

void MainWindow::on_openBtn_pressed()
{
    int elevnuminput = ui->elevNumDropDown->currentText().toInt();
    QString passnuminput = ui->passNumDropDown->currentText();

    QString allactions = "\nPassenger " + passnuminput + " pressed open door button in Car " + QString::number(elevnuminput);//selected passenger pressed open door in selected car
    allactions += QString::fromStdString(this->ecs->getelevarr()[elevnuminput - 1]->holdOpenDoor());//open door in selected elev

    ui->outputBox->append(allactions);
}

void MainWindow::on_openBtn_released()
{
    int elevnuminput = ui->elevNumDropDown->currentText().toInt();
    QString passnuminput = ui->passNumDropDown->currentText();

    QString allactions = "\nPassenger " + passnuminput + " released open door button in Car " + QString::number(elevnuminput);//selected passenger released open door in selected car
    allactions += QString::fromStdString(this->ecs->getelevarr()[elevnuminput - 1]->closeDoor());//close door in selected elev

    ui->outputBox->append(allactions);
}
void MainWindow::on_upBtn_clicked()
{
    int flrnuminput = ui->flrNumDropDown->currentText().toInt();
    int passnuminput = ui->passNumDropDown->currentText().toInt();
    QTime currenttime = ui->currtimeEdit->time();
    QComboBox* elevdropdown = ui->elevNumDropDown;
    QLineEdit* currweightdisplay = ui->currlbsInput;

    ui->outputBox->append(QString::fromStdString(this->ecs->flrreq("up",flrnuminput,passnuminput,currenttime,elevdropdown,currweightdisplay)));
    //pass in the pointer of the the elev dropdown and currweight linedit to be able to edit inside of ecs
}

void MainWindow::on_downBtn_clicked()
{
    int flrnuminput = ui->flrNumDropDown->currentText().toInt();
    int passnuminput = ui->passNumDropDown->currentText().toInt();
    QTime currenttime = ui->currtimeEdit->time();
    QComboBox* elevdropdown = ui->elevNumDropDown;
    QLineEdit* currweightdisplay = ui->currlbsInput;

    ui->outputBox->append(QString::fromStdString(this->ecs->flrreq("down",flrnuminput,passnuminput,currenttime,elevdropdown,currweightdisplay)));
    //pass in the pointer of the the elev dropdown and currweight linedit to be able to edit inside of ecs
}

void MainWindow::on_pushBtn_clicked()
{
    int destflrnuminput = ui->destflrNumDropDown->currentText().toInt();
    int elevnuminput = ui->elevNumDropDown->currentText().toInt();
    int passnuminput = ui->passNumDropDown->currentText().toInt();
        QLineEdit* currweightdisplay = ui->currlbsInput;

    ui->outputBox->append(QString::fromStdString(this->ecs->elevreq(destflrnuminput,elevnuminput,passnuminput,currweightdisplay)));
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
{//find a better way to always update
    ui->currlbsInput->setText(QString::number(this->ecs->getelevarr()[elevnum.toInt()-1]->getcurrweight()));
}

void MainWindow::on_fireBtn_clicked()
{
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

    ui->outputBox->append(QString::fromStdString(this->ecs->elevsafetyreq("obstacle",0,-1)));//set to just trigger the first elevator

}

void MainWindow::on_overldBtn_clicked()
{
    int flrnuminput = ui->flrNumDropDown->currentText().toInt();
    int heavypass = ui->passNuminit->text().toInt();//num of passengers, is the last pos in pass array we init as the heavy passenger for this case
    QTime currenttime = ui->currtimeEdit->time();
    QComboBox* elevdropdown = ui->elevNumDropDown;
    QLineEdit* currweightdisplay = ui->currlbsInput;

    ui->outputBox->append(QString::fromStdString(this->ecs->flrreq("up",flrnuminput,heavypass + 1,currenttime,elevdropdown,currweightdisplay)));
}

void MainWindow::on_helpBtn_clicked()
{
    int elevnuminput = ui->elevNumDropDown->currentText().toInt();
    int passnuminput = ui->passNumDropDown->currentText().toInt();

    ui->outputBox->append(QString::fromStdString(this->ecs->elevsafetyreq("help",elevnuminput,passnuminput)));
}
