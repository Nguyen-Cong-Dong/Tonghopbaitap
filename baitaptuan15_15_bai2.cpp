#include <iostream>
#include <vector>
#include <cstdlib> // dung cho rand()
#include <ctime>   // dung cho time()
#include <chrono>  // dung de do thoi gian chay

using namespace std;
using namespace std::chrono;

//PHAN 1: DINH NGHIA CAU TRUC CAY (MOC NOI)
struct NutCay {
    int DuLieu;
    NutCay* ConTrai;
    NutCay* ConPhai;

    // Ham khoi tao (Constructor)
    NutCay(int giaTri) {
        DuLieu = giaTri;
        ConTrai = NULL;
        ConPhai = NULL;
    }
};

//PHAN 2: THUAT TOAN KIEM TRA HAI CAY GIONG NHAU
bool KiemTraTuongDong(NutCay* cay1, NutCay* cay2) {
    // Truong hop 1: Ca hai cay deu rong -> Giong nhau
    if (cay1 == NULL && cay2 == NULL) {
        return true;
    }

    // Truong hop 2: Mot cay rong, mot cay co du lieu -> Khac nhau
    if (cay1 == NULL || cay2 == NULL) {
        return false;
    }

    // Truong hop 3: Du lieu tai nut hien tai khac nhau -> Khac nhau
    if (cay1->DuLieu != cay2->DuLieu) {
        return false;
    }

    // Truong hop 4: De quy kiem tra tiep con trai va con phai
    // Ca nhanh trai va nhanh phai phai giong nhau thi moi tra ve true
    return KiemTraTuongDong(cay1->ConTrai, cay2->ConTrai) &&
        KiemTraTuongDong(cay1->ConPhai, cay2->ConPhai);
}

//HAM HO TRO: TAO CAY DE TEST
// Ham them nut vao cay (don gian de tao du lieu test)
NutCay* ThemNutMoi(NutCay* goc, int giaTri) {
    if (goc == NULL) {
        return new NutCay(giaTri);
    }
    // Them ngau nhien vao trai hoac phai de tao cay "bat ky"
    // De tranh cay bi lech han ve 1 ben (gay tran bo nho khi de quy sau),
    // ta se chia deu (mo phong cay can bang mot chut)
    if (giaTri < goc->DuLieu) {
        goc->ConTrai = ThemNutMoi(goc->ConTrai, giaTri);
    }
    else {
        goc->ConPhai = ThemNutMoi(goc->ConPhai, giaTri);
    }
    return goc;
}

// Ham tao cay tu dong voi so luong lon
NutCay* TaoCayLon(int soLuongNut, int hatGiong) {
    NutCay* goc = NULL;
    srand(hatGiong); // Dat seed de 2 cay co the giong hoac khac nhau
    for (int i = 0; i < soLuongNut; i++) {
        // Tao gia tri ngau nhien tu 0 den 1000000
        goc = ThemNutMoi(goc, rand() % 1000000);
    }
    return goc;
}

// Ham xoa cay de giai phong bo nho
void XoaCay(NutCay* goc) {
    if (goc == NULL) return;
    XoaCay(goc->ConTrai);
    XoaCay(goc->ConPhai);
    delete goc;
}

int main() {
    srand(time(NULL));

    int soNut = 150000;

   
    bool muonGiongNhau = rand() % 2;

    int hatGiongA = 12345; // Hat giong co dinh cho cay A
    int hatGiongB;

    if (muonGiongNhau) {
        cout << ">>> CHE DO: Tao 2 cay GIONG HET NHAU <<<" << endl;
        hatGiongB = 12345; // Giong het cay A
    }
    else {
        cout << ">>> CHE DO: Tao 2 cay KHAC NHAU <<<" << endl;
        hatGiongB = 67890; // Hat giong khac -> Cay se khac hoan toan
    }

    cout << "Dang tao 2 cay voi so luong nut: " << soNut << "..." << endl;

    // Tao 2 cay dua tren hat giong da quyet dinh o tren
    NutCay* cayA = TaoCayLon(soNut, hatGiongA);
    NutCay* cayB = TaoCayLon(soNut, hatGiongB);

    cout << "Da tao xong du lieu. Bat dau so sanh..." << endl;

    //DO THOI GIAN & KIEM TRA
    auto thoiDiemBatDau = high_resolution_clock::now();

    bool ketQua = KiemTraTuongDong(cayA, cayB);

    auto thoiDiemKetThuc = high_resolution_clock::now();
    auto thoiGianChay = duration_cast<milliseconds>(thoiDiemKetThuc - thoiDiemBatDau);

    //IN KET QUA
    cout << "------------------------------------------------" << endl;
    if (ketQua) {
        cout << "KET QUA THUAT TOAN: Hai cay GIONG HET NHAU!" << endl;
    }
    else {
        cout << "KET QUA THUAT TOAN: Hai cay KHAC NHAU!" << endl;
    }
    cout << "Thoi gian thuc thi: " << thoiGianChay.count() << " ms" << endl;
    cout << "------------------------------------------------" << endl;

    // Kiem chung lai xem chuong trinh chay co dung voi y dinh ban dau khong
    if (muonGiongNhau == ketQua) {
        cout << "(Test thanh cong: Ket qua dung voi du lieu dau vao)" << endl;
    }
    else {
        cout << "(Canh bao: Co loi logic xay ra!)" << endl;
    }

    // Don dep bo nho
    XoaCay(cayA);
    XoaCay(cayB);

    return 0;
}