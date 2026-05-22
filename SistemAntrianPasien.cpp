#include <iostream>
#include <fstream>
#include <string>

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
