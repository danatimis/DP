#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <string>
#include <sstream>

using namespace std;

const int MAX_CLAUZE = 1000;
const int MAX_LITERE = 10;
const int MAX_VAR = 100;

int formula[MAX_CLAUZE][MAX_LITERE];
int dim_clauza[MAX_CLAUZE];
int asignari[MAX_VAR] = {0};

int nr_clauze = 0, max_litere_pe_clauza = 0, nr_variabile = 0;

void citesteFormulaDinFisier(const char* nume_fisier) {
    ifstream fin(nume_fisier);
    if (!fin) {
        cout << "Eroare la deschiderea fișierului!" << endl;
        exit(1);
    }

    string linie;
    while (getline(fin, linie)) {
        if (linie.empty()) continue;
        if (linie[0] == 'c') continue;
        if (linie[0] == 'p') {
            string tmp;
            int numVars;
            istringstream iss(linie);
            iss >> tmp >> tmp >> numVars >> nr_clauze;
            nr_variabile = numVars;
            continue;
        }

        istringstream iss(linie);
        int x;
        dim_clauza[nr_clauze] = 0;
        while (iss >> x) {
            if (x == 0) break;
            formula[nr_clauze][dim_clauza[nr_clauze]++] = x;
        }
        nr_clauze++;
    }


}

bool clauzaEsteSatisfacuta(int idx) {
    for (int j = 0; j < dim_clauza[idx]; j++) {
        int lit = formula[idx][j];
        int var = abs(lit);
        int val = asignari[var];

        if ((lit > 0 && val == 1) || (lit < 0 && val == -1)) {
            return true;
        }
    }
    return false;
}


bool clauzaEsteFalsa(int idx) {
    for (int j = 0; j < dim_clauza[idx]; j++) {
        int lit = formula[idx][j];
        int var = abs(lit);
        int val = asignari[var];

        if (val == 0) return false;
        if ((lit > 0 && val == 1) || (lit < 0 && val == -1)) {
            return false;
        }
    }
    return true;
}


bool toateClauzeleSatisfacuteSauPosibile() {
    for (int i = 0; i < nr_clauze; i++) {
        if (clauzaEsteFalsa(i)) return false;
    }
    return true;
}


bool backtrack(int var) {
    if (!toateClauzeleSatisfacuteSauPosibile()) return false;

    if (var > nr_variabile) {
        return true;
    }

    asignari[var] = 1;
    if (backtrack(var + 1)) return true;

    asignari[var] = -1;
    if (backtrack(var + 1)) return true;

    asignari[var] = 0;
    return false;
}

int main() {
    citesteFormulaDinFisier("input3.txt");

    if (backtrack(1)) {
        cout << "SATISFIABILA" << endl;
    } else {
        cout << "NESATISFIABILA" << endl;
    }

    return 0;
}
