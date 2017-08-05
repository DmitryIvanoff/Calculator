#ifndef CALCULATORWINDOW_H
#define CALCULATORWINDOW_H
#include "calculator.h"
#include <QMainWindow>

namespace Ui {
class CalculatorWindow;
}

class CalculatorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CalculatorWindow(QWidget *parent = 0);
    ~CalculatorWindow();

signals:
     OperatorSetted(const int); //какой оператор выбран
     SendClearData();
protected:
     void resizeEvent(QResizeEvent *);
     void keyPressEvent(QKeyEvent *);
public slots:

private slots:
     void ReceiveBrackets();
     void backspace(int);
     void HandleAnswer(QString);
     void SetCurrOper(int);
     void SetCurrNum(double);
     void on_ErrorMsg(QString);
      void on_clearData();
     void on_pb_7_clicked();

     void on_pb_8_clicked();

     void on_pb_9_clicked();

     void on_pb_1_clicked();

     void on_pb_4_clicked();

     void on_pb_5_clicked();

     void on_pb_6_clicked();

     void on_pb_3_clicked();

     void on_pb_2_clicked();

     void on_pb_0_clicked();

     void on_pb_10_clicked();


     void on_pb_11_clicked();

     void on_pb_100_clicked();

     void on_pb_13_clicked();

     void on_pB_DeleteDigit_clicked();

     void on_pb_12_clicked();

     void on_pb_14_clicked();

     void on_pb_18_clicked();

     void on_pb_sqrt_clicked();

     void on_pb_power_clicked();

     void on_pb_clear_clicked();

     void on_pb_rb_clicked();

     void on_pb_lb_clicked();

     void on_pb_ln_clicked();

     void on_pb_sin_clicked();

     void on_pb_pi_clicked();

     void on_pb_log_clicked();

     void on_pb_cos_clicked();

     void on_pb_tan_clicked();

     void on_pb_16_clicked();

private:
     bool brackets;
     void StringHandler(const QString &str);
    Calculator* c;
    Ui::CalculatorWindow *ui;
    QString str;
};

#endif // CALCULATORWINDOW_H
