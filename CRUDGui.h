#pragma once
#include <qlabel.h>
#include <qwidget.h>
#include <qformlayout.h>
#include <qboxlayout.h>
#include <qlistwidget.h>
#include <qpushbutton.h>
#include <qtablewidget.h>
#include <qlineedit.h>
#include <qmessagebox.h>
#include "MyTableModel.h"
#include "ui_Lab_10_11.h"
#include "Service.h"
#include "Observer.h"

class CRUDCosGui : public QWidget, public Observer
{
    Service& service;
    Cos& cos;

    QHBoxLayout* hlyMain = new QHBoxLayout;

    //QTableWidget* table;
    MyTableModel* tableM;
    QTableView* tableV;

    QLineEdit* txtTitlu;
    QLineEdit* txtActor;
    QLineEdit* txtGen;
    QLineEdit* txtAnAparitie;
    QLineEdit* txtNr;
    QLineEdit* txtNumeFisier;
    QLineEdit* txtSize;

    QPushButton* btnRandomCos;
    QPushButton* btnGolireCos;



    QVBoxLayout* vly = new QVBoxLayout;
    QWidget* wid = new QWidget;

    int lb_index;

    void initGUIComponents();
    void connectSignalSlots();
    void reload(vector<Film> filme);

    void guiCosAdd();
    void guiCosRandom();
    void guiCosExport();
    void guiCosReset();

public:
    CRUDCosGui(Service& s, Cos& c) : service{ s }, cos{c}
    {
        cos.addObserver(this);
        initGUIComponents();
        tableV->setModel(tableM);
        connectSignalSlots();
        tableM->setElements(service.service_get_cos());
        txtSize->setText(QString::number(service.service_lungime_cos()));
    }
    void update() override;
};

