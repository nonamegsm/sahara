#include "log_event.h"
#include "ui_log_event.h"
#include <QDateTime>
#include <QDir>
#include <QProcess>

Log_Event::Log_Event(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Log_Event)
{
    ui->setupUi(this);

    QPalette palette;
    palette.setBrush(QPalette::Window,QBrush(QColor(Qt::white)));
//    palette.setBrush();
    setAutoFillBackground(true);
    setPalette(palette);
    ui->apply->setEnabled(false);
    ui->create_new_window->setEnabled(false);
    QDateTime datetime  = QDateTime::currentDateTime();
    ui->old_date->setDate(datetime.date());
    ui->old_time->setTime(datetime.time());
    ui->new_date->setDate(datetime.date());
    ui->new_time->setTime(datetime.time());
}

Log_Event::~Log_Event()
{
    delete ui;
}

bool Log_Event::create_dir()
{
    QDir dir(QDir::currentPath());
    if(!dir.exists("./log")){
        if(!dir.mkdir("log")){
            qDebug()<<"create log fail!";
            return false;
        }
    }
    dir.cd("./log");
    if(!dir.exists("./event")){
        if(!dir.mkdir("event")){
            qDebug()<<"create event fail!";
            return false;
        }
    }
    return true;
}

//查询日志；
QString Log_Event::search_log(QString old_date, QString new_date, QString old_time, QString new_time)
{
    QString str;
    QDir dir("./log/event");

    QStringList filter;
    filter << "*.txt";
    dir.setNameFilters(filter);
    QFileInfoList filelist    = dir.entryInfoList();
    for(int i=0;i<filelist.size();i++){
        if((filelist.at(i).fileName() >= (old_date + ".txt")) && (filelist.at(i).fileName() <= (new_date + ".txt"))){
            QFile file(tr("./log/event/%1").arg(filelist.at(i).fileName()));
            if(!file.open(QIODevice::ReadOnly | QIODevice::Truncate)){
                qDebug()<<file.errorString();
            }
            QTextStream out(&file);
            while(!out.atEnd()){
                QString temp;
                temp = out.readLine();
                if(filelist.at(i) == new_date){
                    if(temp.section(" ",1,1) > new_time){
                        break;
                    }
                }
                if(filelist.at(i) == old_date){
                    if(temp.section(".",1,1) >= old_time){
                        str += temp+'\n';
                    }
                }
                else {
                    str += temp+'\n';
                }
            }
            file.close();
        }
    }
    return str;
}

QString Log_Event::last_log()
{
    QString str;
    QDateTime datetime  = QDateTime::currentDateTime();
    QDateTime before_datetime;
    switch(index){
    case 0:
        before_datetime = datetime.addDays(-1);
        break;
    case 1:
        before_datetime = datetime.addDays(-2);
        break;
    case 2:
        before_datetime = datetime.addDays(-4);
        break;
    case 4:
        before_datetime = datetime.addDays(-7);
        break;
    case 5:
        before_datetime = datetime.addDays(-14);
        break;
    case 6:
        before_datetime = datetime.addDays(-28);
        break;
    case 7:
        str = search_log("0000.00.00",datetime.date().toString("yyyy.MM.dd"),"00:00:00",datetime.time().toString("hh:mm:ss"));
        return str;
    }
    str = search_log(before_datetime.date().toString("yyyy.MM.dd"),datetime.date().toString("yyyy.MM.dd"),"00:00:00",datetime.time().toString("hh:mm:ss"));
    return str;
}

QString Log_Event::from_log()
{
    QString str;
    str = search_log(ui->old_date->text(),ui->new_date->text(),ui->old_time->text(),ui->new_time->text());
    return str;
}

void Log_Event::save_log(Device_Name name, QString str)
{
    QString date    = QDate::currentDate().toString("yyyy.MM.dd");
    QString time    = QTime::currentTime().toString("hh:mm:ss");
    QString info;
    info    = tr("%1 %2 %3: %4\n").arg(date).arg(time).arg(name).arg(str);
    if(create_dir()){
        QFile file(tr("./log/event/%1.txt").arg(date));
        if(!file.open(QIODevice::WriteOnly | QIODevice::Append)){
            qDebug()<<file.errorString();
        }
        QTextStream in(&file);
        in << info;
        file.close();
    }
}


void Log_Event::on_radioButton_last_clicked(bool checked)
{
    checked = checked;
    flag    = 0;
    ui->apply->setEnabled(true);
    ui->create_new_window->setEnabled(true);
}

void Log_Event::on_radioButton_From_clicked(bool checked)
{
    checked = checked;
    flag    = 1;
    ui->apply->setEnabled(true);
    ui->create_new_window->setEnabled(true);
}

void Log_Event::on_comboBox_currentIndexChanged(int index)
{
    this->index = index;
}

void Log_Event::on_apply_clicked()
{
    ui->textBrowser->clear();
    if(flag == 0){
        str = last_log();
    }
    else {
        str = from_log();
    }
    ui->textBrowser->insertPlainText(str);
    emit new_widget(str);
}

void Log_Event::on_clear_log_clicked()
{
    QProcess process;
    QString cmd = "rm -rf ./log/event";
    process.execute(cmd);
    str.clear();
    emit new_widget(" ");
    ui->textBrowser->clear();
}

void Log_Event::on_create_new_window_clicked()
{
    log_widget  = new Log_widget;
    connect(this,SIGNAL(new_widget(QString)),log_widget,SLOT(show_log(QString)));
    emit new_widget(str);
    log_widget->show();
}
