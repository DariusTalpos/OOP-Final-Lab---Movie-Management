#include "Lab_10_11.h"
#include "Teste.h"
#include <QtWidgets/QApplication>
using namespace std;

int main(int argc, char *argv[])
{
   Cos cos,cost;
   FileRepository fr,frt;
   ValidatorFilme val,valt;
   Service service{fr, cos, val },servicet{frt,cost,valt};
   Repository rept;
   Teste test{servicet, rept, frt, cost};
   QApplication a(argc, argv);
   GUILab_10_11 w(service, cos);
   test.teste();
   w.show();
   return a.exec();
}
