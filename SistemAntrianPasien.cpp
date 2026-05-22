#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int main() {
	NodeLapangan* rootUtama = NULL;
	
	int pilihMenu;
	string namaInput, olahragaInput,namaLapangan,namaTim;
	
	do{
		cout<<"\n ==== Menu Manajemen Sport Center ==="<<endl;
		cout<<"1. Tambah Lapangan" <<endl;
		cout<<"2. Melihat Lapangan"<<endl;
		cout<<"3. Catat Penyewaan Lapangan"<<endl;
		cout<<"4. Catat Selesai Penggunaan"<<endl;
		cout<<"5. Hapus Lapangan"<<endl;
		cout<<"6. Undo Aksi Terakhir"<<endl;
		cout<<"7. Tampilkan Antrian"<<endl;
		cout<<"0. Program selesai"<<endl;
		cout<<"Pilih Menu: ";
		cin>>pilihMenu;
		cin.ignore();
		
		if(pilihMenu == 1 ) {
			cout<<"[ Tambah Lapangan ]"<<endl; 
			cout<<"Input Nama lapangan : ";
			getline(cin,namaInput);
			
			cout<<"Input Jenis Olahraga : ";
			getline(cin,olahragaInput);
			
			rootUtama = tambahLapangan(rootUtama,namaInput,olahragaInput);
			}
			
		if(pilihMenu == 2){
			if(rootUtama == NULL){
				cout<<"Belum ada data lapangan"<<endl;
				}
			else {
				tampilkanLapangan(rootUtama);
				}
			}
			
		if(pilihMenu == 3){
			cout<<"[ SEWA LAPANGAN ]"<<endl;
			
			cout<<"Masukan Nama Lapangan : ";
			getline(cin,namaLapangan);
			cout<<"Masukan Nama Tim Anda : ";
			getline(cin,namaTim);
			
			sewaLapangan(rootUtama,namaLapangan,namaTim);
			
			}
			
		if(pilihMenu == 4){
			cout<<"[ SELESAI LAPANGAN ]"<<endl;
			cout<<"Masukan nama lapangan : ";
			getline(cin,namaLapangan);
			
			selesaiLapangan(rootUtama, namaLapangan);
			}
			
		if(pilihMenu == 5) {
			cout<<"[ MENGHAPUS LAPANGAN ]"<<endl;
			cout<<"Masukan nama lapangan : ";
			getline(cin,namaLapangan);
			
			rootUtama = hapusLapangan(rootUtama,namaLapangan);
			}
			
		if(pilihMenu == 6){
			cout<<"[ UNDO AKTIVITAS ]"<<endl;
			undoAksi(rootUtama);
			}
			
		if(pilihMenu == 7){
			cout<<"[ TAMPILKAN ANTRIAN LAPANGAN ]"<<endl;
			cout<<"Masukan Nama Lapangan yang Ingin Dilihat: ";
			getline(cin, namaLapangan);
			
			tampilkanAntrian(rootUtama,namaLapangan);
			}
		
		if(pilihMenu == 0){
			cout<<"Terima Kasih! Keluar dari sistem Sport Center "<<endl;
			}
		}while(pilihMenu >= 1 && pilihMenu <=7);
	
	
	}

