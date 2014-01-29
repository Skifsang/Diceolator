#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Dice.h"
#include <QString>
#include <QDebug>
#include "Character.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

int calculateModifier (const int number){
    if (number % 2 != 0){
        return ((number - 1) / 2) - 5;
    }
    else return (number / 2) - 5;
}

int calculateCandidatToBecomeAbility (){
    int arrayOfD6Throws[3];

    for (int i = 0; i < 4; i++){
        arrayOfD6Throws[i] = Dice(6).throwDice(1, 0);
    }

    for(int i = 0; i < 3; i++)
    {
        for(int j = i + 1; j < 4; j++)
        {
            if (arrayOfD6Throws[i] < arrayOfD6Throws[j])
            {
                int temp = arrayOfD6Throws[i];
                arrayOfD6Throws[i] = arrayOfD6Throws[j];
                arrayOfD6Throws[j] = temp;
            }
        }
    }

    int sum = arrayOfD6Throws[0] + arrayOfD6Throws[1] + arrayOfD6Throws[2];
    return sum;
}

void MainWindow::on_Calculate_pressed()
{
    int sum = 0;
    sum += Dice(4).throwDice(ui->spinBoxD4->value(), ui->spinBoxD4Modifier->value());
    sum += Dice(6).throwDice(ui->spinBoxD6->value(), ui->spinBoxD6Modifier->value());
    sum += Dice(8).throwDice(ui->spinBoxD8->value(), ui->spinBoxD8Modifier->value());
    sum += Dice(12).throwDice(ui->spinBoxD12->value(), ui->spinBoxD12Modifier->value());
    sum += Dice(20).throwDice(ui->spinBoxD20->value(), ui->spinBoxD20Modifier->value());
    ui->sumLabel->setText(QString::number(sum));
}



void MainWindow::on_calculatesCandidateToBecomeAbility_pressed()
{
    Character heroTemplate(0, 0, 0, 0, 0, 0);

    ui->labelCandidatToBecomeAbility1->setText(QString::number(calculateCandidatToBecomeAbility()));
    ui->labelCandidatToBecomeAbility2->setText(QString::number(calculateCandidatToBecomeAbility()));
    ui->labelCandidatToBecomeAbility3->setText(QString::number(calculateCandidatToBecomeAbility()));
    ui->labelCandidatToBecomeAbility4->setText(QString::number(calculateCandidatToBecomeAbility()));
    ui->labelCandidatToBecomeAbility5->setText(QString::number(calculateCandidatToBecomeAbility()));
    ui->labelCandidatToBecomeAbility6->setText(QString::number(calculateCandidatToBecomeAbility()));

    ui->labelCandidatToBecomeAbility1Modifier
            ->setText(QString::number(calculateModifier
                                      (ui->labelCandidatToBecomeAbility1->text().toInt())));
    ui->labelCandidatToBecomeAbility2Modifier
            ->setText(QString::number(calculateModifier
                                      (ui->labelCandidatToBecomeAbility2->text().toInt())));
    ui->labelCandidatToBecomeAbility3Modifier
            ->setText(QString::number(calculateModifier
                                      (ui->labelCandidatToBecomeAbility3->text().toInt())));
    ui->labelCandidatToBecomeAbility4Modifier
            ->setText(QString::number(calculateModifier
                                      (ui->labelCandidatToBecomeAbility4->text().toInt())));
    ui->labelCandidatToBecomeAbility5Modifier
            ->setText(QString::number(calculateModifier
                                      (ui->labelCandidatToBecomeAbility5->text().toInt())));
    ui->labelCandidatToBecomeAbility6Modifier
            ->setText(QString::number(calculateModifier
                                      (ui->labelCandidatToBecomeAbility6->text().toInt())));

    if ((ui->labelCandidatToBecomeAbility1Modifier->text().toInt() +
            ui->labelCandidatToBecomeAbility2Modifier->text().toInt() +
            ui->labelCandidatToBecomeAbility3Modifier->text().toInt() +
            ui->labelCandidatToBecomeAbility4Modifier->text().toInt() +
            ui->labelCandidatToBecomeAbility5Modifier->text().toInt() +
            ui->labelCandidatToBecomeAbility6Modifier->text().toInt() > 0) &&
        ((ui->labelCandidatToBecomeAbility1->text().toInt() >= 13) ||
         (ui->labelCandidatToBecomeAbility2->text().toInt() >= 13) ||
         (ui->labelCandidatToBecomeAbility3->text().toInt() >= 13) ||
         (ui->labelCandidatToBecomeAbility4->text().toInt() >= 13) ||
         (ui->labelCandidatToBecomeAbility5->text().toInt() >= 13) ||
         (ui->labelCandidatToBecomeAbility6->text().toInt() >= 13))){

        ui->calculatesCandidateToBecomeAbility
                ->setText("Получившиеся значения достаточно высоки, вы не имеете права выбрать другие");
        ui->calculatesCandidateToBecomeAbility->setEnabled(false);
    }
}
