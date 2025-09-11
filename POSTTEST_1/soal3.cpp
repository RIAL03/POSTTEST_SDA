// Soal 3. Struct + Array
// Nama : Muhammad Rizal Alfath
// Nim : 2409106039

#include <iostream>
#include <string>
using namespace std;

//struct Mahasiswa
struct Mahasiswa {
    string nama;
    string nim;
    double ipk;
};

int main() {
    const int JUMLAH = 5;
    Mahasiswa mhs[JUMLAH];

    // Input data 5 mahasiswa
    cout << "Masukkan data " << JUMLAH << " mahasiswa:\n";
    for (int i = 0; i < JUMLAH; i++) {
        cout << "\nMahasiswa ke-" << (i + 1) << ":\n";
        cout << "Nama : ";
        getline(cin >> ws, mhs[i].nama);
        cout << "NIM  : ";
        cin >> mhs[i].nim;
        cout << "IPK  : ";
        cin >> mhs[i].ipk;
    }

    // Cari mahasiswa dengan IPK tertinggi
    int indeksTertinggi = 0;
    for (int i = 1; i < JUMLAH; i++) {
        if (mhs[i].ipk > mhs[indeksTertinggi].ipk) {
            indeksTertinggi = i;
        }
    }

    // Tampilkan mahasiswa dengan IPK tertinggi
    cout << "\nMahasiswa dengan IPK tertinggi:\n";
    cout << "Nama : " << mhs[indeksTertinggi].nama << endl;
    cout << "NIM  : " << mhs[indeksTertinggi].nim << endl;
    cout << "IPK  : " << mhs[indeksTertinggi].ipk << endl;

    return 0;
}
