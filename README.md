# Explain This Code (main.cpp)

```cpp
#include <iostream>
#include <queue>
#include <stack>
#include <string>
using namespace std;
```

Ini hanya package/modul yang akan digunakan di program cpp digunakan sesuai sama kebutuhan.

### 1. `#include <iostream>`

Ini untuk **input dan output standar**.

Tanpa ini, kamu tidak bisa pakai:

```cpp
cout
cin
endl
```

Kalau `iostream` dihapus = program error.

### 2. `#include <queue>`

Ini untuk struktur data **Queue (antrian)** = FIFO (First In First Out).

Artinya:
yang masuk duluan, keluar duluan.

Contoh penggunaan:

```cpp
queue<int> q;
// Menambah data ke antrian (belakang)
q.push();
// Menghapus data dari depan antrian (org pertama dilayani & keluar)
q.pop();
// Melihat data paling depan(yang akan keluar duluan)
q.front();
// Kebalikan dr front (yang terakhir masuk)
q.back();

```

Biasanya dipakai untuk:

- sistem antrian pasien
- printer queue
- task scheduling

### 3. `#include <stack>`

Ini untuk struktur data **Stack (tumpukan)** = LIFO (Last In First Out).

Yang masuk terakhir, keluar duluan.

Contoh:

```cpp
stack<int> s;
// Nambah data ke atas tumpukan
s.push();
// Hapus data paling atas (terakhir masuk)
s.pop();
// Melihat data paling atas tanpa dihapus
s.top();
// Menghapus
s.empy();
// Jumlah Elemen
s.size();
```

Dipakai untuk:

- undo / redo
- history browser
- backtracking
- evaluasi ekspresi

```cpp
struct pasien {
    int id;
    string nama;
    int umur;
    string keluhan;
};
```

Mendefinisikan struktur data bernama `pasien` untuk menyimpan informasi satu orang pasien. Jadi artinya:

- id = identitas pasien tipenya `int`
- nama = nama pasien tipenya `string`
- umur = umur pasien tipenya `int`
- keluhan = keluhan penyakit pasien tipenya `string`

Pasien adalah tipe data baru yang menegelompokkan beberapa data berbeda dalam satu objek.

### 4. `clearScreen()`

```cpp
void clearScreen() {
    cout << "\033[2J\033[H";
}
```

Memiliki fungsi untuk clear terminal menggunakan ANSI escape code.

### 5. `pause()`

```cpp
void pause() {
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}
```

Fungsi mengghentikan program sementara sampai si user menekan enter.

- `cin.ignore` = membuang karakter sisa di input
- `cin.get()` = menunggu user menekan enter

Ini dipakai agar output tidak langsung hilang sebelum user membaca.

### 6. Queque & Stack

```cpp
queue<pasien> antrian;
stack<pasien> riwayat;
```

Kode yang mendeklarasikan dua struktur data untuk mengelola data dengan tipe `pasien`

```cpp
queue<pasien> antrian;
```

memiliki arti membuat antrian pasien(FIFO).

- `queue` struktur data antrian
- `<pasien>` setiap elemen di dalam queque bertipe `pasien`.
- `antrian` nama variabelnya

Artinya menyimpan pasien tang menunggu giliran dipanggil

```cpp
stack<pasien> riwayat;
```

membuat stack pasien (LIFO).

- `stack` struktur data tumpukan
- `<pasien>` setiap elemen bertipe `pasien`
- `riwayat` nama variabelnya

Artinya menyimpan riwayat pasien yang sudah dipanggil

Simplenya:

- antrian = siapa yang belum dilayani
- riwayat = siapa yang sudah dilayani

### 7. void enqueue()

```cpp
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

```

`pasien p` sebagai tempat sementara untuk menambung pasien sebelum dimasukkan ke antrian.

jadi ada validasi input

```cpp
while (true) {
    cin >> p.id;
    if(!cin.fail() && p.id > 0) break;
}
```

memastikan id itu adalah harus angka positif, jika salah input maka di ulang, `cin.clear()` dan `cin.ignore()` untuk membersihkan error input.

```cpp
getline(cin, p.nama);
```

Fungsinya agar bisa membaca nama lengkap di satu line.

```cpp
cin.ignore(1000, '\n');
```

Artinya membuat max 1000 karakter sampai bertemu enter, kalo dia inputnya salah.

### 8. void dequeue()

```cpp
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

```

Fungsi tersebut memiliki kondisi dimana jika tidak ada pasien, tampilkan pesan dan hentikan fungsi agak tidak ada error. kemudian mengambil pasien yang pertama masuk antrian(FIFO). mengeluarkan pasien tersebut dari queue. Kemudian ditambah/disimpan ke stack `riwayat` untuk keperluan undo pemanggilan terakhir (LIFO)

### 9. void view_antrian()

```cpp
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
```

Kalau tidak ada pasien, tampilkan pesan anttrian kosong. dan membuat copyan antrian ke variabel `temp` supaya bisa dibaca dengan `pop()` tanpa merusak antrian asli. Kemudian membuat looping mengambil pasien dari paling depan dari `temp`(`front()`), menampilkan data pasien(id, nama, umur, keluhan) kemudian menghapus pasien dari `temp(pop)`, mengulang sampai `temp` kosong.

### 10. void view_riwayat()

```cpp
void view_riwayat()
{
    if (riwayat.empty())
    {
        cout << "Riwayat Kosong\n\n";
        return;
    }

    stack<pasien> temp = riwayat;
    cout << "No" << " | " << "Nama" << " | " << "Umur" << " | " << "Keluhan" << " | " << endl;
    while (!temp.empty()) {
        cout << temp.top().id << " | " << temp.top().nama << " | " << temp.top().umur << " | " << temp.top().keluhan << endl;
        temp.pop();
    }
}
```

jika stack `riwayat` kosong, maka tampilkan pesan dan hentikan fungsi agar tidak lanjut menampilkan data. Kemudian membuat salinan supaya bisa ditampilkan dengan `pop()` tanpa menghapus data asli di `riwayat`.

```cpp
stack<pasien> temp = riwayat;
```

```cpp
while (!temp.empty())
{
    cout << temp.top().id << " | "
         << temp.top().nama << " | "
         << temp.top().umur << " | "
         << temp.top().keluhan << endl;
    temp.pop();
}
```

Looping menampilkan isi riwayat. Jika data tidak kosong maka tampilkan. `top()` mengambil pasien terakhir yang dipanggil (LIFO), `pop()` menghapus dari `temp` kemudian diulang sampai `temp` kosong.

### 11. void undo()

```cpp
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
```

Memiliki kondisi jika tidak ada pasien di riwayat (belum pernah panggil pasien), tampilkan pesan riwayat kosong, dan kembalikan agar tidak error. kemudian

```cpp
    pasien p = riwayat.top();
```

mengambil pasien yang terakhir dipanggil. dan mengeluarkan pasien tersebut dari stack riwayat.

```cpp
riwayat.pop();
```

kemudian mengembalikan pasien ke queue antrian.

```cpp
antrian.push(p);

```
