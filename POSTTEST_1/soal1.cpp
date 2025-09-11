// Soal 1. Array + Pointer
// Nama : Muhammad Rizal Alfath
// Nim : 2409106039

#include <iostream>
using namespace std;

// Fungsi untuk membalik array menggunakan pointer
void balikArray(int *arr, int n) {
    int *awal = arr;
    int *akhir = arr + n - 1;
    while (awal < akhir) {
        int temp = *awal;
        *awal = *akhir;
        *akhir = temp;
        awal++;
        akhir--;
    }
}

int main() {
    const int N = 7;
    int data[N];

    // Isi array
    for (int i = 0; i < N; i++) {
        if (i % 2 == 0) {
            data[i] = 0;
        } else {
            data[i] = 3 * ((i + 1) / 2); // 3,6,9,...
        }
    }

    // Tampilkan array sebelum dibalik
    cout << "Array sebelum dibalik: ";
    for (int i = 0; i < N; i++) {
        cout << data[i] << " ";
    }
    cout << endl;

    // Balik array
    balikArray(data, N);

    // Tampilkan array setelah dibalik
    cout << "Array setelah dibalik: ";
    for (int i = 0; i < N; i++) {
        cout << data[i] << " ";
    }
    cout << endl;

    return 0;
}
