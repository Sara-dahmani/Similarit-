#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <unordered_map>
#include <vector>

using namespace std ;

unordered_map<string, int> transformDocumentToHashTable(const string& nomDoc) {
    unordered_map<string, int> frequence;

    ifstream f(nomDoc);
    string line;

    while (getline(f, line)) {
        istringstream iss(line);
        string word;

        while (iss >> word) {
            frequence[word]++;
        }
    }

    return frequence ;
}

// Le calcul du produit scalair
double produitScalair(const unordered_map<string, int>& tabDoc1, const unordered_map<string, int>& tabDoc2) {
    double result = 0;
    for (const auto& entry : tabDoc1) {
        if (tabDoc2.find(entry.first) != tabDoc2.end()) {
            result += entry.second * tabDoc2.at(entry.first);
        }
    }
    return result;
}

// le clacul du module des hashTable ou norme
double module(const unordered_map<string, int>& tabDoc) {
    double result = 0.0;
    for (const auto& entry : tabDoc) {
        result += pow(entry.second, 2);
    }
    return sqrt(result);
}

// la fonction qui calcul la similarité

double similarite(const unordered_map<string, int>& tabDoc1, const unordered_map<string, int>& tabDoc2) {
    double produit = produitScalair(tabDoc1, tabDoc2);
    double moduleTabDoc1 = module(tabDoc1);
    double moduleTabDoc2 = module(tabDoc2);

    if ( moduleTabDoc1 == 0.0 || moduleTabDoc2 == 0.0) {
        return 0.0; 
    }

    return (produit / (moduleTabDoc1 * moduleTabDoc2))*100 ;
}

int main() {
    // entrez les noms de nos deux fichier 
    string nomDoc1 = "sara.txt";
    string nomDoc2 = "sara2.txt";

    // Transformez le contenues des docs on des HashTable
    unordered_map<string, int> tabDoc1 = transformDocumentToHashTable(nomDoc1);
    unordered_map<string, int> tabDoc2 = transformDocumentToHashTable(nomDoc2);

    // // Affichage de hash table du doc 1 
    // for (const auto& entry : tabDoc1) {
    //     cout << "Mots: " << entry.first << ", Occurrence: " << entry.second << endl;
    // }

    //appelle de la fonction de similarité 

    double similarité = similarite(tabDoc1 , tabDoc2);

    cout << "La similitude entre les deux fichier est de :" << similarité << " %" << endl ;

    return 0;
}