#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// 1. Khai báo cấu trúc dữ liệu
struct SinhVien {
    string hoTen;
    string mssv;
    int namSinh;
    float gpa;
};

struct Node {
    SinhVien data;
    Node* next;
};

struct List {
    Node* firstNode;
};

// Hàm khởi tạo danh sách
void Init(List* list) {
    list->firstNode = NULL;
}

Node* CreateNode(SinhVien sv) {
    Node* p = new Node;
    p->data = sv;
    p->next = NULL;
    return p;
}

// Hàm thêm vào cuối danh sách (để nhập dữ liệu ban đầu)
void AddTail(List* list, SinhVien sv) {
    Node* p = CreateNode(sv);
    if (list->firstNode == NULL) {
        list->firstNode = p;
    }
    else {
        Node* k = list->firstNode;
        while (k->next != NULL) {
            k = k->next;
        }
        k->next = p;
    }
}

// 2. Thực hiện in danh sách thông tin sinh viên
void PrintList(List* list) {
    Node* node = list->firstNode;
    int i = 0;
    cout << "\n" << left << setw(5) << "STT"
        << setw(20) << "Ho Ten"
        << setw(15) << "MSSV"
        << setw(10) << "Nam Sinh"
        << setw(10) << "GPA" << endl;
    cout << "------------------------------------------------------------\n";

    while (node != NULL) {
        cout << left << setw(5) << ++i
            << setw(20) << node->data.hoTen
            << setw(15) << node->data.mssv
            << setw(10) << node->data.namSinh
            << setw(10) << node->data.gpa << endl;
        node = node->next;
    }
    cout << endl;
}

// 3. Tính chiều dài của danh sách
int List_Length(List* list) {
    Node* node = list->firstNode;
    int i = 0;
    while (node != NULL) {
        i++;
        node = node->next;
    }
    return i;
}

// 4. Tìm số lượng sinh viên có GPA > 3.2
int CountHighGPA(List* list) {
    Node* node = list->firstNode;
    int count = 0;
    while (node != NULL) {
        if (node->data.gpa > 3.2) {
            count++;
        }
        node = node->next;
    }
    return count;
}

// Hàm hoán đổi dữ liệu giữa 2 node
void SwapData(Node* a, Node* b) {
    SinhVien temp = a->data;
    a->data = b->data;
    b->data = temp;
}

// 5a. Sắp xếp danh sách theo thứ tự tăng dần của điểm GPA
void SortByGPA(List* list) {
    for (Node* p = list->firstNode; p != NULL; p = p->next) {
        for (Node* q = p->next; q != NULL; q = q->next) {
            if (p->data.gpa > q->data.gpa) { // Tăng dần
                SwapData(p, q);
            }
        }
    }
}

// 5b. Thêm sinh viên mới (GPA 2.4) và chèn đúng thứ tự
void InsertSorted(List* list, SinhVien sv) {
    Node* newNode = CreateNode(sv);

    // Trường hợp 1: Danh sách rỗng hoặc chèn vào đầu (nếu GPA nhỏ hơn đầu)
    if (list->firstNode == NULL || sv.gpa < list->firstNode->data.gpa) {
        newNode->next = list->firstNode;
        list->firstNode = newNode;
        return;
    }

    // Trường hợp 2: Tìm vị trí thích hợp ở giữa hoặc cuối
    Node* current = list->firstNode;
    // Duyệt đến khi node tiếp theo có GPA lớn hơn hoặc bằng GPA cần chèn, hoặc hết danh sách
    while (current->next != NULL && current->next->data.gpa < sv.gpa) {
        current = current->next;
    }

    // Chèn newNode vào sau current
    newNode->next = current->next;
    current->next = newNode;
}

int main() {
    List myList;
    Init(&myList);

    // --- Tạo dữ liệu giả lập để test ---
    AddTail(&myList, { "Nguyen Van Duc", "20230001", 2005, 3.5 });
    AddTail(&myList, { "Nguyen Cong Dong", "20233318", 2005, 2.1 });
    AddTail(&myList, { "Le Van Khiem", "20220003", 2004, 3.8 });
    AddTail(&myList, { "Pham Van Dung", "20230004", 2005, 3.0 });

    cout << "=== 1. & 2. DANH SACH SINH VIEN BAN DAU ===";
    PrintList(&myList);

    // --- 3. Tính chiều dài ---
    cout << "=== 3. CHIEU DAI DANH SACH ===" << endl;
    cout << "So luong sinh vien: " << List_Length(&myList) << endl;

    // --- 4. Đếm sinh viên GPA > 3.2 ---
    cout << "\n=== 4. SO LUONG SINH VIEN CO GPA > 3.2 ===" << endl;
    cout << "Ket qua: " << CountHighGPA(&myList) << " sinh vien." << endl;

    // --- 5. Sắp xếp và chèn thêm ---
    cout << "\n=== 5a. DANH SACH SAU KHI SAP XEP TANG DAN THEO GPA ===";
    SortByGPA(&myList);
    PrintList(&myList);

    cout << "\n=== 5b. CHEN SINH VIEN MOI (GPA 2.4) VAO DUNG VI TRI ===";
    SinhVien svMoi = { "Pham Van Hua", "20259999", 2007, 2.4 };
    InsertSorted(&myList, svMoi);
    PrintList(&myList);

    return 0;
}