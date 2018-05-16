#include "log_widget.h"
#include "ui_log_widget.h"

Log_widget::Log_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Log_widget)
{
    ui->setupUi(this);
    setWindowTitle("display event message log");
}

Log_widget::~Log_widget()
{
    delete ui;
}

void Log_widget::closeEvent(QCloseEvent *e)
{
    this->deleteLater();
}

void Log_widget::show_log(QString str)
{
    ui->textBrowser->insertPlainText(str);
}
