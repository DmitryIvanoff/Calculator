#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <QtCore>
#include <QtGui>

//-------Как это работает?-----
//В общем, у калькулятора есть 4 состояния.
//IDLE Исходное(Нейтральное),в котором пребывает калькулятор
//в состояние NUMBER он переходит,когда выбирается число
//в состояние OPERATOR - когда оператор
//в состояние ANSWER - когда получен ответ

enum InputState{IDLE,NUMBER,OPERATOR,ANSWER};
class Calculator : public QObject
{
    Q_OBJECT
public:
    explicit Calculator(QObject *parent = 0);
    ~Calculator();
private:
    QString answer;       //ответ;
    QStack<double>* K;  //стек операндов
    QStack<int>* T;  //стек операторов
    double CurrentNumber; //текущее введенное число
    int CurrentOperator; //текущее введенный оператор
    void ExpressionHandler(); //здесь будем складывать числа и операторы в нужные стеки
    void AnswerUpdate(double);//обновление ответа
    void HandleOperator();  //обработка оператора
    void RemoveOperFromStack(); //расчет р-та
    InputState mode;   //режим ( число или оператор)
    int PrevOperator;  //предыдущий оператор
    int BracketsCount;
signals:
     SendAnswer(QString);   //обновление ответа
     SendErrorMsg(QString);  //сообщение об ошибке
     SendCurrentOperator(int);//отправка оператора окну
     SendCurrentNum(double); //отправка числа окну
     backspace(int); //очистка строки в зависимости от оператора
     SendBrackets();
public slots:
     void SetNumber(const QString);  //установка текущего числа
     void SetOperator(const int);  //установка текущего оператора
     void on_clearData();          //очистка данных
private slots:


};

#endif // CALCULATOR_H
