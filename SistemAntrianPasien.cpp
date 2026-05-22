#include <iostream>
#include <fstream>
#include <string>

struct Tanggal{
    int tgl, bln, thn;
};

struct Pasien{
    string nama, noTiket, nomorTelepon, keluhan;
    int usia;
    char jenisKelamin;
    bool sudahDilayani;
    Tanggal tglKunjungan;
};

struct Node{
    Pasien info;
    Node* next;
    Node* prev;
};

int nomorAntrian = 1;

void mengecheckAntrian() {
    ifstream file("DataPasien.txt");
    string line;

    while (getline(file, line)) {
        if (!line.empty()) {
            nomorAntrian++;
        }
    }

    file.close();
}

void tampilAntrian(Node* awal) {

    if (awal == nullptr) {
        cout << "\n[!] Antrian kosong!" << endl;
        return;
    }

    Node* temp = awal;
    int no = 1;

    cout << "\n======================================================" << endl;
    cout << "                 DAFTAR ANTRIAN" << endl;
    cout << "======================================================" << endl;
    cout << "NO\tTIKET\tNAMA\t\tSTATUS" << endl;
    cout << "------------------------------------------------------" << endl;

    while (temp != nullptr) {

        cout << no << "\t"
             << temp->info.noTiket << "\t"
             << temp->info.nama << "\t\t"
             << (temp->info.sudahDilayani ? "SUDAH" : "BELUM")
             << endl;

        temp = temp->next;
        no++;
    }

    cout << "======================================================" << endl;
}

void layaniPasien(Node*& awal, Node*& akhir) {

    if (awal == nullptr) {
        cout << "\n[!] Antrian kosong!" << endl;
        return;
    }

    Node* hapus = awal;

    hapus->info.sudahDilayani = true;

    cout << "\n[+] Pasien "
         << hapus->info.nama
         << " sudah dilayani!" << endl;

    awal = awal->next;

    if (awal != nullptr) {
        awal->prev = nullptr;
    }
    else {
        akhir = nullptr;
    }

    delete hapus;
}

void tampilRiwayat() {

    ifstream file("DataPasien.txt");

    if (!file.is_open()) {
        cout << "\n[!] File tidak bisa dibuka!" << endl;
        return;
    }

    Pasien daftarPasien[100];
    string tglTeks[100];
    long nilaiTanggal[100];

    int jumlahPasien = 0;

    string line;

    while (getline(file, line)) {

        if (line.empty()) continue;

        string tiket = "", nama = "", telp = "", keluhan = "";
        string usiaStr = "", jk = "", statusStr = "", tglStr = "";

        int kolom = 0;

        for (size_t i = 0; i < line.length(); i++) {

            if (line[i] == '#') {
                kolom++;
                continue;
            }

            if (kolom == 0) tiket += line[i];
            else if (kolom == 1) nama += line[i];
            else if (kolom == 2) telp += line[i];
            else if (kolom == 3) keluhan += line[i];
            else if (kolom == 4) usiaStr += line[i];
            else if (kolom == 5) jk += line[i];
            else if (kolom == 6) statusStr += line[i];
            else if (kolom == 7) tglStr += line[i];
        }

        daftarPasien[jumlahPasien].noTiket = tiket;
        daftarPasien[jumlahPasien].nama = nama;
        daftarPasien[jumlahPasien].nomorTelepon = telp;
        daftarPasien[jumlahPasien].keluhan = keluhan;

        daftarPasien[jumlahPasien].usia =
            (usiaStr.empty()) ? 0 : stoi(usiaStr);

        daftarPasien[jumlahPasien].jenisKelamin =
            (jk.empty()) ? '-' : jk[0];

        daftarPasien[jumlahPasien].sudahDilayani =
            (statusStr == "1");

        tglTeks[jumlahPasien] = tglStr;

        long angkaSorting = 0;

        size_t pos1 = tglStr.find('-');
        size_t pos2 = tglStr.find('-', pos1 + 1);

        if (pos1 != string::npos && pos2 != string::npos) {

            int tgl = stoi(tglStr.substr(0, pos1));

            int bln = stoi(
                tglStr.substr(pos1 + 1, pos2 - pos1 - 1)
            );

            int thn = stoi(tglStr.substr(pos2 + 1));

            angkaSorting =
                (thn * 10000) + (bln * 100) + tgl;
        }

        nilaiTanggal[jumlahPasien] = angkaSorting;

        jumlahPasien++;
    }

    file.close();

    for (int i = 0; i < jumlahPasien - 1; i++) {

        for (int j = 0; j < jumlahPasien - i - 1; j++) {

            if (nilaiTanggal[j] > nilaiTanggal[j + 1]) {

                swap(nilaiTanggal[j], nilaiTanggal[j + 1]);
                swap(tglTeks[j], tglTeks[j + 1]);
                swap(daftarPasien[j], daftarPasien[j + 1]);
            }
        }
    }

    cout << "\n======================================================" << endl;
    cout << "        RIWAYAT PASIEN BERDASARKAN TANGGAL" << endl;
    cout << "======================================================" << endl;

    if (jumlahPasien == 0) {
        cout << "Riwayat masih kosong." << endl;
    }

    for (int i = 0; i < jumlahPasien; i++) {

        cout << "Tanggal Kunjungan : " << tglTeks[i] << endl;
        cout << "No Tiket          : " << daftarPasien[i].noTiket << endl;
        cout << "Nama Pasien       : " << daftarPasien[i].nama << endl;
        cout << "No Telepon        : " << daftarPasien[i].nomorTelepon << endl;
        cout << "Keluhan           : " << daftarPasien[i].keluhan << endl;
        cout << "Usia              : " << daftarPasien[i].usia << " Tahun" << endl;

        cout << "Jenis Kelamin     : "
             << (daftarPasien[i].jenisKelamin == 'L'
             ? "Laki-laki"
             : "Perempuan")
             << endl;

        cout << "Status Pelayanan  : "
             << (daftarPasien[i].sudahDilayani
             ? "SUDAH DILAYANI"
             : "BELUM DILAYANI")
             << endl;

        cout << "------------------------------------------------------" << endl;
    }
}


void cariPasienDiFile(string tiketDicari) {

    ifstream file("DataPasien.txt");

    if (!file.is_open()) {
        cout << "\n[!] Database gagal dibuka atau belum ada data!" << endl;
        return;
    }

    string line;
    bool ketemu = false;

    cout << "\n====================================" << endl;
    cout << "        HASIL PENCARIAN PASIEN" << endl;
    cout << "====================================" << endl;

    while (getline(file, line)) {

        if (line.empty()) continue;

        string tiket = "", nama = "", telp = "", keluhan = "";
        string usia = "", jk = "", status = "", tgl = "";

        int kolom = 0;

        for (int i = 0; i < line.length(); i++) {

            if (line[i] == '#') {
                kolom++;
                continue;
            }

            if (kolom == 0) tiket += line[i];
            else if (kolom == 1) nama += line[i];
            else if (kolom == 2) telp += line[i];
            else if (kolom == 3) keluhan += line[i];
            else if (kolom == 4) usia += line[i];
            else if (kolom == 5) jk += line[i];
            else if (kolom == 6) status += line[i];
            else if (kolom == 7) tgl += line[i];
        }

        if (tiket == tiketDicari) {

            cout << "No Tiket       : " << tiket << endl;
            cout << "Nama Pasien    : " << nama << endl;
            cout << "No Telepon     : " << telp << endl;
            cout << "Keluhan        : " << keluhan << endl;
            cout << "Usia           : " << usia << " Tahun" << endl;
            cout << "Jenis Kelamin  : "
                 << (jk == "L" ? "Laki-laki" : "Perempuan") << endl;

            cout << "Status         : "
                 << (status == "1" ? "SUDAH DILAYANI" : "BELUM DILAYANI")
                 << endl;

            cout << "Tgl Kunjungan  : " << tgl << endl;
            cout << "------------------------------------" << endl;

            ketemu = true;
            break;
        }
    }

    file.close();

    if (!ketemu) {
        cout << "\n[!] Pasien dengan tiket "
             << tiketDicari
             << " tidak ditemukan!" << endl;
    }
}
void tambahPasien(Node** awal, Node** akhir, Pasien databaru) {

    Node* baru = new Node;

    baru->info = databaru;
    baru->next = nullptr;
    baru->prev = nullptr;

    if (*awal == nullptr) {
        *awal = *akhir = baru;
    }

    else {
        (*akhir)->next = baru;
        baru->prev = *akhir;
        *akhir = baru;
    }
}
void hapusRiwayat() {

    ifstream file("DataPasien.txt");
    ofstream temp("temp.txt");

    string tiketHapus;
    string line;

    bool ketemu = false;

    cout << "Masukkan nomor tiket yang ingin dihapus : ";
    getline(cin, tiketHapus);

    while (getline(file, line)) {

        if (line.find(tiketHapus + "#") == 0) {

            ketemu = true;
            continue;
        }

        temp << line << endl;
    }

    file.close();
    temp.close();

    remove("DataPasien.txt");
    rename("temp.txt", "DataPasien.txt");

    if (ketemu) {
        cout << "\n[+] Data berhasil dihapus!" << endl;
    }

    else {
        cout << "\n[!] Data tidak ditemukan!" << endl;
    }
}
void simpanData(Pasien data) {

    ofstream arsip;

    arsip.open("DataPasien.txt", ios::app);

    if (arsip.is_open()) {

        arsip << data.noTiket << "#"
              << data.nama << "#"
              << data.nomorTelepon << "#"
              << data.keluhan << "#"
              << data.usia << "#"
              << data.jenisKelamin << "#"
              << data.sudahDilayani << "#"
              << data.tglKunjungan.tgl << "-"
              << data.tglKunjungan.bln << "-"
              << data.tglKunjungan.thn << "#"
              << endl;

        arsip.close();

        cout << "\n[+] Data pasien "
             << data.nama
             << " berhasil disimpan!"
             << endl;
    }

    else {
        cout << "\n[!] File database gagal dibuka!" << endl;
    }
}

using namespace std;
int main() {
    Node* awal = nullptr;
    Node* akhir = nullptr;
    string cariTiket;
    int pilih;

   
    loadAntrianDariFile(&awal, &akhir);

    do {
        cout << "\n====================================" << endl;
        cout << "      SISTEM KLINIK SEDERHANA" << endl;
        cout << "====================================" << endl;
        cout << "1. Tambah Pasien" << endl;
        cout << "2. Lihat Antrian" << endl;
        cout << "3. Layani Pasien" << endl;
        cout << "4. Riwayat Pasien" << endl;
        cout << "5. Cari Pasien" << endl;
        cout << "6. Hapus Riwayat" << endl;
        cout << "0. Keluar" << endl;
        cout << "====================================" << endl;
        cout << "Pilih Menu : ";
        cin >> pilih;
        cin.ignore(); // BERSIHKAN BUFFER setelah input integer menu

        if (pilih == 1) {
            Pasien p;
            cout << "\n====================================" << endl;
            cout << "          TAMBAH PASIEN" << endl;
            cout << "====================================" << endl;
            cout << "Nama Pasien      : "; getline(cin, p.nama);

            p.noTiket = "A" + to_string(nomorAntrian);
            nomorAntrian++;
            cout << "No Tiket         : " << p.noTiket << endl;

            cout << "Nomor Telepon    : "; getline(cin, p.nomorTelepon);
            cout << "Keluhan          : "; getline(cin, p.keluhan);
            cout << "Usia             : "; cin >> p.usia;
            cout << "Jenis Kelamin    : "; cin >> p.jenisKelamin;
            cout << "Tanggal (t b th) : "; cin >> p.tglKunjungan.tgl >> p.tglKunjungan.bln >> p.tglKunjungan.thn;
            
            cin.ignore();

            p.sudahDilayani = false;
            tambahPasien(&awal, &akhir, p);
            simpanData(p);
            cout << "\n[+] Data pasien " << p.nama << " berhasil disimpan!" << endl;
        }
        else if (pilih == 2) {
            tampilAntrian(awal);
        }
        else if (pilih == 3) {
            layaniPasien(awal, akhir);
        }
        else if (pilih == 4) {
            tampilRiwayat();
        }
        else if (pilih == 5) {
            cout << "Nomor tiket : "; cin >> cariTiket;
            cin.ignore();
            cariPasienDiFile(cariTiket);
        }
        else if (pilih == 6) {
            hapusRiwayat();
        }

    } while (pilih != 0);

    
    Node* temp = awal;
    while (temp != nullptr) {
        Node* berikutnya = temp->next;
        delete temp;
        temp = berikutnya;
    }

    return 0;
}
