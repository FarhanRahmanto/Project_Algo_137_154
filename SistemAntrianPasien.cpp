#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

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

        if (!line.empty() && line[0] == 'A') {
            nomorAntrian++;
        }
    }

    file.close();
}

void tampilAntrian(Node* awal) {

    system("cls"); 

    if (awal == nullptr) {
        cout << "\n[!] Antrian kosong!" << endl;
        cout << "\nTekan Enter untuk kembali ke menu...";
        cin.get();
        return;
    }

    Node* temp = awal;
    int no = 1;

    cout << "\n======================================================" << endl;
    cout << "                    DAFTAR ANTRIAN" << endl;
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
    
    cout << "\nTekan Enter untuk kembali ke menu...";
    cin.get();
}

void cariPasienDiFile(string tiketDicari) {

    system("cls"); 

    ifstream file("DataPasien.txt");

    if (!file.is_open()) {
        cout << "\n[!] Database gagal dibuka!" << endl;
        cout << "\nTekan Enter untuk kembali...";
        cin.get();
        return;
    }

    string line;
    bool ketemu = false;

    while (getline(file, line)) {

        if (line.empty()) continue;

        string tiket="", nama="", telp="", keluhan="";
        string usia="", jk="", status="", tgl="";

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
            else if (kolom == 4) usia += line[i];
            else if (kolom == 5) jk += line[i];
            else if (kolom == 6) status += line[i];
            else if (kolom == 7) tgl += line[i];
        }

        if (tiket == tiketDicari) {

            cout << "\n====================================" << endl;
            cout << "            DATA PASIEN" << endl;
            cout << "====================================" << endl;

            cout << "No Tiket      : " << tiket << endl;
            cout << "Nama Pasien   : " << nama << endl;
            cout << "No Telepon    : " << telp << endl;
            cout << "Keluhan       : " << keluhan << endl;
            cout << "Usia          : " << usia << endl;
            cout << "Jenis Kelamin : "
                 << (jk == "L" ? "Laki-laki" : "Perempuan")
                 << endl;

            cout << "Status        : "
                 << (status == "1"
                 ? "SUDAH DILAYANI"
                 : "BELUM DILAYANI")
                 << endl;

            cout << "Tanggal       : " << tgl << endl;
            cout << "------------------------------------" << endl;

            ketemu = true;
        }
    }

    file.close();

    if (!ketemu) {
        cout << "\n[!] Data pasien tidak ditemukan!" << endl;
    }
    
    cout << "\nTekan Enter untuk kembali...";
    cin.get();
}

void layaniPasien(Node*& awal, Node*& akhir) {

    system("cls"); 

    if (awal == nullptr) {
        cout << "\n====================================" << endl;
        cout << "          PANGGILAN PASIEN" << endl;
        cout << "====================================" << endl;
        cout << "\n[!] Antrian kosong!" << endl;
        cout << "\nTekan Enter untuk kembali...";
        cin.get();
        return;
    }

    Node* hapus = awal;

    string tiket = hapus->info.noTiket;

    cout << "\n====================================" << endl;
    cout << "          PANGGILAN PASIEN" << endl;
    cout << "====================================" << endl;
    cout << "\n[+] Pasien "
         << hapus->info.nama
         << " sudah dilayani!" << endl;

    
    awal = awal->next;

    if (awal != nullptr) {
        awal->prev = nullptr;
    } else {
        akhir = nullptr;
    }

    delete hapus;


    ifstream file("DataPasien.txt");
    ofstream temp("temp.txt");

    string line;

    while (getline(file, line)) {
        if (line.find(tiket + "#") == 0) {
            
            
            size_t pos = 0;
            for (int p = 0; p < 6; p++) {
                pos = line.find('#', pos + 1);
            }
            
            
            size_t pos_setelah = line.find('#', pos + 1);
            
            
            string baru = line.substr(0, pos) + "#1" + line.substr(pos_setelah);
            
            temp << baru << endl;
        }
        else {
            temp << line << endl;
        }
    }
    file.close();
    temp.close();

    remove("DataPasien.txt");
    rename("temp.txt", "DataPasien.txt");
    
    cout << "\nTekan Enter untuk kembali...";
    cin.get();
}

void tampilRiwayat() {

    system("cls"); 

    ifstream file("DataPasien.txt");

    if (!file.is_open()) {
        cout << "\n[!] File tidak bisa dibuka!" << endl;
        cout << "\nTekan Enter untuk kembali...";
        cin.get();
        return;
    }

    Pasien daftarPasien[100];
    string tglTeks[100];
    long nilaiTanggal[100];

    int jumlahPasien = 0;

    string line;

    while (getline(file, line)) {

        if (line.empty()) continue;

        string tiket="", nama="", telp="", keluhan="";
        string usiaStr="", jk="", statusStr="", tglStr="";

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
            atoi(usiaStr.c_str());

        daftarPasien[jumlahPasien].jenisKelamin =
            jk[0];

        daftarPasien[jumlahPasien].sudahDilayani =
            (statusStr == "1");

        tglTeks[jumlahPasien] = tglStr;

        long angkaSorting = 0;

        size_t pos1 = tglStr.find('-');
        size_t pos2 = tglStr.find('-', pos1 + 1);

        if (pos1 != string::npos &&
            pos2 != string::npos) {

            int tgl = atoi(
                tglStr.substr(0, pos1).c_str()
            );

            int bln = atoi(
                tglStr.substr(
                    pos1 + 1,
                    pos2 - pos1 - 1
                ).c_str()
            );

            int thn = atoi(
                tglStr.substr(pos2 + 1).c_str()
            );

            angkaSorting =
                (thn * 10000) +
                (bln * 100) +
                tgl;
        }

        nilaiTanggal[jumlahPasien] = angkaSorting;

        jumlahPasien++;
    }

    file.close();

    
    for (int i = 0; i < jumlahPasien - 1; i++) {

        for (int j = 0; j < jumlahPasien - i - 1; j++) {

            if (nilaiTanggal[j] >
                nilaiTanggal[j + 1]) {

                long tempTanggal =
                    nilaiTanggal[j];

                nilaiTanggal[j] =
                    nilaiTanggal[j + 1];

                nilaiTanggal[j + 1] =
                    tempTanggal;

                string tempTgl =
                    tglTeks[j];

                tglTeks[j] =
                    tglTeks[j + 1];

                tglTeks[j + 1] =
                    tempTgl;

                Pasien tempPasien =
                    daftarPasien[j];

                daftarPasien[j] =
                    daftarPasien[j + 1];

                daftarPasien[j + 1] =
                    tempPasien;
            }
        }
    }

    cout << "\n======================================================" << endl;
    cout << "                   RIWAYAT PASIEN" << endl;
    cout << "======================================================" << endl;

    if (jumlahPasien == 0) {
        cout << "Riwayat kosong." << endl;
    }

    for (int i = 0; i < jumlahPasien; i++) {

        cout << "Tanggal        : "
             << tglTeks[i] << endl;

        cout << "No Tiket       : "
             << daftarPasien[i].noTiket << endl;

        cout << "Nama Pasien    : "
             << daftarPasien[i].nama << endl;

        cout << "No Telepon     : "
             << daftarPasien[i].nomorTelepon << endl;

        cout << "Keluhan        : "
             << daftarPasien[i].keluhan << endl;

        cout << "Usia           : "
             << daftarPasien[i].usia << endl;

        cout << "Jenis Kelamin  : "
             << (daftarPasien[i].jenisKelamin == 'L'
             ? "Laki-laki"
             : "Perempuan")
             << endl;

        cout << "Status         : "
             << (daftarPasien[i].sudahDilayani
             ? "SUDAH DILAYANI"
             : "BELUM DILAYANI")
             << endl;

        cout << "------------------------------------------------------" << endl;
    }
    
    cout << "\nTekan Enter untuk kembali...";
    cin.get();
}

void tambahPasien(Node** awal,
                  Node** akhir,
                  Pasien databaru) {

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

    system("cls"); 

    cout << "====================================" << endl;
    cout << "	HAPUS RIWAYAT PASIEN		" << endl;
    cout << "====================================" << endl;

    ifstream file("DataPasien.txt");
    ofstream temp("temp.txt");

    string tiketHapus;
    string line;

    bool ketemu = false;

    cout << "Masukkan nomor tiket : ";
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
    
    cout << "\nTekan Enter untuk kembali...";
    cin.get();
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
              << (data.sudahDilayani ? "1" : "0") << "#" 
              << data.tglKunjungan.tgl << "-"
              << data.tglKunjungan.bln << "-"
              << data.tglKunjungan.thn << "#"
              << endl;

        arsip.close();

        cout << "\n[+] Data berhasil disimpan!" << endl;
    }

    else {
        cout << "\n[!] File gagal dibuka!" << endl;
    }
}

int main() {

    Node* awal = nullptr;
    Node* akhir = nullptr;

    string cariTiket;

    mengecheckAntrian();

    int pilih;

    do {

        system("cls"); 

        cout << "====================================" << endl;
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
        cout << "Pilihan Menu : ";

        cin >> pilih;
        cin.ignore();

        if (pilih == 1) {

            system("cls"); 
            Pasien p;

            cout << "====================================" << endl;
            cout << "           TAMBAH PASIEN" << endl;
            cout << "====================================" << endl;

            
            cout << "Nama Pasien      : ";
            getline(cin, p.nama);

            while (p.nama.empty()) {
                cout << "[!] Nama tidak boleh kosong : ";
                getline(cin, p.nama);
            }

            
            cout << "Nomor Telepon    : ";
            getline(cin, p.nomorTelepon);

            while (p.nomorTelepon.empty()) {
                cout << "[!] Nomor telepon tidak boleh kosong : ";
                getline(cin, p.nomorTelepon);
            }

            
            cout << "Keluhan          : ";
            getline(cin, p.keluhan);

            while (p.keluhan.empty()) {
                cout << "[!] Keluhan tidak boleh kosong : ";
                getline(cin, p.keluhan);
            }

            
            cout << "Usia             : ";

            while (!(cin >> p.usia) || p.usia <= 0) {
                cout << "[!] Usia harus angka positif : ";
                cin.clear();
                cin.ignore(1000, '\n');
            }

            
            cout << "Jenis Kelamin (L/P) : ";
            cin >> p.jenisKelamin;

            while (p.jenisKelamin != 'L' &&
                   p.jenisKelamin != 'P' &&
                   p.jenisKelamin != 'l' &&
                   p.jenisKelamin != 'p') {

                cout << "[!] Input hanya L/P : ";
                cin >> p.jenisKelamin;
            }

            
            cout << "Tanggal (t b th) : ";

            while (!(cin >> p.tglKunjungan.tgl
                         >> p.tglKunjungan.bln
                         >> p.tglKunjungan.thn)) {

                cout << "[!] Input tanggal salah : ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cin.ignore(); 

            
            p.noTiket = "A" + to_string(nomorAntrian);
            nomorAntrian++;

            cout << "No Tiket         : " << p.noTiket << endl;

            p.sudahDilayani = false;

            tambahPasien(&awal, &akhir, p);
            simpanData(p);
            
            cout << "\nTekan Enter untuk kembali ke menu...";
            cin.get();
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

            cout << "Masukkan tiket : ";
            cin >> cariTiket;
            cin.ignore();

            cariPasienDiFile(cariTiket);
        }

        else if (pilih == 6) {
            hapusRiwayat();
        }

    } while (pilih != 0);

    return 0;
}
