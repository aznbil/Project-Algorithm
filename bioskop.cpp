#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

struct bioskop {
    string judul;
    string genre;
    int durasi; // dalam menit
    float rating;
};

const int max_film = 100;
bioskop film[max_film];
int dataYgDiinput = 0, index = 0;
string cari;
void menu(), ubahkapital(string& str), searching(), input(), bubble_sort_desc(), tampilkanData(int index), bubble_sort_asdc(), sorting(), fileopen(int index) ;


int main() {  
    ifstream myfile;
    myfile.open("tampilkandata");
    myfile >> dataYgDiinput;
    myfile.close();
    menu();
    
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
        cout << "4. Searching\n";
        cout << "5. Exit\n";
        cout << "Masukkan Pilihan: ";
        cin >> pilih;

        switch (pilih) {
            case 1:
                system("cls");
                input();
                break;
            case 2:
                system("cls");
                tampilkanData(index);
                break;
            case 3:
                system("cls");
                sorting();
                break;
            case 4:
                searching();
                break;
            case 5:
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

void searching(){
    cin.ignore();
    cout<<"Masukan Judul Film yang ingin anda cari : ";
    getline(cin, cari);
    ubahkapital(cari);
    int i = 0;
    bool ketemu = false ;

    while( !ketemu ){
        if(cari==film[i].judul)ketemu = true;
        if(i = dataYgDiinput)break;
        else i++;
    }
    if( ketemu )tampilkanData(index);
    else cout<<"Film yang anda cari tidak di temukan"<<endl;
    
}

void input() {
    int jumlahData;
    cout << "Masukan Banyak Data Yang Ingin Di Inputkan : ";
    cin >> jumlahData;

    if (jumlahData < 1) {
        cout << "Input tidak valid" << endl;
        return;
    }
    if (dataYgDiinput + jumlahData > max_film) {
        cout << "Input melebihi batas" << endl;
        return;
    }
    ofstream data; 
    data.open("databioskop",ios::app ); 
    
    for (int i = 0; i < jumlahData ; i++) {
        cout << "Masukkan data ke-" << i + 1 << ":\n";
        cin.ignore();
        cout << "Judul Film\t: ";
        getline(cin, film[dataYgDiinput].judul);
        ubahkapital(film[dataYgDiinput].judul);
        data << film[dataYgDiinput].judul;
        data << endl;
        cout << "Genre Film\t: ";
        getline(cin, film[dataYgDiinput].genre);
        data << film[dataYgDiinput].genre;
        data << endl;
        cout << "Durasi (menit)\t: ";
        cin >> film[dataYgDiinput].durasi;
        data << film[dataYgDiinput].durasi;
        data << endl;
        cout << "Rating Film\t: ";
        cin >> film[dataYgDiinput].rating;
        data << film[dataYgDiinput].rating;
        data << endl;
        cout << "-----------------------" << endl;
        cout << endl;
        ofstream myfile;
        myfile.open("tampilkandata", ios::trunc);
        dataYgDiinput ++;
        myfile << dataYgDiinput;
        myfile.close();
    }
    data.close();
    
}

//menggunakan pemanggilan rekursif

void tampilkanData(int index) {
    if (dataYgDiinput == 0) {
        cout << "Belum ada data yang dimasukkan.\n";
        return;
    }
    

    if (index == 0) {
        ifstream data("databioskop");
        if(!data){
        cout << "Gagal open file\n";
        return;
        }
        for(int i = 0; i < dataYgDiinput; i++){
        getline(data, film[i].judul);
        getline(data, film[i].genre);
        data >> film[i].durasi;
        data >> film[i].rating;
        data.ignore();
        }
        data.close();
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
                tampilkanData(index);
                break;
            case 2:
                system("cls");
                bubble_sort_asdc();
                cout << "Data setelah sorting:\n";
                tampilkanData(index);
                break;
            case 3:
                // cout << "Terima Kasih\n";
                break;
            default:
                cout << "Pilihan salah, coba lagi.\n";
        }
        cout << "Ingin melanjutkan? (y/n): ";
        cin >> jawab;
    } while (jawab == 'y' || jawab == 'Y');
}



void ubahkapital(string& str) {
    for (char& c : str) {
        c = toupper(c);
    }
}