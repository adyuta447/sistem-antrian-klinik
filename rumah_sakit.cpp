#include <iostream>
#include <queue>
#include <stack>
#include <string>
using namespace std;

struct pasien
{
    int id;
    string nama;
    int umur;
    string keluhan;

};

void clearScreen() {
    cout << "\033[2J\033[H";
}

void pause() {
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

queue<pasien> antrian;
stack<pasien> riwayat;

void enqueue () {
    pasien p;
    while (true) {
        cout << "ID Pasien: ";
        cin >> p.id;

        if(!cin.fail() && p.id > 0) {
            break;
        }
        cout << "Input salah! ID harus angka positif" << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        clearScreen();
    }

    cin.ignore();
    cout << "Masukan Nama Pasien: ";
    cin.ignore();
    getline(cin, p.nama);
    while (true) {
    cout << "Umur: ";
    cin >> p.umur;

    if(!cin.fail() && p.id > 0) {
        break;
    }
    cout << "Input salah! ID harus angka positif" << endl;
    cin.clear();
    cin.ignore(1000, '\n');
    }
    
    cout << "Keluhan: ";
    cin.ignore();
    getline(cin, p.keluhan);
    cout << "\nPasien dengan Nama " << p.nama << " Telah Masuk Antrian\n\n";
    antrian.push(p);
}

void dequeue ()
{
    if(antrian.empty()) {
        cout << "Antrian Kosong\n\n";
        return;
    }

    pasien p = antrian.front();
    antrian.pop();
    riwayat.push(p);
    cout << "Memanggil Pasien dengan Nama " << p.nama << "\n\n";
}

void view_antrian ()
{
    if (antrian.empty()) {
        cout << "Antrian Kosong\n\n";
    }

    queue<pasien> temp = antrian;
            cout << "No" << " | " << "Nama" << " | " << "Umur" << " | " << "Keluhan" << "|" << endl;
    while (!temp.empty())
    {
        cout << temp.front().id << " | " << temp.front().nama << " | " << temp.front().umur << " | " << temp.front().keluhan << "\n\n";
        temp.pop();
    }
}

void view_riwayat()
{
    if (riwayat.empty())
    {
        cout << "Riwayat Kosong\n\n";
    }

    stack<pasien> temp = riwayat;
    cout << "No" << " | " << "Nama" << " | " << "Umur" << " | " << "Keluhan" << " | " << endl;
    while (!temp.empty())
    {
        cout << temp.top().id << " | " << temp.top().nama << " | " << temp.top().umur << " | " << temp.top().keluhan << endl;
        temp.pop();
    }
}

void undo()
{
    if (riwayat.empty())
    {
        cout << "Riwayat Kosong\n\n";
        return;
    }
    pasien p = riwayat.top();
    riwayat.pop();            
    antrian.push(p);          
    cout << "Pasien " << p.nama << " berhasil dikembalikan ke antrian\n\n";
}


int main ()
{
    int pilihan;
    clearScreen();

    do
    {
        cout << "Sistem Administrasi Klinik Suka Maju Mundur 67" << endl;
        cout << "Choose Menu: " << endl;
        cout << "> 1.Added Patient" << endl;
        cout << "> 2.Called Patient" << endl;
        cout << "> 3.Shows Queue" << endl;
        cout << "> 4.Shows History" << endl;
        cout << "> 5.Undo\n";
        cout << "> 0.Exit\n\n";
        cout << "Masukan Pilihan > ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            clearScreen();
            enqueue();
            pause();
            clearScreen();
            break;
        case 2:
            clearScreen();
            dequeue();
            pause();
            clearScreen();
            break;
        case 3:
            clearScreen();
            view_antrian();
            pause();
            clearScreen();
            break;
        case 4:
            clearScreen();
            view_riwayat();
            pause();
            clearScreen();
            break;
        case 5:
            clearScreen();
            undo();
            pause();
            clearScreen();
            break;
        default:
            cout << "Opsi yang Anda Masukan Salah";
            break;
        }
    } while (pilihan != 0);
    return 0;
}
