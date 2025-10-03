#include <iostream>
#include <string>
using namespace std;

struct Node {
    char data;
    Node* next;
};

//Menambahkan elemen baru ke dalam stack
void push(Node*& top, char data) {
    Node* newNode = new Node{data, top};
    top = newNode;
}

//Menghapus data paling atas dalam stack
char pop(Node*& top) {
    if (top == nullptr) return '\0'; // Return null character jika stack kosong
    Node* temp = top;
    char poppedValue = temp->data;
    top = top->next;
    delete temp;
    return poppedValue;
}

string reverseString(string s) {
    Node* stackTop = nullptr;
    string reversed = "";

    //1. Push setiap karakter ke dalam stack
    for (int i = 0; i < s.length(); i++) {
        push(stackTop, s[i]);
    }

    //2. Pop setiap karakter dari stack, lalu masukan ke string reversed
    while (stackTop != nullptr) {
        reversed += pop(stackTop);
    }

    return reversed;
}

int main() {
    string text = "Struktur Data";
    cout << "Teks asli: " << text << endl;
    cout << "Teks terbalik: " << reverseString(text) << endl; 
    // Output: ataD rutkurtS
    return 0;
}
