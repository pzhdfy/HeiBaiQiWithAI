#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class QPushButton;
class QIcon;
struct State;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QPushButton* pushButtonList[9][9];
    int a[10][10];
    int c;//1 is black
    int num1;//black number
    int num2;
    int hardLevel;

    QIcon icon0;
    QIcon icon1;
    QIcon icon2;
    QIcon icon11;
    QIcon icon22;

    void init();
    void pArray();
    int SF1Array(int i,int j);
    int SF2Array(int i,int j);
    void aiDo();
    void aiDo1();
    void aiDo2();
    void aiDo3();
    double computePositonValue(int x,int y);

private slots:
    void on_horizontalSlider_valueChanged(int value);
    void on_action_6_triggered();
    void on_action_5_triggered();
    void on_action_4_triggered();
    void on_action_2_triggered();
    void on_action_triggered();
    void buttons_clicked();

};

#endif // MAINWINDOW_H
