#include "calculatorwindow.h"
#include "ui_calculatorwindow.h"
#include <QKeyEvent>
CalculatorWindow::CalculatorWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CalculatorWindow)
{
    ui->setupUi(this);
    c=new Calculator();
    ui->lineEdit->setReadOnly(true);
    connect(c,SIGNAL(SendAnswer(QString)),this,SLOT(HandleAnswer(QString)));      // Кальк::ответ-UI::текст
    connect(this,SIGNAL(OperatorSetted(int)),c,SLOT(SetOperator(int)));           // UI::ВыбранОпер-Кальк::ЗаданОпер
    connect(ui->lineEdit,SIGNAL(textChanged(QString)),c,SLOT(SetNumber(QString)));// UI::Edit1-кальк::число
    connect(c,SIGNAL(SendCurrentOperator(int)),this,SLOT(SetCurrOper(int)));      // Кальк::ВыбранОпер-UI::обновление строки
    connect(this,SIGNAL(SendClearData()),this,SLOT(on_clearData()));             //UI::ClearAllButt - Кальк::ОчисткаAll,UI::Очистка
    connect(this,SIGNAL(SendClearData()),c,SLOT(on_clearData()));
    connect(c,SIGNAL(SendCurrentNum(double)),this,SLOT(SetCurrNum(double)));     //Кальк::текНомер- UI::текст
    connect(c,SIGNAL(backspace(int)),this,SLOT(backspace(int)));                 //вызывается, когда надо изменить текущий оператор
    connect(c,SIGNAL(SendErrorMsg(QString)),this,SLOT(on_ErrorMsg(QString)));   //Кальк::ошибка-UI::ошибка
    connect(c,SIGNAL(SendBrackets()),this,SLOT(ReceiveBrackets()));            //когда надо заключить текущее выражение в скобки
    str=QString("");
    brackets=false;
}

CalculatorWindow::~CalculatorWindow()
{
    delete c;
    delete ui;
}

void CalculatorWindow::resizeEvent(QResizeEvent *event)
{
    QSize s(event->size().width()-20,event->size().height()-20);
    ui->verticalLayoutWidget->resize(s);
    QMainWindow::resizeEvent(event);
}

void CalculatorWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
       case Qt::Key_0:
        on_pb_0_clicked();
        break;
    case Qt::Key_1:
        on_pb_1_clicked();
     break;
    case Qt::Key_2:
        on_pb_2_clicked();
     break;
    case Qt::Key_3:
        on_pb_3_clicked();
     break;
    case Qt::Key_4:
        on_pb_4_clicked();
     break;
    case Qt::Key_5:
        on_pb_5_clicked();
     break;
    case Qt::Key_6:
        on_pb_6_clicked();
     break;
    case Qt::Key_7:
        on_pb_7_clicked();
     break;
    case Qt::Key_8:
        on_pb_8_clicked();
     break;
    case Qt::Key_9:
        on_pb_9_clicked();
     break;
    case Qt::Key_Plus:
        on_pb_11_clicked();
     break;
    case Qt::Key_Comma:
        on_pb_10_clicked();
     break;
    case Qt::Key_Minus:
        on_pb_12_clicked();
     break;
    case Qt::Key_Multi_key:
        on_pb_13_clicked();
     break;
    case Qt::Key_division:
        on_pb_14_clicked();
     break;
    case Qt::Key_Backspace:
        on_pB_DeleteDigit_clicked();
        break;

    case Qt::Key_Enter:
        on_pb_100_clicked();
     break;
    }
}

void CalculatorWindow::ReceiveBrackets()
{
    brackets=true;
}

void CalculatorWindow::backspace(int op)
{
    int s=ui->lineEdit_2->text().size();
    switch (op)
     {
    case 1: //+

        ui->lineEdit_2->setSelection(s-1,s);
        break;
    case 2://-
        ui->lineEdit_2->setSelection(s-1,s);
        break;
    case 3://*
        ui->lineEdit_2->setSelection(s-1,s);
        break;
    case 4:// /
        ui->lineEdit_2->setSelection(s-1,s);
        break;
    case 5:// ^
        ui->lineEdit_2->setSelection(s-1,s);
        break;
    case 8:
        //ui->lineEdit_2->setSelection(s-8,s);
        break;
     }
}

void CalculatorWindow::HandleAnswer(QString ans)
{
    ui->lineEdit->setText(ans);
    ui->lineEdit->selectAll();
}

void CalculatorWindow::StringHandler(const QString& str)
{
    if (ui->lineEdit->text()=="0")
    {
        ui->lineEdit->selectAll();
    }
    ui->lineEdit->insert(str);
   // ui->lineEdit_2->insert(str);
}

void CalculatorWindow::SetCurrOper(int op)
{
    int s;
    int len;

  switch(op)
  {
     case 1:
     case 2:
     case 3:
     case 4:
     case 5:
     case 6:
     case 7:
      if (str!="")
      {
        ui->lineEdit_2->deselect();
        str=QString("");
      }
  }

   switch (op)
  {
      case 1:
         ui->lineEdit_2->insert("+");
         break;
     case 2:
         ui->lineEdit_2->insert("-");
         break;
     case 3:
         ui->lineEdit_2->insert("*");
         if (brackets)
         {
             ui->lineEdit_2->setCursorPosition(0);
             ui->lineEdit_2->insert("(");
             ui->lineEdit_2->setCursorPosition(ui->lineEdit_2->text().length()-1);
             ui->lineEdit_2->insert(")");
             ui->lineEdit_2->setCursorPosition(ui->lineEdit_2->text().length());
             brackets=false;
         }
         break;
     case 4:
      ui->lineEdit_2->insert("/");
      if (brackets)
      {
          ui->lineEdit_2->setCursorPosition(0);
          ui->lineEdit_2->insert("(");
          ui->lineEdit_2->setCursorPosition(ui->lineEdit_2->text().length()-1);
          ui->lineEdit_2->insert(")");
          ui->lineEdit_2->setCursorPosition(ui->lineEdit_2->text().length());
          brackets=false;
      }
      break;
     case 5:
         ui->lineEdit_2->insert("^");
         if (brackets)
         {
             ui->lineEdit_2->setCursorPosition(0);
             ui->lineEdit_2->insert("(");
             ui->lineEdit_2->setCursorPosition(ui->lineEdit_2->text().length()-1);
             ui->lineEdit_2->insert(")");
             ui->lineEdit_2->setCursorPosition(ui->lineEdit_2->text().length());
             brackets=false;
         }
      break;
      case 6:
         ui->lineEdit_2->insert("(");
         break;
      case 7:
          ui->lineEdit_2->insert(")");
          break;
      case 8:// sqrt
          if (str==QString(""))
          {
             str=QString("sqrt("+ui->lineEdit->text()+")");
             ui->lineEdit_2->insert(str);
             s=ui->lineEdit_2->text().length();
             len=str.length();
             ui->lineEdit_2->setSelection(s-len,s);
          }
          else
          {
              str=QString("sqrt("+str+")");
              ui->lineEdit_2->insert(str);
              s=ui->lineEdit_2->text().length();
              len=str.length();
              ui->lineEdit_2->setSelection(s-len,s);
          }
       break;
     case 9:  //ln
       if (str==QString(""))
       {
         str=QString("ln("+ui->lineEdit->text()+")");
         ui->lineEdit_2->insert(str);
         s=ui->lineEdit_2->text().length();
         len=str.length();
         ui->lineEdit_2->setSelection(s-len,s);
       }
       else
       {
           str=QString("ln("+str+")");
           ui->lineEdit_2->insert(str);
           s=ui->lineEdit_2->text().length();
           len=str.length();
           ui->lineEdit_2->setSelection(s-len,s);
       }
       break;
   case 10:
       if (str==QString(""))
       {
         str=QString("sin("+ui->lineEdit->text()+")");
         ui->lineEdit_2->insert(str);
         s=ui->lineEdit_2->text().length();
         len=str.length();
         ui->lineEdit_2->setSelection(s-len,s);
       }
       else
       {
           str=QString("sin("+str+")");
           ui->lineEdit_2->insert(str);
           s=ui->lineEdit_2->text().length();
           len=str.length();
           ui->lineEdit_2->setSelection(s-len,s);
       }
          break;
 case 11:
     if (str==QString(""))
     {
       str=QString("lg("+ui->lineEdit->text()+")");
       ui->lineEdit_2->insert(str);
       s=ui->lineEdit_2->text().length();
       len=str.length();
       ui->lineEdit_2->setSelection(s-len,s);
     }
     else
     {
         str=QString("lg("+str+")");
         ui->lineEdit_2->insert(str);
         s=ui->lineEdit_2->text().length();
         len=str.length();
         ui->lineEdit_2->setSelection(s-len,s);
     }
        break;
 case 12:
     if (str==QString(""))
     {
       str=QString("cos("+ui->lineEdit->text()+")");
       ui->lineEdit_2->insert(str);
       s=ui->lineEdit_2->text().length();
       len=str.length();
       ui->lineEdit_2->setSelection(s-len,s);
     }
     else
     {
         str=QString("cos("+str+")");
         ui->lineEdit_2->insert(str);
         s=ui->lineEdit_2->text().length();
         len=str.length();
         ui->lineEdit_2->setSelection(s-len,s);
     }
        break;
     break;
 case 13:
     if (str==QString(""))
     {
       str=QString("tan("+ui->lineEdit->text()+")");
       ui->lineEdit_2->insert(str);
       s=ui->lineEdit_2->text().length();
       len=str.length();
       ui->lineEdit_2->setSelection(s-len,s);
     }
     else
     {
         str=QString("tan("+str+")");
         ui->lineEdit_2->insert(str);
         s=ui->lineEdit_2->text().length();
         len=str.length();
         ui->lineEdit_2->setSelection(s-len,s);
     }
        break;
   case 14:
       if (str==QString(""))
       {
         str=QString("("+ui->lineEdit->text()+")");
         ui->lineEdit_2->insert(str);
         s=ui->lineEdit_2->text().length();
         len=str.length();
         ui->lineEdit_2->setSelection(s-len,s);
       }
       else
       {
           str=QString("(-"+str+")");
           ui->lineEdit_2->insert(str);
           s=ui->lineEdit_2->text().length();
           len=str.length();
           ui->lineEdit_2->setSelection(s-len,s);
       }
          break;
   case 15:
       if (str==QString(""))
       {
         str=QString("reciproc("+ui->lineEdit->text()+")");
         ui->lineEdit_2->insert(str);
         s=ui->lineEdit_2->text().length();
         len=str.length();
         ui->lineEdit_2->setSelection(s-len,s);
       }
       else
       {
           str=QString("reciproc("+str+")");
           ui->lineEdit_2->insert(str);
           s=ui->lineEdit_2->text().length();
           len=str.length();
           ui->lineEdit_2->setSelection(s-len,s);
       }
          break;
      case 0: // =

        break;
   }
}

void CalculatorWindow::SetCurrNum(double num)
{
    if (num>=0)
    ui->lineEdit_2->insert(QString::number(num,'G'));
    else
    {
        ui->lineEdit_2->insert("("+QString::number(num,'G')+")");
    }

}

void CalculatorWindow::on_ErrorMsg(QString msg)
{
    ui->lineEdit->selectAll();
    ui->lineEdit_2->setText("");
    ui->lineEdit->insert("error");
    emit SendClearData();
}

void CalculatorWindow::on_clearData()
{

    ui->lineEdit->setText("0");
    ui->lineEdit_2->setText("");
    str=QString("");

}

void CalculatorWindow::on_pb_7_clicked()
{
   StringHandler("7");
}

void CalculatorWindow::on_pb_8_clicked()
{
   StringHandler("8");
}

void CalculatorWindow::on_pb_9_clicked()
{
    StringHandler("9");
}

void CalculatorWindow::on_pb_1_clicked()
{
   StringHandler("1");
}

void CalculatorWindow::on_pb_4_clicked()
{
    StringHandler("4");
}

void CalculatorWindow::on_pb_5_clicked()
{
  StringHandler("5");
}

void CalculatorWindow::on_pb_6_clicked()
{
   StringHandler("6");
}

void CalculatorWindow::on_pb_3_clicked()
{
   StringHandler("3");
}

void CalculatorWindow::on_pb_2_clicked()
{
   StringHandler("2");
}

void CalculatorWindow::on_pb_0_clicked()
{
   StringHandler("0");

}

void CalculatorWindow::on_pb_10_clicked()  //.
{

    StringHandler(".");


}

void CalculatorWindow::on_pb_11_clicked() //+
{
    emit OperatorSetted(1);
    ui->lineEdit->selectAll();//emit mode switched
   // ui->lineEdit_2->insert("+");

}

void CalculatorWindow::on_pb_100_clicked()           // =
{
    int s;
    int len;
    emit OperatorSetted(0);
    ui->lineEdit_2->setText(ui->lineEdit->text());
    str=ui->lineEdit->text();
    s=ui->lineEdit_2->text().length();
    len=str.length();
    ui->lineEdit_2->setSelection(s-len,s);


}

void CalculatorWindow::on_pb_13_clicked()           // *
{
    emit OperatorSetted(3);
    ui->lineEdit->selectAll();
   // ui->lineEdit_2->insert("*");
}

void CalculatorWindow::on_pB_DeleteDigit_clicked()  // <-
{
    ui->lineEdit->backspace();
    if (ui->lineEdit->text()=="")
    {
        ui->lineEdit->setText("0");
    }
}

void CalculatorWindow::on_pb_12_clicked()           // -
{
    emit OperatorSetted(2);
    ui->lineEdit->selectAll();
}

void CalculatorWindow::on_pb_14_clicked()          // /
{
    emit OperatorSetted(4);
    ui->lineEdit->selectAll();
}

void CalculatorWindow::on_pb_18_clicked()          // +-
{
  if (ui->lineEdit->text()[0]=='-')
  {
     ui->lineEdit->setSelection(0,1);
     ui->lineEdit->insert("");
  }
  else
  {
    ui->lineEdit->setCursorPosition(0);
    ui->lineEdit->insert("-");
    ui->lineEdit->setCursorPosition(ui->lineEdit->text().length());
  }
  emit OperatorSetted(14);
}


void CalculatorWindow::on_pb_sqrt_clicked()  // sqrt()
{
    emit OperatorSetted(8);
    ui->lineEdit->selectAll();
}

void CalculatorWindow::on_pb_power_clicked() // ^
{
    emit OperatorSetted(5);
    ui->lineEdit->selectAll();
}

void CalculatorWindow::on_pb_clear_clicked()  // C
{
    emit SendClearData();
}

void CalculatorWindow::on_pb_rb_clicked()   // (
{
    emit OperatorSetted(6);
    ui->lineEdit->selectAll();
}

void CalculatorWindow::on_pb_lb_clicked()   // )
{
    emit OperatorSetted(7);
}

void CalculatorWindow::on_pb_ln_clicked()  // ln
{
    emit OperatorSetted(9);
    ui->lineEdit->selectAll();
}

void CalculatorWindow::on_pb_sin_clicked()  //sin
{
    emit OperatorSetted(10);
    ui->lineEdit->selectAll();
}

void CalculatorWindow::on_pb_pi_clicked()  // pi
{
    ui->lineEdit->setText(QString::number(M_PI,'G',31));
}

void CalculatorWindow::on_pb_log_clicked() //lg
{
    emit OperatorSetted(11);
    ui->lineEdit->selectAll();
}

void CalculatorWindow::on_pb_cos_clicked()  //cos
{
    emit OperatorSetted(12);
    ui->lineEdit->selectAll();
}

void CalculatorWindow::on_pb_tan_clicked()  //tan
{
    emit OperatorSetted(13);
    ui->lineEdit->selectAll();
}

void CalculatorWindow::on_pb_16_clicked()  //1/x
{
    emit OperatorSetted(15);
    ui->lineEdit->selectAll();
}
