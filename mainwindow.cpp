#include "mainwindow.h"
#include "ui_mainwindow.h"

double firstNum = 0.0;
bool userIsTypingSecondNumber = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    connect(ui->pushButton_0, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_1, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_2, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_3, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_4, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_5, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_6, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_7, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_8, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_9, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_decimal, SIGNAL(released()), this, SLOT(on_pushButton_decimal_released()));
    connect(ui->pushButton_equal, SIGNAL(released()), this, SLOT(on_pushButton_equal_released()));
    connect(ui->pushButton_plusMinus, SIGNAL(released()), this, SLOT(unary_operation_pressed()));
    connect(ui->pushButton_percent, SIGNAL(released()), this, SLOT(unary_operation_pressed()));
    connect(ui->pushButton_clear, SIGNAL(released()), this, SLOT(on_pushButton_clear_released()));
    connect(ui->pushButton_divide, SIGNAL(released()), this, SLOT(binary_operation_pressed()));
    connect(ui->pushButton_mult, SIGNAL(released()), this, SLOT(binary_operation_pressed()));
    connect(ui->pushButton_minus, SIGNAL(released()), this, SLOT(binary_operation_pressed()));
    connect(ui->pushButton_plus, SIGNAL(released()), this, SLOT(binary_operation_pressed()));

    ui->pushButton_minus->setCheckable(true);
    ui->pushButton_plus->setCheckable(true);
    ui->pushButton_divide->setCheckable(true);
    ui->pushButton_mult->setCheckable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digit_pressed()
{
    QPushButton *button = (QPushButton*)sender();

    double label_number;
    QString new_label;


    if((ui->pushButton_plus->isChecked() || ui->pushButton_minus->isChecked() ||
         ui->pushButton_mult->isChecked() || ui->pushButton_divide->isChecked()) && (!userIsTypingSecondNumber))
    {
        label_number = button->text().toDouble();
        userIsTypingSecondNumber = true;
        new_label =QString::number(label_number,'g',11);
    }
    else
    {
        if(ui->screen->text().contains('.'))
        {
            new_label = ui->screen->text() + button->text();
        }
        else
        {
            label_number = (ui->screen->text() + button->text()).toDouble();
            new_label = QString::number(label_number, 'g', 11);
        }
    }
    ui->screen->setText(new_label);
}

void MainWindow::on_pushButton_decimal_released()
{
    if(!ui->screen->text().contains('.'))
    {
        ui->screen->setText(ui->screen->text() + '.');
    }
}

void MainWindow::unary_operation_pressed()
{
    QPushButton *button = (QPushButton *)sender();

    double all_numbers;
    QString newLabel;

    if(button->text() == "+/-") {
    all_numbers = ui->screen->text().toDouble();
    all_numbers = all_numbers * -1;
    newLabel = QString::number(all_numbers, 'g', 11);
    ui->screen->setText(newLabel);
    }

    if(button->text() == "%") {
    all_numbers = ui->screen->text().toDouble();
    all_numbers = all_numbers * 0.01;
    newLabel = QString::number(all_numbers, 'g', 11);
    ui->screen->setText(newLabel);
    }
}


void MainWindow::on_pushButton_clear_released()
{
    ui->pushButton_divide->setChecked(false);
    ui->pushButton_mult->setChecked(false);
    ui->pushButton_plus->setChecked(false);
    ui->pushButton_minus->setChecked(false);

    userIsTypingSecondNumber = false;
    ui->screen->setText("0");
}


void MainWindow::on_pushButton_equal_released()
{
    double labelNumber, secondNum;
    QString newLabel;

    secondNum = ui->screen->text().toDouble();

    if (ui->pushButton_plus->isChecked())
    {
        labelNumber = firstNum + secondNum;
        newLabel = QString::number(labelNumber, 'g', 11);
        ui->screen->setText(newLabel);
        ui->pushButton_plus->setChecked(false);
    }
    else if (ui->pushButton_minus->isChecked())
    {
        labelNumber = firstNum - secondNum;
        newLabel = QString::number(labelNumber, 'g', 11);
        ui->screen->setText(newLabel);
        ui->pushButton_minus->setChecked(false);
    }

    else if (ui->pushButton_mult->isChecked())
    {
        labelNumber = firstNum * secondNum;
        newLabel = QString::number(labelNumber, 'g', 11);
        ui->screen->setText(newLabel);
        ui->pushButton_mult->setChecked(false);
    }
    else if (ui->pushButton_divide->isChecked())
    {
        labelNumber = firstNum / secondNum;
        newLabel = QString::number(labelNumber, 'g', 11);
        ui->screen->setText(newLabel);
        ui->pushButton_divide->setChecked(false);
    }
    userIsTypingSecondNumber = false;
}

void MainWindow::binary_operation_pressed()
{
    QPushButton *button = (QPushButton *)sender();

    firstNum = ui->screen->text().toDouble();
    button->setChecked(true);
}
