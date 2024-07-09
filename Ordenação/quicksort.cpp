#include <iostream>
#include <vector>

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// Função de partição que coloca o pivô na posição correta
int partition(std::vector<int> &arr, int low, int high) {
    int pivo = arr[high]; // Pivô
    int i = (low - 1); // Índice do menor elemento

    for (int j = low; j <= high - 1; j++) {
        // Se o elemento atual é menor ou igual ao pivô
        if (arr[j] <= pivo) {
            i++; // Incrementa o índice do menor elemento
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(std::vector<int> &arr, int low, int high) {
    if (low < high) {
        // pos é o índice da partição, arr[pos] está no lugar certo
        int pos = partition(arr, low, high);

        // Ordena os elementos separadamente antes e depois da partição
        quickSort(arr, low, pos - 1);
        quickSort(arr, pos + 1, high);
    }
}

// Função para imprimir o array
void printArray(const std::vector<int> &arr) {
    for (int i = 0; i < arr.size(); i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
}

int main() {
    std::vector<int> arr = {10, 7, 8, 9, 1, 5};
    int n = arr.size();
    std::cout << "Array original: ";
    printArray(arr);
    quickSort(arr, 0, n - 1);
    std::cout << "Array ordenado: ";
    printArray(arr);
    return 0;
}
