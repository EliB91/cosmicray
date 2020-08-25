//
//  main.cpp
//  cosmicrays
//
//  Created by Elisa Bernardelli on 08/08/2020.
//  Copyright © 2020 Elisa Bernardelli. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cmath>
#include <sys/stat.h>
#include <sys/types.h>
#include <cstring>
#include <iomanip>
#include <vector>
#include <string>
#include <math.h>

//ROOT SERVE PER I GRAFICI

using namespace std;

int main(){
    double er = 4.8481368111358E-12; //2.0647E-4; //earthradius raggioterra, qua ho usato 1 AU CONVERTITA IN MPC; 2,0647 × 10^-10 parsec, QUA USO I Kpc
    ifstream in;
    in.open("/Users/Brisa/Programmino/cosmicrays/trajectoryN.txt");
    //X    Y    Z    Px    Py    Pz

    int dim;
    double *X = new double[dim];
    double *Y = new double[dim];
    double *Z = new double[dim];
    double *Px = new double[dim];
    double *Py = new double[dim];
    double *Pz= new double[dim];
    double e; // variabile appoggio per colonne
    double *trajectory = new double[dim]; // array della traiettoria dell i esimo raggio cosmico in particolare trajectory[4] dovrà contere la direzione del 5° raggio cosmico
    double *ptot = new double[dim];

    /*
     *  oltre ad avere la direzione ho la posizione del raggio cosmico, e sapendo la
     *  posizione della Terra (-8.5,0,0), in kpc, facendo un attimo di geometria
     *  dovresti ricavare se il raggio cosmico punta alla terra o meno. terra grande 1
     *  AU o arrivare fino a 1 pc (non di più direi, se anche a 1 pc nessuno punta a
     *  terra ci pensiamo un attimo ma è un po' un problema...)
    */

    // Nel file ho aggiunto il dato 4706 contate con wc che sono la dimensione dell'array (4717-11 righe iniziali)
    in >> dim;

    for(int i = 0; i<dim; i++) {
        in >> e;
        in >> e;
        in >> e;
        in >> X[i];
        in >> Y[i];
        in >> Z[i];
        in >> Px[i];
        in >> Py[i];
        in >> Pz[i];
    };

    in.close();

    ofstream out;

    out.open("/Users/Brisa/Programmino/cosmicrays/E_RC_source3kpc.txt");

    //coordinata iniziale terra (-8.5,0,0), coordinata iniziale sorgente (-3,0,0)

    for(int i=0; i<dim; i++) {
        // Il sdr è centrato sul GC e la terra è a (-8.5,0,0)
        trajectory[i] = sqrt((X[i]-8.5)*(X[i])-8.5)+ Y[i]*Y[i] + Z[i]*Z[i];
        ptot[i] = sqrt(Px[i]*Px[i]+ Py[i]*Py[i] + Pz[i]*Pz[i] );
    }
    //decide se un rc è o no nel target in base alla distanza e alla p tot//

         ///////////////////////////
         ////// DA CONTROLLARE
          ////////////////////////////////////////////////////////////////

   //vettore (Px,Py,Pz) in direzione
    /* faccio intersezione retta data da raggio cosmico con
     vettore ptot=(Px, Py, Pz) e punto t=(X,Y,Z) come traiettoria

PER ANDREA: x, y, z devo definirle?
     X, Y e Z e Px, Py e Pz le ho definite riga 50... , non devo metterle piu' no?


    double * x = new double[dim];
    double * y = new double[dim];
    double * z = new double[dim];

 EQUAZIONE RETTA raggio cosmico

     (x-X)/Px = (y-Y)/Py = (z-Z)/Pz

 SFERA data dalla terra con raggio definito
     dalla double er = 4.8481368111358E-12 definita sopra

     definisco il centro della terra:
     definisco qui le costanti?

     double c1=-8.5;
     double c2=0;
     double c3=0;

   EQUAZIONE SFERA ER

     double u=0;
     double v=0;
     double w=0;

     [(u-c1)*(u-c1)+(v-c2)*(v-c2)+(w-c3)*(w-c3)]= er*er

     u,v e w devo definirle?
     er l'ho definito ad inizio del programma

     devo scrivere il sistema tra retta raggiocosmico e sfera er

     /* per l'interesezione farei un if else ma chiedi */
    for(int b= 0; b<dim ; b++) {
    double * raggiocosmico = new double[dim];
    if(raggiocosmico<er )
        cout << "raggio cosmico colpisce la terra" << endl;
        out <<  << endl;

    if(i>er ) cout << "raggio cosmico colpisce la terra" << endl;

        else {
            cout << "Non la colpisce" << b << endl;}

            }

            out.close();

     }

    delete [] X;
    delete [] Y;
    delete [] Z;
    delete [] Px;
    delete [] Py;
    delete [] Pz;
    delete [] trajectory;
    delete [] ptot;

    return 0;
}

