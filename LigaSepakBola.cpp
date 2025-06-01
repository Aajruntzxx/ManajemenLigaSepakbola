#include <iostream>
#include <cstdio>
#include <cstring>
#include <iomanip> 

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
    FILE* fp = fopen("tim.txt", "w");
    if (fp == NULL) {
        cout << "Gagal membuka file untuk menyimpan.\n";
        return;
    }

    for (int i = 0; i < jumlahTim; i++) {
        fprintf(fp, "%s;%d;%d;%d;%d;%d;%d;%d\n",
            daftarTim[i].nama, daftarTim[i].main, daftarTim[i].menang,
            daftarTim[i].seri, daftarTim[i].kalah, daftarTim[i].golMasuk,
            daftarTim[i].golKemasukan, daftarTim[i].poin);
    }

    fclose(fp);
}

void BacaDariFile() {
    FILE* fp = fopen("tim.txt", "r");
    if (fp == NULL) {
        cout << "Belum ada data file tersimpan.\n";
        return;
    }

    jumlahTim = 0;
    while (!feof(fp) && jumlahTim < MAKS_TIM) {
        char nama[50];
        int main, menang, seri, kalah, golMasuk, golKemasukan, poin;

        int hasil = fscanf(fp, "%49[^;];%d;%d;%d;%d;%d;%d;%d\n",
            nama, &main, &menang, &seri, &kalah, &golMasuk, &golKemasukan, &poin);

        if (hasil == 8) {
            strcpy(daftarTim[jumlahTim].nama, nama);
            daftarTim[jumlahTim].main = main;
            daftarTim[jumlahTim].menang = menang;
            daftarTim[jumlahTim].seri = seri;
            daftarTim[jumlahTim].kalah = kalah;
            daftarTim[jumlahTim].golMasuk = golMasuk;
            daftarTim[jumlahTim].golKemasukan = golKemasukan;
            daftarTim[jumlahTim].poin = poin;
            jumlahTim++;
        } else {
            break;
        }
    }

    fclose(fp);
}

void tambahTim() {
    system("cls");
    if (jumlahTim >= MAKS_TIM) {
        cout << "Jumlah tim sudah maksimal.\n";
        system("pause");
        return;
    }

    cout << "===== TAMBAH DAFTAR TIM =====\n";
    cout << "Masukkan nama tim: ";
    cin.ignore();
    cin.getline(daftarTim[jumlahTim].nama, 50);

    if (cariTim(daftarTim[jumlahTim].nama) != -1) {
        cout << "Tim sudah terdaftar.\n";
        system("pause");
        return;
    }

    jumlahTim++;
    cout << "Tim berhasil ditambahkan.\n";
    simpanKeFile();
    system("pause");
}

void tambahPertandingan() {
    system("cls");
    char tim1[50], tim2[50];
    int skor1, skor2;

    cout << "===== MENAMBAHKAN PERTANDINGAN =====\n";
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
        system("pause");
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
    system("pause");
}


void tampilKlasemen() {
    system("cls");

    for (int i = 0; i < jumlahTim - 1; ++i) {
        for (int j = 0; j < jumlahTim - i - 1; ++j) {
            if (daftarTim[j].poin < daftarTim[j + 1].poin) {
                Tim temp = daftarTim[j];
                daftarTim[j] = daftarTim[j + 1];
                daftarTim[j + 1] = temp;
            }
        }
    }

    cout << "\n===== Klasemen Liga =====\n";
    cout << left << setw(20) << "Tim"
         << right << setw(6) << "Main"
         << setw(8) << "Menang"
         << setw(6) << "Seri"
         << setw(7) << "Kalah"
         << setw(10) << "Gol"
         << setw(6) << "Poin" << endl;

    for (int i = 0; i < jumlahTim; ++i) {
        Tim* t = &daftarTim[i];
        cout << left << setw(20) << t->nama
             << right << setw(6) << t->main
             << setw(8) << t->menang
             << setw(6) << t->seri
             << setw(7) << t->kalah
             << setw(5) << t->golMasuk << " " << setw(4) << t->golKemasukan
             << setw(6) << t->poin << endl;
    }
    cout << "===============================================\n";
    system("pause");
}

void cariDanTampilkanTim() {
    system("cls");
    char namaCari[50];
    cout << "===== MENCARI TIM =====\n";
    cout << "Masukkan nama tim yang dicari: ";
    cin.ignore();
    cin.getline(namaCari, 50);

    int idx = cariTim(namaCari);
    if (idx == -1) {
        cout << "Tim tidak ditemukan.\n";
    } else {
        Tim* t = &daftarTim[idx];
        cout << "\nDetail Tim : " << t->nama << " \n";
        cout << "Main       : " << t->main << "\n";
        cout << "Menang     : " << t->menang << "\n";
        cout << "Seri       : " << t->seri << "\n";
        cout << "Kalah      : " << t->kalah << "\n";
        cout << "Gol        : " << t->golMasuk << " - " << t->golKemasukan << "\n";
        cout << "Poin       : " << t->poin << "\n";
    }
    system("pause");
}

void editTim() {
    system("cls");
    char namaLama[50];
    cout << " ===== MENGEDIT TIM =====\n";
    cout << "Masukkan nama tim yang ingin diedit: ";
    cin.ignore();
    cin.getline(namaLama, 50);

    int idx = cariTim(namaLama);
    if (idx == -1) {
        cout << "Tim tidak ditemukan.\n";
        system("pause");
        return;
    }

    cout << "Masukkan nama baru untuk tim \"" << namaLama << "\": ";
    char namaBaru[50];
    cin.getline(namaBaru, 50);

    if (cariTim(namaBaru) != -1) {
        cout << "Nama tim sudah digunakan.\n";
        system("pause");
        return;
    }

    strcpy(daftarTim[idx].nama, namaBaru);
    cout << "Nama tim berhasil diubah.\n";
    simpanKeFile();
    system("pause");
}

void hapusTim() {
    system("cls");
    char namaHapus[50];
    cout << " ===== HAPUS TIM ===== \n";
    cout << "Masukkan nama tim yang ingin dihapus: ";
    cin.ignore();
    cin.getline(namaHapus, 50);

    int idx = cariTim(namaHapus);
    if (idx == -1) {
        cout << "Tim tidak ditemukan.\n";
        system("pause");
        return;
    }

    for (int i = idx; i < jumlahTim - 1; i++) {
        daftarTim[i] = daftarTim[i + 1];
    }
    jumlahTim--;

    cout << "Tim berhasil dihapus.\n";
    simpanKeFile();
    system("pause");
}

void menu() {
    int pilihan;
    do {
        system("cls");
        cout << "\n===== Menu Manajemen Liga =====\n";
        cout << "1. Tambah Tim\n";
        cout << "2. Tambah Pertandingan\n";
        cout << "3. Tampilkan Klasemen\n";
        cout << "4. Cari Tim\n";
        cout << "5. Edit Tim\n";
        cout << "6. Hapus Tim\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: 
              tambahTim(); 
              break;
            case 2: 
              tambahPertandingan(); 
              break;
            case 3: 
              tampilKlasemen(); 
              break;
            case 4: 
              cariDanTampilkanTim(); 
              break;
            case 5: 
              editTim(); 
              break;
            case 6: 
              hapusTim(); 
              break;
            case 0: 
              cout << "Keluar dari program.\n"; 
              break;
            default: 
              cout << "Pilihan tidak valid.\n"; 
              system("pause");
        }

    } while (pilihan != 0);
}

int main() {
    BacaDariFile();
    menu();
    return 0;
}
