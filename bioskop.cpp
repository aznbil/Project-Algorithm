#include <iostream>
using namespace std;

struct bioskop {
    string judul;
    string genre;
    int durasi; // dalam menit
    float rating;
};

const int max_film = 100;
bioskop film[max_film];
int dataYgDiinput = 0;

void input() {
    int jumlahDataBaru;
    cout << "Berapa data yang ingin diinput? ";
    cin >> jumlahDataBaru;

    if (jumlahDataBaru < 1) {
        cout << "Input tidak valid" << endl;
        return;
    }
    if (dataYgDiinput + jumlahDataBaru > max_film) {
        cout << "Input melebihi batas" << endl;
        return;
    }

    for (int i = dataYgDiinput; i < dataYgDiinput + jumlahDataBaru; i++) {
        cout << "Masukkan data ke-" << i + 1 << ":\n";
        cin.ignore();
        cout << "Judul Film\t: ";
        getline(cin, film[i].judul);
        cout << "Genre Film\t: ";
        getline(cin, film[i].genre);
        cout << "Durasi (menit)\t: ";
        cin >> film[i].durasi;
        cout << "Rating Film\t: ";
        cin >> film[i].rating;
        cout << "-----------------------" << endl;
        cout << endl;
    }
    dataYgDiinput += jumlahDataBaru;
}

//menggunakan pemanggilan rekursif
void tampilkanData(int index = 0) {
    if (dataYgDiinput == 0) {
        cout << "Belum ada data yang dimasukkan.\n";
        return;
    }
    
    if (index == 0) {
        cout << "Data Film:\n";
    }

    // Basis Rekursi: Jika index sudah mencapai jumlah data yang diinput, berhenti
    if (index >= dataYgDiinput) {
        return;
    }

    // Menampilkan data film pada index saat ini
    cout << "\nJudul Film\t: " << film[index].judul << endl;
    cout << "Genre Film\t: " << film[index].genre << endl;
    cout << "Durasi (menit)\t: " << film[index].durasi << " menit" << endl;
    cout << "Rating Film\t: " << film[index].rating << endl;
    cout << "-----------------------" << endl;
    cout << endl;

    // Panggil fungsi untuk menampilkan data selanjutnya (rekursif)
    tampilkanData(index + 1);
}


void bubble_sort_desc() {
    for (int i = 0; i < dataYgDiinput - 1; i++) {
        for (int j = 0; j < dataYgDiinput - i - 1; j++) {
            if (film[j].rating < film[j + 1].rating) { // Urutkan dari terbesar ke terkecil
                swap(film[j], film[j + 1]);
            }
        }
    }
}

void bubble_sort_asdc() {
    for (int i = 0; i < dataYgDiinput - 1; i++) {
        for (int j = 0; j < dataYgDiinput - i - 1; j++) {
            if (film[j].rating > film[j + 1].rating) { // Urutkan terkecil ke terbesar
                swap(film[j], film[j + 1]);
            }
        }
    }
}

void sorting() {
    int pilih;
    char jawab;
    do{
        system("cls");
        cout << "\nMenu:\n";
        cout << "1. Bubble Sort DESC(Berdasarkan Rating)\n";
        cout << "2. Bubble Sort ASDC(Berdasarkan Rating)\n";
        cout << "3. Exit\n";
        cout << "Masukkan Pilihan: ";
        cin >> pilih;

        switch (pilih) {
            case 1:
                system("cls");
                bubble_sort_desc();
                cout << "Data setelah sorting:\n";
                tampilkanData();
                break;
            case 2:
                system("cls");
                bubble_sort_asdc();
                cout << "Data setelah sorting:\n";
                tampilkanData();
                break;
            case 3:
                cout << "Terima Kasih\n";
                exit(0);
                break;
            default:
                cout << "Pilihan salah, coba lagi.\n";
        }
        cout << "Ingin melanjutkan? (y/n): ";
        cin >> jawab;
    } while (jawab == 'y' || jawab == 'Y');
}

void menu() {
    int pilih;
    char jawab;
    do {
        system("cls");
        cout << "\nMenu:\n";
        cout << "1. Input Data\n";
        cout << "2. Tampilkan Data\n";
        cout << "3. Sorting Data\n";
        cout << "4. Exit\n";
        cout << "Masukkan Pilihan: ";
        cin >> pilih;

        switch (pilih) {
            case 1:
                system("cls");
                input();
                break;
            case 2:
                system("cls");
                tampilkanData();
                break;
            case 3:
                system("cls");
                sorting();
                break;
            case 4:
                cout << "Terima Kasih\n";
                exit(0);
                break;
            default:
                cout << "Pilihan salah, coba lagi.\n";
        }
        cout << "Ingin kembali ke menu utama? (y/n): ";
        cin >> jawab;
    } while (jawab == 'y' || jawab == 'Y');
}

int main() {
    menu();
}
