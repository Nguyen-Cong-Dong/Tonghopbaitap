#include <iostream>
#include <cmath>
using namespace std;

// Dinh nghia kich thuoc toi da
#define KICH_THUOC_MAX 100
#define RONG -1

// Dinh nghia cau truc cay su dung mang
struct MangCay {
    int GiaTri[KICH_THUOC_MAX]; // Mang luu gia tri nut
    int SoLuongNut;             // Tong so nut hien co
};

// Ham khoi tao cay rong
void KhoiTaoCay(MangCay& mc) {
    mc.SoLuongNut = 0;
    for (int i = 0; i < KICH_THUOC_MAX; i++) {
        mc.GiaTri[i] = RONG;
    }
}


int LayChiSoTrai(int i) {
    return 2 * i;
}

int LayChiSoPhai(int i) {
    return 2 * i + 1;
}

//PHAN 1: DUYET CAY

// 1. Duyet truoc (Pre-order: Nut -> Trai -> Phai)
void DuyetTienTo(int viTri, MangCay mc) {
    if (viTri <= mc.SoLuongNut && mc.GiaTri[viTri] != RONG) {
        cout << mc.GiaTri[viTri] << " ";           // Tham nut
        DuyetTienTo(LayChiSoTrai(viTri), mc);      // Duyet trai
        DuyetTienTo(LayChiSoPhai(viTri), mc);      // Duyet phai
    }
}

// 2. Duyet giua (In-order: Trai -> Nut -> Phai)
void DuyetTrungTo(int viTri, MangCay mc) {
    if (viTri <= mc.SoLuongNut && mc.GiaTri[viTri] != RONG) {
        DuyetTrungTo(LayChiSoTrai(viTri), mc);     // Duyet trai
        cout << mc.GiaTri[viTri] << " ";           // Tham nut
        DuyetTrungTo(LayChiSoPhai(viTri), mc);     // Duyet phai
    }
}

// 3. Duyet sau (Post-order: Trai -> Phai -> Nut)
void DuyetHauTo(int viTri, MangCay mc) {
    if (viTri <= mc.SoLuongNut && mc.GiaTri[viTri] != RONG) {
        DuyetHauTo(LayChiSoTrai(viTri), mc);       // Duyet trai
        DuyetHauTo(LayChiSoPhai(viTri), mc);       // Duyet phai
        cout << mc.GiaTri[viTri] << " ";           // Tham nut
    }
}

//PHAN 2: VUN DONG


void VunDongTaiNut(MangCay& mc, int i, int n) {
    int khoa = mc.GiaTri[i];
    int j = 2 * i; // j la con trai cua i

    while (j <= n) {
        // Neu co con phai va con phai lon hon con trai thi xet con phai
        if (j < n && mc.GiaTri[j] < mc.GiaTri[j + 1]) {
            j = j + 1;
        }

        // So sanh khoa (nut cha) voi nut con lon nhat
        if (khoa > mc.GiaTri[j]) {
            // Neu cha da lon hon con thi dung, vi tri dung
            mc.GiaTri[i] = khoa; 
            return;
        }
        else {
            // Neu con lon hon cha, day con len vi tri cha
            mc.GiaTri[i] = mc.GiaTri[j];
            // Tiep tuc xet xuong phia duoi
            i = j;
            j = 2 * i;
        }
        mc.GiaTri[i] = khoa; // Dat khoa vao vi tri cuoi cung tim duoc
    }
}

void TaoDong(MangCay& mc) {
    int n = mc.SoLuongNut;
    for (int i = n / 2; i >= 1; i--) {
        VunDongTaiNut(mc, i, n);
    }
}

int main() {
    MangCay cayNhiPhan;
    KhoiTaoCay(cayNhiPhan);

 
    int duLieuMau[] = { 0, 4, 1, 3, 2, 16, 9, 10, 14, 8, 7 };
    int soLuong = 10;

    cayNhiPhan.SoLuongNut = soLuong;
    for (int i = 1; i <= soLuong; i++) {
        cayNhiPhan.GiaTri[i] = duLieuMau[i];
    }

    //1. IN GIA TRI DUYET
    cout << "1. CAC KIEU DUYET CAY: " << endl;

    cout << "Duyet truoc (Pre-order): ";
    DuyetTienTo(1, cayNhiPhan);
    cout << endl;

    cout << "Duyet giua (In-order):   ";
    DuyetTrungTo(1, cayNhiPhan);
    cout << endl;

    cout << "Duyet sau (Post-order):  ";
    DuyetHauTo(1, cayNhiPhan);
    cout << endl;

    // 2. VUN DONG VA IN KET QUA
    cout << "\n2. VUN DONG: " << endl;
    TaoDong(cayNhiPhan);

    cout << "Gia tri cay sau khi vun dong (Duyet truoc): ";
    DuyetTienTo(1, cayNhiPhan);
    cout << endl;

    // In mang de kiem tra thu tu luu tru thuc te
    cout << "Mang thuc te sau khi vun dong: ";
    for (int i = 1; i <= cayNhiPhan.SoLuongNut; i++) {
        cout << cayNhiPhan.GiaTri[i] << " ";
    }
    cout << endl;

    return 0;
}