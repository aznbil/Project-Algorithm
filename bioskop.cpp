#include <iostream>
#include <cstring>
#include <fstream>
#include <ctime>
using namespace std;

//ANGGOTA KELOMPOK 
//Nama: M.Ahsan R.S (123240246)
//Nama: Aziz Nabil Putra Darmawan (123240239)
//Nama: Kevin Prasetya (123240231)


struct bioskop {
    string judul;
    string genre;
    int durasi; // dalam menit
    float rating;
};

const int max_film = 100;
bioskop film[max_film];
int dataYgDiinput = 0, index = 0;
string cari, username, password;
void menu(), ubahkapital(string& str), searching(), input(), bubble_sort_desc(), tampilkanData(bioskop* film, int index), bubble_sort_asdc(), sorting(), fileopen(int index) ;
void buat_akun(), login(), loginpage(), menu_user(), menu_admin(), beli(), riwayat_pembelian();

int main() {  
    ifstream myfile;
    myfile.open("tampilkandata");
    myfile >> dataYgDiinput;
    myfile.close();
    loginpage();  
}

void loginpage(){
    int pilih;
    system("cls");
    
    cout<<"1. Login"<<endl;
    cout<<"2. Buat Akun"<<endl;
    cout<<"======================="<<endl;
    cout<<"Apa yang ingin anda lakukan : ";
    cin>>pilih;
    switch(pilih){
        case 1 : 
            login();
            break;
        case 2 :
            buat_akun();
            break;
        default : 
            cout << "Input tidak tersedia" << endl;
            system("pause");
            break;
    }
}

void login(){
    system("cls");
    string usernamesementara, passwordsementara, verifikasiusername, verifikasipassword, verifikasiperan;
    bool berhasil;
    berhasil = false;
    for(int i = 2 ; i >= 0 ; i--){
        ifstream login;
        login.open("akun.txt");
        cout<<"Masukan Username anda \t: ";
        cin>>username;
        cout<<"Masukan Password anda \t: ";
        cin>>password;
        while(!login.eof()){
            login >> verifikasiusername;
            login >> verifikasipassword;
            login >> verifikasiperan;
            if((verifikasiusername == username) && (verifikasipassword == password)){
                cout<<endl<<"anda berhasil login"<<endl<<endl;
                berhasil = true;
                system("pause");
                break;
            }
        }
        if((i == 0) && (!berhasil)){
            cout<<"Kesempatan Login anda Habis, Silahkan Coba Kembali Lain Kali"<<endl;
            exit(0);
        }else if(!berhasil){
            cout<<"Username atau Password anda salah"<<endl;
            cout<<"Anda Masih memiliki "<< i <<" kesempatan lagi"<<endl;
            cout<<"Silahkan mengisi kembali"<<endl;
            cout<<endl;
            system("pause");
        }
         if (berhasil){
            break;
        }
        login.close();
    }
    if(verifikasiperan == "user")menu_user();
    else if(verifikasiperan == "admin")menu_admin();
}

void menu_admin() {
    int pilih;
    char jawab;
    system("cls");
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
                tampilkanData(film, index);
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

void menu_user(){
    int pilih;
    system("cls");
    cout << "1. Beli " << endl;
    cout << "2. Riwayat Pembelian" << endl;
    cout << "3. Keluar " << endl;
    cout << "Pilih : " ;
    cin >> pilih;
    switch(pilih){
        case 1 : 
            beli();
            break;
        case 2 :
            riwayat_pembelian();
            break;
        case 3 : 
            return;
            break;
        default :
            cout << "Input tidak tersedia" << endl;
            break;
    }
}

void beli(){
    system("cls");
    int banyak,jumlah=0;
    char konfirmasi;
    bool check=false;
    string nama;
    // Ambil hari saat ini
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int hari = ltm->tm_wday; // 0 = Minggu, 1 = Senin, ..., 6 = Sabtu
    // strftime(output,50,"%A");
    // Menentukan apakah weekday atau weekend
    bool isWeekend;
    int harga_tiket;
    string hari_str;
    if (hari == 0 || hari == 6) {
        isWeekend = true;
        harga_tiket = 50000;
        hari_str = "Weekend";
    } else {
        isWeekend = false;
        harga_tiket = 32000;
        hari_str = "Weekday";
    }
    do{
        system("cls");
        // ifstream beli;
        // beli.open("databioskop");
        tampilkanData(film, index);
        cout<<endl;
        cout <<"Hari ini adalah   : " << hari_str << endl;
        cout<<"Masukkan nama Film : ";
        cin>>nama;
        ubahkapital(nama);
        for(int i=0 ; i<dataYgDiinput ; i++){
            // beli >> film[i].judul;
            if((film[i].judul != nama ) && (i==dataYgDiinput)){
                cout<<"Barang yang anda pilih tidak ada di etalase"<<endl;
                cout<<"Silahkan pilih kembali"<<endl;
                system("pause");
                break;
            }else if(film[i].judul == nama){
                    system("cls");
                    cout<<"Ada perbedaan harga untuk weekday and weekend"<<endl;
                    cout<<"Weekday = Rp.32000"<<endl;
                    cout<<"Weekend = Rp.50000"<<endl;
                    cout<<"======================Ticket======================"<<endl;
                    cout<<"Judul \t: "<<film[i].judul<<endl;
                    cout<<"Genre \t: "<<film[i].genre <<endl;
                    cout<<"Durasi\t: "<<film[i].durasi<<endl;
                    cout<<"Harga \t: "<<harga_tiket<<endl;
                    cout<<"==================================================="<<endl;
                    cout<<"Masukan Jumlah Tiket Yang Ingin Di Beli : ";
                    cin>>banyak;
                    jumlah = harga_tiket*banyak;
                    system("cls");
                    cout<<"======================Ticket======================"<<endl;
                    cout<<"Judul \t: "<<film[i].judul<<endl;
                    cout<<"Genre \t: "<<film[i].genre <<endl;
                    cout<<"Durasi\t: "<<film[i].durasi<<endl;
                    cout<<"Harga \t: "<<harga_tiket<<endl;
                    cout<<"==================================================="<<endl;
                    cout<<"Jumlah Yang Harus Anda Bayar : "<< "Rp." <<jumlah<<endl;   
                    cout<<"Konfirmasi Pembelian ? (Y/N) : ";
                    cin>>konfirmasi;
                    konfirmasi = toupper(konfirmasi);
                    if(konfirmasi == 'Y'){
                        cout<<"Silahkan Menikmati :)"<<endl;
                        cout<<"Terima Kasih"<<endl;
                        system("pause");
                        ofstream riyawat("struk_pembelian"+username+".txt", ios::app);
                        riyawat << film[i].judul <<" "<< film[i].genre <<" "<< film[i].durasi<<" "<<banyak<<" "<<harga_tiket<<" "<< jumlah<<endl;
                        riyawat.close();
                        check = true;
                        break;
                    }else{
                        cout<<"Pembelian dibatalkan"<<endl;
                    }
                }
            }
    }while((konfirmasi != 'Y') && (check != true));
}

void riwayat_pembelian(){
    string judul, genre;
    int durasi,banyak,harga,jumlah;
    system("cls");
    ifstream file("struk_pembelian"+username+".txt");
    if(!file){
        cout << "Anda belum melakukan transaksi" << endl;
        return;
    }else{
        while(!file.eof()){
            file >>judul >> genre >> durasi >> banyak >> harga >> jumlah;
            cout<<"============================================="<<endl;
            cout<<"Judul \t\t: "<< judul <<endl;
            cout<<"Genre \t\t: "<< genre <<endl;
            cout<<"Durasi\t\t: "<< durasi <<endl;
            cout<<"Banyak\t\t: "<< banyak <<endl;
            cout<<"Harga tiket\t: " << harga <<endl;
            cout<<"Total Harga\t: " << jumlah<<endl;
            cout<<"============================================="<<endl;
            cout<<endl;
        }
    }
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
    if( ketemu )tampilkanData(film, index);
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

void tampilkanData(bioskop* film, int index) {
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
    tampilkanData(film, index + 1);
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
                tampilkanData(film ,index);
                break;
            case 2:
                system("cls");
                bubble_sort_asdc();
                cout << "Data setelah sorting:\n";
                tampilkanData(film, index);
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

void buat_akun(){
    string  peran; 
    int siapa;
    system("cls");
    cout<<"Jenis Peran"<<endl;
    cout<<"1. user"<<endl;
    cout<<"2. admin"<<endl;
    cout<<"-----------------"<<endl;
    cout<<"Siapakah Anda : ";
    cin>>siapa;
    if(siapa == 1 )peran = "user";
    else if(siapa == 2)peran = "admin";
    
    cout    <<"Masukan Username Anda : ";
    cin     >>username;
    cout    <<"Masukan Password Anda : ";
    cin     >>password;

    ofstream akun;
    akun.open("akun.txt", ios::app);
    akun    << username;
    akun    << endl;
    akun    << password;
    akun    << endl;
    akun    << peran;
    akun    << endl;

    if(akun){
        cout<<"Selamat Akun anda sudah di buat"<<endl;
        cout<<"Silahkan Lanjut ke menu login"<<endl;
        system("pause");
        login();
    }else{
        cout<<"Terjadi kesalahan, silahkan coba lagi"<<endl;
    }
    akun.close();
}

void ubahkapital(string& str) {
    for (char& c : str) {
        c = toupper(c);
    }
}