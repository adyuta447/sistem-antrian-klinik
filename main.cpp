// Studi Kasus: Sistem Antrian Pasien di Klinik.
// Pasien dilayani berdasarkan FIFO, dengan dukungan prioritas untuk kondisi tertentu.
// Sistem menyediakan fitur undo pemanggilan terakhir menggunakan Stack.

// Fitur Utama:
// 1. Tambah pasien ke antrian (enqueue) dan input data pasien (ID, nama, poli, prioritas, status)
// 2. Panggil pasien berikutnya (dequeue) berdasarkan FIFO dan prioritas
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
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct Pasien {
    int id;
    string nama;
    string poli;
    int prioritas;   
    string status; 
};

struct ComparePriority {
    bool operator()(Pasien a, Pasien b) {
        return a.prioritas < b.prioritas;
    }
};

map<string, queue<Pasien>> antrianNormal;
map<string, priority_queue<Pasien, vector<Pasien>, ComparePriority>> antrianDarurat;

vector<Pasien> riwayat;
stack<Pasien> undoStack;
stack<Pasien> redoStack;

void tambahPasien() {
    Pasien p;
    cout << "Input ID pasien: ";
    cin >> p.id;
    cout << "Input nama pasien: ";
    cin >> p.nama;
    cout << "Input poli tujuan: ";
    cin >> p.poli;
    cout << "Input prioritas: ";
    cin >> p.prioritas;
    p.status = "menunggu";
    if (p.prioritas == 1) {
        antrianDarurat[p.poli].push(p);
    } else {
        antrianNormal[p.poli].push(p);
    }
    cout << "Pasien berhasil ditambahkan ke antrian." << endl;
}

void panggilPasien() {
    string poli;
    cout << "Masukkan poli ";
    cin >> poli;
    if (!antrianDarurat[poli].empty()) {
        Pasien p = antrianDarurat[poli].top();
        antrianDarurat[poli].pop();
        p.status = "dipanggil";
        riwayat.push_back(p);
        undoStack.push(p);
        cout << "Pasien prioritas darurat dipanggil: " << p.nama << endl;
    } else if (!antrianNormal[poli].empty()) {
        Pasien p = antrianNormal[poli].front();
        antrianNormal[poli].pop();
        p.status = "dipanggil";
        riwayat.push_back(p);
        undoStack.push(p);
        cout << "Pasien dipanggil: " << p.nama << endl;
    } else {
        cout << "Tidak ada pasien di antrian poli " << poli << endl;
    }
}

void undoPanggilan() {
    if (!undoStack.empty()) {
        Pasien p = undoStack.top();
        undoStack.pop();
        redoStack.push(p);
        p.status = "waiting";
        if (p.prioritas == 1) {
            antrianDarurat[p.poli].push(p);
        } else {
            antrianNormal[p.poli].push(p);
        }
        cout << "Panggilan pasien " << p.nama << " dibatalkan." << endl;
    } else {
        cout << "Tidak ada panggilan untuk dibatalkan." << endl;
    }
}

void tampilkanAntrian() {
    cout << "Antrian Pasien per Poli: " << endl;
    for (const auto& pair : antrianNormal) {
        cout << "Poli " << pair.first << ": ";
        queue<Pasien> q = pair.second;
        while (!q.empty()) {
            Pasien p = q.front();
            q.pop();
            cout << p.nama << " (Prioritas: " << p.prioritas << ", Status: " << p.status << ") | ";
        }
        cout << endl;   
    }
    for (const auto& pair : antrianDarurat) {
        cout << "Poli " << pair.first << " (Darurat): ";
        priority_queue<Pasien, vector<Pasien>, ComparePriority> pq = pair.second;
        while (!pq.empty()) {
            Pasien p = pq.top();
            pq.pop();
            cout << p.nama << " (Prioritas: " << p.prioritas << ", Status: " << p.status << ") | ";
        }
        cout << endl;   
    }
}

void cariPasien() {
    string key;
    cout << "Cari nama/ID: ";
    cin.ignore();
    getline(cin, key);

    for (auto &poli : antrianNormal) {
        queue<Pasien> q = poli.second;
        while (!q.empty()) {
            Pasien p = q.front();
            q.pop();
            if (p.nama == key || to_string(p.id) == key) {
                cout << "Ditemukan: " << p.nama << " di poli " << p.poli << endl;
                return;
            }
        }
    }

    cout << "Pasien tidak ditemukan.\n";
}

void tampilkanRiwayat() {
    cout << "Riwayat Panggilan Pasien: " << endl;
    for (const auto& p : riwayat) {
        cout << p.nama << " (ID: " << p.id << ", Poli: " << p.poli << ", Prioritas: " << p.prioritas << ", Status: " << p.status << ")" << endl;
    }
}

void clearScreen() {
    cout << "\033[2J\033[H";
}


int main() {
    int pilihan;
    do {
        cout << "Sistem Antrian Pasien di Klinik" << endl;
        cout << "Menu: " << endl;
        cout << "1. Tambah Pasien" << endl;
        cout << "2. Panggil Pasien" << endl;
        cout << "3. Undo Panggilan" << endl;
        cout << "4. Tampilkan Antrian" << endl;
        cout << "5. Cari Pasien" << endl;
        cout << "6. Tampilkan Riwayat Panggilan" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilih: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                clearScreen();
                tambahPasien();
                break;
            case 2:
                clearScreen();
                panggilPasien();
                break;
            case 3:
                clearScreen();
                undoPanggilan();
                break;
            case 4:
                clearScreen();
                tampilkanAntrian();
                break;
            case 5:
                clearScreen();
                cariPasien();
                break;
            case 6:
                clearScreen();
                tampilkanRiwayat();
                break;
            case 0:
                cout << "Keluar dari program." << endl;
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
        }
    } while (pilihan != 0);

    return 0;
}
