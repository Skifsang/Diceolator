#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Dice.h"
#include <QString>
#include <QDebug>
#include "Character.h"
#include <QComboBox>

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

const int lowerThresholdAbility = 13;
const QString youAbilityHighEnough = "Получившиеся значения достаточно высоки. Чтобы получить другие перезагрузите игру";
int count = 0;
QStringList listOfCandidatsToBecomeAbility;

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
   // Character heroTemplate(0, 0, 0, 0, 0, 0);

    setupAbilites(ui->labelCandidatToBecomeAbility1, ui->labelCandidatToBecomeAbility1Modifier);
    setupAbilites(ui->labelCandidatToBecomeAbility2, ui->labelCandidatToBecomeAbility2Modifier);
    setupAbilites(ui->labelCandidatToBecomeAbility3, ui->labelCandidatToBecomeAbility3Modifier);
    setupAbilites(ui->labelCandidatToBecomeAbility4, ui->labelCandidatToBecomeAbility4Modifier);
    setupAbilites(ui->labelCandidatToBecomeAbility5, ui->labelCandidatToBecomeAbility5Modifier);
    setupAbilites(ui->labelCandidatToBecomeAbility6, ui->labelCandidatToBecomeAbility6Modifier);

    listOfCandidatsToBecomeAbility << ui->labelCandidatToBecomeAbility1->text() <<
                                      ui->labelCandidatToBecomeAbility2->text() <<
                                      ui->labelCandidatToBecomeAbility3->text() <<
                                      ui->labelCandidatToBecomeAbility4->text() <<
                                      ui->labelCandidatToBecomeAbility5->text() <<
                                      ui->labelCandidatToBecomeAbility6->text();

    if (checkForLowerAbility(ui->labelCandidatToBecomeAbility1, ui->labelCandidatToBecomeAbility2,
                             ui->labelCandidatToBecomeAbility3, ui->labelCandidatToBecomeAbility4,
                             ui->labelCandidatToBecomeAbility5, ui->labelCandidatToBecomeAbility6)){

        ui->calculatesCandidateToBecomeAbility
                ->setText(youAbilityHighEnough);
        ui->calculatesCandidateToBecomeAbility->setEnabled(false);
    }

    setupComboBoxes(ui->comboBoxStrength, & listOfCandidatsToBecomeAbility);
    setupComboBoxes(ui->comboBoxDexterity, & listOfCandidatsToBecomeAbility);
    setupComboBoxes(ui->comboBoxConstitution, & listOfCandidatsToBecomeAbility);
    setupComboBoxes(ui->comboBoxIntelligence, & listOfCandidatsToBecomeAbility);
    setupComboBoxes(ui->comboBoxWisdom, & listOfCandidatsToBecomeAbility);
    setupComboBoxes(ui->comboBoxCharisma, & listOfCandidatsToBecomeAbility);
}

//Процедура отображения полученных вычислений пользователю
void MainWindow::setupAbilites(QLabel * labelAbility, QLabel * labelAbilityModifier)
{
    labelAbility->setText(QString::number(calculateCandidatToBecomeAbility()));
    labelAbilityModifier->setText(QString::number(calculateModifier(labelAbility->text().toInt())));
}

//Вычисление модификатора числа
int MainWindow::calculateModifier(const int number)
{
    if (number % 2 != 0){
        return ((number - 1) / 2) - 5;
    }
    else return (number / 2) - 5;
}

//Вычисление числа, которое игрок может использовать в качестве характеристики
int MainWindow::calculateCandidatToBecomeAbility()
{
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

//Проверка отсутствия слишком низких характеристик
bool MainWindow::checkForLowerAbility(QLabel * labelAbility1, QLabel * labelAbility2,
                                      QLabel * labelAbility3, QLabel * labelAbility4,
                                      QLabel * labelAbility5, QLabel * labelAbility6)
{

    if ((calculateModifier(labelAbility1->text().toInt()) + calculateModifier(labelAbility2->text().toInt()) +
         calculateModifier(labelAbility3->text().toInt()) + calculateModifier(labelAbility4->text().toInt()) +
         calculateModifier(labelAbility5->text().toInt()) + calculateModifier(labelAbility6->text().toInt()) > 0) &&
            ((labelAbility1->text().toInt() >= lowerThresholdAbility) || (labelAbility2->text().toInt() >= lowerThresholdAbility) ||
             (labelAbility3->text().toInt() >= lowerThresholdAbility) || (labelAbility4->text().toInt() >= lowerThresholdAbility) ||
             (labelAbility5->text().toInt() >= lowerThresholdAbility) || (labelAbility6->text().toInt() >= lowerThresholdAbility)))
        return true;
    else return false;
}

void MainWindow::setupComboBoxes(QComboBox * comboBox, QStringList * listOfCandidatsToBecomeAbility)
{
    comboBox->addItems(*listOfCandidatsToBecomeAbility);
}

void MainWindow::on_comboBoxStrength_activated(int index)
{
    qDebug () << index << count;
    if ((ui->comboBoxStrength->currentText() != listOfCandidatsToBecomeAbility[0]) ||
            (ui->comboBoxStrength->currentText() != ui->comboBoxStrength->itemText(0))){
        if (ui->comboBoxStrength->currentText() == ""){

            ui->comboBoxStrength->clear();
            ui->comboBoxStrength->addItems(listOfCandidatsToBecomeAbility);
            ui->comboBoxDexterity->clear();
            ui->comboBoxDexterity->addItems(listOfCandidatsToBecomeAbility);
            ui->comboBoxConstitution->clear();
            ui->comboBoxConstitution->addItems(listOfCandidatsToBecomeAbility);
            ui->comboBoxIntelligence->clear();
            ui->comboBoxIntelligence->addItems(listOfCandidatsToBecomeAbility);
            ui->comboBoxWisdom->clear();
            ui->comboBoxWisdom->addItems(listOfCandidatsToBecomeAbility);
            ui->comboBoxCharisma->clear();
            ui->comboBoxCharisma->addItems(listOfCandidatsToBecomeAbility);
        }
        else{
            ui->comboBoxStrength->clear();
            ui->comboBoxStrength->addItem(listOfCandidatsToBecomeAbility[index]);
            ui->comboBoxStrength->addItem("");
            ui->comboBoxCharisma->removeItem(index);
            ui->comboBoxDexterity->removeItem(index);
            ui->comboBoxConstitution->removeItem(index);
            ui->comboBoxWisdom->removeItem(index);
            ui->comboBoxIntelligence->removeItem(index);
        }
    }
}

void MainWindow::on_comboBoxDexterity_activated(int index)
{
    qDebug () << index << count;
    if ((ui->comboBoxDexterity->currentText() != listOfCandidatsToBecomeAbility[0]) ||
            (ui->comboBoxDexterity->currentText() != ui->comboBoxDexterity->itemText(0))){
        if (ui->comboBoxDexterity->currentText() == ""){

            ui->comboBoxStrength->clear();
            ui->comboBoxStrength->addItems(listOfCandidatsToBecomeAbility);
            ui->comboBoxDexterity->clear();
            ui->comboBoxDexterity->addItems(listOfCandidatsToBecomeAbility);
            ui->comboBoxConstitution->clear();
            ui->comboBoxConstitution->addItems(listOfCandidatsToBecomeAbility);
            ui->comboBoxIntelligence->clear();
            ui->comboBoxIntelligence->addItems(listOfCandidatsToBecomeAbility);
            ui->comboBoxWisdom->clear();
            ui->comboBoxWisdom->addItems(listOfCandidatsToBecomeAbility);
            ui->comboBoxCharisma->clear();
            ui->comboBoxCharisma->addItems(listOfCandidatsToBecomeAbility);
        }
        else{
            ui->comboBoxDexterity->clear();
            ui->comboBoxDexterity->addItem(listOfCandidatsToBecomeAbility[index]);
            ui->comboBoxDexterity->addItem("");
            ui->comboBoxCharisma->removeItem(index);
            ui->comboBoxStrength->removeItem(index);
            ui->comboBoxConstitution->removeItem(index);
            ui->comboBoxWisdom->removeItem(index);
            ui->comboBoxIntelligence->removeItem(index);
        }
    }
}

void MainWindow::on_comboBoxIntelligence_activated(int index)
{
    qDebug () << index << count;
    if ((ui->comboBoxConstitution->currentText() != listOfCandidatsToBecomeAbility[0]) ||
            (ui->comboBoxConstitution->currentText() != ui->comboBoxConstitution->itemText(0))){
        if (ui->comboBoxIntelligence->currentText() == ""){

            ui->comboBoxStrength->clear();
            ui->comboBoxStrength->addItems(listOfCandidatsToBecomeAbility);
            ui->comboBoxDexterity->clear();
            ui->comboBoxDexterity->addItems(listOfCandidatsToBecomeAbility);
            ui->comboBoxConstitution->clear();
            ui->comboBoxConstitution->addItems(listOfCandidatsToBecomeAbility);
            ui->comboBoxIntelligence->clear();
            ui->comboBoxIntelligence->addItems(listOfCandidatsToBecomeAbility);
            ui->comboBoxWisdom->clear();
            ui->comboBoxWisdom->addItems(listOfCandidatsToBecomeAbility);
            ui->comboBoxCharisma->clear();
            ui->comboBoxCharisma->addItems(listOfCandidatsToBecomeAbility);
        }
        else{
            ui->comboBoxIntelligence->clear();
            ui->comboBoxIntelligence->addItem(listOfCandidatsToBecomeAbility[index]);
            ui->comboBoxIntelligence->addItem("");
            ui->comboBoxCharisma->removeItem(index);
            ui->comboBoxDexterity->removeItem(index);
            ui->comboBoxConstitution->removeItem(index);
            ui->comboBoxWisdom->removeItem(index);
            ui->comboBoxStrength->removeItem(index);
        }
    }
}

void MainWindow::on_comboBoxConstitution_activated(int index)
{
    qDebug () << index << count;
    if ((ui->comboBoxConstitution->currentText() != listOfCandidatsToBecomeAbility[0]) ||
            (ui->comboBoxConstitution->currentText() != ui->comboBoxConstitution->itemText(0))){
        if (ui->comboBoxConstitution->currentText() == ""){

            ui->comboBoxStrength->clear();
            ui->comboBoxStrength->addItems(listOfCandidatsToBecomeAbility);
            ui->comboBoxDexterity->clear();
            ui->comboBoxDexterity->addItems(listOfCandidatsToBecomeAbility);
            ui->comboBoxConstitution->clear();
            ui->comboBoxConstitution->addItems(listOfCandidatsToBecomeAbility);
            ui->comboBoxIntelligence->clear();
            ui->comboBoxIntelligence->addItems(listOfCandidatsToBecomeAbility);
            ui->comboBoxWisdom->clear();
            ui->comboBoxWisdom->addItems(listOfCandidatsToBecomeAbility);
            ui->comboBoxCharisma->clear();
            ui->comboBoxCharisma->addItems(listOfCandidatsToBecomeAbility);
        }
        else{
            ui->comboBoxConstitution->clear();
            ui->comboBoxConstitution->addItem(listOfCandidatsToBecomeAbility[index]);
            ui->comboBoxConstitution->addItem("");
            ui->comboBoxCharisma->removeItem(index);
            ui->comboBoxDexterity->removeItem(index);
            ui->comboBoxStrength->removeItem(index);
            ui->comboBoxWisdom->removeItem(index);
            ui->comboBoxIntelligence->removeItem(index);
        }
    }
}

void MainWindow::on_comboBoxWisdom_activated(int index)
{
    qDebug () << index << count;
    if ((ui->comboBoxWisdom->currentText() != listOfCandidatsToBecomeAbility[0]) ||
            (ui->comboBoxWisdom->currentText() != ui->comboBoxWisdom->itemText(0))){
        if (ui->comboBoxWisdom->currentText() == ""){

            ui->comboBoxStrength->clear();
            ui->comboBoxStrength->addItems(listOfCandidatsToBecomeAbility);
            ui->comboBoxDexterity->clear();
            ui->comboBoxDexterity->addItems(listOfCandidatsToBecomeAbility);
            ui->comboBoxConstitution->clear();
            ui->comboBoxConstitution->addItems(listOfCandidatsToBecomeAbility);
            ui->comboBoxIntelligence->clear();
            ui->comboBoxIntelligence->addItems(listOfCandidatsToBecomeAbility);
            ui->comboBoxWisdom->clear();
            ui->comboBoxWisdom->addItems(listOfCandidatsToBecomeAbility);
            ui->comboBoxCharisma->clear();
            ui->comboBoxCharisma->addItems(listOfCandidatsToBecomeAbility);
        }
        else{
            ui->comboBoxWisdom->clear();
            ui->comboBoxWisdom->addItem(listOfCandidatsToBecomeAbility[index]);
            ui->comboBoxWisdom->addItem("");
            ui->comboBoxCharisma->removeItem(index);
            ui->comboBoxDexterity->removeItem(index);
            ui->comboBoxConstitution->removeItem(index);
            ui->comboBoxStrength->removeItem(index);
            ui->comboBoxIntelligence->removeItem(index);
        }
    }
}

void MainWindow::on_comboBoxCharisma_activated(int index)
{
    qDebug () << index << count;
    if ((ui->comboBoxCharisma->currentText() != listOfCandidatsToBecomeAbility[0]) ||
            (ui->comboBoxCharisma->currentText() != ui->comboBoxCharisma->itemText(0))){
        if (ui->comboBoxCharisma->currentText() == ""){

            ui->comboBoxStrength->clear();
            ui->comboBoxStrength->addItems(listOfCandidatsToBecomeAbility);
            ui->comboBoxDexterity->clear();
            ui->comboBoxDexterity->addItems(listOfCandidatsToBecomeAbility);
            ui->comboBoxConstitution->clear();
            ui->comboBoxConstitution->addItems(listOfCandidatsToBecomeAbility);
            ui->comboBoxIntelligence->clear();
            ui->comboBoxIntelligence->addItems(listOfCandidatsToBecomeAbility);
            ui->comboBoxWisdom->clear();
            ui->comboBoxWisdom->addItems(listOfCandidatsToBecomeAbility);
            ui->comboBoxCharisma->clear();
            ui->comboBoxCharisma->addItems(listOfCandidatsToBecomeAbility);
        }
        else{
            ui->comboBoxCharisma->clear();
            ui->comboBoxCharisma->addItem(listOfCandidatsToBecomeAbility[index]);
            ui->comboBoxCharisma->addItem("");
            ui->comboBoxStrength->removeItem(index);
            ui->comboBoxDexterity->removeItem(index);
            ui->comboBoxConstitution->removeItem(index);
            ui->comboBoxWisdom->removeItem(index);
            ui->comboBoxIntelligence->removeItem(index);
        }
    }
}
