# Project_Algo_137_154
Tugas Project Alogritma dan Struktur Data

Sistem Manajemen Antrian Klinik Sederhana (C++11)
Aplikasi berbasis CLI (Command Line Interface) untuk mengelola antrian dan riwayat pasien di klinik. Program ini dirancang menggunakan bahasa C++11 dengan menerapkan struktur data Doubly Linked List untuk manajemen memori dinamis (runtime) dan sistem File Handling untuk penyimpanan data yang persisten.

🚀 Fitur Utama
Pendaftaran Pasien Dinamis: Menambahkan pasien ke dalam antrian berbasis Doubly Linked List (RAM) dan otomatis mencadangkannya ke file teks (DataPasien.txt).

Sistem Antrian Otomatis (FIFO): Memproses pasien satu per satu berdasarkan siapa yang datang lebih dulu. Status pasien otomatis berubah menjadi "Sudah Dilayani" baik di memori maupun di dalam berkas database.

Pemuatan Ulang Data (Auto-Reload): Saat program dibuka kembali, sistem otomatis memisahkan pasien yang belum dilayani untuk dimasukkan kembali ke antrian aktif, sementara nomor antrian terakhir akan dilanjutkan secara otomatis.

Urutkan Riwayat Berdasarkan Tanggal: Menampilkan seluruh riwayat pasien yang terdaftar secara kronologis menggunakan algoritma Bubble Sort manual.

Pencarian & Penghapusan Fleksibel: Mencari data pasien secara instan atau menghapus riwayat pasien tertentu langsung dari file database menggunakan nomor tiket.

🛠️ Spesifikasi & Spesifikasi Teknis
Bahasa Pemrograman: C++ (Standar C++11)

Library Standar (Tanpa Dependency Eksternal):

– Untuk interaksi input/output CLI.

– Untuk operasi Stream berkas (membaca, menulis, dan memperbarui database DataPasien.txt).

– Untuk manipulasi teks dan ekstraksi token/kolom menggunakan metode std::string::find dan std::string::substr.

Struktur Data: Doubly Linked List (Node* next dan Node* prev) untuk mempermudah operasi penambahan dan penghapusan antrian di baris paling depan (operasi Queue).

📂 Format Penyimpanan Database (DataPasien.txt)
Data disimpan dengan format flat-file menggunakan pembatas (delimiter) tagar (#), yang distrukturkan sebagai berikut:
