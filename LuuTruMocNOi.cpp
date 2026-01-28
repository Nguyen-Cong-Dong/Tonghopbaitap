#include <iostream>
#include <string>

using namespace std;
struct Node {
    string info;        // INFO: Chứa thông tin của nút 
    struct Node* LP;    // LP: Chứa địa chỉ nút gốc cây con trái 
    struct Node* RP;    // RP: Chứa địa chỉ nút gốc cây con phải 

    // Hàm khởi tạo nút (Constructor) 
    Node(string val) {
        info = val;
        LP = NULL;      // Khởi tạo con trỏ trái rỗng 
        RP = NULL;      // Khởi tạo con trỏ phải rỗng
    }
};

// --- Cài đặt các hàm duyệt ---

// Duyệt tiền tố (NLR)
void NLR(Node* p) {
    if (p != NULL) {
        cout << p->info << " ";   // Thăm gốc (N)
        NLR(p->LP);               // Duyệt con trái (L)
        NLR(p->RP);               // Duyệt con phải (R)
    }
}

// Duyệt trung tố (LNR)
void LNR(Node* p) {
    if (p != NULL) {
        LNR(p->LP);               // L
        cout << p->info << " ";   // N
        LNR(p->RP);               // R
    }
}

// Duyệt hậu tố (LRN)
void LRN(Node* p) {
    if (p != NULL) {
        LRN(p->LP);               // L
        LRN(p->RP);               // R
        cout << p->info << " ";   // N
    }
}

int main() {
    // 1. Khởi tạo cây với nút gốc là A 
    Node* root = new Node("A");

    // 2. Tạo các nút con theo đúng hình vẽ trên bảng 
    root->LP = new Node("A.1");
    root->RP = new Node("A.2");

    // 3. Tạo các nút lá (mức 3)
    root->LP->LP = new Node("A.1.1");
    root->LP->RP = new Node("A.1.2");

    root->RP->LP = new Node("A.2.1");
    root->RP->RP = new Node("A.2.2");

    // Hiển thị kết quả duyệt cây
    cout << "Duyet tien to (NLR): "; NLR(root); cout << endl;
    cout << "Duyet trung to (LNR): "; LNR(root); cout << endl;
    cout << "Duyet hau to (LRN): "; LRN(root); cout << endl;

    return 0;
}