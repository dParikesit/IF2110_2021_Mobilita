# Mobita and The Legend Of Alstrokedeath
Permainan untuk menolong mobita agar kita lulus mata kuliah Alstrukdat.
> Tugas Besar IF2110 Algoritma Struktur Data <br /> Mobita <br /> Semester Ganjil 2021/2022

Dibuat oleh Kelompok 11 K02
- Muhammad Fahkry Malta	13519032
- Raden Haryosatyo Wisjnunandono	13520070
- Dimas Shidqi Parikesit	13520087
- Amar Fadil	13520103
- Malik Akbar Hashemi Rafsanjani	13520105

## Deskripsi Singkat Program
Dengan adanya pandemi COVID-19, usaha orang tua Mobita mengalami penurunan pendapatan. 
Setelah diringankannya PPKM, Mobita ingin membantu orang tuanya mendapat penghasilan 
menjadi seorang kurir. Tugas kalian adalah membantu Mobita membuatkan aplikasi yang akan 
membantunya melacak pesanan, navigasi peta, mengambil dan menurunkan barang.
Buatlah sebuah permainan berbasis CLI (command-line interface) tentang pengantaran barang. 
Permainan ini dibuat dalam bahasa C dengan menggunakan struktur data yang sudah kalian 
pelajari di mata kuliah ini. Kalian boleh menggunakan struktur data yang sudah kalian buat 
untuk praktikum pada tugas besar ini.


## UML Diagram
![UML Diagram](assets/uml-diagram.png)

## Directory Structure
```
├───src                     [Source file root]
│   ├───adt                 [ADT Files]
│   │   ├───list            [ADT List Statis]
│   │   ├───listdin         [ADT List Dinamis]
│   │   ├───listlinked      [ADT Linked List]
│   │   ├───machine         [ADT Word Machine]
│   │   ├───matrix          [ADT Matrix]
│   │   ├───point           [ADT Point]
│   │   ├───queue           [ADT Queue]
│   │   └───stack           [ADT Stack]
│   ├───core                [Core Files]
│   │   ├───command         [Command Module]
│   │   ├───gameplay        [Gameplay Module]
│   │   └───main            [Main Program]
│   ├───helper              [Helper Files]
│   │   ├───pcolor          [Print Color Module]
│   │   └───stream          [File I/O Module]
│   ├───include             [Include Headers]
│   ├───object              [Object Files]
│   │   ├───ability         [Ability Object]
│   │   ├───building        [Building Object]
│   │   ├───gadget          [Gadget Object]
│   │   └───item            [Item Object]
│   └───system              [System Files]
│       ├───gamemanager     [Game Manager System]
│       ├───map             [Map System]
│       ├───stats           [Stats System]
│       └───time            [Time System]
└───test                    [Data Test]
```

## Build
### 1. Requirement
Pastikan dependency berikut terpenuhi sebelum melakukan build program:
- CMake >= 3.6
- Make
- GNU C Compiler (untuk Windows, pastikan untuk memakai GCC dari MinGW)
### 2. Step
- Windows: Jalankan script `build.bat`.
    ```
    build.bat
    ```
- Linux/Bash: Jalankan script `build.sh`.
    ```
    ./build.sh
    ```
Binary akan berada di dalam folder `build/bin` setelah menjalankan script.

## Usage
- Jalankan file `main` (atau `main.exe` pada Windows) pada directory `build/bin` setelah melakukan build.

- Load (`LOAD_GAME`) atau new game (`NEW_GAME`) untuk memulai permainan.

    > Kamu dapat memakai konfigurasi level default pada `test/config.txt` dengan input nama file konfigurasi `../../test/cofig.txt` (asumsi binary berada pada `build/bin` dan test berada pada `test`) setelah memasukkan command `NEW_GAME`.

- Lihat daftar command yang tersedia dengan input command `HELP`.

- Untuk keluar dari permainan, masukkan command `EXIT` dan masukkan `Y` untuk konfirmasi keluar dari permainan.

## Pembagian Tugas
| Anggota Kelompok | Tugas yang Dikerjakan |
| ---------------- | --------------------- |
| Amar Fadil | ADT Mesin Kata - Mesin Karakter, Helper Stream, ADT Queue, System GameManager, System Stats |
| Dimas Shidqi Parikesit | ADT Point, ADT Linked List, Objec Item, ADT Gadget |
| Malik Akbar Hashemi R. | ADT ListDin, ADT Map, Core Command |
| Raden Haryosatyo Wisjnunandono | Core Gameplay, System Time, ADT Matrix |
| Muhammad Fahkry Malta | ADT List, ADT Stack, Object Ability, Object Building |

## Daftar Fitur
- [x] New Game
- [x] Exit
- [x] Help
- [x] Load Game [Bonus]
- [x] Move
- [x] Pick Up
- [x] Drop Off
- [x] Map
- [x] To Do
- [x] In Progress
- [x] Buy
- [x] Inventory
- [x] Save Game [Bonus]
- [x] Return [Bonus]
- [x] Status [Addition]
- [x] VIP Item [Bonus]
- [x] Senter Pengecil [Bonus]
>   Note:
>   - [x] = Selesai
>   - [ ] = Tidak Selesai