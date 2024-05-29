#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QLabel>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    //操作符
    enum Operator { None, Plus, Minus, Multiply, Divide };
    //当前操作符
    Operator currentOperator = None; // 初始化为None
    //操作数
    double operand = 0.0;
    //是否进行操作
    bool pendingOperation = false;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //输入数字
    void appendNumber(int number);
    //输入小数点
    void appendPoint();
    //输入操作符
    void applyOperator(Operator op);
    //计算结果
    void calculate();
    //清空
    void clearDisplay();
    //删除最后一项
    void cut();

};
#endif // MAINWINDOW_H
