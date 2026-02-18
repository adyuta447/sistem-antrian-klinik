#include <iostream>
#include <queue>
#include <stack>
#include <string>
using namespace std;

struct pasien
{
    string nama;
    int umur;

};

queue<pasien> antrian;
stack<pasien> riwayat;

void enqueue ()
{
    pasien p;
    cout << "Masukan Nama Pasien: ";
    cin >> p.nama;
    cout << "\nPasien dengan Nama " << p.nama << " Telah Masuk Antrian\n\n";
    antrian.push(p);
}

void dequeue ()
{
    if (antrian.empty())
    {
        cout << "Antrian Kosong\n\n";
    }

    pasien p = antrian.front();
    antrian.pop();
    riwayat.push(p);
    cout << "Memanggil Pasien dengan Nama " << p.nama << "\n\n";
}

void view_antrian ()
{
    if (antrian.empty())
    {
        cout << "Antrian Kosong\n\n";
    }

    queue<pasien> temp = antrian;
    while (!temp.empty())
    {
        cout << "-"  << temp.front().nama << "\n\n";
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
    while (!temp.empty())
    {
        cout << "-" << temp.top().nama << "\n\n";
        temp.pop();
    }
}

void undo()
{
    if (riwayat.empty())
    {
        cout << "Riwayat Kosong \n\n";
    }

    queue<pasien> temp = antrian;
    pasien p = riwayat.top();
    antrian.push(p);

    cout << "Pasien " << temp.back().nama << "Telah Ditambahkan ke Antrian\n\n";
}

void clearScreen() {
    cout << "\033[2J\033[H";
}


int main ()
{
    int pilihan;

    do
    {
        cout << "    PILIH MENU    \n";
        cout << "1.Tambah Pasien\n";
        cout << "2.Panggil Pasien\n";
        cout << "3.Tampilakan Antrian\n";
        cout << "4.Tampilkan Riwayat\n";
        cout << "5.Undo\n";
        cout << "0.Exit\n\n";
        cout << "Masukan Pilihan: ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
        clearScreen();
            enqueue();
            break;
        case 2:
        clearScreen();
            dequeue();
            break;
        case 3:
        clearScreen();
            view_antrian();
            break;
        case 4:
        clearScreen();
            view_riwayat();
            break;
        case 5:
        clearScreen();
            undo();
            break;
        default:
            cout << "Opsi yang Anda Masukan Salah";
            break;
        }
    } while (pilihan != 0);
}
