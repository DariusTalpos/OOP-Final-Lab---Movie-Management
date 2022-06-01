#include "CRUDGui.h"
void CRUDCosGui::initGUIComponents()
{

    setLayout(hlyMain);

    QWidget* widStanga = new QWidget;
    QVBoxLayout* vertLay = new QVBoxLayout;
    widStanga->setLayout(vertLay);
    //list = new QListWidget;
    //table = new QTableWidget;
    tableV = new QTableView();
    tableM = new MyTableModel(service.service_get_cos());
    //vertLay->addWidget(list);
    vertLay->addWidget(tableV);

    QWidget* w = new QWidget;
    QFormLayout* form = new QFormLayout;
    w->setLayout(form);

    txtSize = new QLineEdit;
    form->addRow(new QLabel("Dimensiune: "), txtSize);

    txtNr = new QLineEdit;
    form->addRow(new QLabel("Nr. filme: "), txtNr);
    btnRandomCos = new QPushButton("Adaugare random in cos");
    form->addWidget(btnRandomCos);

    vertLay->addWidget(w);


    QWidget* widDetalii = new QWidget;
    QFormLayout* formLDetalii = new QFormLayout;
    widDetalii->setLayout(formLDetalii);
    /*txtTitlu = new QLineEdit;
    formLDetalii->addRow(new QLabel("Titlu: "), txtTitlu);
    txtActor = new QLineEdit;
    formLDetalii->addRow(new QLabel("Actor principal: "), txtActor);
    txtGen = new QLineEdit;
    formLDetalii->addRow(new QLabel("Gen: "), txtGen);
    txtAnAparitie = new QLineEdit;
    formLDetalii->addRow(new QLabel("An aparitie: "), txtAnAparitie);*/

    //btnAdaugaCos = new QPushButton("Adaugare in cos");
    btnGolireCos = new QPushButton("Golire cos");
    //formLDetalii->addWidget(btnAdaugaCos);
    formLDetalii->addWidget(btnGolireCos);


    hlyMain->addWidget(widStanga);
    hlyMain->addWidget(widDetalii);
}

void CRUDCosGui::connectSignalSlots() {
    QObject::connect(btnGolireCos, &QPushButton::clicked, this, &CRUDCosGui::guiCosReset);
    QObject::connect(btnRandomCos, &QPushButton::clicked, this, &CRUDCosGui::guiCosRandom);


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
}

void CRUDCosGui::guiCosAdd()
{
    try
    {
        service.service_add_cos(txtTitlu->text().toStdString());
        //reload(service.service_get_cos());
    }
    catch (ValidatorExceptii& ve)
    {
        QMessageBox::warning(this, "Eroare", QString::fromStdString(ve.getErori()));
    }
}

void CRUDCosGui::guiCosReset()
{
    try
    {
        service.service_reset_cos();
        //reload(service.service_get_cos());
    }
    catch (ValidatorExceptii& ve)
    {
        QMessageBox::warning(this, "Eroare", QString::fromStdString(ve.getErori()));
    }
}

void CRUDCosGui::guiCosRandom()
{
    try
    {
        service.service_fill_cos(txtNr->text().toStdString());
        //reload(service.service_get_cos());
    }
    catch (ValidatorExceptii& ve)
    {
        QMessageBox::warning(this, "Eroare", QString::fromStdString(ve.getErori()));
    }
}

void CRUDCosGui::guiCosExport()
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

void CRUDCosGui::reload(vector<Film> filme)
{
    /*lb_index = static_cast<int>(filme.size()) + 1;
    list->clear();
    for (const auto f : filme)
    {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(f.getTitlu()));
        item->setData(Qt::UserRole, QString::fromStdString(f.getGen()));
        list->addItem(item);
    }
    txtSize->setText(QString::number(service.service_lungime_cos()));*/

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
        table->setItem(poz, 0, item);
        table->setItem(poz, 1, item2);
        poz++;
    }*/
}

void CRUDCosGui::update()
{
    //reload(service.service_get_cos());
    tableM->setElements(service.service_get_cos());
    txtSize->setText(QString::number(service.service_lungime_cos()));
}
