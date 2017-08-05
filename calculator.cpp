#include "calculator.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cmath>
Calculator::Calculator(QObject *parent) : QObject(parent)
{
    CurrentNumber=0.0;
    CurrentOperator=0;
    PrevOperator=0;
    T=new QStack<int>();
    K=new QStack<double>();
    mode=IDLE;
    BracketsCount=0;

}

Calculator::~Calculator()
{
    delete T;
    delete K;

}

void Calculator::ExpressionHandler()
{
   switch (mode)
   {
    case 0:               //IDLE
       break;
    case 1:               //NUMBER
       K->push(CurrentNumber);
       std::cout<<CurrentNumber;
       break;
    case 2:               //OPERATOR

       HandleOperator();
       break;
    case 3:               //ANSWER
       break;
   }
}

void Calculator::AnswerUpdate(double answer) //здесь будем обновлять ответ после выполнения каждого оператора
{

   emit SendAnswer(QString::number(answer,'g',15));

}

void Calculator::HandleOperator()
{

    //             =  +  -  *  /  ^  (  ) sqrt ln sin lg cos tan +- 1/x
    int P[15][16]={6, 1, 1, 1, 1, 1, 1, 5,  1,  1, 1,  1, 1, 1,  1,  1,      //$emptystack
                   4, 2, 2, 1, 1, 1, 1, 4,  1,  1, 1,  1, 1, 1,  1,  1,       //+
                   4, 2, 2, 1, 1, 1, 1, 4,  1,  1, 1,  1, 1, 1,  1,  1,       //-
                   4, 2, 2, 2, 2, 1, 1, 4,  1,  1, 1,  1, 1, 1,  1,  1,        // *
                   4, 2, 2, 2, 2, 1, 1, 4,  1,  1, 1,  1, 1, 1,  1,  1,       // /
                   4, 2, 2, 2, 2, 2, 1, 4,  1,  1, 1,  1, 1, 1,  1,  1,        // ^
                   5, 1, 1, 1, 1, 1, 1, 3,  1,  1, 1,  1, 1, 1,  1,  1,     //(
                   4, 2, 2, 2, 2, 2, 5, 4,  1,  1, 1,  1, 1, 1,  1,  1,      //sqrt
                   4, 2, 2, 2, 2, 2, 5, 4,  1,  1, 1,  1, 1, 1,  1,  1,      //ln
                   4, 2, 2, 2, 2, 2, 5, 4,  1,  1, 1,  1, 1, 1,  1,  1,      //sin
                   4, 2, 2, 2, 2, 2, 5, 4,  1,  1, 1,  1, 1, 1,  1,  1,      //lg
                   4, 2, 2, 2, 2, 2, 5, 4,  1,  1, 1,  1, 1, 1,  1,  1,     //cos
                   4, 2, 2, 2, 2, 2, 5, 4,  1,  1, 1,  1, 1, 1,  1,  1,      //tan
                   4, 2, 2, 2, 2, 2, 5, 4,  1,  1, 1,  1, 1, 1,  1,  1,      //+-
                   4, 2, 2, 2, 2, 2, 5, 4,  1,  1, 1,  1, 1, 1,  1,  1,      //1/x
                };

    // матрица функций(состоит из чисел, показывающих какие команды выполнить
    // в зависимости от тек оператора и от оператора, который содержится на вершине стека T)
    // i-предыдущий оператор, j-оператор, который добавляется
  int i;
  if (T->isEmpty())
  {
      i=0;
  }
  else
  {
      i=T->top();
  }

  int j=CurrentOperator;
  switch (P[i][j])     //в зависимости от i и j выбираем действие из матрицы P
  {
    case 1:
      T->push(CurrentOperator);
      break;
    case 2:
      RemoveOperFromStack();
      T->push(CurrentOperator);
      break;
    case 3:
      T->pop();
      break;
    case 4:
      RemoveOperFromStack();
      break;
    case 5:
      emit SendErrorMsg("Err");
      break;
    case 6:
      if (!(K->isEmpty()))
      {
      AnswerUpdate(K->at(0));
      }
      break;


  }
}

void Calculator::RemoveOperFromStack()
{
    int op=T->pop();
    double a;
    double b;
    double answer;
    switch (op)
    {
    case 1:    // +
        a=K->pop();
        b=K->pop();
        answer=(a+b);
        K->push(answer);
        break;
    case 2:    // -
        a=K->pop();
        b=K->pop();
        answer=(b-a);
        K->push(answer);
        break;
    case 3:    // *
        a=K->pop();
        b=K->pop();
        answer=(a*b);
        K->push(answer);
        break;
    case 4:   //  /
        a=K->pop();
        b=K->pop();
        answer=(b/a);
        K->push(answer);
        break;
   case 5:   // ^
        a=K->pop();
        b=K->pop();
        answer=(pow(b,a));
        K->push(answer);
        break;
   case 8:  //sqrt
        a=K->pop();
        answer=(sqrt(a));
        K->push(answer);
        break;
    case 9:  //ln
         a=K->pop();
         answer=(log(a));
         K->push(answer);
         break;
    case 10:  //sin
         a=K->pop();
         answer=(sin(a));
         K->push(answer);
         break;
    case 11:  //lg
         a=K->pop();
         answer=(log10(a));
         K->push(answer);
         break;
    case 12:  //cos
         a=K->pop();
         answer=(cos(a));
         K->push(answer);
         break;
    case 13:  //tg
         a=K->pop();
         answer=(tan(a));
         K->push(answer);
         break;
    case 14:
        a=K->pop();
        answer=((-1.0)*(a));
        K->push(answer);
        break;
    case 15:
        a=K->pop();
        answer=(1/a);
        K->push(answer);
        break;





    }
     CurrentNumber=answer;
    mode=ANSWER;
     AnswerUpdate(answer);
}

void Calculator::SetNumber(QString number)
{
    if (mode==ANSWER)
    {
        CurrentNumber=number.toDouble();
        PrevOperator=0;
        mode=OPERATOR;
        return;
    }
    if (mode==IDLE)
    {
        mode=NUMBER;
    }
    if (mode==OPERATOR)
    {
       switch (CurrentOperator)
       {
       // + - * / ^
       case 1:
       case 2:
       case 3:
       case 4:
       case 5:
           T->push(CurrentOperator);
           emit SendCurrentOperator(CurrentOperator);
           mode=NUMBER;
           break;

       // ( ) sqrt
       case 6:
       case 7:
       case 8:
       case 9:
       case 10:
       case 11:
       case 12:
       case 13:
       case 14:
       case 15:
           mode=NUMBER;
           break;
      /*  default:
           T->push(CurrentOperator);
           emit SendCurrentOperator(CurrentOperator);
           mode=NUMBER;
           break;*/
       }
    }

   CurrentNumber=number.toDouble();


}

void Calculator::SetOperator(const int oper)
{
    if (mode==ANSWER)
    {
        mode=OPERATOR;
    }
    if (mode == IDLE)
    {
        switch(oper)
        {
           // = + - * / ^
           case 0:
           case 1:
           case 2:
           case 3:
           case 4:
           case 5:
              mode=NUMBER;
              ExpressionHandler();
              emit SendCurrentNum(CurrentNumber);
              PrevOperator=0;
              mode=OPERATOR;
              break;
           case 6:
            //ExpressionHandler();
              mode=NUMBER;
              break;
           case 8:  // sqrt
           case 9:  // ln
           case 10:  // sin
           case 11:  // lg
           case 12:  // cos
           case 13:  // tg
           case 14:   //+-
           case 15: // 1/x
               mode=NUMBER;
               ExpressionHandler();
               PrevOperator=0;
               mode=OPERATOR;
               break;
        }
    }
    if (mode==NUMBER)
    {
       switch(oper)
       {
          // = + - * / ^
          case 0:
          case 1:
          case 2:
          case 3:
          case 4:
          case 5:
             ExpressionHandler();
             emit SendCurrentNum(CurrentNumber);
             PrevOperator=0;
             mode=OPERATOR;
             break;
          case 6:  // (
             CurrentOperator=6;
             T->push(6);
             ++BracketsCount;
             emit SendCurrentOperator(6);
            return;
          case 7:  // )
             if (BracketsCount)
             {
               ExpressionHandler();
               emit SendCurrentNum(CurrentNumber);
               PrevOperator=0;
               mode=OPERATOR;
             }
             break;
          case 8:  // sqrt
             ExpressionHandler();
             PrevOperator=0;
             mode=OPERATOR;
             break;
       case 9:  // ln
          ExpressionHandler();
          PrevOperator=0;
          mode=OPERATOR;
          break;
       case 10:  // sin
           ExpressionHandler();
           PrevOperator=0;
           mode=OPERATOR;
           break;
       case 11:  // lg
           ExpressionHandler();
           PrevOperator=0;
           mode=OPERATOR;
           break;
       case 12:  // cos
           ExpressionHandler();
           PrevOperator=0;
           mode=OPERATOR;
           break;
       case 13:  // tg
           ExpressionHandler();
           PrevOperator=0;
           mode=OPERATOR;
           break;
       case 14:
       case 15:
           ExpressionHandler();
           PrevOperator=0;
           mode=OPERATOR;
           break;
       }

      // SendCurrentNumber();
    }
      switch (oper)
      {
      case 1: // +
          CurrentOperator=1;
          emit SendCurrentOperator(1);
          ExpressionHandler();
          PrevOperator=T->pop();
          emit backspace(1);
          break;
      case 2: // -
          CurrentOperator=2;
          emit SendCurrentOperator(2);
          ExpressionHandler();
          PrevOperator=T->pop();
          emit backspace(2);
          break;
      case 3: // *
          CurrentOperator=3;
          emit SendCurrentOperator(3);
          if ((PrevOperator==1)||(PrevOperator==2))
          {
              emit SendBrackets();
          }
          ExpressionHandler();
          PrevOperator=T->pop();
          emit backspace(3);
          break;
      case 4: // /
          CurrentOperator=4;
          emit SendCurrentOperator(4);
          if ((PrevOperator==1)||(PrevOperator==2))
          {
              emit SendBrackets();
          }
          ExpressionHandler();
          PrevOperator=T->pop();
          emit backspace(4);
          break;
      case 5:  // ^
          CurrentOperator=5;
          emit SendCurrentOperator(5);
          if ((PrevOperator==1)||(PrevOperator==2))
          {
              emit SendBrackets();
          }
          ExpressionHandler();
          PrevOperator=T->pop();
          emit backspace(5);
          break;
      case 6:  // (
          CurrentOperator=6;
          if ((PrevOperator!=6)&&(PrevOperator!=0))
          {
          T->push(PrevOperator);
          std::cout<<"'"<<PrevOperator<<"'";
          emit SendCurrentOperator(PrevOperator);
          PrevOperator=6;
          }
          ExpressionHandler();
          ++BracketsCount;
          emit SendCurrentOperator(CurrentOperator);
          break;
      case 7:  // )
          CurrentOperator=7;
          if (BracketsCount>0)
          {
            if (!T->isEmpty())
             {
               while (T->top()!=6)
               {
                   ExpressionHandler();
                   mode=OPERATOR;
               }
                --BracketsCount;

             }
          ExpressionHandler();
          emit SendCurrentOperator(CurrentOperator);
          }
          break;
      case 8:  // sqrt
          emit SendCurrentOperator(8);
          T->push(8);
          RemoveOperFromStack();
          PrevOperator=0;
          break;
      case 9:  // ln
          emit SendCurrentOperator(9);
          T->push(9);
          RemoveOperFromStack();
          PrevOperator=0;
          break;
      case 10:  //sin
          emit SendCurrentOperator(10);
          T->push(10);
          RemoveOperFromStack();
          PrevOperator=0;
          break;
      case 11:  //lg
          emit SendCurrentOperator(11);
          T->push(11);
          RemoveOperFromStack();
          PrevOperator=0;
          break;
      case 12:  // cos
          emit SendCurrentOperator(12);
          T->push(12);
          RemoveOperFromStack();
          PrevOperator=0;
          break;
      case 13:  // tg
          emit SendCurrentOperator(13);
          T->push(13);
          RemoveOperFromStack();
          PrevOperator=0;
          break;
      case 14:  // +-
          emit SendCurrentOperator(14);
          T->push(14);
          RemoveOperFromStack();
          PrevOperator=0;
          break;
      case 15:  // 1/x
          emit SendCurrentOperator(15);
          T->push(15);
          RemoveOperFromStack();
          PrevOperator=0;
          break;

      //......
       case 0:  //=
          CurrentOperator=0; 
          while(!(T->isEmpty()))
          {
          ExpressionHandler();
          mode=OPERATOR;
          }
       default:
          return;

       //и т.д.
      }



}

void Calculator::on_clearData()
{
        T->clear();
        K->clear();
        CurrentNumber=0.0;
        CurrentOperator=0;
        T=new QStack<int>();
        K=new QStack<double>();
        PrevOperator=0;
        mode=IDLE;
}
