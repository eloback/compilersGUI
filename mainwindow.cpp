#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QFileDialog"
#include "QFile"
#include <QTextStream>
#include <QMessageBox>
#include <QTableWidget>
#include <QTableWidgetItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    file_path_ = "";
    ui->textEdit->setText("");
}

void MainWindow::on_actionOpen_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(this,"Open the file");
    QFile file(file_name);
    file_path_ = file_name;
    if(!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "..", "file not open");
        return;
    }
    QTextStream in (&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}


void MainWindow::on_actionSave_triggered()
{
    QFile file(file_path_);
    if(!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "..", "file not saved");
        return;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
}


void MainWindow::on_actionSave_as_triggered()
{
    QString file_name = QFileDialog::getSaveFileName(this,"Save the file");
    QFile file(file_name);
    file_path_ = file_name;
    if(!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "..", "file not saved");
        return;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}


void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}


void MainWindow::on_actionAbout_this_App_triggered()
{
    QString about_text;
    about_text = "Author: Eduardo Loback, Enzo Redivo.\n";
    about_text += "(C) C-- IDE (R)";
    QMessageBox::about(this, "About C-- IDE", about_text);
}


void MainWindow::on_actionShow_Symbol_Table_triggered()
{
    //example of inserting data on the table
    QTableWidget *table = ui->tableWidget;
    const int dataLenght = 2;
    QString data[dataLenght][9] = {
        {"e", "Float", "false", "false", "false", "0", "false", "false", "false"},
        {"c", "Int", "false", "false", "false", "0", "false", "false", "false"}
    };
    int tableColumnCount = ui->tableWidget->columnCount();
    for(int i=0; i< dataLenght; i++){
        table->insertRow(i);
        QTableWidgetItem *item;
        for(int j=0; j<tableColumnCount; j++){
            item = new QTableWidgetItem;
            QString text = data[i][j];
            item->setText(text);

            table->setItem(i, j, item);
        }
    }
}

