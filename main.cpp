#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <algorithm>

using namespace std;

// Función de búsqueda ternaria
int busquedaTernaria(vector<int>& arr, int izquierda, int derecha, int clave) {
    if (derecha >= izquierda) {
        int tercio1 = izquierda + (derecha - izquierda) / 3;
        int tercio2 = derecha - (derecha - izquierda) / 3;

        if (arr[tercio1] == clave) return tercio1;
        if (arr[tercio2] == clave) return tercio2;

        if (clave < arr[tercio1]) {
            return busquedaTernaria(arr, izquierda, tercio1 - 1, clave);
        } else if (clave > arr[tercio2]) {
            return busquedaTernaria(arr, tercio2 + 1, derecha, clave);
        } else {
            return busquedaTernaria(arr, tercio1 + 1, tercio2 - 1, clave);
        }
    }
    return -1; // No encontrado
}

int main() {
    ifstream archivo("numeros_aleatorios.txt");
    vector<int> numeros;
    int numero;

    // Leer números del archivo
    if (archivo.is_open()) {
        while (archivo >> numero) {
            numeros.push_back(numero);
        }
        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo." << endl;
        return 1;
    }

    // Ordenar el vector para la búsqueda ternaria
    sort(numeros.begin(), numeros.end());

    int clave;
    cout << "Introduce el número que deseas buscar: ";
    cin >> clave;

    // Medir el tiempo de ejecución
    auto inicio = chrono::high_resolution_clock::now();
    int resultado = busquedaTernaria(numeros, 0, numeros.size() - 1, clave);
    auto fin = chrono::high_resolution_clock::now();
    chrono::duration<double> duracion = fin - inicio;

    if (resultado != -1) {
        cout << "Número encontrado en el índice: " << resultado << endl;
    } else {
        cout << "Número no encontrado." << endl;
    }

    cout << "Tiempo de ejecución: " << duracion.count() << " segundos" << endl;

    return 0;
}


