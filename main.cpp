#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}


void bubbleSort(std::vector<int> &arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}


void quickSort(std::vector<int> &arr, int left, int right) {
    if (left < right) {
        int pivot = arr[(left + right) / 2];
        int i = left;
        int j = right;
        while (i <= j) {
            while (arr[i] < pivot) i++;
            while (arr[j] > pivot) j--;
            if (i <= j) {
                swap(arr[i], arr[j]);
                i++;
                j--;
            }
        }
        quickSort(arr, left, j);
        quickSort(arr, i, right);
    }
}

void quickSortInit(std::vector<int> &arr) {
    quickSort(arr, 0, arr.size() - 1);
}

void insertionSort(std::vector<int> &arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}


std::vector<int> generateRandomList(int size, int minValue, int maxValue) {
    std::vector<int> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = minValue + rand() % (maxValue - minValue + 1);
    }
    return arr;
}


template <typename Func>
double measureTime(Func sortingFunction, std::vector<int> &arr) {
    clock_t start = clock();
    sortingFunction(arr);
    clock_t end = clock();
    return double(end - start) / CLOCKS_PER_SEC;
}


bool isSorted(const std::vector<int> &arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i - 1] > arr[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    srand(time(nullptr));

    const int size = 1000;
    std::vector<int> randomList = generateRandomList(size, 1, 10000);

    // Kopie listy do testowania różnych algorytmów
    std::vector<int> list1 = randomList;
    std::vector<int> list2 = randomList;
    std::vector<int> list3 = randomList;

    double bubbleSortTime = measureTime(bubbleSort, list1);
    double quicksortTime = measureTime(quickSortInit, list2);
    double insertionSortTime = measureTime(insertionSort, list3);

    std::cout << "Czas sortowania bąbelkowego: " << bubbleSortTime << " sekund\n";
    std::cout << "Czas sortowania quickSortInit: " << quicksortTime << " sekund\n";
    std::cout << "Czas sortowania przez wstawianie: " << insertionSortTime << " sekund\n";

    std::cout << "Sortowanie bąbelkowe poprawne: " << (isSorted(list1) ? "Tak" : "Nie") << '\n';
    std::cout << "Sortowanie quickSortInit poprawne: " << (isSorted(list2) ? "Tak" : "Nie") << '\n';
    std::cout << "Sortowanie przez wstawianie poprawne: " << (isSorted(list3) ? "Tak" : "Nie") << '\n';

    return 0;
}