//Posttest-2
//Nama : Muhammad Rizal Alfath
//Nim : 2409106039

#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;

// Struktur data untuk item inventory
struct Item {
    string namaItem;
    int jumlah;
    string tipe;
    Item* next;
};

// Struktur data untuk identitas pemain
struct Identitas {
    string nama;
    string nim;
};

// Deklarasi fungsi
Identitas inputIdentitas();
void tambahItemBaru(Item*& head, int jumlahAwal, const Identitas& identitas);
void sisipkanItem(Item*& head, int jumlahAwal, int posisiSisip, const Identitas& identitas);
void hapusItemTerakhir(Item*& head, const Identitas& identitas);
void gunakanItem(Item*& head, const Identitas& identitas);
void tampilkanInventory(Item* head, const Identitas& identitas);
void menuInventory(Item* head);
void clearScreen();
int getDuaDigitTerakhir(string nim);
int getDigitTerakhir(string nim);
void printMenuHeader(const Identitas& identitas);
bool isValidNIM(const string& nim);

int main() {
    // Input identitas di awal program
    Identitas identitas = inputIdentitas();
    
    // informasi dari NIM
    int duaDigitTerakhir = getDuaDigitTerakhir(identitas.nim);
    int digitTerakhir = getDigitTerakhir(identitas.nim);
    int posisiSisip = digitTerakhir + 1;
    
    Item* head = nullptr;
    int pilihan;
    
    do {
        clearScreen();
        printMenuHeader(identitas);
        cout << "Pilihan: ";
        
        // Error handling untuk input pilihan menu
        while (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input tidak valid. Silakan masukkan angka: ";
        }
        cin.ignore(); // Membersihkan buffer
        
        switch(pilihan) {
            case 1:
                tambahItemBaru(head, duaDigitTerakhir, identitas);
                break;
            case 2:
                sisipkanItem(head, duaDigitTerakhir, posisiSisip, identitas);
                break;
            case 3:
                hapusItemTerakhir(head, identitas);
                break;
            case 4:
                gunakanItem(head, identitas);
                break;
            case 5:
                tampilkanInventory(head, identitas);
                break;
            case 6:
                cout << "Terima kasih telah menggunakan sistem inventory!" << endl;
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
        
        if (pilihan != 6 && pilihan != 5) {
            cout << "\nTekan Enter untuk melanjutkan...";
            cin.get();
        }
    } while (pilihan != 6);
    
    // Membersihkan memori sebelum keluar
    while (head != nullptr) {
        Item* temp = head;
        head = head->next;
        delete temp;
    }
    
    return 0;
}

void printMenuHeader(const Identitas& identitas) {
    const int WIDTH = 50;
    string headerText = identitas.nama + " - " + identitas.nim;
    
    cout << "+--------------------------------------------------+" << endl;
    cout << "|             GAME INVENTORY MANAGEMENT            |" << endl;
    cout << "|";
    
    // Menghitung posisi untuk header text agar berada di tengah
    int padding = (WIDTH - headerText.length() - 2) / 2;
    for (int i = 0; i < padding; i++) cout << " ";
    cout << headerText;
    for (int i = 0; i < (WIDTH - headerText.length() - 2 - padding); i++) cout << " ";
    cout << "  |" << endl;
    
    cout << "+--------------------------------------------------+" << endl;
    cout << "| 1. Tambah Item Baru                              |" << endl;
    cout << "| 2. Sisipkan Item                                 |" << endl;
    cout << "| 3. Hapus Item Terakhir                           |" << endl;
    cout << "| 4. Gunakan Item                                  |" << endl;
    cout << "| 5. Tampilkan Inventory                           |" << endl;
    cout << "| 6. Keluar                                        |" << endl;
    cout << "+--------------------------------------------------+" << endl;
}

// Fungsi untuk memvalidasi NIM
bool isValidNIM(const string& nim) {
    if (nim.empty()) return false;
    
    // Memastikan semua karakter adalah digit
    for (char c : nim) {
        if (!isdigit(c)) return false;
    }
    
    return true;
}

Identitas inputIdentitas() {
    Identitas identitas;
    clearScreen();
    cout << "=== SELAMAT DATANG DI GAME INVENTORY MANAGEMENT ===" << endl;
    cout << "Silakan masukkan identitas Anda:" << endl;
    
    // Input nama
    cout << "Nama: ";
    getline(cin, identitas.nama);
    
    // Input NIM dengan error handling
    while (true) {
        cout << "NIM: ";
        getline(cin, identitas.nim);
        
        if (isValidNIM(identitas.nim)) {
            break;
        } else {
            cout << "NIM tidak valid. Harus berisi angka saja. Silakan coba lagi." << endl;
        }
    }
    
    return identitas;
}

int getDuaDigitTerakhir(string nim) {
    if (nim.length() < 2) return 0;
    string duaDigit = nim.substr(nim.length() - 2);
    return stoi(duaDigit);
}

int getDigitTerakhir(string nim) {
    if (nim.empty()) return 0;
    char lastChar = nim.back();
    if (isdigit(lastChar)) {
        return lastChar - '0';
    }
    return 0;
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void tambahItemBaru(Item*& head, int jumlahAwal, const Identitas& identitas) {
    clearScreen();
    printMenuHeader(identitas);
    cout << "=== TAMBAH ITEM BARU ===" << endl;
    
    Item* newItem = new Item;
    
    cout << "Nama Item: ";
    getline(cin, newItem->namaItem);
    
    // Validasi input nama item tidak kosong
    while (newItem->namaItem.empty()) {
        cout << "Nama item tidak boleh kosong. Silakan masukkan lagi: ";
        getline(cin, newItem->namaItem);
    }
    
    cout << "Tipe Item (Sword, Potion, dll): ";
    getline(cin, newItem->tipe);
    
    // Validasi input tipe item tidak kosong
    while (newItem->tipe.empty()) {
        cout << "Tipe item tidak boleh kosong. Silakan masukkan lagi: ";
        getline(cin, newItem->tipe);
    }
    
    // Jumlah awal berdasarkan dua digit terakhir NIM
    newItem->jumlah = jumlahAwal;
    cout << "Jumlah item: " << newItem->jumlah << " (otomatis dari NIM)" << endl;
    
    newItem->next = nullptr;
    
    if (head == nullptr) {
        head = newItem;
    } else {
        Item* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newItem;
    }
    
    cout << "\nItem berhasil ditambahkan!" << endl;
}

void sisipkanItem(Item*& head, int jumlahAwal, int posisiSisip, const Identitas& identitas) {
    clearScreen();
    printMenuHeader(identitas);

    cout << endl << "=== SISIPKAN ITEM ===" << endl;
    
    if (head == nullptr) {
        cout << "Inventory kosong. Menambahkan item sebagai item pertama." << endl;
        tambahItemBaru(head, jumlahAwal, identitas);
        return;
    }
    
    cout << "Posisi penyisipan: " << posisiSisip << " (berdasarkan NIM)" << endl;
    
    Item* newItem = new Item;
    
    cout << "Nama Item: ";
    getline(cin, newItem->namaItem);
    
    // Validasi input nama item tidak kosong
    while (newItem->namaItem.empty()) {
        cout << "Nama item tidak boleh kosong. Silakan masukkan lagi: ";
        getline(cin, newItem->namaItem);
    }
    
    cout << "Tipe Item (Sword, Potion, dll): ";
    getline(cin, newItem->tipe);
    
    // Validasi input tipe item tidak kosong
    while (newItem->tipe.empty()) {
        cout << "Tipe item tidak boleh kosong. Silakan masukkan lagi: ";
        getline(cin, newItem->tipe);
    }
    
    // Jumlah awal berdasarkan dua digit terakhir NIM
    newItem->jumlah = jumlahAwal;
    cout << "Jumlah item: " << newItem->jumlah << " (otomatis dari NIM)" << endl;
    
    newItem->next = nullptr;
    
    // Jika menyisipkan di posisi pertama
    if (posisiSisip <= 1) {
        newItem->next = head;
        head = newItem;
        cout << "\nItem berhasil disisipkan di awal inventory!" << endl;
        return;
    }
    
    // Mencari posisi untuk menyisipkan
    Item* temp = head;
    int counter = 1;
    
    while (temp->next != nullptr && counter < posisiSisip - 1) {
        temp = temp->next;
        counter++;
    }
    
    // Menyisipkan item
    newItem->next = temp->next;
    temp->next = newItem;
    
    cout << "\nItem berhasil disisipkan pada posisi " << (counter + 1) << "!" << endl;
}

void hapusItemTerakhir(Item*& head, const Identitas& identitas) {
    clearScreen();
    printMenuHeader(identitas);
    cout << endl << "=== HAPUS ITEM TERAKHIR ===" << endl;
    
    if (head == nullptr) {
        cout << "Inventory kosong. Tidak ada item yang dapat dihapus." << endl;
        return;
    }
    
    if (head->next == nullptr) {
        // Hanya ada satu item
        delete head;
        head = nullptr;
        cout << "Item terakhir berhasil dihapus. Inventory sekarang kosong." << endl;
        return;
    }
    
    Item* temp = head;
    while (temp->next->next != nullptr) {
        temp = temp->next;
    }
    
    delete temp->next;
    temp->next = nullptr;
    
    cout << "Item terakhir berhasil dihapus!" << endl;
}

void gunakanItem(Item*& head, const Identitas& identitas) {
    clearScreen();
    printMenuHeader(identitas);

    cout << endl << "=== INVENTORY ANDA ===" << endl;
    menuInventory(head);

    cout << endl << "=== GUNAKAN ITEM ===" << endl;
    
    if (head == nullptr) {
        cout << "Inventory kosong. Tidak ada item yang dapat digunakan." << endl;
        return;
    }
    
    string namaDicari;
    cout << "Masukkan nama item yang ingin digunakan: ";
    getline(cin, namaDicari);
    
    // Validasi input nama item tidak kosong
    while (namaDicari.empty()) {
        cout << "Nama item tidak boleh kosong. Silakan masukkan lagi: ";
        getline(cin, namaDicari);
    }
    
    Item* temp = head;
    Item* prev = nullptr;
    bool ditemukan = false;
    
    while (temp != nullptr) {
        if (temp->namaItem == namaDicari) {
            ditemukan = true;
            break;
        }
        prev = temp;
        temp = temp->next;
    }
    
    if (!ditemukan) {
        cout << "Item '" << namaDicari << "' tidak ditemukan dalam inventory." << endl;
        return;
    }
    
    // Mengurangi jumlah item
    temp->jumlah--;
    cout << "Item '" << temp->namaItem << "' digunakan. Jumlah sekarang: " << temp->jumlah << endl;
    
    // Jika jumlah menjadi 0, hapus item
    if (temp->jumlah == 0) {
        cout << "Jumlah item '" << temp->namaItem << "' telah habis. Menghapus dari inventory." << endl;
        
        if (prev == nullptr) {
            // Item yang dihapus adalah head
            head = temp->next;
        } else {
            prev->next = temp->next;
        }
        
        delete temp;
    }
}

void menuInventory(Item* head){
    cout << "+----+----------------------+--------+------------------+" << endl;
    cout << "| No | Nama Item            | Jumlah | Tipe             |" << endl;
    cout << "+----+----------------------+--------+------------------+" << endl;
    
    Item* temp = head;
    int counter = 1;
    
    while (temp != nullptr) {
        cout << "| " << setw(2) << counter << " | ";
        cout << setw(20) << left << temp->namaItem.substr(0, 20) << " | ";
        cout << setw(6) << temp->jumlah << " | ";
        cout << setw(16) << left << temp->tipe.substr(0, 16) << " |" << endl;
        
        temp = temp->next;
        counter++;
    }
    
    cout << "+----+----------------------+--------+------------------+" << endl;
}

void tampilkanInventory(Item* head, const Identitas& identitas) {
    clearScreen();
    printMenuHeader(identitas);
    
    cout << endl << "=== INVENTORY ANDA ===" << endl;
    
    if (head == nullptr) {
        cout << "Inventory kosong." << endl;
        cout << "\nTekan Enter untuk kembali ke menu...";
        cin.get();
        return;
    }
    
    menuInventory(head);
    cout << "\nTekan Enter untuk kembali ke menu...";
    cin.get();
}