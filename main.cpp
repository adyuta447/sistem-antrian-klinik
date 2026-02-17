// Studi Kasus: Sistem Antrian Pasien di Klinik.
// Pasien dilayani berdasarkan FIFO, dengan dukungan prioritas untuk kondisi tertentu.
// Sistem menyediakan fitur undo pemanggilan terakhir menggunakan Stack.

// Fitur Utama:
// 1. Tambah pasien ke antrian (enqueue)
// 2. Panggil pasien berikutnya (dequeue)
// 3. Undo pemanggilan terakhir (stack)
// 4. Tampilkan isi antrian & riwayat panggilan

// Fitur Tambahan:
// 5. Setiap pasien memiliki data lengkap (ID, nama, poli, prioritas, dan status)
// 6. Sistem mendukung antrian berdasarkan poli/dokter (multi-queue)
// 7. Pasien dengan prioritas darurat akan dipanggil lebih dulu (priority queue + FIFO)
// 8. Tersedia status pasien: menunggu, dipanggil, sedang dilayani, selesai, tidak hadir
// 9. Tersedia fitur skip pasien jika tidak hadir
// 10. Tersedia fitur redo pemanggilan setelah undo
// 11. Tersedia fitur pencarian dan penghapusan pasien berdasarkan ID atau nama
// 12. Sistem menyimpan riwayat pemanggilan pasien (log aktivitas)
// 13. Data antrian dapat disimpan ke file agar tidak hilang saat program ditutup
#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <string>

using namespace std;

struct Pasien {
    int id;
    string nama;
    string poli;
    int prioritas;
    string status;
};



