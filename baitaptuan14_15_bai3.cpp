#include <iostream>
using namespace std;

//DINH NGHIA CAU TRUC NUT
struct Node {
    int value;      // Gia tri cua nut
    Node* left;     // Con tro nut con trai
    Node* right;    // Con tro nut con phai

    // Ham khoi tao
    Node(int v, Node* l, Node* r) {
        value = v;
        left = l;
        right = r;
    }
};

//LOP CAY NHI PHAN TIM KIEM (BST)
class BSTree {
private:
    Node* root; // Nut goc

public:
    // Ham tao: Khoi tao cay rong
    BSTree() {
        root = NULL;
    }

    // Ham huy: Goi ham xoa rong cay de giai phong bo nho
    ~BSTree() {
        makeEmpty();
    }

    // Kiem tra cay co rong hay khong
    bool isEmpty() {
        return (root == NULL);
    }

    // Xoa het cac nut tren cay (Goi ham de quy private)
    void makeEmpty() {
        makeEmpty(root);
    }

    // Chen mot gia tri moi vao cay (Goi ham de quy private)
    void insert(int val1) {
        insert(val1, root);
    }

    // Tim kiem gia tri (Goi ham de quy private)
    Node* search(int val2) {
        return search(val2, root);
    }

    //CAC HAM CAI DAT CHI TIET

    // 1. Xoa rong cay (Duyet hau to: Xoa con truoc -> Xoa cha sau)
    void makeEmpty(Node*& nodeHienTai) {
        if (nodeHienTai != NULL) {
            makeEmpty(nodeHienTai->left);  // De quy xoa ben trai
            makeEmpty(nodeHienTai->right); // De quy xoa ben phai
            delete nodeHienTai;            // Xoa nut hien tai
            nodeHienTai = NULL;            // Gan con tro ve NULL de tranh loi
        }
    }

    // 2. Chen mot nut moi vao cay (Dung tinh chat BST: Nho sang trai, Lon sang phai)
    void insert(int giaTriNap, Node*& nodeHienTai) {
        if (nodeHienTai == NULL) {
            // Neu vi tri hien tai trong, tao nut moi tai day
            nodeHienTai = new Node(giaTriNap, NULL, NULL);
        }
        else if (giaTriNap < nodeHienTai->value) {
            // Neu nho hon, di sang nhanh trai
            insert(giaTriNap, nodeHienTai->left);
        }
        else if (giaTriNap > nodeHienTai->value) {
            // Neu lon hon, di sang nhanh phai
            insert(giaTriNap, nodeHienTai->right);
        }
        // Neu bang nhau (trung lap) thi khong lam gi (hoac tuy chinh sach)
    }

    // 3. Tim kiem nut co gia tri cho truoc
    Node* search(int giaTriCanTim, Node* nodeHienTai) {
        if (nodeHienTai == NULL) {
            return NULL; // Khong tim thay
        }

        if (giaTriCanTim < nodeHienTai->value) {
            return search(giaTriCanTim, nodeHienTai->left); // Tim ben trai
        }
        else if (giaTriCanTim > nodeHienTai->value) {
            return search(giaTriCanTim, nodeHienTai->right); // Tim ben phai
        }
        else {
            return nodeHienTai; // Da tim thay (giaTriCanTim == nodeHienTai->value)
        }
    }

    // Getter cho root (de ham main co the truy cap duoc vi root dang la private)
    Node* getRoot() {
        return root;
    }
};

//CAC HAM DUYET CAY

// 1. Duyet Truoc (Pre-order): Nut -> Trai -> Phai
void PREORDER_travl(Node* t) {
    if (t != NULL) {
        cout << t->value << " ";     // In gia tri
        PREORDER_travl(t->left);     // Duyet trai
        PREORDER_travl(t->right);    // Duyet phai
    }
}

// 2. Duyet Giua (In-order): Trai -> Nut -> Phai
// Voi BST, duyet giua se in ra day so tang dan
void INORDER_travl(Node* t) {
    if (t != NULL) {
        INORDER_travl(t->left);      // Duyet trai
        cout << t->value << " ";     // In gia tri
        INORDER_travl(t->right);     // Duyet phai
    }
}

// 3. Duyet Sau (Post-order): Trai -> Phai -> Nut
void POSTORDER_travl(Node* t) {
    if (t != NULL) {
        POSTORDER_travl(t->left);    // Duyet trai
        POSTORDER_travl(t->right);   // Duyet phai
        cout << t->value << " ";     // In gia tri
    }
}

// CHUONG TRINH CHINH (MAIN)
int main() {
    BSTree bst;

    bst.insert(5);
    bst.insert(6);
    bst.insert(3);
    bst.insert(8);
    bst.insert(7);
    bst.insert(4);
    bst.insert(2);

    // Lay root de duyet cay
    Node* root = bst.getRoot();

    cout << "--- 1. Duyet cay theo thu tu truoc (Pre-order) ---" << endl;
    PREORDER_travl(root);
    cout << endl << endl;

    //YEU CAU BO SUNG: In them duyet Giua va Sau
    cout << "--- 2. Duyet cay theo thu tu giua (In-order / Tang dan) ---" << endl;
    INORDER_travl(root);
    cout << endl << endl;

    cout << "--- 3. Duyet cay theo thu tu sau (Post-order) ---" << endl;
    POSTORDER_travl(root);
    cout << endl << endl;

    // Tim kiem
    Node* n1 = bst.search(4);
    Node* n2 = bst.search(9);

    cout << "--- Ket qua tim kiem ---" << endl;
    if (n1 != NULL)
        cout << "Node co gia tri = 4 la: " << n1->value << endl;
    else
        cout << "Khong tim thay node 4" << endl;

    if (n2 == NULL)
        cout << "Khong tim thay node co gia tri = 9" << endl;
    else
        cout << "Tim thay node 9" << endl;

    // Lam rong cay
    bst.makeEmpty();
    if (bst.isEmpty())
        cout << "\n-> Cay da bi xoa rong thanh cong!" << endl;

    return 0;
}