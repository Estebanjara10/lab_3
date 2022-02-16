#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

using std::string;
using std::bitset;
//
//string toBinary(int txt);
string contar0_1(string byteStr);
int n;
std::string text;
string fuenteName;
string salidaName;
//
int main()
{
    int opcion=1;
    while(opcion != 0){
        cout << endl << "Seleccione un metodo"<<endl;
        cout << "------------------------------"<<endl;
        cout << "1.Metodo 1"<<endl;
        cout << "2.Metodo 2"<<endl;
        cout << "0.Para SALIR..."<<endl;;
        cout << "------------------------------"<<endl;
        cin>>opcion;
        switch(opcion){
        case 1:
            cout<<"Ingrese valor de N para bloque (semilla): " << endl;
            cin>>n;
            //
            cout<<"Ingrese nombre archivo fuente: " << endl;
            cin>>fuenteName;
            //
            cout<<"Ingrese nombre archivo salida: " << endl;
            cin>>salidaName;
            //
            ifstream txtInFile;
            // Nota: La ruta tiene como separador el doble \\, para Windows
            string rutaTmp = "C:\\temp\\";
            txtInFile.open(rutaTmp.append(fuenteName).append(".txt"));
            // creacion del archivo de salida:
            ofstream binOutFile;
            rutaTmp = "C:\\temp\\";
            binOutFile.open(rutaTmp.append(salidaName).append(".txt"));
            //
            // cout << "Ingrese el texto a encriptar: ";
            // std::getline(std::cin >> std::ws, text); // importante para leer del CIN textos con espacios de UNA SOlA Linea!!
            std::getline(txtInFile >> std::ws, text); // Lee el texto hasta el primer espacio en una LINEA del archivo!
            // txtInFile >> text // Lee el texto hasta el primer espacio en el archivo!
            cout << "TEXTO BASE:  " << text << endl;
            //
            string byteStr = "";
            for (int i = 0; i < (int)text.length(); ++i) { // ciclo para convertir a binario
                  //
                  bitset<8> bs4(text[i]);
                  //cout << bs4 << " ";
                  byteStr.append(bs4.to_string());
                  /*
                  if (i % 6 == 0 && i != 0)
                      cout << endl;
                  */
            }
            int byteStrLen = (int)byteStr.length();
            int residuo = byteStrLen % n;
            if ((n < 2) || (residuo > 0)) {
                cout << "El valor N del bloque NO es adecuado !!" << endl;
                break;
            } else if (n > byteStrLen) {
                n = byteStrLen;
            }
            cout << "BIN ANTES:  " << byteStr << endl;
            string byteSalidaStr = byteStr;
            // Se aplica la conversion inicial al bloque 1 segun el metodo #1:
            for (int i=0; i<n ;i++ ) {
                if (byteStr[i]=='0') {
                    byteSalidaStr[i]='1'; //intercambio de numeros de la primera parte
                 }
                else {
                    byteSalidaStr[i]='0';
                }
            }
            int numBloq = byteStrLen / n; //proceso del metodo 1
            int idx = 0;
            int i = 0;
            string bloqueStr = "";
            cout << "numBloq, resid: " << numBloq << "," << residuo << endl;
            while(i < numBloq) {
                for (int k = 0; k < n; k++) {
                    bloqueStr.append(1, byteStr[idx + k]);
                }
                cout << "bloqueStr=" << bloqueStr << endl;
                cout << "contar0_1(bloqueStr)=" << contar0_1(bloqueStr) << endl;
                bloqueStr = "";
                i++;
                idx = i * n;
            }

            cout << "BIN DESPUES: " << byteSalidaStr << endl;
            binOutFile << byteSalidaStr;
            binOutFile.close();
        break;
        // FIN CASE 1!

    } // fin switch
  } //fin while
} //fin main
//
// Funciones:
string contar0_1(string bloqueStr) {   // funcion para el conteo de 1 y 0
    string res = "";
    int cont0 = 0, cont1 = 0;
    for(int z = 0; z < (int)bloqueStr.length(); z++) {
        if (bloqueStr[z] == '0') {
            cont0++;
        } else {
            cont1++;
        }
    }
    if(cont0 == cont1) {
        res = "igual";
    } else if(cont0 > cont1) {
        res = "+0";
    } else {
        res = "+1";
    }
    return res;
}
