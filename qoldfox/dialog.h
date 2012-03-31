//////////////////////////////////////////////////////////////////////////
// This file belongs to qOldFox.                                        //
// Copyright (C) 2012 Ashok Shankar Das ashok.s.das@gmail.com           //
// Released under GNU GPL-V2 licence.                                   //
// for details of licence please see the copying file                   //
// or visit http://www.gnu.org and get a copy of GNU GPL-V2 licence     //
// This file is automatically generated by QtCreator.                   //
//////////////////////////////////////////////////////////////////////////

#ifndef DIALOG_H
#define DIALOG_H
#include <QMessageBox>
#include <QDebug>
#include <QString>
#include <QSqlRecord>
#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QProcess>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QSqlQueryModel>


namespace Ui {
    class Dialog;
}
struct myLocation
{
    float latitude;
    float longitude;
    QString city;
    //QString country;
};

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Ui::Dialog *ui;
    QGraphicsScene myScene;
    QGraphicsPixmapItem item;
    myLocation currentloc;
    myLocation lastloc;
    QPen mypen;
    QFont myfont;
    QProcess tracer;
    QSqlDatabase db;
    QSqlQueryModel model;
    long typeIndex;
    void setup_database();
    QSqlError last_error(){ return db.lastError();}
    void plotLocation(struct myLocation *mloc);
    void load_map();

private slots:
    void on_traceButton_clicked();
    void on_stopButton_clicked();
    void on_exitButton_clicked();
    void processError(QProcess::ProcessError err);
    void myOutput();

};

#endif // DIALOG_H