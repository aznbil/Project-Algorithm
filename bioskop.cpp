#include <iostream>
using namespace std;

struct bioskop{
  int id_film;
  string judul;
  string genre;
};

void quick_short();
void menu();

int main(){
  cout << "Hello World" << endl;
}

void menu(){
  int pilih;

  cout << "Menu" << endl;
  cout << "1. Quick Sort" << endl;
  cout << "2. Merge Sort" << endl;
  cout << "3. Selection Sort" << endl;
  cout << "4. Insertion Sort" << endl;
  cout << "5. Bubble Sort" << endl;
  cout << "6. Exit" << endl;
  cout << "Masukkan Pilihan : ";
  cin >> pilih;

  switch(pilih){
    case 1:
      quick_short();
      break;
    case 2:
      break;
    case 3:
      break;
    case 4:
      break;
    case 5:
      break;
    case 6:
      break;
    default:
      cout << "Pilihan Salah" << endl;
  }
}

