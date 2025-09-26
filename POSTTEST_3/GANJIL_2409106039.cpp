//Posttest-3
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
    Item* prev; // ditambahkan untuk double linked list
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
void tampilkanInventory(Item* kepala, const Identitas& identitas);
void menuInventory(Item* head);
void clearScreen();
int getDuaDigitTerakhir(string nim);
int getDigitTerakhir(string nim);
void printMenuHeader(const Identitas& identitas);
bool isValidNIM(const string& nim);
void tampilkanInventoryBelakang(Item* kepala); 
void tampilkanDetail(Item* kepala, bool tampilDepan, const Identitas& identitas); 
int main() {
    // Input identitas di awal program
    Identitas identitas = inputIdentitas();
    
    // informasi dari NIM
    int duaDigitTerakhir = 39;
    int digitTerakhir = 9;
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
    newItem->next = nullptr;
    newItem->prev = nullptr;
    
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
    
    if (head == nullptr) {
        head = newItem;
    } else {
        Item* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newItem;
        newItem->prev = temp;
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
    
    cout << "Posisi penyisipan: " << posisiSisip << " (berdasarkan NIM (9 + 1))" << endl;
    
    Item* newItem = new Item;
    newItem->next = nullptr;
    newItem->prev = nullptr;
    
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
    
    // Jika menyisipkan di posisi pertama
    if (posisiSisip <= 1) {
        newItem->next = head;
        newItem->prev = nullptr;
        head->prev = newItem;
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
    newItem->prev = temp;
    if (temp->next != nullptr) {
        temp->next->prev = newItem;
    }
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
    
    // Cari last node
    Item* last = head;
    while (last->next != nullptr) {
        last = last->next;
    }
    
    if (last->prev == nullptr) {
        // Hanya ada satu item
        delete last;
        head = nullptr;
        cout << "Item terakhir berhasil dihapus. Inventory sekarang kosong." << endl;
        return;
    }
    
    // Lebih dari satu item
    last->prev->next = nullptr;
    delete last;
    
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
            if (head != nullptr) head->prev = nullptr;
        } else {
            prev->next = temp->next;
            if (temp->next != nullptr) temp->next->prev = prev;
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

void tampilkanInventory(Item* kepala, const Identitas& identitas) {
    clearScreen();
    printMenuHeader(identitas);
    
    cout << endl << "=== INVENTORY ANDA ===" << endl;
    
    if (kepala == nullptr) {
        cout << "Inventory kosong." << endl;
        cout << "\nTekan Enter untuk kembali ke menu...";
        cin.get();
        return;
    }
    
    // Tampilkan inventory awal (dari depan)
    bool tampilDepan = true;
    menuInventory(kepala);

    // Submenu
    int pilihanSubmenu = 0;
    do {
        cout << "\n=== SubMenu ==="<< endl;
        if (tampilDepan) {
            cout << "1. Tampilkan Item dari belakang" << endl;
        } else {
            cout << "1. Tampilkan Item dari depan" << endl;
        }
        cout << "2. Tampilkan detail item" << endl;
        cout << "3. Keluar" << endl;
        cout << "Pilihan: ";
        
        // error handling: baca input dan validasi (1..3)
        while (true) {
            if (!(cin >> pilihanSubmenu)) {
                // input bukan angka -> bersihkan state & buffer, lalu redraw
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                
                clearScreen();
                printMenuHeader(identitas);
                if (tampilDepan) {
                    cout << endl << "=== INVENTORY ANDA (DARI DEPAN) ===" << endl;
                    menuInventory(kepala);
                } else {
                    cout << endl << "=== INVENTORY ANDA (DARI BELAKANG) ===" << endl;
                    tampilkanInventoryBelakang(kepala);
                }
                
                cout << endl;
                if (tampilDepan) cout << "1. Tampilkan Item dari belakang" << endl;
                else             cout << "1. Tampilkan Item dari depan" << endl;
                cout << "2. Tampilkan detail item" << endl;
                cout << "3. Keluar" << endl;
                cout << "Input tidak valid. Silakan masukkan angka (1-3): ";
                continue;
            }
            
            if (pilihanSubmenu < 1 || pilihanSubmenu > 3) {
                // angka di luar opsi -> redraw dan minta ulang
                clearScreen();
                printMenuHeader(identitas);
                if (tampilDepan) {
                    cout << endl << "=== INVENTORY ANDA (DARI DEPAN) ===" << endl;
                    menuInventory(kepala);
                } else {
                    cout << endl << "=== INVENTORY ANDA (DARI BELAKANG) ===" << endl;
                    tampilkanInventoryBelakang(kepala);
                }
                
                cout << endl;
                if (tampilDepan) cout << "1. Tampilkan Item dari belakang" << endl;
                else             cout << "1. Tampilkan Item dari depan" << endl;
                cout << "2. Tampilkan detail item" << endl;
                cout << "3. Keluar" << endl;
                cout << "Pilihan tidak valid. Masukkan angka antara 1 dan 3: ";
                continue;
            }
            // input valid
            break;
        }
        // Buang sisa newline setelah pembacaan angka agar getline tidak terlewati
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        if (pilihanSubmenu == 1) {
            clearScreen();
            printMenuHeader(identitas);
            if (tampilDepan) {
                cout << endl << "=== INVENTORY ANDA (DARI BELAKANG) ===" << endl;
                tampilkanInventoryBelakang(kepala);
            } else {
                cout << endl << "=== INVENTORY ANDA (DARI DEPAN) ===" << endl;
                menuInventory(kepala);
            }
            cout << "\nTekan Enter untuk kembali ke submenu...";
            { string _tmp; getline(cin, _tmp); }
            // toggle view setelah menampilkan
            tampilDepan = !tampilDepan;
        } else if (pilihanSubmenu == 2) {
            // Tampilkan inventory sesuai view lalu minta input ID dan tampilkan detail
            clearScreen();
            printMenuHeader(identitas);
            if (tampilDepan) {
                cout << endl << "=== INVENTORY ANDA (DARI DEPAN) ===" << endl;
                menuInventory(kepala);
            } else {
                cout << endl << "=== INVENTORY ANDA (DARI BELAKANG) ===" << endl;
                tampilkanInventoryBelakang(kepala);
            }
            // Minta input ID dan tampilkan detail satu item
            tampilkanDetail(kepala, tampilDepan, identitas);
            cout << "\nTekan Enter untuk kembali ke submenu...";
            { string _tmp; getline(cin, _tmp); }
            // redraw submenu (tanpa rekursi) agar tidak double ketika user keluar
            clearScreen();
            printMenuHeader(identitas);
            if (tampilDepan) {
                cout << endl << "=== INVENTORY ANDA (DARI DEPAN) ===" << endl;
                menuInventory(kepala);
            } else {
                cout << endl << "=== INVENTORY ANDA (DARI BELAKANG) ===" << endl;
                tampilkanInventoryBelakang(kepala);
            }
            // lanjutkan loop submenu
            continue;
            
        } else if (pilihanSubmenu == 3) {
            // Keluar dari submenu -> kembali ke menu utama
            return;
        } else {
            continue;
        }
    } while (pilihanSubmenu != 3);
}

// fungsi baru: tampilkan inventory dari belakang (descending)
void tampilkanInventoryBelakang(Item* kepala) {
    cout << "+----+----------------------+--------+------------------+" << endl;
    cout << "| No | Nama Item            | Jumlah | Tipe             |" << endl;
    cout << "+----+----------------------+--------+------------------+" << endl;
    
    if (kepala == nullptr) {
        cout << "+----+----------------------+--------+------------------+" << endl;
        return;
    }
    
    // cari node terakhir
    Item* penunjuk = kepala;
    while (penunjuk->next != nullptr) penunjuk = penunjuk->next;
    
    // hitung total item untuk nomor urut descending
    int totalItem = 0;
    Item* penunjuk2 = kepala;
    while (penunjuk2 != nullptr) { totalItem++; penunjuk2 = penunjuk2->next; }
    int nomorUrut = totalItem;
    
    // tampilkan dari belakang
    while (penunjuk != nullptr) {
        cout << "| " << setw(2) << nomorUrut << " | ";
        cout << setw(20) << left << penunjuk->namaItem.substr(0, 20) << " | ";
        cout << setw(6) << penunjuk->jumlah << " | ";
        cout << setw(16) << left << penunjuk->tipe.substr(0, 16) << " |" << endl;
        
        penunjuk = penunjuk->prev;
        nomorUrut--;
    }
    
    cout << "+----+----------------------+--------+------------------+" << endl;
}

// fungsi baru: menampilkan detail 1 item berdasarkan ID (No di tabel)
void tampilkanDetail(Item* kepala, bool tampilDepan, const Identitas& identitas) {
    // Hitung total node
    int totalItem = 0;
    Item* penunjuk = kepala;
    while (penunjuk != nullptr) { totalItem++; penunjuk = penunjuk->next; }

    if (totalItem == 0) {
        cout << "Inventory kosong." << endl;
        return;
    }

    int idItem = 0;
    cout << "\nMasukkan ID item yang ingin ditampilkan: ";
    while (true) {
        if (!(cin >> idItem)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input tidak valid. Masukkan angka ID: ";
            continue;
        }
        cin.ignore(); // clear newline
        if (idItem < 1 || idItem > totalItem) {
            cout << "ID di luar jangkauan. Masukkan ID antara 1 dan " << totalItem << ": ";
            continue;
        }
        break;
    }

    // Temukan node ke-id (posisi forward = id)
    Item* itemTerpilih = kepala;
    for (int i = 1; i < idItem; ++i) {
        itemTerpilih = itemTerpilih->next;
    }

    // Bersihkan layar sehingga hanya tabel ID yang dipilih yang tampil
    clearScreen();

    printMenuHeader(identitas);

    cout << "\n=== Detail Item ===" << endl;
    // Tampilkan hanya baris yang dipilih dengan format tabel yang sama
    cout << "+----+----------------------+--------+------------------+" << endl;
    cout << "| No | Nama Item            | Jumlah | Tipe             |" << endl;
    cout << "+----+----------------------+--------+------------------+" << endl;

    cout << "| " << setw(2) << idItem << " | ";
    cout << setw(20) << left << itemTerpilih->namaItem.substr(0, 20) << " | ";
    cout << setw(6) << itemTerpilih->jumlah << " | ";
    cout << setw(16) << left << itemTerpilih->tipe.substr(0, 16) << " |" << endl;

    cout << "+----+----------------------+--------+------------------+" << endl;
}