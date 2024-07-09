#include <iostream>
#include <vector>

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void heapify(std::vector<int> &arr, int n, int i) {
    int largest = i; // Inicializa o maior como raiz
    int left = 2 * i + 1; // Filho esquerdo
    int right = 2 * i + 2; // Filho direito

    // Se o filho esquerdo é maior que a raiz
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // Se o filho direito é maior que o maior até agora
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // Se o maior não é a raiz
    if (largest != i) {
        swap(arr[i], arr[largest]);

        // Recursivamente faz heapify na subárvore afetada
        heapify(arr, n, largest);
    }
}

void heapSort(std::vector<int> &arr) {
    int n = arr.size();

    // Constrói o heap (reorganiza o array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extrai os elementos do heap um a um
    for (int i = n - 1; i >= 0; i--) {
        // Move a raiz atual para o final
        swap(arr[0], arr[i]);

        // Chama max heapify no heap reduzido
        heapify(arr, i, 0);
    }
}

void printArray(const std::vector<int> &arr) {
    for (int i = 0; i < arr.size(); i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
}

int main() {
    std::vector<int> arr = {12, 11, 13, 5, 6, 7};
    int n = arr.size();
    std::cout << "Array original: ";
    printArray(arr);
    heapSort(arr);
    std::cout << "Array ordenado: ";
    printArray(arr);
    return 0;
}
