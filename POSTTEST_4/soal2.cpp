#include <iostream>
#include <string>
using namespace std;

struct Node {
    char data;
    Node* next;
};

//Menggunakan fungsi push dan pop pada soal1, fungsi nya kurang lebih sama
void push(Node*& top, char data) {
    Node* newNode = new Node{data, top};
    top = newNode;
}

char pop(Node*& top) {
    if (top == nullptr) return '\0'; 
    Node* temp = top;
    char poppedValue = temp->data;
    top = top->next;
    delete temp;
    return poppedValue;
}

bool areBracketsBalanced(string expr) {
    Node* stackTop = nullptr;

    //Looping setiap karakter dalam expr
    for (int i = 0; i < expr.length(); i++) {
        char ch = expr[i];

        // Jika kurung buka, push ke stack
        if (ch == '(' || ch == '{' || ch == '[') {
            push(stackTop, ch);
        }
        // Jika kurung tutup
        else if (ch == ')' || ch == '}' || ch == ']') {
            //Mengecek Apakah stack kosong
            if (stackTop == nullptr) {
                return false; // Tidak ada pasangan kurung buka
            }
            //Pop stack
            char topChar = pop(stackTop);

            // Cek apakah cocok pasangannya
            if ((ch == ')' && topChar != '(') ||
                (ch == '}' && topChar != '{') ||
                (ch == ']' && topChar != '[')) {
                return false;
            }
        }
    }

    //Setelah loop selesai, jika stack kosong, return true, jika tidak return false.
    // Setelah semua karakter dicek, stack harus kosong
    return stackTop == nullptr;
}

int main() {
    string expr1 = "{[()]}";
    cout << expr1 << " -> " 
         << (areBracketsBalanced(expr1) ? "Seimbang" : "Tidak Seimbang") 
         << endl;

    string expr2 = "{[(])}";
    cout << expr2 << " -> " 
         << (areBracketsBalanced(expr2) ? "Seimbang" : "Tidak Seimbang") 
         << endl;

    return 0;
}
