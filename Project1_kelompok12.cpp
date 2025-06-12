#include <iostream>
#include <cstring>
#include <fstream>
#include <ctime>
using namespace std;

//ANGGOTA KELOMPOK 
//Nama: M.Ahsan R.S (123240246)
//Nama: Aziz Nabil Putra Darmawan (123240239)
//Nama: Kevin Prasetya (123240231)


//Revisi
//1. Menambahkan Binary search
//2. Menambahkan Sorting

struct bioskop {
    string judul;
    string genre;
    int durasi; // dalam menit
    float rating;
};

const int max_film = 100;
bioskop film[max_film];
int dataYgDiinput = 0;
string cari, username, password;
void menu(), ubahkapital(string& str),  input(), bubble_sort_desc(), tampilkanData(bioskop* film, int index = 0), sorting(), fileopen(int index) ;
void buat_akun(), login(), loginpage(), menu_user(), menu_admin(), beli(), riwayat_pembelian(), update_data(), merge(bioskop * film, int low, int high, int mid);
void  readFile(), deletefile(), insertion_sort(), quick_sort(int low, int high), shell_sort(), binary_search(), selection_sort(), merge_sort(bioskop * film, int low, int high);
int searching(), partion(int low, int high), Binary(string judul);

int main() {  
    ifstream myfile;
    myfile.open("tampilkandata");
    myfile >> dataYgDiinput;
    readFile();
    myfile.close();

    loginpage();  
}

void readFile(){
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
}

void loginpage(){
    int pilih;
    char jawab;
    do{
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
    cout << "Ingin kembali ke menu login? (y/n): ";
    cin >> jawab;
    }while(jawab == 'y' || 'Y');
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
        cout << "5. Update Data\n";
        cout << "6. Delete Data\n";
        cout << "7. Exit\n";
        cout << "Masukkan Pilihan: ";
        cin >> pilih;

        switch (pilih) {
            case 1:
                system("cls");
                input();
                break;
            case 2:
                system("cls");
                tampilkanData(film, 0);
                break;
            case 3:
                system("cls");
                sorting();
                break;
            case 4:
                cout << "1. Sequential Search\n" ;
                cout << "2. Binary Search\n";
                cout << "Pilih : ";
                cin >> pilih;
                if(pilih == 1){
                    searching();
                }if(pilih == 2){
                    binary_search();
                }
                break;
            case 5:
                update_data();
                break;
            case 6:deletefile();
                break;
            case 7:exit(0);
                return;
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
    char yakin;
        do{
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
        cout<<"Apakah anda masih ingin lanjut berbelanja? (Y/N) : ";
        cin>>yakin;
    }while(yakin == 'y' || yakin =='Y');
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
        tampilkanData(film, 0);
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

int searching(){
    cout<<"Masukan Judul Film yang ingin anda cari : ";
    cin.ignore();
    getline(cin, cari);
    ubahkapital(cari);
    int i = 0;
    bool ketemu = false ;

    while( !ketemu ){
        if(cari==film[i].judul){
            ketemu = true;
            i == dataYgDiinput;
            break;
        }
        // if(i == dataYgDiinput)break;
        else i++;
    }
    if( !ketemu ){
        cout<<"Film yang anda cari tidak di temukan"<<endl;}
    else {
        cout << "\nJudul Film\t: " << film[i].judul << endl;
        cout << "Genre Film\t: " << film[i].genre << endl;
        cout << "Durasi (menit)\t: " << film[i].durasi << " menit" << endl;
        cout << "Rating Film\t: " << film[i].rating << endl;
        cout << "-----------------------" << endl;
        cout << endl;
    }
    return i;
    // return film[i].judul;
}

int Binary(string judul){
    shell_sort(); // di urutkan dahulu
    int left = 0;
    int right = dataYgDiinput - 1;

    while (left <= right){
        int mid = left + (right - left)/2;
        if(film[mid].judul == judul){
            return mid;
        }
        if(film[mid].judul < judul){
            left = mid + 1;
        }else{
            right = mid - 1;
        }
    }
    return -1; //tidak ditemukan
}

void binary_search(){
    cout<<"Masukan Judul Film yang ingin anda cari : ";
    cin.ignore();
    getline(cin, cari);
    ubahkapital(cari);

    int hasil = Binary(cari);
    if(hasil != -1){
        cout << "\nJudul Film\t: " << film[hasil].judul << endl;
        cout << "Genre Film\t: " << film[hasil].genre << endl;
        cout << "Durasi (menit)\t: " << film[hasil].durasi << " menit" << endl;
        cout << "Rating Film\t: " << film[hasil].rating << endl;
        cout << "-----------------------" << endl;
        cout << endl;
    }else{
        cout << "Film yang anda cari tidak di temukan\n";
    }
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

void update_data(){
    int i = searching();
    int update;
    cout <<"1. Nama "<<endl;
    cout <<"2. Genre"<<endl;
    cout <<"3. Durasi"<<endl;
    cout <<"4. Rating"<<endl;
    cout <<"=========================="<<endl;
    cout <<"Silahkan Pilih Yang Ingin Anda Edit : ";
    cin>>update;
    switch(update){
        case 1:
        cin.ignore();
        cout<<"Masukan Nama Baru : ";
        getline(cin, film[i].judul);
        break;

        case 2:
        cout<<"Masukan Genre Baru : ";
        cin.ignore();
        getline(cin, film[i].genre);
        break;

        case 3:
        cout << "Masukkan Durasi Baru :";
        cin >> film[i].durasi;
        break;

        case 4:
        cout << "Masukkan Rating Baru :";
        cin >> film[i].rating;  
        break;

        default:
        cout << "Pilihan tidak tersedia. Silahkan ulangi.";
        break;
    } 
    ofstream data; 
    data.open("databioskop",ios::trunc ); 
    for(int i=0 ; i<dataYgDiinput ; i++){
        data << film[i].judul;
        data << endl;
        data << film[i].genre;
        data << endl;
        data << film[i].durasi;
        data << endl;
        data << film[i].rating;
        data << endl;
    }
    
}

//menggunakan pemanggilan rekursif

void tampilkanData(bioskop* film, int index) {
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

void insertion_sort(){
    int i, key, j;
    for (i = 1; i < dataYgDiinput; i++){ 
		bioskop key = film[i]; 
		j = i - 1; 
		while (j >= 0 && film[j].rating > key.rating) { 
			film[j + 1] = film[j]; 
			j--; 
		} 
		film[j + 1] = key; 
	} 
}

int partion(int low, int high){
    bioskop pivot = film[high];
    int i = (low - 1);

    for(int j = low; j <= high - 1; j++){
        if(film[j].durasi > pivot.durasi){
            i++;
            swap(film[i], film[j]);
        }
    }
    swap(film[i+1], film[high]);
    return i + 1;
}

void quick_sort( int low, int high){
    if(low < high){
        int pi = partion(low, high);
        quick_sort(low, pi - 1);
        quick_sort(pi + 1, high);
    }
}

void shell_sort(){
    int gap, j, k;
    for(int gap = dataYgDiinput/2; gap > 0; gap = gap/2){
        for(j = gap; j < dataYgDiinput; j++){
            for(k = j - gap; k >= 0; k -= gap){
                if(film[k+gap].durasi >= film[k].durasi)
                break;
                else
                swap(film[k+gap], film[k]);
            }
        }
    }
}

void selection_sort(){
    int i, j, min_idx;
    for(i = 0; i < dataYgDiinput; i++){
        min_idx = i;
        for(j = i + 1; j < dataYgDiinput; j++)
        if(film[j].judul <= film[min_idx].judul)
                min_idx = j;
            swap(film[j], film[min_idx]);
    }
}

void merge(bioskop * film, int low, int high, int mid){
    int i, j, k; 
    string temp[high - low + 1];
    i = low;
    k = 0;
    j = mid + 1;

    while (i <= mid && j <= high)
    {
      if (film[i].judul < film[j].judul)
	{
	  temp[k] = film[i].judul;
	  k++;
	  i++;
	}
      else
	{
	  temp[k] = film[j].judul;
	  k++;
	  j++;
	}
    }

  // Insert all the remaining values from i to mid into temp[].
  while (i <= mid)
    {
      temp[k] = film[i].judul;
      k++;
      i++;
    }

  // Insert all the remaining values from j to high into temp[].
  while (j <= high)
    {
      temp[k] = film[j].judul;
      k++;
      j++;
    }


  // Assign sorted data stored in temp[] to a[].
  for (i = low; i <= high; i++)
    {
      film[i].judul = temp[i - low];
    }
}

void merge_sort(bioskop * film, int low, int high){
    int mid;
    if(low < high){
        mid = (low + high) / 2;
        merge_sort(film, low, mid);
        merge_sort(film, mid + 1, high);

        merge (film, low, high, mid);
    }
}

void sorting() {
    int pilih;
    char jawab;
    
        system("cls");
        cout << "\nMenu:\n";
        cout << "1. Berdasarkan rating (desc)\n";
        cout << "2. Berdasarkan rating (asdc)\n";
        cout << "3. Berdasarkan durasi (desc)\n";
        cout << "4. Berdasarkan durasi (asdc)\n";
        cout << "5. Berdasarkan Judul  (desc)\n";
        cout << "6. Berdasarkan Judul  (asdc)\n";
        cout << "7. Exit\n";
        cout << "Masukkan Pilihan: ";
        cin >> pilih;

        switch (pilih) {
            case 1:
                system("cls");
                bubble_sort_desc();
                cout << "Data setelah sorting:\n";
                tampilkanData(film ,0);
                break;
            case 2:
                system("cls");
                insertion_sort();
                cout << "Data setelah sorting:\n";
                tampilkanData(film, 0);
                break;
            case 3:
                quick_sort(0, dataYgDiinput - 1);
                tampilkanData(film, 0);
                break;
            case 4 :
                shell_sort();
                tampilkanData(film, 0);
                break;
            case 5 :
                system("cls");
                selection_sort();
                cout << "Data setelah sorting:\n";
                tampilkanData(film, 0);
                break;
            case 6 : 
                system("cls");
                merge_sort(film, 0, dataYgDiinput - 1);
                tampilkanData(film, 0);
            case 7 : 
                return;
                break;
            default:
                cout << "Pilihan salah, coba lagi.\n";
        } 
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

void deletefile(){
    string nama;
    cout<<"Masukan Nama Film yang ingin di hapus : ";
    cin>>nama;
    ubahkapital(nama);
    for(int i=0 ; i<dataYgDiinput ; i++){
        for(int j=i ; j<=dataYgDiinput ; j++){
            if(nama == film[i].judul){
                swap(film[i], film[j]);
            }
        }
    }dataYgDiinput--;
    ofstream data; 
    data.open("databioskop",ios::trunc ); 
    for(int i=0 ; i<dataYgDiinput ; i++){
        data << film[i].judul;
        data << endl;
        data << film[i].genre;
        data << endl;
        data << film[i].durasi;
        data << endl;
        data << film[i].rating;
        data << endl;
    }
    ofstream myfile;
    myfile.open("tampilkandata", ios::trunc);
    myfile << dataYgDiinput;
    myfile.close();
}

void ubahkapital(string& str) {
    for (char& c : str) {
        c = toupper(c);
    }
}