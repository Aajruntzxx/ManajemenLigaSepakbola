#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int MAKS_TIM = 20;

struct Tim {
    char nama[50];
    int main = 0;
    int menang = 0;
    int seri = 0;
    int kalah = 0;
    int golMasuk = 0;
    int golKemasukan = 0;
    int poin = 0;
};

Tim daftarTim[MAKS_TIM];
int jumlahTim = 0;

int cariTim(const char nama[]) {
    for (int i = 0; i < jumlahTim; ++i) {
        if (strcmp(nama, daftarTim[i].nama) == 0) {
            return i;
        }
    }
    return -1;
}

void simpanKeFile() {
    ofstream file("tim.txt");
    for (int i = 0; i < jumlahTim; ++i) {
        Tim* t = &daftarTim[i];
        file << t->nama << ";" << t->main << ";" << t->menang << ";" << t->seri << ";"
             << t->kalah << ";" << t->golMasuk << ";" << t->golKemasukan << ";" << t->poin << "\n";
    }
    file.close();
}

void muatDariFile() {
    ifstream file("tim.txt");
    while (!file.eof()) {
        Tim t;
        file.getline(t.nama, 50, ';');
        if (strlen(t.nama) == 0) break;
        file >> t.main;
        file.ignore();
        file >> t.menang;
        file.ignore();
        file >> t.seri;
        file.ignore();
        file >> t.kalah;
        file.ignore();
        file >> t.golMasuk;
        file.ignore();
        file >> t.golKemasukan;
        file.ignore();
        file >> t.poin;
        file.ignore();
        daftarTim[jumlahTim++] = t;
    }
    file.close();
}

void tambahTim() {
    if (jumlahTim >= MAKS_TIM) {
        cout << "Jumlah tim sudah maksimal.\n";
        return;
    }

    cout << "Masukkan nama tim: ";
    cin.ignore();
    cin.getline(daftarTim[jumlahTim].nama, 50);

    if (cariTim(daftarTim[jumlahTim].nama) != -1) {
        cout << "Tim sudah terdaftar.\n";
        return;
    }

    jumlahTim++;
    cout << "Tim berhasil ditambahkan.\n";
    simpanKeFile();
}

void tambahPertandingan() {
    char tim1[50], tim2[50];
    int skor1, skor2;

    cout << "Nama tim 1: ";
    cin.ignore();
    cin.getline(tim1, 50);
    cout << "Nama tim 2: ";
    cin.getline(tim2, 50);
    cout << "Skor " << tim1 << ": ";
    cin >> skor1;
    cout << "Skor " << tim2 << ": ";
    cin >> skor2;

    int i1 = cariTim(tim1);
    int i2 = cariTim(tim2);

    if (i1 == -1 || i2 == -1) {
        cout << "Salah satu tim tidak ditemukan.\n";
        return;
    }

    Tim* t1 = &daftarTim[i1];
    Tim* t2 = &daftarTim[i2];

    t1->main++; t2->main++;
    t1->golMasuk += skor1;
    t1->golKemasukan += skor2;
    t2->golMasuk += skor2;
    t2->golKemasukan += skor1;

    if (skor1 > skor2) {
        t1->menang++; t1->poin += 3;
        t2->kalah++;
    } else if (skor1 < skor2) {
        t2->menang++; t2->poin += 3;
        t1->kalah++;
    } else {
        t1->seri++; t2->seri++;
        t1->poin++; t2->poin++;
    }

    cout << "Hasil pertandingan ditambahkan.\n";
    simpanKeFile();
}

void tampilKlasemen() {
    // Bubble sort berdasarkan poin
    for (int i = 0; i < jumlahTim - 1; ++i) {
        for (int j = 0; j < jumlahTim - i - 1; ++j) {
            if (daftarTim[j].poin < daftarTim[j+1].poin) {
                Tim temp = daftarTim[j];
                daftarTim[j] = daftarTim[j+1];
                daftarTim[j+1] = temp;
            }
        }
    }

    cout << "\n===== Klasemen Liga =====\n";
    cout << "Tim\t\tMain Menang Seri Kalah Gol Poin\n";
    for (int i = 0; i < jumlahTim; ++i) {
        Tim* t = &daftarTim[i];
        cout << t->nama << "\t\t"
             << t->main << "    "
             << t->menang << "     "
             << t->seri << "     "
             << t->kalah << "     "
             << t->golMasuk << "-" << t->golKemasukan << "  "
             << t->poin << "\n";
    }
}

void cariDanTampilkanTim() {
    char namaCari[50];
    cout << "Masukkan nama tim yang dicari: ";
    cin.ignore();
    cin.getline(namaCari, 50);

    int idx = cariTim(namaCari);
    if (idx == -1) {
        cout << "Tim tidak ditemukan.\n";
    } else {
        Tim* t = &daftarTim[idx];
        cout << "\n--- Detail Tim: " << t->nama << " ---\n";
        cout << "Main       : " << t->main << "\n";
        cout << "Menang     : " << t->menang << "\n";
        cout << "Seri       : " << t->seri << "\n";
        cout << "Kalah      : " << t->kalah << "\n";
        cout << "Gol        : " << t->golMasuk << " - " << t->golKemasukan << "\n";
        cout << "Poin       : " << t->poin << "\n";
    }
}

void menu() {
    int pilihan;
    do {
        system("cls"); // Membersihkan layar (hanya di Windows)

        cout << "===== Menu Manajemen Liga =====\n";
        cout << "1. Tambah Tim\n";
        cout << "2. Tambah Pertandingan\n";
        cout << "3. Tampilkan Klasemen\n";
        cout << "4. Cari Tim\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: 
                tambahTim(); 
                system("pause"); 
                break;
            case 2: 
                tambahPertandingan(); 
                system("pause"); 
                break;
            case 3: 
                tampilKlasemen(); 
                system("pause"); 
                break;
            case 4: 
                cariDanTampilkanTim(); 
                system("pause"); 
                break;
            case 0:  
                cout << "Keluar dari program.\n"; 
                break;
            default: 
                cout << "Pilihan tidak valid.\n"; 
                system("pause"); break;
        }
    } while (pilihan != 0);
}

int main() {
    muatDariFile();
    menu();
    return 0;
}
