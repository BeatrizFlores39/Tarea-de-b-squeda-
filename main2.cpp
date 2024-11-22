#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <limits>

using namespace std;

// Función para hacer la búsqueda ternaria
int busquedaTernaria(const vector<int>& arr, int inicio, int fin, int clave) {
    if (inicio > fin) {
        return -1; // Si no se encuentra la clave
    }

    int tercio1 = inicio + (fin - inicio) / 3;
    int tercio2 = fin - (fin - inicio) / 3;

    if (arr[tercio1] == clave) {
        return tercio1; // Encontrado en el primer tercio
    } else if (arr[tercio2] == clave) {
        return tercio2; // Encontrado en el segundo tercio
    } else if (clave < arr[tercio1]) {
        return busquedaTernaria(arr, inicio, tercio1 - 1, clave); // Revisar en el primer tercio
    } else if (clave > arr[tercio2]) {
        return busquedaTernaria(arr, tercio2 + 1, fin, clave); // Revisar en el último tercio
    } else {
        return busquedaTernaria(arr, tercio1 + 1, tercio2 - 1, clave); // Revisar entre los tercios
    }
}

int main() {
    ifstream archivo("numeros_aleatorios.txt");
    vector<int> numeros;
    int numero;

    // Abrir el archivo y leer los números
    if (archivo.is_open()) {
        while (archivo >> numero) {
            numeros.push_back(numero); // Guardar los números en el vector
        }
        archivo.close();
    } else {
        cerr << "Error: No pude abrir el archivo." << endl;
        return 1;
    }

    // Ordenar los números para la búsqueda ternaria
    sort(numeros.begin(), numeros.end());

    // Variables para medir tiempos
    double tiempoMax = 0.0;
    double tiempoMin = numeric_limits<double>::max();
    double tiempoTotal = 0.0;

    // Medir el tiempo de búsqueda de cada número
    for (size_t i = 0; i < numeros.size(); ++i) {
        int clave = numeros[i]; // Acceder al elemento actual

        clock_t inicio = clock(); // Inicio del tiempo
        int resultado = busquedaTernaria(numeros, 0, numeros.size() - 1, clave);
        clock_t fin = clock(); // Fin del tiempo

        double tiempo = static_cast<double>(fin - inicio) / CLOCKS_PER_SEC;

        tiempoMax = max(tiempoMax, tiempo);
        tiempoMin = min(tiempoMin, tiempo);
        tiempoTotal += tiempo;

    
    }

    // Mostrar los resultados de los tiempos
    cout << "\nResultados del tiempo de búsqueda:" << endl;
    cout << "Tiempo minimo: " << tiempoMin << " segundos" << endl;
    cout << "Tiempo maximo: " << tiempoMax << " segundos" << endl;
    cout << "Tiempo promedio: " << (tiempoTotal / numeros.size()) << " segundos" << endl;

    return 0;
}