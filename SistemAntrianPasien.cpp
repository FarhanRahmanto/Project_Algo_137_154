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
