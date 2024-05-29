#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>
#include <QPushButton>
#include <QTimer>
#include<QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui->setupUi(this);
    //创建数字按钮的连接
    for(int i = 0; i < 10; ++i) {
        QString buttonName =QString("pushButton%1").arg(i);
        QPushButton* pButton = findChild<QPushButton*>(buttonName);
        if (pButton) {
            connect(pButton, &QPushButton::clicked, this, [this, i]() { appendNumber(i); });
        }
    }

    // 创建操作符按钮的连接
    connect(ui->pushButtonAdd, &QPushButton::clicked, this, [this]() { applyOperator(Plus); });
    connect(ui->pushButtonSubtract, &QPushButton::clicked, this, [this]() { applyOperator(Minus); });
    connect(ui->pushButtonMultiply, &QPushButton::clicked, this, [this]() { applyOperator(Multiply); });
    connect(ui->pushButtonDivision, &QPushButton::clicked, this, [this]() { applyOperator(Divide); });
    connect(ui->pushButtonEqual, &QPushButton::clicked, this, &MainWindow::calculate);
    connect(ui->pushButtonCE, &QPushButton::clicked, this, &MainWindow::clearDisplay);
    connect(ui->pushButtonDot, &QPushButton::clicked, this, &MainWindow::appendPoint);
    connect(ui->pushButtonDelete,&QPushButton::clicked, this,&MainWindow::cut);

}
void MainWindow::clearDisplay()
{
    ui->label->setText("0"); // 重置显示为初始值"0"
    operand = 0.0; // 重置操作数为0
    currentOperator = None; // 重置当前操作符符为None
    pendingOperation = false; // 清除待处理运算标志
}

void MainWindow::cut()
{
    QString currentText = ui->label->text(); // 获取当前文本
      if (!currentText.isEmpty()) { // 确保文本不为空才进行操作
          currentText.chop(1); // 删除最后一个字符
          ui->label->setText(currentText); // 更新显示
      }
}
void MainWindow::appendNumber(int number)
{
    QString text = ui->label->text();
    if(text == "0") {
        ui->label->setText(QString::number(number));
    } else {
        ui->label->setText(text + QString::number(number));
    }
}

void MainWindow::appendPoint()
{
    QString text = ui->label->text();
    if(!text.contains(".")) {
        ui->label->setText(text + ".");
    }
}
void MainWindow::applyOperator(Operator op)
{
    if(pendingOperation) { // 如果有未完成的运算，先计算
        calculate();
    }

    operand = ui->label->text().toDouble(); // 获取当前显示的数值作为操作数
    currentOperator = op; // 更新当前运算符
    ui->label->setText("0"); // 重置显示为0准备下一次输入
    pendingOperation = true; // 标记有待进行的运算
}

void MainWindow::calculate()
{
    if(!pendingOperation) return; // 没有待处理运算，直接返回

    double currentValue = ui->label->text().toDouble(); // 获取当前输入的数值
    double result = 0;

    switch(currentOperator) {
    case Plus:
        result = operand + currentValue;
        break;
    case Minus:
        result = operand - currentValue;
        break;
    case Multiply:
        result = operand * currentValue;
        break;
    case Divide:
        if(currentValue != 0.0) {
            result = operand / currentValue;
        } else {
            ui->label->setText("Error"); // 处理除以0的情况
            return;
        }
        break;
    default:
        return;
    }

    // 显示结果，并重置状态
    ui->label->setText(QString::number(result, 'g', 15));
    operand = result; // 将结果作为新的操作数，以支持连续运算
    currentOperator = None;
    pendingOperation = false;
}
MainWindow::~MainWindow()
{
    delete ui;
}
