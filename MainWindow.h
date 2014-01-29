#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QLabel>
#include <QMainWindow>
#include <QComboBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_Calculate_pressed();

    void on_calculatesCandidateToBecomeAbility_pressed();

    void on_comboBoxStrength_activated(int index);

    void on_comboBoxDexterity_activated(int index);

    void on_comboBoxIntelligence_activated(int index);

    void on_comboBoxConstitution_activated(int index);

    void on_comboBoxWisdom_activated(int index);

    void on_comboBoxCharisma_activated(int index);

private:
    Ui::MainWindow *ui;

    void setupAbilites (QLabel* labelAbility, QLabel* labelAbilityModifier);
    int calculateModifier (const int number);
    int calculateCandidatToBecomeAbility ();
    bool checkForLowerAbility (QLabel* labelAbility1, QLabel*labelAbility2, QLabel*labelAbility3
                               , QLabel*labelAbility4, QLabel*labelAbility5, QLabel*labelAbility6);
    void setupComboBoxes (QComboBox * comboBox, QStringList * listOfCandidatsToBecomeAbility);
};

#endif // MAINWINDOW_H
