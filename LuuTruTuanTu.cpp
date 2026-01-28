#include <iostream>
#include <string>

using namespace std;


#define MAXLENGTH 100         
#define NIL -1                  
const string EMPTY = "FREE";    

typedef string DataType;        
typedef int Node;              

typedef struct {
    DataType Data[MAXLENGTH];   
    int MaxNode;
} Tree;

// --- Các hàm cơ bản ---

int EmptyTree(Tree T) {
    return T.MaxNode == 0;
}

Node Root(Tree T) {
    if (!EmptyTree(T)) return 0; 
    else return NIL;             
}

int Left_Child(Node p, Tree T) {
    return 2 * (p + 1) - 1;      // Công thức tính con trái
}

int Right_Child(Node p, Tree T) {
    return 2 * (p + 1);          // Công thức tính con phải 
}

// --- Các hàm duyệt ---

// Duyệt tiền tố (NLR)
void NLR(Node p, Tree T) {
    // Kiểm tra p trong phạm vi mảng và ô đó có dữ liệu không
    if (p >= 0 && p < MAXLENGTH && T.Data[p] != EMPTY) {
        cout << T.Data[p] << " ";           // Thăm gốc (N)
        NLR(Left_Child(p, T), T);           // Duyệt con trái (L)
        NLR(Right_Child(p, T), T);          // Duyệt con phải (R)
    }
}

// Duyệt trung tố (LNR)
void LNR(Node p, Tree T) {
    if (p >= 0 && p < MAXLENGTH && T.Data[p] != EMPTY) {
        LNR(Left_Child(p, T), T);           // L 
        cout << T.Data[p] << " ";           // N 
        LNR(Right_Child(p, T), T);          // R 
    }
}

// Duyệt hậu tố (LRN)
void LRN(Node p, Tree T) {
    if (p >= 0 && p < MAXLENGTH && T.Data[p] != EMPTY) {
        LRN(Left_Child(p, T), T);           // L
        LRN(Right_Child(p, T), T);          // R 
        cout << T.Data[p] << " ";           // N
    }
}

int main() {
    Tree T;

    T.MaxNode = 7;

    // Khởi tạo mảng trống ban đầu
    for (int i = 0; i < MAXLENGTH; i++) T.Data[i] = EMPTY;

    T.Data[0] = "A";            // Gốc
    T.Data[1] = "A.1";          // Con trái của A
    T.Data[2] = "A.2";          // Con phải của A
    T.Data[3] = "A.1.1";        // Con trái của A.1
    T.Data[4] = "A.1.2";        // Con phải của A.1
    T.Data[5] = "A.2.1";        // Con trái của A.2
    T.Data[6] = "A.2.2";        // Con phải của A.2

    cout << "Duyet tien to (NLR): "; NLR(Root(T), T); cout << endl;
    cout << "Duyet trung to (LNR): "; LNR(Root(T), T); cout << endl;
    cout << "Duyet hau to (LRN): "; LRN(Root(T), T); cout << endl;

    return 0;
}
