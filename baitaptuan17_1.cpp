#include <iostream>
#include <string>
#include <algorithm> // Dùng cho hàm max
using namespace std;

// Định nghĩa cấu trúc Node
struct Node {
    string title;       // Tên mục (Chapter, Section...)
    int pageCount;      // Số trang của mục này
    Node* left;         // Trỏ đến mục con đầu tiên (Sub-section)
    Node* right;        // Trỏ đến mục cùng cấp tiếp theo (Next Chapter/Section)

    // Constructor khởi tạo node
    Node(string t, int p) {
        title = t;
        pageCount = p;
        left = NULL;
        right = NULL;
    }
};

typedef Node* Tree; // Định nghĩa kiểu Tree là con trỏ Node
// Hàm đệ quy tính tổng số trang của một node và toàn bộ con cháu của nó
int getTotalPages(Node* root) {
    if (root == NULL) return 0;

    int total = root->pageCount; // Số trang của chính nó

    // Duyệt qua tất cả các con của root (nằm bên nhánh trái và chuỗi phải của nhánh trái)
    //Trong cây nhị phân tương đương, con của root nằm ở root->left. 
    // Các anh em của con nằm ở root->left->right...
    Node* child = root->left;
    while (child != NULL) {
        total += getTotalPages(child);
        child = child->right;
    }
    return total;
}
int countChapters(Tree T) {
    if (T == NULL || T->left == NULL) return 0;

    int count = 0;
    Node* p = T->left; // Truy cập vào con cả (Chương 1)

    while (p != NULL) {
        count++;
        p = p->right; // Chuyển sang em kế tiếp (Chương 2, 3...)
    }
    return count;
}
void findLongestChapter(Tree T) {
    if (T == NULL || T->left == NULL) {
        cout << "Sach rong hoac khong co chuong nao." << endl;
        return;
    }

    Node* currentChapter = T->left; // Bắt đầu từ chương 1
    Node* maxChapter = currentChapter;
    int maxPages = 0;

    while (currentChapter != NULL) {
        int currentTotal = getTotalPages(currentChapter);
        if (currentTotal > maxPages) {
            maxPages = currentTotal;
            maxChapter = currentChapter;
        }
        currentChapter = currentChapter->right; // Xét chương tiếp theo
    }

    cout << "Chuong dai nhat la: " << maxChapter->title
        << " voi tong so trang: " << maxPages << endl;
}
// Hàm tìm và xóa node đệ quy
// parent: node cha (trong ngữ nghĩa cây mục lục)
// current: node đang xét
// prevSibling: node anh em liền trước (để nối link khi xóa)
bool deleteItem(Node* parent, Node* current, Node* prevSibling, string targetTitle) {
    if (current == NULL) return false;

    if (current->title == targetTitle) {
        // Trường hợp 1: Node cần xóa là con đầu tiên của Parent (nằm bên Left)
        if (prevSibling == NULL) {
            parent->left = current->right; // Parent trỏ sang em của current
        }
        // Trường hợp 2: Node cần xóa là em của một node khác (nằm bên Right)
        else {
            prevSibling->right = current->right; // Anh nối thẳng sang em của current
        }

        // Giải phóng bộ nhớ
        delete current;
        cout << "Da xoa muc: " << targetTitle << endl;
        return true;
    }

    // Đệ quy tìm trong nhánh con (Left) - Lúc này current trở thành Parent của đám con
    if (deleteItem(current, current->left, NULL, targetTitle)) return true;

    // Đệ quy tìm trong nhánh anh em (Right) - Lúc này Parent vẫn là Parent cũ, current là prevSibling
    if (deleteItem(parent, current->right, current, targetTitle)) return true;

    return false;
}

void findAndDelete(Tree T, string title) {
    if (T == NULL) return;
    // Gọi hàm xóa bắt đầu từ con cả của Root
    if (!deleteItem(T, T->left, NULL, title)) {
        cout << "Khong tim thay muc: " << title << endl;
    }
}
// Hàm duyệt in mục lục con
void printTOC(Node* node, int level) {
    if (node == NULL) return;

    // In thụt đầu dòng theo cấp độ
    for (int i = 0; i < level; i++) cout << "\t";
    cout << "- " << node->title << " (" << node->pageCount << " trang)" << endl;

    // Duyệt con cả (xuống cấp độ sâu hơn)
    printTOC(node->left, level + 1);

    // Duyệt em kế tiếp (cùng cấp độ)
    printTOC(node->right, level);
}

void findAndPrintChapter(Tree T, string chapterTitle) {
    Node* p = T->left; // Duyệt danh sách các chương
    while (p != NULL) {
        if (p->title == chapterTitle) {
            cout << "Muc luc cua " << chapterTitle << ":" << endl;
            // In bản thân chương đó
            // cout << p->title << " (" << p->pageCount << " pp)" << endl; 
            // In các mục con (bắt đầu từ Left)
            printTOC(p->left, 1);
            return;
        }
        p = p->right;
    }
    cout << "Khong tim thay chuong: " << chapterTitle << endl;
}
int main() {
    // 1. Tạo cây sách (Mô phỏng nhập liệu)
    Node* book = new Node("Giai Thuat & Lap Trinh", 0);

    // Thêm Chương 1
    Node* c1 = new Node("Chuong 1: Tong quan", 5);
    book->left = c1; // C1 là con cả của Book

    // Thêm Mục 1.1 và 1.2 cho Chương 1
    Node* s1_1 = new Node("Muc 1.1: Khai niem", 3);
    Node* s1_2 = new Node("Muc 1.2: Lich su", 4);
    c1->left = s1_1;    // 1.1 là con cả của C1
    s1_1->right = s1_2; // 1.2 là em của 1.1

    // Thêm Chương 2 (Em của Chương 1)
    Node* c2 = new Node("Chuong 2: Mang", 2);
    c1->right = c2;

    // Thêm Mục 2.1, 2.2, 2.3 cho Chương 2
    Node* s2_1 = new Node("Muc 2.1: Mang 1 chieu", 6);
    Node* s2_2 = new Node("Muc 2.2: Mang 2 chieu", 7);
    Node* s2_3 = new Node("Muc 2.3: Con tro", 8);
    c2->left = s2_1;
    s2_1->right = s2_2;
    s2_2->right = s2_3;

    //THỰC HIỆN CÁC YÊU CẦU

    cout << "Yeu cau 1: Xac dinh so chuong" << endl;
    cout << "So chuong cua cuon sach: " << countChapters(book) << endl;

    cout << "\nYeu cau 2: Tim chuong dai nhat" << endl;
    findLongestChapter(book);
    // Giải thích: Chương 1 có 5+3+4=12 trang. Chương 2 có 2+6+7+8=23 trang. -> Chọn Chương 2.

    cout << "\nYeu cau 4: In muc luc Chuong 2" << endl;
    findAndPrintChapter(book, "Chuong 2: Mang");

    cout << "\nYeu cau 3: Xoa mot muc (Xoa Muc 2.2)" << endl;
    findAndDelete(book, "Muc 2.2: Mang 2 chieu");

    cout << "Sau khi xoa, in lai muc luc Chuong 2:" << endl;
    findAndPrintChapter(book, "Chuong 2: Mang");

    // Kiểm tra lại chương dài nhất sau khi xóa
    cout << "\nKiem tra lai chuong dai nhat sau khi xoa:" << endl;
    findLongestChapter(book);

    return 0;
}