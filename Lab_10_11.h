#pragma once

#include <QtWidgets/QMainWindow>
#include <qlabel.h>
#include <qwidget.h>
#include <qformlayout.h>
#include <qboxlayout.h>
#include <qlistwidget.h>
#include <qpushbutton.h>
#include <qtablewidget.h>
#include "MyListModel.h"
#include "MyTableModel.h"
#include "CRUDGui.h"
#include "CosReadOnlyGUI.h"
#include "ui_Lab_10_11.h"
#include "Service.h"
#include "Cos.h"

class GUILab_10_11 : public QWidget
{
private:

    Service& service;
    Cos& cos;

    vector<Film> empty;
    vector<string> btnGen;
    vector<QPushButton*> butoaneGen;
    QHBoxLayout* hlyMain = new QHBoxLayout;

    //QListWidget* list;
    //QTableWidget* table;
    QListView* listV;
    MyListModel* listM;
   /* QTableView* tableV;
    MyTableModel* tableM;*/

    QLineEdit* txtTitlu;
    QLineEdit* txtActor;
    QLineEdit* txtGen;
    QLineEdit* txtAnAparitie;
    QLineEdit* txtNr;
    QLineEdit* txtNumeFisier;
    QWidget* widGen = new QWidget;
    QFormLayout* formGen = new QFormLayout;

    QPushButton* btnAdaugaFilm;
    QPushButton* btnModificareFilm;
    QPushButton* btnStergereFilm;
    QPushButton* btnSortareTitlu;
    QPushButton* btnSortareActor;
    QPushButton* btnSortareAnGen;
    QPushButton* btnFilm;
    QPushButton* btnUndo;
    QPushButton* btnCautareTitlu;
    QPushButton* btnFilterAn;
    QPushButton* btnCRUDCos;
    QPushButton* btnReadOnlyCos;
    QPushButton* btnAdaugaCos;
    QPushButton* btnRandomCos;
    QPushButton* btnGolireCos;
    QPushButton* btnExport;
    QPushButton* resetti;


    QVBoxLayout* vly = new QVBoxLayout;
    QWidget* wid = new QWidget;

    int lb_index;
    bool stitlu;
    bool sactor;
    bool san;

    void initGUIComponents();
    void addDynamicButtons();
    void connectSignalSlots();

    void gui_add();
    void gui_modify();
    void gui_delete();
    void gui_sort_titlu();
    void gui_sort_actor();
    void gui_sort_an_gen();
    void gui_undo();
    void gui_filter_titlu();
    void gui_filter_an();
    void gui_show_cos();
    void guiCosRandom();
    void guiCosAdauga();
    void guiGolireCos();
    void guiExport();
    void you_asked_for_it();
    void reload(vector<Film> filme, vector<Film> filtrat);

public:
    GUILab_10_11(Service& s, Cos& c) : service{ s }, cos{c}
    {
        initGUIComponents();
        //tableV->setModel(tableM);
        listV->setModel(listM);
        connectSignalSlots();
        //tableM->setElements(service.service_get());
        listM->setElements(service.service_get());
    }
};