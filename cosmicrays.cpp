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
#define C1 -8.5
#define C2 0
#define C3 0

#define DEBUG

using namespace std;

int main(){
    double er = 4.8481368111358E-12; //2.0647E-4; //earthradius raggioterra, qua ho usato 1 AU CONVERTITA IN MPC; 2,0647 × 10^-10 parsec, QUA USO I Kpc
    ifstream in;
    in.open("./trajectoryN_short.txt");
    //X    Y    Z    Px    Py    Pz

    int dim;
    in >> dim;
    cout << "Dimension : " << dim << endl;
    double *X = new double[dim];
    double *Y = new double[dim];
    double *Z = new double[dim];
    double *Px = new double[dim];
    double *Py = new double[dim];
    double *Pz= new double[dim];
    double e; // variabile appoggio per colonne
    double *trajectory = new double[dim]; // array della traiettoria dell i esimo raggio cosmico in particolare trajectory[4] dovrà contere la direzione del 5° raggio cosmico
    double *ptot = new double[dim];

    double *x = new double[dim];
    double *y = new double[dim];
    double *z = new double[dim];

    double u=0;
    double v=0;
    double w=0;

    /*
    *  oltre ad avere la direzione ho la posizione del raggio cosmico, e sapendo la
    *  posizione della Terra (-8.5,0,0), in kpc, facendo un attimo di geometria
    *  dovresti ricavare se il raggio cosmico punta alla terra o meno. terra grande 1
    *  AU o arrivare fino a 1 pc (non di più direi, se anche a 1 pc nessuno punta a
    *  terra ci pensiamo un attimo ma è un po' un problema...)
    */

    for(int i = 0; i < dim; i++) {
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

    out.open("/tmp/cosmicrays_output.txt");

    //coordinata iniziale terra (-8.5,0,0), coordinata iniziale sorgente (-3,0,0)

    for(int i=0; i < dim; i++) {
        // Il sdr è centrato sul GC e la terra è a (-8.5,0,0)
#ifdef DEBUG
        cout << "--------" << endl;
        cout << "X[" << i << "] = " << X[i] << endl;
        cout << "Y[" << i << "] = " << Y[i] << endl;
        cout << "Z[" << i << "] = " << Z[i] << endl;
        cout << "Px[" << i << "] = " << Px[i] << endl;
        cout << "Py[" << i << "] = " << Py[i] << endl;
        cout << "Pz[" << i << "] = " << Pz[i] << endl;
#endif //DEBUG

        trajectory[i] = sqrt(pow(X[i]-8.5, 2) + pow(Y[i], 2) + pow(Z[i], 2));
        ptot[i] = sqrt(pow(Px[i], 2) + pow(Py[i], 2) + pow(Pz[i], 2));
    }

    for (int i=0; i<10; i++) {
        cout << "--------" << endl;
        cout << "trajectory : " << trajectory[i] << endl;
        cout << "ptot : " << ptot[i] << endl;
    }
    /* Faccio intersezione retta data da raggio cosmico con
    * vettore ptot=(Px, Py, Pz) e punto t=(X,Y,Z) come traiettoria
    *
    * EQUAZIONE RETTA raggio cosmico
    * (x-X)/Px = (y-Y)/Py = (z-Z)/Pz
    *
    * SFERA data dalla terra con raggio definito
    * dalla double er = 4.8481368111358E-12 definita sopra
    *
    * EQUAZIONE SFERA ER
    * [(u-C1)*(u-C1)+(v-C2)*(v-C2)+(w-C3)*(w-C3)]= er*er
    * devo scrivere il sistema tra retta raggiocosmico e sfera er
    * per l'interesezione farei un if else ma chiedi
    */

    for (int b = 0; b < dim ; b++) {
        double raggiocosmico;

        if(raggiocosmico < er ) {
            cout << "raggio cosmico colpisce la terra" << endl;
            out << endl;
        }

        if(b > er) {
            cout << "raggio cosmico colpisce la terra" << endl;
        }
        else {
            cout << "Non la colpisce" << b << endl;
        }

        out.close();
    }

    delete[] X;
    delete[] Y;
    delete[] Z;
    delete[] Px;
    delete[] Py;
    delete[] Pz;
    delete[] trajectory;
    delete[] ptot;

    return 0;
}

