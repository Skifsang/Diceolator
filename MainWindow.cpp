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
QStringList trueListOfCandidatsToBecomeAbility;

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

    listOfCandidatsToBecomeAbility << "" << ui->labelCandidatToBecomeAbility1->text() <<
                                      ui->labelCandidatToBecomeAbility2->text() <<
                                      ui->labelCandidatToBecomeAbility3->text() <<
                                      ui->labelCandidatToBecomeAbility4->text() <<
                                      ui->labelCandidatToBecomeAbility5->text() <<
                                      ui->labelCandidatToBecomeAbility6->text();
    trueListOfCandidatsToBecomeAbility = listOfCandidatsToBecomeAbility;


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

//Заполнить боксы кандидатами в характеристики
void MainWindow::setupComboBoxes(QComboBox * comboBox, QStringList * listOfCandidatsToBecomeAbility)
{
    comboBox->addItems(*listOfCandidatsToBecomeAbility);
}

//Запомнить выбранную характерисику
void fairSpreadAbility (int index, QComboBox * box){

        box->setItemText(0, box->itemText(index));
        box->currentText() = box->itemText(0);
        box->setEnabled(false);

}

//Внести данные в список вещей коробки, после выбора характерисики
void testBOX (QComboBox * box){
    if (box->isEnabled()) {
        box->clear();
        box->addItems(listOfCandidatsToBecomeAbility);
    }
}

void MainWindow::on_comboBoxStrength_activated(int index)
{

        if (ui->comboBoxStrength->currentText() != ""){
           fairSpreadAbility(index, ui->comboBoxStrength);
           listOfCandidatsToBecomeAbility.removeAt(index);
            testBOX(ui->comboBoxDexterity);
            testBOX(ui->comboBoxConstitution);
            testBOX(ui->comboBoxIntelligence);
            testBOX(ui->comboBoxWisdom);
            testBOX(ui->comboBoxCharisma);
        }


}

void MainWindow::on_comboBoxDexterity_activated(int index)
{

    if (ui->comboBoxDexterity->currentText() != ""){
        fairSpreadAbility(index, ui->comboBoxDexterity);
        listOfCandidatsToBecomeAbility.removeAt(index);
        testBOX(ui->comboBoxStrength);
        testBOX(ui->comboBoxConstitution);
        testBOX(ui->comboBoxIntelligence);
        testBOX(ui->comboBoxWisdom);
        testBOX(ui->comboBoxCharisma);
    }

}

void MainWindow::on_comboBoxIntelligence_activated(int index)
{

    if (ui->comboBoxIntelligence->currentText() != ""){
        fairSpreadAbility(index, ui->comboBoxIntelligence);
        listOfCandidatsToBecomeAbility.removeAt(index);
        testBOX(ui->comboBoxDexterity);
        testBOX(ui->comboBoxConstitution);
        testBOX(ui->comboBoxStrength);
        testBOX(ui->comboBoxWisdom);
        testBOX(ui->comboBoxCharisma);
    }

}

void MainWindow::on_comboBoxConstitution_activated(int index)
{
    if (ui->comboBoxConstitution->currentText() != ""){
        fairSpreadAbility(index, ui->comboBoxConstitution);
        listOfCandidatsToBecomeAbility.removeAt(index);
        testBOX(ui->comboBoxDexterity);
        testBOX(ui->comboBoxStrength);
        testBOX(ui->comboBoxIntelligence);
        testBOX(ui->comboBoxWisdom);
        testBOX(ui->comboBoxCharisma);
    }

}

void MainWindow::on_comboBoxWisdom_activated(int index)
{
    if (ui->comboBoxWisdom->currentText() != ""){
      fairSpreadAbility(index, ui->comboBoxWisdom);
      listOfCandidatsToBecomeAbility.removeAt(index);
      testBOX(ui->comboBoxDexterity);
      testBOX(ui->comboBoxConstitution);
      testBOX(ui->comboBoxIntelligence);
      testBOX(ui->comboBoxStrength);
      testBOX(ui->comboBoxCharisma);
    }

}

void MainWindow::on_comboBoxCharisma_activated(int index)
{
    if (ui->comboBoxCharisma->currentText() != ""){
        fairSpreadAbility(index, ui->comboBoxCharisma);
        listOfCandidatsToBecomeAbility.removeAt(index);
        testBOX(ui->comboBoxDexterity);
        testBOX(ui->comboBoxConstitution);
        testBOX(ui->comboBoxIntelligence);
        testBOX(ui->comboBoxWisdom);
        testBOX(ui->comboBoxStrength);
    }

}

//Очистка коробки
void clearBox (QComboBox * box){
    box->clear();
    box->setEnabled(true);
}

void MainWindow::on_dropSpreadAbilites_pressed()
{
    clearBox(ui->comboBoxStrength);
    clearBox(ui->comboBoxDexterity);
    clearBox(ui->comboBoxConstitution);
    clearBox(ui->comboBoxIntelligence);
    clearBox(ui->comboBoxWisdom);
    clearBox(ui->comboBoxCharisma);
    listOfCandidatsToBecomeAbility = trueListOfCandidatsToBecomeAbility;
    setupComboBoxes(ui->comboBoxStrength, &listOfCandidatsToBecomeAbility);
    setupComboBoxes(ui->comboBoxDexterity, &listOfCandidatsToBecomeAbility);
    setupComboBoxes(ui->comboBoxConstitution, &listOfCandidatsToBecomeAbility);
    setupComboBoxes(ui->comboBoxIntelligence, &listOfCandidatsToBecomeAbility);
    setupComboBoxes(ui->comboBoxWisdom, &listOfCandidatsToBecomeAbility);
    setupComboBoxes(ui->comboBoxCharisma, &listOfCandidatsToBecomeAbility);
}
