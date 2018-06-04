
#include <QApplication>
#include "principal.h"

int main()
{
    /*Automate2D a(2,3,2,4);

    cout << "Creation d'etats" << endl;
    Etat2D e2(7,4);
    e2.setCellule(4,2,true);
    e2.setCellule(3,1,true);
    e2.setCellule(6,3,true);
    e2.setCellule(1,0,true);
    e2setCellule(6,0,true);

    Simulateur2D s(a,e2);
    cout<<e2;
    for(unsigned int i=0;i<10;i++){

        s.next();
        cout<<s.dernier()<<"\n";

    }*/
	
	cout<<"Hello World !!"<<std::endl;

    cout << "Creation d'etats" << endl;
    Etat1D e1(15);
    e1.setCellule(4,true);
    e1.setCellule(3,true);
    e1.setCellule(6,true);
    e1.setCellule(1,true);
    e1.setCellule(13,true);
    e1.setCellule(11,true);
    e1.setCellule(10,true);
    e1.setCellule(0,true);
    e1.setCellule(8,true);

    Automate1D a=Automate1D(25);

    Simulateur1D s(a,e1);
    cout<<e1;
    for(unsigned int i=0;i<10;i++){
        s.next();
        cout<<s.dernier()<<"\n";

    }


    return 0;

}
