#include "Lab_10_11.h"
#include <QtWidgets/qformlayout.h>
#include <qlineedit.h>
#include <QtWidgets/QMessageBox>

void GUILab_10_11::initGUIComponents()
{
    service.service_load();
    stitlu = sactor = san = true;

    setLayout(hlyMain);

    QWidget* widStanga = new QWidget;
    QVBoxLayout* vertLay = new QVBoxLayout;
    widStanga->setLayout(vertLay);
    //list = new QListWidget;
    //vertLay->addWidget(list);
    //table = new QTableWidget;
    //vertLay->addWidget(table);
    listV = new QListView();
    listM = new MyListModel(service.service_get());
    vertLay->addWidget(listV);
    //tableV = new QTableView();
    //tableM = new MyTableModel(service.service_get());
    //vertLay->addWidget(tableV);

    QWidget* widButoaneStanga = new QWidget;
    QHBoxLayout* hlyButoaneStanga = new QHBoxLayout;
    widButoaneStanga->setLayout(hlyButoaneStanga);
    btnSortareTitlu = new QPushButton("Sortare dupa titlu");
    hlyButoaneStanga->addWidget(btnSortareTitlu);

    btnSortareActor = new QPushButton("Sortare dupa actor");
    hlyButoaneStanga->addWidget(btnSortareActor);

    btnSortareAnGen = new QPushButton("Sortare dupa an si gen");
    hlyButoaneStanga->addWidget(btnSortareAnGen);
    vertLay->addWidget(widButoaneStanga);
    hlyMain->addWidget(widStanga);

   
    QWidget* widDetalii = new QWidget;
    QFormLayout* formLDetalii = new QFormLayout;
    widDetalii->setLayout(formLDetalii);
    txtTitlu = new QLineEdit;
    formLDetalii->addRow(new QLabel("Titlu: "), txtTitlu);
    txtActor = new QLineEdit;
    formLDetalii->addRow(new QLabel("Actor principal: "), txtActor);
    txtGen = new QLineEdit;
    formLDetalii->addRow(new QLabel("Gen: "), txtGen);
    txtAnAparitie = new QLineEdit;
    formLDetalii->addRow(new QLabel("An aparitie: "), txtAnAparitie);

    btnAdaugaFilm = new QPushButton("Adaugare film");
    btnModificareFilm = new QPushButton("Modificare film");
    btnStergereFilm = new QPushButton("Stergere film");
    btnUndo = new QPushButton("Undo");
    btnCautareTitlu = new QPushButton("Cautare dupa titlu");
    btnFilterAn = new QPushButton("Filtrare dupa an");
    resetti = new QPushButton("Restare cautare/filtrare");
    
    QWidget* w = new QWidget;
    QFormLayout* form = new QFormLayout;
    w->setLayout(form);

    btnCRUDCos = new QPushButton("CRUD Cos");
    btnReadOnlyCos = new QPushButton("ReadOnly Cos");
    form->addWidget(btnCRUDCos);
    form->addWidget(btnReadOnlyCos);

    btnAdaugaCos = new QPushButton("Adauga film in cos");
    btnGolireCos = new QPushButton("Golire cos");
    form->addWidget(btnAdaugaCos);
    form->addWidget(btnGolireCos);

    txtNr = new QLineEdit;
    form->addRow(new QLabel("Nr. filme: "), txtNr);
    btnRandomCos = new QPushButton("Adaugare random in cos");
    form->addWidget(btnRandomCos);

    txtNumeFisier = new QLineEdit;
    form->addRow(new QLabel("Nume fisier: "), txtNumeFisier);
    btnExport = new QPushButton("Export cos");
    form->addWidget(btnExport);



    formLDetalii->addWidget(btnAdaugaFilm);
    formLDetalii->addWidget(btnModificareFilm);
    formLDetalii->addWidget(btnStergereFilm);
    formLDetalii->addWidget(btnUndo);
    formLDetalii->addWidget(btnCautareTitlu);
    formLDetalii->addWidget(btnFilterAn);
    formLDetalii->addWidget(resetti);
    


    hlyMain->addWidget(widDetalii);
    hlyMain->addWidget(w);
    hlyMain->addWidget(wid);
    
    reload(service.service_get(), service.service_get_cos());

    addDynamicButtons();

    widGen->setLayout(formGen);
    hlyMain->addWidget(widGen);
}

void GUILab_10_11::addDynamicButtons()
{
    vector<Film> lista = service.service_get();
    bool ok;
    for (const auto f : lista)
    {
        ok = false;
        for (const auto& gen : btnGen)
            if (f.getGen() == gen)
                ok = true;
        if (ok == false)
        {
            QPushButton* btnDyn = new QPushButton(QString::fromStdString(f.getGen()));
            butoaneGen.push_back(btnDyn);
            formGen->addWidget(btnDyn);
            QObject::connect(btnDyn, &QPushButton::clicked, [this, btnDyn]() 
                {
                    string data;
                    unordered_map<string, int> stats = service.service_raport();
                    if(stats[btnDyn->text().toStdString()]!=1)
                        data = "Exista " + to_string(stats[btnDyn->text().toStdString()]) + string(" filme care au genul ") + btnDyn->text().toStdString();
                    else
                        data = "Exista un film care are genul " + btnDyn->text().toStdString();
                    QMessageBox::information(this, "Raport", QString::fromStdString(data));
                });

        }
    }
}

void GUILab_10_11::connectSignalSlots() {
    QObject::connect(btnAdaugaFilm, &QPushButton::clicked,this, &GUILab_10_11::gui_add);
    QObject::connect(btnModificareFilm, &QPushButton::clicked, this, &GUILab_10_11::gui_modify);
    QObject::connect(btnStergereFilm, &QPushButton::clicked, this, &GUILab_10_11::gui_delete);
    QObject::connect(btnSortareTitlu, &QPushButton::clicked, this, &GUILab_10_11::gui_sort_titlu);
    QObject::connect(btnSortareActor, &QPushButton::clicked, this, &GUILab_10_11::gui_sort_actor);
    QObject::connect(btnSortareAnGen, &QPushButton::clicked, this, &GUILab_10_11::gui_sort_an_gen);
    QObject::connect(btnUndo, &QPushButton::clicked, this, &GUILab_10_11::gui_undo);
    QObject::connect(btnCautareTitlu, &QPushButton::clicked, this, &GUILab_10_11::gui_filter_titlu);
    QObject::connect(btnAdaugaCos, &QPushButton::clicked, this, &GUILab_10_11::guiCosAdauga);
    QObject::connect(btnGolireCos, &QPushButton::clicked, this, &GUILab_10_11::guiGolireCos);
    QObject::connect(btnRandomCos, &QPushButton::clicked, this, &GUILab_10_11::guiCosRandom);
    QObject::connect(btnExport, &QPushButton::clicked, this, &GUILab_10_11::guiExport);
    QObject::connect(btnFilterAn, &QPushButton::clicked, this, &GUILab_10_11::gui_filter_an);
    QObject::connect(btnCRUDCos, &QPushButton::clicked, this, &GUILab_10_11::gui_show_cos);
    QObject::connect(btnReadOnlyCos, &QPushButton::clicked, this, &GUILab_10_11::you_asked_for_it);
    QObject::connect(resetti, &QPushButton::clicked, this, [=]
        {
            //reload(service.service_get(), empty);
            //tableM->setElements(service.service_get());
            listM->setElements(service.service_get());
        });
    /*QObject::connect(list, &QListWidget::itemSelectionChanged, [&]() {
        auto sel = list->selectedItems();
        if (sel.empty()) 
        {
            txtTitlu->setText("");
            txtGen->setText("");
            txtActor->setText("");
            txtAnAparitie->setText("");
        }
        else 
        {
            auto sel_item = sel.at(0);
            auto titlu = sel_item->text();
            auto gen = sel_item->data(Qt::UserRole).toString();
            Film to_print;
            int index = 1;
            for (const auto& film : service.service_get()) {
                if (film.getTitlu() == titlu.toStdString() && film.getGen() == gen.toStdString()) {
                    to_print = film;
                    lb_index = index;
                }
                ++index;
            }
            txtTitlu->setText(titlu);
            txtGen->setText(gen);
            txtActor->setText(QString::fromStdString(to_print.getActor()));
            txtAnAparitie->setText(QString::number(to_print.getAn()));
        }
        });*/


    /*QObject::connect(table, &QTableWidget::itemSelectionChanged, [&]() {
        auto sel = table->selectedItems();
        if (sel.empty())
        {
            txtTitlu->setText("");
            txtGen->setText("");
            txtActor->setText("");
            txtAnAparitie->setText("");
        }
        else
        {
            auto sel_item = sel.at(0);
            auto titlu = sel_item->text();
            auto gen = sel_item->data(Qt::UserRole).toString();
            Film to_print;
            int index = 1;
            for (const auto& film : service.service_get()) {
                if ((film.getTitlu() == titlu.toStdString() && film.getGen() == gen.toStdString()) || (film.getActor() == titlu.toStdString() && film.getGen() == gen.toStdString())) {
                    to_print = film;
                    lb_index = index;
                }
                ++index;
            }
            txtTitlu->setText(QString::fromStdString(to_print.getTitlu()));
            txtGen->setText(gen);
            txtActor->setText(QString::fromStdString(to_print.getActor()));
            txtAnAparitie->setText(QString::number(to_print.getAn()));
        }
        });*/
    
        QObject::connect(listV->selectionModel(), &QItemSelectionModel::selectionChanged, [&]() {
            auto sel = listV->selectionModel()->selectedIndexes();
            if (sel.empty())
            {
                txtTitlu->setText("");
                txtGen->setText("");
                txtActor->setText("");
                txtAnAparitie->setText("");
            }
            else
            {
                auto sel_item = sel.at(0);
                auto titlu = sel_item.data(Qt::UserRole).toString();
                auto gen = QString::fromStdString(service.service_search(titlu.toStdString()).getGen());

                Film to_print;
                int index = 1;
                for (const auto& film : service.service_get()) {
                    if (film.getTitlu() == titlu.toStdString() && film.getGen() == gen.toStdString()) {
                        to_print = film;
                        lb_index = index;
                    }
                    ++index;
                }
                txtTitlu->setText(titlu);
                txtGen->setText(gen);
                txtActor->setText(QString::fromStdString(to_print.getActor()));
                txtAnAparitie->setText(QString::number(to_print.getAn()));
            }
            });

        /*QObject::connect(tableV->selectionModel(), &QItemSelectionModel::selectionChanged, [&]() {
            auto sel = tableV->selectionModel()->selectedIndexes();
            if (sel.empty())
            {
                txtTitlu->setText("");
                txtGen->setText("");
                txtActor->setText("");
                txtAnAparitie->setText("");
            }
            else
            {
                auto sel_item = sel.at(0);
                auto titlu = sel_item.data(Qt::UserRole).toString();
                auto gen = QString::fromStdString(service.service_search(titlu.toStdString()).getGen());
                Film to_print;
                int index = 1;
                for (const auto& film : service.service_get()) {
                    if ((film.getTitlu() == titlu.toStdString() && film.getGen() == gen.toStdString()) || (film.getActor() == titlu.toStdString() && film.getGen() == gen.toStdString())) {
                        to_print = film;
                        lb_index = index;
                    }
                    ++index;
                }
                txtTitlu->setText(QString::fromStdString(to_print.getTitlu()));
                txtGen->setText(gen);
                txtActor->setText(QString::fromStdString(to_print.getActor()));
                txtAnAparitie->setText(QString::number(to_print.getAn()));
            }
            });*/
}

void GUILab_10_11::gui_add()
{
    try
    {
        service.service_add(txtTitlu->text().toStdString(), txtGen->text().toStdString(), txtActor->text().toStdString(), txtAnAparitie->text().toStdString());
        //reload(service.service_get(), service.service_get_cos());
        //tableM->setElements(service.service_get());
        listM->setElements(service.service_get());
    }
    catch (ValidatorExceptii& ve)
    {
        QMessageBox::warning(this, "Eroare", QString::fromStdString(ve.getErori()));
    }
}

void GUILab_10_11::gui_modify()
{
    string pozitie = to_string(lb_index);
    try
    {
        service.service_modify(txtTitlu->text().toStdString(), txtGen->text().toStdString(), txtActor->text().toStdString(), txtAnAparitie->text().toStdString(), pozitie);
        //reload(service.service_get(), service.service_get_cos());
        //tableM->setElements(service.service_get());
        listM->setElements(service.service_get());
    }
    catch (ValidatorExceptii& ve)
    {
        QMessageBox::warning(this, "Eroare", QString::fromStdString(ve.getErori()));
    }
}

void GUILab_10_11::gui_delete()
{
    string pozitie = to_string(lb_index);
    try
    {
        service.service_delete(pozitie);
        //reload(service.service_get(), empty);
        //tableM->setElements(service.service_get());
        listM->setElements(service.service_get());
    }
    catch (ValidatorExceptii& ve)
    {
        QMessageBox::warning(this, "Eroare", QString::fromStdString(ve.getErori()));
    }
}

void GUILab_10_11::gui_sort_titlu()
{
    
    if (stitlu)
    {
        stitlu = false;
        //reload(service.service_sort("titlu", "crescator"), empty);
        //tableM->setElements(service.service_sort("titlu", "crescator"));
        listM->setElements(service.service_sort("titlu", "crescator"));
    }
    else
    {
        stitlu = true;
        //reload(service.service_sort("titlu", "descrescator"), empty);
        //tableM->setElements(service.service_sort("titlu", "descrescator"));
        listM->setElements(service.service_sort("titlu", "descrescator"));
    }
}

void GUILab_10_11::gui_sort_actor()
{
    if (sactor)
    {
        sactor = false;
        //reload(service.service_sort("actor", "crescator"), empty);
        //tableM->setElements(service.service_sort("actor", "crescator"));
        listM->setElements(service.service_sort("actor", "crescator"));
    }
    else
    {
        sactor = true;
        //reload(service.service_sort("actor", "descrescator"), empty);
        //tableM->setElements(service.service_sort("actor","descrescator"));
        listM->setElements(service.service_sort("actor", "descrescator"));
    }
    
}

void GUILab_10_11::gui_sort_an_gen()
{
    if (san)
    {
        san = false;
        //reload(service.service_sort("an+gen", "crescator"), empty);
        //tableM->setElements(service.service_sort("an+gen","crescator"));
        listM->setElements(service.service_sort("an+gen", "crescator"));
    }
    else
    {
        san = true;
        //reload(service.service_sort("an+gen", "descrescator"), empty);
        //tableM->setElements(service.service_sort("an+gen","descrescator"));
        listM->setElements(service.service_sort("an+gen", "descrescator"));
    }
}

void GUILab_10_11::gui_undo()
{
    try
    {
        service.service_undo();
        //reload(service.service_get(), empty);
        //tableM->setElements(service.service_get());
        listM->setElements(service.service_get());
    }
    catch (ValidatorExceptii& ve)
    {
        QMessageBox::warning(this, "Eroare", QString::fromStdString(ve.getErori()));
    }
}

void GUILab_10_11::gui_filter_titlu()
{
    try
    {
        vector<Film> filtrat = service.service_filter("1", txtTitlu->text().toStdString());
        reload(service.service_get(), filtrat);
        //tableM->setElements(filtrat);
        listM->setElements(filtrat);
    }
    catch (ValidatorExceptii& ve)
    {
        QMessageBox::warning(this, "Eroare", QString::fromStdString(ve.getErori()));
    }

}

void GUILab_10_11::gui_filter_an()
{
    try
    {
        vector<Film> filtrat = service.service_filter("3", txtAnAparitie->text().toStdString());
        reload(service.service_get(), filtrat);
        //tableM->setElements(filtrat);
        listM->setElements(filtrat);
    }
    catch (ValidatorExceptii& ve)
    {
        QMessageBox::warning(this, "Eroare", QString::fromStdString(ve.getErori()));
    }
}

void GUILab_10_11::gui_show_cos()
{
    CRUDCosGui* CRUDcos = new CRUDCosGui(service, cos);
    CRUDcos->show();
}

void GUILab_10_11::you_asked_for_it()
{
    CosReadOnlyGUI* imSorry = new CosReadOnlyGUI(service, cos);
    imSorry->show();
}

void GUILab_10_11::guiCosRandom()
{
    try
    {
        cos.cos_fill(stoi(txtNr->text().toStdString()),service.service_get());
    }
    catch (ValidatorExceptii& ve)
    {
        QMessageBox::warning(this, "Eroare", QString::fromStdString(ve.getErori()));
    }
}

void GUILab_10_11::guiCosAdauga()
{
    try
    {
        service.service_add_cos(txtTitlu->text().toStdString());
    }
    catch (ValidatorExceptii& ve)
    {
        QMessageBox::warning(this, "Eroare", QString::fromStdString(ve.getErori()));
    }

}

void GUILab_10_11::guiGolireCos()
{
    try
    {
        service.service_reset_cos();
    }
    catch (ValidatorExceptii& ve)
    {
        QMessageBox::warning(this, "Eroare", QString::fromStdString(ve.getErori()));
    }
}

void GUILab_10_11::guiExport()
{
    try
    {
        service.service_export(txtNumeFisier->text().toStdString(), service.service_get_cos());
    }
    catch (ValidatorExceptii& ve)
    {
        QMessageBox::warning(this, "Eroare", QString::fromStdString(ve.getErori()));
    }
}

void GUILab_10_11::reload(vector<Film> filme, vector<Film> filtrat)
{
    /*lb_index = static_cast<int>(filme.size()) + 1;
    list->clear();
    for (const auto f : filme)
    {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(f.getTitlu()));
        item->setData(Qt::UserRole, QString::fromStdString(f.getGen()));
        for (const auto c : filtrat)
        {
            if(c.getTitlu()==f.getTitlu())
                item->setData(Qt::BackgroundRole, QBrush{ Qt::green, Qt::SolidPattern });
        }
        list->addItem(item);
    }*/

   /* table->clear();
    table->setRowCount(static_cast<int>(filme.size()));
    table->setColumnCount(2);
    int poz = 0;
    for (const auto f : filme)
    {
        QTableWidgetItem* item = new QTableWidgetItem(QString::fromStdString(f.getTitlu()));
        QTableWidgetItem* item2 = new QTableWidgetItem(QString::fromStdString(f.getActor()));
        item->setData(Qt::UserRole, QString::fromStdString(f.getGen()));
        item2->setData(Qt::UserRole, QString::fromStdString(f.getGen()));
        for (const auto c : filtrat)
        {
            if (c.getTitlu() == f.getTitlu())
            {
                item->setData(Qt::BackgroundRole, QBrush{ Qt::green, Qt::SolidPattern });
                item2->setData(Qt::BackgroundRole, QBrush{ Qt::green, Qt::SolidPattern });
            }
        }
        table->setItem(poz,0,item);
        table->setItem(poz, 1, item2);
        poz++;
    }*/
}


