#include <iostream>
#include <string>
#include <chrono> // Thư viện để đo thời gian thực thi

using namespace std;

// 1. Định nghĩa cấu trúc Node
// Mỗi node chứa index (số), tên mục (chuỗi) và 2 con trỏ (cây nhị phân)
struct Node {
    int index;          // Index dạng số
    string title;       // Tên mục dạng chuỗi
    Node* left;         // Con trái (hoặc Mục con đầu tiên)
    Node* right;        // Con phải (hoặc Mục em kế tiếp)

    // Constructor để tạo node nhanh
    Node(int idx, string t) {
        index = idx;
        title = t;
        left = NULL;
        right = NULL;
    }
};

// Hàm tạo node mới
Node* createNode(int index, string title) {
    return new Node(index, title);
}

// 2. Giải thuật kiểm tra hai cây có giống nhau không
bool areBooksCopies(Node* tree1, Node* tree2) {
    // Trường hợp cơ sở: Cả hai đều rỗng -> Giống nhau
    if (tree1 == NULL && tree2 == NULL) {
        return true;
    }

    // Trường hợp: Một cây rỗng, một cây có dữ liệu -> Khác nhau về cấu trúc
    if (tree1 == NULL || tree2 == NULL) {
        return false;
    }

    // Kiểm tra dữ liệu tại node hiện tại
    if (tree1->index != tree2->index || tree1->title != tree2->title) {
        return false;
    }

    // Đệ quy kiểm tra nhánh trái và nhánh phải
    return areBooksCopies(tree1->left, tree2->left) &&
        areBooksCopies(tree1->right, tree2->right);
}

// Hàm giải phóng bộ nhớ cây (Dọn dẹp)
void deleteTree(Node* root) {
    if (root == NULL) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    //Tạo Cây 1 (Cuốn sách gốc)
    // Cấu trúc giả định: Book -> Chuong 1 -> (Muc 1.1, Muc 1.2)
    Node* book1 = createNode(0, "Cuon Sach A");
    Node* b1_c1 = createNode(1, "Chuong 1");
    Node* b1_c2 = createNode(2, "Chuong 2");
    Node* b1_1_1 = createNode(11, "Muc 1.1");

    book1->left = b1_c1;      // Chương 1 là con của Sách
    b1_c1->right = b1_c2;     // Chương 2 là em của Chương 1
    b1_c1->left = b1_1_1;     // Mục 1.1 là con của Chương 1

    //Tạo Cây 2 (Bản copy hoàn hảo của Cây 1)
    Node* book2 = createNode(0, "Cuon Sach A");
    Node* b2_c1 = createNode(1, "Chuong 1");
    Node* b2_c2 = createNode(2, "Chuong 2");
    Node* b2_1_1 = createNode(11, "Muc 1.1");

    book2->left = b2_c1;
    b2_c1->right = b2_c2;
    b2_c1->left = b2_1_1;

    //Tạo Cây 3 (Khác Cây 1 một chút để test)
    Node* book3 = createNode(0, "Cuon Sach A"); // Gốc giống
    book3->left = createNode(1, "Chuong 1");    // Con giống
    // Nhưng thiếu các phần còn lại...

    // 3. Thực hiện kiểm tra và đo thời gian
    cout << "--- BAT DAU KIEM TRA ---" << endl;

    // Đo thời gian kiểm tra Book 1 và Book 2
    auto start = chrono::high_resolution_clock::now();

    bool result1 = areBooksCopies(book1, book2);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;

    if (result1) {
        cout << "Ket qua: Hai cuon sach 1 va 2 LA BAN COPY cua nhau." << endl;
    }
    else {
        cout << "Ket qua: Hai cuon sach 1 va 2 KHONG PHAI la ban copy." << endl;
    }
    cout << "Thoi gian thuc thi: " << duration.count() << " ms" << endl;

    // Kiểm tra Book 1 và Book 3
    bool result2 = areBooksCopies(book1, book3);
    if (result2) {
        cout << "Ket qua: Hai cuon sach 1 va 3 LA BAN COPY cua nhau." << endl;
    }
    else {
        cout << "Ket qua: Hai cuon sach 1 va 3 KHONG PHAI la ban copy." << endl;
    }

    // Dọn dẹp bộ nhớ
    deleteTree(book1);
    deleteTree(book2);
    deleteTree(book3);

    return 0;
}