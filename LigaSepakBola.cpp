#include <iostream>
#include <cstdio>
#include <cstring>
#include <iomanip>

using namespace std;

const int MAKS_TIM = 20;
const int MAKS_PEMAIN_PER_TIM = 30;

struct Pemain {
    char nama[50];
    int nomor;
    char posisi[20];
};

struct Tim {
    char nama[50];
    int main = 0;
    int menang = 0;
    int seri = 0;
    int kalah = 0;
    int golMasuk = 0;
    int golKemasukan = 0;
    int poin = 0;
    Pemain daftarPemain[MAKS_PEMAIN_PER_TIM];
    int jumlahPemain = 0;
};

Tim daftarTim[MAKS_TIM];
int jumlahTim = 0;

// Fungsi cari tim berdasarkan nama
int cariTim(const char nama[]) {
    for (int i = 0; i < jumlahTim; ++i) {
        if (strcmp(nama, daftarTim[i].nama) == 0) {
            return i;
        }
    }
    return -1;
}

// Fungsi cari pemain dalam tim tertentu berdasarkan nama
int cariPemain(Tim& tim, const char nama[]) {
    for (int i = 0; i < tim.jumlahPemain; ++i) {
        if (strcmp(nama, tim.daftarPemain[i].nama) == 0) {
            return i;
        }
    }
    return -1;
}

// Simpan data tim dan pemain ke file
void simpanKeFile() {
    FILE* fp = fopen("tim.txt", "w");
    if (fp == NULL) {
        cout << "Gagal membuka file untuk menyimpan.\n";
        return;
    }

    for (int i = 0; i < jumlahTim; i++) {
        // Simpan data tim
        fprintf(fp, "%s;%d;%d;%d;%d;%d;%d;%d;%d\n",
            daftarTim[i].nama, daftarTim[i].main, daftarTim[i].menang,
            daftarTim[i].seri, daftarTim[i].kalah, daftarTim[i].golMasuk,
            daftarTim[i].golKemasukan, daftarTim[i].poin, daftarTim[i].jumlahPemain);

        // Simpan data pemain tiap tim
        for (int j = 0; j < daftarTim[i].jumlahPemain; j++) {
            fprintf(fp, "%s;%d;%s\n",
                daftarTim[i].daftarPemain[j].nama,
                daftarTim[i].daftarPemain[j].nomor,
                daftarTim[i].daftarPemain[j].posisi);
        }
    }

    fclose(fp);
}

// Membaca data tim dan pemain dari file
void BacaDariFile() {
    FILE* fp = fopen("tim.txt", "r");
    if (fp == NULL) {
        cout << "Belum ada data file tersimpan.\n";
        return;
    }

    jumlahTim = 0;
    while (!feof(fp) && jumlahTim < MAKS_TIM) {
        char nama[50];
        int main, menang, seri, kalah, golMasuk, golKemasukan, poin, jumlahPemain;

        int hasil = fscanf(fp, "%49[^;];%d;%d;%d;%d;%d;%d;%d;%d\n",
            nama, &main, &menang, &seri, &kalah, &golMasuk, &golKemasukan, &poin, &jumlahPemain);

        if (hasil == 9) {
            strcpy(daftarTim[jumlahTim].nama, nama);
            daftarTim[jumlahTim].main = main;
            daftarTim[jumlahTim].menang = menang;
            daftarTim[jumlahTim].seri = seri;
            daftarTim[jumlahTim].kalah = kalah;
            daftarTim[jumlahTim].golMasuk = golMasuk;
            daftarTim[jumlahTim].golKemasukan = golKemasukan;
            daftarTim[jumlahTim].poin = poin;
            daftarTim[jumlahTim].jumlahPemain = jumlahPemain;

            // Baca data pemain untuk tim ini
            for (int j = 0; j < jumlahPemain; ++j) {
                char namaPemain[50];
                int nomor;
                char posisi[20];

                int res = fscanf(fp, "%49[^;];%d;%19[^\n]\n", namaPemain, &nomor, posisi);
                if (res == 3) {
                    strcpy(daftarTim[jumlahTim].daftarPemain[j].nama, namaPemain);
                    daftarTim[jumlahTim].daftarPemain[j].nomor = nomor;
                    strcpy(daftarTim[jumlahTim].daftarPemain[j].posisi, posisi);
                } else {
                    break;
                }
            }
            jumlahTim++;
        } else {
            break;
        }
    }

    fclose(fp);
}

// Tambah tim baru
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

    // Reset statistik awal
    daftarTim[jumlahTim].main = 0;
    daftarTim[jumlahTim].menang = 0;
    daftarTim[jumlahTim].seri = 0;
    daftarTim[jumlahTim].kalah = 0;
    daftarTim[jumlahTim].golMasuk = 0;
    daftarTim[jumlahTim].golKemasukan = 0;
    daftarTim[jumlahTim].poin = 0;
    daftarTim[jumlahTim].jumlahPemain = 0;

    jumlahTim++;
    cout << "Tim berhasil ditambahkan.\n";
    simpanKeFile();
    system("pause");
}

// Tambah pemain ke tim tertentu
void tambahPemain() {
    system("cls");
    if (jumlahTim == 0) {
        cout << "Belum ada tim terdaftar.\n";
        system("pause");
        return;
    }

    char namaTim[50];
    cout << "===== TAMBAH PEMAIN =====\n";
    cout << "Masukkan nama tim: ";
    cin.ignore();
    cin.getline(namaTim, 50);

    int idxTim = cariTim(namaTim);
    if (idxTim == -1) {
        cout << "Tim tidak ditemukan.\n";
        system("pause");
        return;
    }

    Tim& tim = daftarTim[idxTim];
    if (tim.jumlahPemain >= MAKS_PEMAIN_PER_TIM) {
        cout << "Jumlah pemain sudah maksimal untuk tim ini.\n";
        system("pause");
        return;
    }

    char namaPemain[50];
    int nomor;
    char posisi[20];

    cout << "Masukkan nama pemain: ";
    cin.getline(namaPemain, 50);
    if (cariPemain(tim, namaPemain) != -1) {
        cout << "Pemain sudah terdaftar di tim ini.\n";
        system("pause");
        return;
    }

    cout << "Masukkan nomor punggung: ";
    cin >> nomor;
    cin.ignore();
    cout << "Masukkan posisi pemain: ";
    cin.getline(posisi, 20);

    Pemain& p = tim.daftarPemain[tim.jumlahPemain];
    strcpy(p.nama, namaPemain);
    p.nomor = nomor;
    strcpy(p.posisi, posisi);

    tim.jumlahPemain++;

    cout << "Pemain berhasil ditambahkan ke tim " << tim.nama << ".\n";
    simpanKeFile();
    system("pause");
}

// Tampilkan daftar pemain tim tertentu
void tampilPemain() {
    system("cls");
    if (jumlahTim == 0) {
        cout << "Belum ada tim terdaftar.\n";
        system("pause");
        return;
    }

    char namaTim[50];
    cout << "===== DAFTAR PEMAIN TIM =====\n";
    cout << "Masukkan nama tim: ";
    cin.ignore();
    cin.getline(namaTim, 50);

    int idxTim = cariTim(namaTim);
    if (idxTim == -1) {
        cout << "Tim tidak ditemukan.\n";
        system("pause");
        return;
    }

    Tim& tim = daftarTim[idxTim];
    if (tim.jumlahPemain == 0) {
        cout << "Tim ini belum memiliki pemain.\n";
        system("pause");
        return;
    }

    cout << "Daftar pemain tim " << tim.nama << ":\n";
    cout << left << setw(20) << "Nama" << setw(10) << "Nomor" << setw(15) << "Posisi" << endl;
    cout << "======================================\n";

    for (int i = 0; i < tim.jumlahPemain; i++) {
        Pemain& p = tim.daftarPemain[i];
        cout << left << setw(20) << p.nama << setw(10) << p.nomor << setw(15) << p.posisi << endl;
    }
    system("pause");
}

// Edit data pemain dalam sebuah tim
void editPemain() {
    system("cls");
    if (jumlahTim == 0) {
        cout << "Belum ada tim terdaftar.\n";
        system("pause");
        return;
    }

    char namaTim[50];
    cout << "===== EDIT PEMAIN =====\n";
    cout << "Masukkan nama tim: ";
    cin.ignore();
    cin.getline(namaTim, 50);

    int idxTim = cariTim(namaTim);
    if (idxTim == -1) {
        cout << "Tim tidak ditemukan.\n";
        system("pause");
        return;
    }

    Tim& tim = daftarTim[idxTim];

    if (tim.jumlahPemain == 0) {
        cout << "Tim ini belum memiliki pemain.\n";
        system("pause");
        return;
    }

    char namaPemain[50];
    cout << "Masukkan nama pemain yang ingin diedit: ";
    cin.getline(namaPemain, 50);

    int idxPemain = cariPemain(tim, namaPemain);
    if (idxPemain == -1) {
        cout << "Pemain tidak ditemukan.\n";
        system("pause");
        return;
    }

    Pemain& p = tim.daftarPemain[idxPemain];

    cout << "Masukkan nama baru pemain (enter jika tidak diubah): ";
    char namaBaru[50];
    cin.getline(namaBaru, 50);
    if (strlen(namaBaru) > 0) {
        // Pastikan tidak duplikat nama pemain dalam tim
        if (cariPemain(tim, namaBaru) != -1 && strcmp(namaBaru, p.nama) != 0) {
            cout << "Nama pemain sudah digunakan.\n";
            system("pause");
            return;
        }
        strcpy(p.nama, namaBaru);
    }

    cout << "Masukkan nomor baru (0 jika tidak diubah): ";
    int nomorBaru;
    cin >> nomorBaru;
    cin.ignore();
    if (nomorBaru > 0) {
        p.nomor = nomorBaru;
    }

    cout << "Masukkan posisi baru (enter jika tidak diubah): ";
    char posisiBaru[20];
    cin.getline(posisiBaru, 20);
    if (strlen(posisiBaru) > 0) {
        strcpy(p.posisi, posisiBaru);
    }

    cout << "Data pemain berhasil diubah.\n";
    simpanKeFile();
    system("pause");
}

// Hapus pemain dari sebuah tim
void hapusPemain() {
    system("cls");
    if (jumlahTim == 0) {
        cout << "Belum ada tim terdaftar.\n";
        system("pause");
        return;
    }

    char namaTim[50];
    cout << "===== HAPUS PEMAIN =====\n";
    cout << "Masukkan nama tim: ";
    cin.ignore();
    cin.getline(namaTim, 50);

    int idxTim = cariTim(namaTim);
    if (idxTim == -1) {
        cout << "Tim tidak ditemukan.\n";
        system("pause");
        return;
    }

    Tim& tim = daftarTim[idxTim];

    if (tim.jumlahPemain == 0) {
        cout << "Tim ini belum memiliki pemain.\n";
        system("pause");
        return;
    }

    char namaPemain[50];
    cout << "Masukkan nama pemain yang ingin dihapus: ";
    cin.getline(namaPemain, 50);

    int idxPemain = cariPemain(tim, namaPemain);
    if (idxPemain == -1) {
        cout << "Pemain tidak ditemukan.\n";
        system("pause");
        return;
    }

    for (int i = idxPemain; i < tim.jumlahPemain - 1; i++) {
        tim.daftarPemain[i] = tim.daftarPemain[i + 1];
    }
    tim.jumlahPemain--;

    cout << "Pemain berhasil dihapus dari tim.\n";
    simpanKeFile();
    system("pause");
}

// Tambah hasil pertandingan (update statistik tim)
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

// Sorting tim berdasarkan poin (descending)
void sortTim() {
    for (int i = 0; i < jumlahTim - 1; ++i) {
        for (int j = 0; j < jumlahTim - i - 1; ++j) {
            if (daftarTim[j].poin < daftarTim[j + 1].poin) {
                Tim temp = daftarTim[j];
                daftarTim[j] = daftarTim[j + 1];
                daftarTim[j + 1] = temp;
            }
        }
    }
}

// Tampilkan klasemen tim
void tampilKlasemen() {
    system("cls");
    if (jumlahTim == 0) {
        cout << "Belum ada tim terdaftar.\n";
        system("pause");
        return;
    }

    sortTim();

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

// Cari tim dan tampilkan detail serta pemainnya
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
        cout << "Main       : " << t->main << endl;
        cout << "Menang     : " << t->menang << endl;
        cout << "Seri       : " << t->seri << endl;
        cout << "Kalah      : " << t->kalah << endl;
        cout << "Gol Masuk  : " << t->golMasuk << endl;
        cout << "Gol Kemasuk: " << t->golKemasukan << endl;
        cout << "Poin       : " << t->poin << endl;

        if (t->jumlahPemain > 0) {
            cout << "\nDaftar Pemain:\n";
            cout << left << setw(20) << "Nama" << setw(10) << "Nomor" << setw(15) << "Posisi" << endl;
            cout << "======================================\n";
            for (int i = 0; i < t->jumlahPemain; i++) {
                Pemain& p = t->daftarPemain[i];
                cout << left << setw(20) << p.nama << setw(10) << p.nomor << setw(15) << p.posisi << endl;
            }
        } else {
            cout << "Tim ini belum memiliki pemain.\n";
        }
    }
    system("pause");
}

// Menu utama
void menu() {
    int pilihan;
    do {
        system("cls");
        cout << "===== PROGRAM MANAJEMEN LIGA SEPAKBOLA =====\n";
        cout << "1. Tambah Tim\n";
        cout << "2. Tambah Pemain\n";
        cout << "3. Edit Pemain\n";
        cout << "4. Hapus Pemain\n";
        cout << "5. Tambah Hasil Pertandingan\n";
        cout << "6. Tampilkan Klasemen\n";
        cout << "7. Tampilkan Daftar Pemain Tim\n";
        cout << "8. Cari Tim\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: 
               tambahTim(); 
               break;
            case 2: 
               tambahPemain(); 
               break;
            case 3: 
               editPemain(); 
               break;
            case 4: 
               hapusPemain(); 
               break;
            case 5: 
               tambahPertandingan(); 
               break;
            case 6: 
               tampilKlasemen(); 
               break;
            case 7: 
               tampilPemain(); 
               break;
            case 8: 
               cariDanTampilkanTim(); 
               break;
            case 0: 
               cout << "Terima kasih!\n"; 
               break;
            default: 
               cout << "Pilihan salah, coba lagi.\n"; 
               system("pause");
        }
    } while (pilihan != 0);
}

int main() {
    BacaDariFile();
    menu();
    return 0;
}
