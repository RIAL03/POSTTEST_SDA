#include <iostream>
#include <string>
using namespace std;

struct Node {
    string document;
    Node* next;
};

void enqueue(Node*& front, Node*& rear, string document) {
    Node* newNode = new Node{document, nullptr};

    // Jika queue kosong
    if (front == nullptr) {
        front = rear = newNode;
    } else {
        rear->next = newNode; // sambungkan yang jauh (rear) ke node baru
        rear = newNode;       // update rear
    }
}

string dequeue(Node*& front, Node*& rear) {
    if (front == nullptr) return ""; // Queue kosong

    // Simpan data dari node depan
    Node* temp = front;
    string doc = temp->document;

    // Geser front ke node berikutnya
    front = front->next;

    // Jika front sudah kosong, rear juga harus null
    if (front == nullptr) {
        rear = nullptr;
    }

    delete temp; // hapus node lama
    return doc;
}

void processAllDocuments(Node*& front, Node*& rear) {
    while (front != nullptr) {
        string doc = dequeue(front, rear);
        cout << "Memproses: " << doc << endl;
    }
}

int main() {
    Node* front = nullptr;
    Node* rear = nullptr;

    enqueue(front, rear, "Document1.pdf");
    enqueue(front, rear, "Report.docx");
    enqueue(front, rear, "Presentation.pptx");

    cout << "Memulai pemrosesan antrian printer:" << endl;
    processAllDocuments(front, rear);

    return 0;
}
