// Soal 2. Array 2D
// Nama : Muhammad Rizal Alfath
// Nim : 2409106039

#include <iostream>
using namespace std;

int main() {
    const int UKURAN = 3;
    int matriks[UKURAN][UKURAN];

    // Input elemen matriks 3x3
    cout << "Masukkan elemen matriks 3x3 (9 angka):\n";
    for (int i = 0; i < UKURAN; i++) {
        for (int j = 0; j < UKURAN; j++) {
            cout << "Elemen [" << i << "][" << j << "]: ";
            cin >> matriks[i][j];
        }
    }

    // Hitung jumlah diagonal utama dan diagonal sekunder
    int jumlahDiagonalUtama = 0;
    int jumlahDiagonalSekunder = 0;

    for (int i = 0; i < UKURAN; i++) {
        jumlahDiagonalUtama += matriks[i][i]; // diagonal utama (kiri atas ke kanan bawah)
        jumlahDiagonalSekunder += matriks[i][UKURAN - 1 - i]; // diagonal sekunder (kanan atas ke kiri bawah)
    }

    // Cetak matriks
    cout << "\nMatriks 3x3:\n";
    for (int i = 0; i < UKURAN; i++) {
        for (int j = 0; j < UKURAN; j++) {
            cout << matriks[i][j] << " ";
        }
        cout << endl;
    }

    // Cetak hasil penjumlahan diagonal
    cout << "\nJumlah diagonal utama: " << jumlahDiagonalUtama << endl;
    cout << "Jumlah diagonal sekunder: " << jumlahDiagonalSekunder << endl;
    cout << "Total keduanya: " << (jumlahDiagonalUtama + jumlahDiagonalSekunder) << endl;

    return 0;
}
