#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include <QFile>
#include <QTextEdit>
#include <QMessageBox>
#include <QDesktopServices>
#include <QTextCodec>
#include <QTextStream>
#include <QString>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_overview_clicked();

    void on_encode_clicked();

    void on_decode_clicked();

    void on_save_clicked();

    void on_clear_clicked();

    void on_overview_dic_clicked();

    void on_form_dic_sym_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
