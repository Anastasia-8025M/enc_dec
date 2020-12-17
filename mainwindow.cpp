#include "mainwindow.h"
#include "ui_mainwindow.h"

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

void MainWindow::on_overview_clicked()
{
    QString str = QFileDialog::getOpenFileName(0,"Open Dialog","","*.txt");
    ui->open_file->setText(str);
    QFile file(str);
    if ((file.exists())&&(file.open(QIODevice::ReadOnly)))
    {
        ui->source_text->setText(file.readAll());
        file.close();
    }
}


void MainWindow::on_encode_clicked()
{
    int flag_srs=0, flag_dic=0;
    QString srs_text = ui->source_text->toPlainText();
    if (QString(srs_text).isEmpty())
    {
        QMessageBox::warning(this, tr("Ошибка"), tr("Поле с исходным текстом пустое."));
    }
    else
    {
        for (int i=0; i < srs_text.length(); i++)
        {
            if ((srs_text[i]>="А" && srs_text[i]<="Я") || (srs_text[i]>="а" && srs_text[i]<="я") || (srs_text[i]=="Ё" && srs_text[i]=="ё") || (srs_text[i]==" ")
                    || (srs_text[i]==".") || (srs_text[i]==",") || (srs_text[i]=="-") || (srs_text[i]=="?") || (srs_text[i]=="!") || (srs_text[i]==":") || (srs_text[i]==";")
                    || (srs_text[i]=="«") || (srs_text[i]=="»"))
                flag_srs+=0;
           else
                flag_srs+=1;
        }
        if (flag_srs==0)
        {
            QString dic_file = ui->dic_text->toPlainText();
            if (QString(dic_file).isEmpty())
            {
                QMessageBox::warning(this, tr("Ошибка"), tr("Словарь отсутствует!"));
            }
            else
            {
                for (int i=0; i < dic_file.length(); i++)
                {
                    if ((dic_file[i]>="А" && dic_file[i]<="Я") || (dic_file[i]>="а" && dic_file[i]<="я") || (dic_file[i]=="Ё" && dic_file[i]=="ё") || (dic_file[i]==" ")
                            || (dic_file[i]==".") || (dic_file[i]==",") || (dic_file[i]=="-") || (dic_file[i]=="?") || (dic_file[i]=="!") || (dic_file[i]==":")
                            || (dic_file[i]==";") || (dic_file[i]=="«") || (dic_file[i]=="»"))
                        flag_dic+=0;
                   else
                        flag_dic+=1;
                }
                if (flag_dic==0)
                {
                    //кодирование
                    int j=0;
                    for (int i=0; i<srs_text.length(); i++)
                    {
                        int tnum,tdicnum;
                        if (j == dic_file.length())
                        {
                            j=0;
                        }

                        if (srs_text[i]==' ')
                            tnum = 152;
                        else if (srs_text[i]=='.')
                            tnum = 46;
                        else if (srs_text[i]==',')
                            tnum = 44;
                        else if (srs_text[i]=='-')
                            tnum = 45;
                        else if (srs_text[i]=='?')
                            tnum = 63;
                        else if (srs_text[i]=='!')
                            tnum = 21;
                        else if (srs_text[i]==':')
                            tnum = 58;
                        else if (srs_text[i]==';')
                            tnum = 59;
                        else if (srs_text[i]=="«")
                            tnum = 171;
                        else if (srs_text[i]=="»")
                            tnum = 187;
                        else
                        {
                            QChar tsym = srs_text[i];
                            tnum = tsym.unicode()-848;
                        }
                        if (dic_file[j]==' ')
                            tdicnum = 152;
                        else if (dic_file[j]=='.')
                            tdicnum = 46;
                        else if (dic_file[i]==',')
                            tdicnum = 44;
                        else if (dic_file[i]=='-')
                            tdicnum = 45;
                        else if (dic_file[i]=='?')
                            tdicnum = 63;
                        else if (dic_file[i]=='!')
                            tdicnum = 21;
                        else if (dic_file[i]==':')
                            tdicnum = 58;
                        else if (dic_file[i]==';')
                            tdicnum = 59;
                        else if (dic_file[i]=="«")
                            tdicnum = 171;
                        else if (dic_file[i]=="»")
                            tdicnum = 187;
                        else
                        {
                            QChar tdicsym = dic_file[j];
                            tdicnum = tdicsym.unicode()-848;
                        }
                        tnum = tnum ^ tdicnum;
                        QString tstr = QString::number(tnum);
                        ui->result_text->insertPlainText(tstr);
                        ui->result_text->insertPlainText(" ");
                        j++;
                    }
                }
                else
                {
                    QMessageBox::warning(this, tr("Ошибка"), tr("Символы словаря не подходит для кодировки"));
                }
            }
        }
        else
        {
            QMessageBox::warning(this, tr("Ошибка"), tr("Исходные символы не подходит для кодировки"));
        }
    }


}

void MainWindow::on_decode_clicked()
{
    int flag_srs=0, flag_dic=0;
    QString srs_text = ui->source_text->toPlainText();
    if (QString(srs_text).isEmpty())
    {
        QMessageBox::warning(this, tr("Ошибка"), tr("Поле с исходным текстом пустое."));
    }
    else
    {
        for (int i=0; i < srs_text.length(); i++)
        {
            if (srs_text[i]>='0' && srs_text[i]<='9' || srs_text[i] ==' ')
                flag_srs+=0;
            else
                flag_srs+=1;
        }
        if (flag_srs==0)
        {
            QString dic_file = ui->dic_text->toPlainText();

            if (QString(dic_file).isEmpty())
            {
                QMessageBox::warning(this, tr("Ошибка"), tr("Словарь отсутствует!"));
            }
            else
            {
                for (int i=0; i < dic_file.length(); i++)
                {
                    if ((dic_file[i]>="А" && dic_file[i]<="Я") || (dic_file[i]>="а" && dic_file[i]<="я") || (dic_file[i]=="Ё" && dic_file[i]=="ё") || (dic_file[i]==" ")
                            || (dic_file[i]==".") || (dic_file[i]==",") || (dic_file[i]=="-") || (dic_file[i]=="?") || (dic_file[i]=="!") || (dic_file[i]==":")
                            || (dic_file[i]==";") || (dic_file[i]=="«") || (dic_file[i]=="»"))
                        flag_dic+=0;
                   else
                        flag_dic+=1;
                }
                if (flag_dic==0)
                {
                    //декодирование
                    int j=0, numsym=0;
                    int codesym[1000];
                    int buf[3];
                    buf[0] = 0;
                    buf[1] = 0;
                    buf[2] = 0;
                    for (int i=0; i<srs_text.length(); i++)
                    {

                        if (srs_text[i]!=' ')
                        {
                            if (srs_text[i] == '0')
                                buf[j]=0;
                            else if (srs_text[i] == '1')
                                buf[j]=1;
                            else if (srs_text[i] == '2')
                                buf[j]=2;
                            else if (srs_text[i] == '3')
                                buf[j]=3;
                            else if (srs_text[i] == '4')
                                buf[j]=4;
                            else if (srs_text[i] == '5')
                                buf[j]=5;
                            else if (srs_text[i] == '6')
                                buf[j]=6;
                            else if (srs_text[i] == '7')
                                buf[j]=7;
                            else if (srs_text[i] == '8')
                                buf[j]=8;
                            else if (srs_text[i] == '9')
                                buf[j]=9;
                            j++;
                        }

                        else
                        {
                            if (j==1)
                            {
                                codesym[numsym]=buf[0];
                                numsym++;
                                j=0;
                            }
                            else if (j==2) {
                                codesym[numsym]=buf[0]*10+buf[1];
                                numsym++;
                                j=0;
                            }
                            else if (j==3) {
                                codesym[numsym]=buf[0]*100+buf[1]*10+buf[2];
                                numsym++;
                                j=0;
                            }
                        }
                    }
                    int t=0;
                    for (int i=0; i<numsym; i++)
                    {
                        int tdicnum;
                        if (t == dic_file.length())
                        {
                            t=0;
                        }

                        if (dic_file[t]==' ')
                            tdicnum = 152;
                        else if (dic_file[t]=='.')
                            tdicnum = 46;
                        else if (dic_file[i]==',')
                            tdicnum = 44;
                        else if (dic_file[i]=='-')
                            tdicnum = 45;
                        else if (dic_file[i]=='?')
                            tdicnum = 63;
                        else if (dic_file[i]=='!')
                            tdicnum = 21;
                        else if (dic_file[i]==':')
                            tdicnum = 58;
                        else if (dic_file[i]==';')
                            tdicnum = 59;
                        else if (dic_file[i]=="«")
                            tdicnum = 171;
                        else if (dic_file[i]=="»")
                            tdicnum = 187;
                        else
                        {
                            QChar tdicsym = dic_file[t];
                            tdicnum = tdicsym.unicode()-848;
                        }
                        codesym[i] = codesym[i] ^ tdicnum;
                        if (codesym[i] == 152)
                            ui->result_text->insertPlainText(" ");
                        else if (codesym[i] == 46)
                            ui->result_text->insertPlainText(".");
                        else if (codesym[i] == 44)
                            ui->result_text->insertPlainText(",");
                        else if (codesym[i] == 45)
                            ui->result_text->insertPlainText("-");
                        else if (codesym[i] == 63)
                            ui->result_text->insertPlainText("?");
                        else if (codesym[i] == 21)
                            ui->result_text->insertPlainText("!");
                        else if (codesym[i] == 58)
                            ui->result_text->insertPlainText(":");
                        else if (codesym[i] == 59)
                            ui->result_text->insertPlainText(";");
                        else if (codesym[i] == 171)
                            ui->result_text->insertPlainText("«");
                        else if (codesym[i] == 187)
                            ui->result_text->insertPlainText("»");
                        else
                        {
                            qDebug()<<codesym[i];
                            ui->result_text->insertPlainText(QString(QChar(codesym[i]+848)));
                        }
                        t++;
                    }
                }
                else
                {
                    QMessageBox::warning(this, tr("Ошибка"), tr("Символы словаря не подходит для декодировки"));
                }
            }

        }
        else
        {
            QMessageBox::warning(this, tr("Ошибка"), tr("Исходный текст не подходит для декодировки"));
        }
    }
}

void MainWindow::on_save_clicked()
{
    QString res_text = ui->result_text->toPlainText();
    if (QString(res_text).isEmpty())
    {
        QMessageBox::warning(this, tr("Ошибка"), tr("Поле с результатом пустое."));
    }
    else
    {
        QString results = QFileDialog::getSaveFileName(this,tr("Save results"),"",tr("Results (*.txt)"));
        QFile file(results);
        if (file.open(QIODevice::WriteOnly))
        {
            file.write(res_text.toUtf8());
            file.close();
            int ret = QMessageBox::information(this, tr("Успешно"), tr("Файл с результатом успешно создан. Хотите открыть?"), QMessageBox::Yes | QMessageBox::No);
            if (ret == QMessageBox::Yes)
            {
                QDesktopServices::openUrl(QUrl::fromLocalFile("/Users/ilatimofeev/Desktop/results.txt"));
            }

        }
    }

}

void MainWindow::on_clear_clicked()
{
    ui->source_text->clear();
    ui->dic_text->clear();
    ui->result_text->clear();
    ui->open_file->clear();
    ui->open_dic->clear();
    ui->num_dic_sym->clear();
}

void MainWindow::on_overview_dic_clicked()
{
    QString str_dic_file = QFileDialog::getOpenFileName(0,"Open Dialog","","*.txt");
    ui->open_dic->setText(str_dic_file);
    QFile file(str_dic_file);
    if ((file.exists())&&(file.open(QIODevice::ReadOnly)))
    {
        ui->dic_text->setText(file.readAll());
        file.close();
    }
}


void MainWindow::on_form_dic_sym_clicked()
{
    QString srs_text = ui->dic_text->toPlainText();
    if (QString(srs_text).isEmpty())
    {
        int num_dic_sym = ui->num_dic_sym->value();
        for (int i=0; i < num_dic_sym; i++)
        {
            int code_sym = rand()%100;
            if (code_sym >= 67)
            {
                ui->dic_text->insertPlainText(" ");
            }
            else if (code_sym == 73)
            {
                ui->dic_text->insertPlainText("«");
            }
            else if (code_sym == 72)
            {
                ui->dic_text->insertPlainText("»");
            }
            else if (code_sym == 71)
            {
                ui->dic_text->insertPlainText(";");
            }
            else if (code_sym == 70)
            {
                ui->dic_text->insertPlainText(":");
            }
            else if (code_sym == 69)
            {
                ui->dic_text->insertPlainText("!");
            }
            else if (code_sym == 68)
            {
                ui->dic_text->insertPlainText("?");
            }
            else if (code_sym == 67)
            {
                ui->dic_text->insertPlainText("-");
            }
            else if (code_sym == 66)
            {
                ui->dic_text->insertPlainText(",");
            }
            else if (code_sym == 65)
            {
                ui->dic_text->insertPlainText(".");
            }
            else
            {
                ui->dic_text->insertPlainText(QString(QChar(code_sym+848+192)));
            }
        }
    }
    else
    {
        QMessageBox::warning(this, tr("Ошибка"), tr("Поле со словарем уже заполнено."));
    }
}

