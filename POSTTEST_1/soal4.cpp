// Soal 4. Pointer pada Fungsi
// Nama : Muhammad Rizal Alfath
// Nim : 2409106039

#include <iostream>
using namespace std;

// Fungsi untuk menukar dua variabel menggunakan double pointer
void tukarNilai(int **a, int **b) {
    int sementara = **a;
    **a = **b;
    **b = sementara;
}

int main() {
    int x, y;

    // Input dua nilai
    cout << "Masukkan nilai pertama: ";
    cin >> x;
    cout << "Masukkan nilai kedua  : ";
    cin >> y;

    // Pointer ke variabel x dan y
    int *ptrX = &x;
    int *ptrY = &y;

    // Tampilkan sebelum pertukaran
    cout << "\nSebelum pertukaran:\n";
    cout << "nilai pertama = " << x << ", nilai kedua = " << y << endl;

    // Panggil fungsi dengan double pointer
    tukarNilai(&ptrX, &ptrY);

    // Tampilkan sesudah pertukaran
    cout << "\nSesudah pertukaran:\n";
    cout << "nilai pertama = " << x << ", nilai kedua = " << y << endl;

    return 0;
}
