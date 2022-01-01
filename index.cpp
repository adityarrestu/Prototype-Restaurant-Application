#include <iostream>
#include <conio.h>
#include <limits>

using namespace std;

// membuat class Menu
class Menu {
    
    public: 
        string namaMenu;
        int hargaMenu;
        int diskonHarga = 0;

};

// deklarasi variabel global
Menu menu[20];
int order[20][3];
int totalHarga;
int totalHargaHandler;
int totalBayar;
int totalKembalian;
int handler[20];
int handlerHolder;
int handlerSelector;

// fungsi membuat Menu
void createMenu(int limit, string namaMenu, int hargaMenu, int diskonHarga);

// fungsi bayar
void payOrder(int &totalHarga);

// fungsi navigasi pengurangan pesanan
void decreaseNavigator(int &limit, int &input);

// fungsi menampilkan pesanan
void displayOrder(int &input);

// fungsi menampilkan menu
int displayMenu(int &list);

// fungsi reset pesanan
void resetOrder() ;

int main() {
    int list = 0;
    char is_continue;

    createMenu(0, "Nasi Goreng", 12000, 0);
    createMenu(1, "Mie Goreng", 12000, 0);
    createMenu(2, "Nasi Gila", 13000, 0);
    createMenu(3, "Mie Godok", 15000, 0);
    createMenu(4, "Mie Gledek", 15000, 0);
    createMenu(5, "Ayam Gledek", 15000, 0);
    createMenu(6, "Ayam Geprek", 15000, 0);
    createMenu(7, "Mie Geprek", 15000, 0);
    createMenu(8, "Mie Jago", 15000, 0);
    createMenu(9, "Kwetiaw  ", 15000, 0);
    createMenu(10, "Rawon  ", 15000, 0);
    createMenu(11, "Karaage  ", 15000, 0);
    
    order:
    int pilihan = displayMenu(list);

    // perulangan pilihan
    while (pilihan != 13) {

        // percabangan pilihan
        switch (pilihan) {
            case 1:
                order[0+list][0] = 0+list;
                order[0+list][1] += 1;
                break;
            
            case 2:
                order[1+list][0] = 1+list;
                order[1+list][1] += 1;
                break;
            
            case 3:
                order[2+list][0] = 2+list;
                order[2+list][1] += 1;
                break;
            
            case 4:
                order[3+list][0] = 3+list;
                order[3+list][1] += 1;
                break;
            
            case 5:
                order[4+list][0] = 4+list;
                order[4+list][1] += 1;
                break;

            case 6:
                order[5+list][0] = 5+list;
                order[5+list][1] += 1;
                break;
            
            case 7:
                list != 0 ? list -= 6 : list += 6;
                break;

            case 8:
                if (list == 0 && list < 12) list += 6;
                break;

            case 9:
                // konfirmasi pesanan
                cout << "\nKonfirmasi Pesanan[y/n]?: " << endl;
                cin >> is_continue;
                if ( (is_continue == 'y') | (is_continue == 'Y')){
                    goto bayar;
                } else if ((is_continue == 'n') | (is_continue == 'N')){
                    goto cancelled;
                }
                break;

            case 11:
                if (handlerSelector > 0) handlerSelector--;
                break;

            case 12:
                handlerSelector < (sizeof(handler)/sizeof(*handler)) ? handlerSelector++ : handlerSelector = 0;
                break;

            case 0:
                order[handler[handlerSelector]][1] -= 1;
                break;

            case 999:
                goto out;
                break;

            default:
                break;
        }
        cancelled:
        pilihan = displayMenu(list);
    }
    bayar:
    system("cls");
    displayOrder(pilihan);

    cout << "\nTerima kasih telah memesan\nMohon tunggu pesanan Anda" << endl;
    getch();
    resetOrder();
    goto order;
    out:

    return 0;
}

// fungsi membuat Menu
void createMenu(int limit, string namaMenu, int hargaMenu, int diskonHarga) {
    menu[limit].namaMenu = namaMenu;
    menu[limit].hargaMenu = hargaMenu;
    menu[limit].diskonHarga = diskonHarga;
}

// fungsi bayar
void payOrder(int &totalHarga) {
    cout << "Total Bayar\t: Rp ";
    cin >> totalBayar;

    totalKembalian = (totalBayar - totalHarga);
    cout << "Total Kembalian\t: Rp " << totalKembalian << endl;
}

// fungsi navigasi pengurangan pesanan
void decreaseNavigator(int &limit, int &input) {
    handler[handlerHolder] = limit;
    handlerHolder++;

    if (limit == handler[handlerSelector] && input != 9) {
        cout << " [-]";
    }
}

// fungsi menampilkan pesanan
void displayOrder(int &input) {

    for (int i = 0; i < 20; i++) {
        int limit = order[i][0];
        int jumlah = order[i][1];
        order[i][2] = ((jumlah * menu[i].hargaMenu) - (menu[i].hargaMenu * menu[i].diskonHarga)); 
        if (jumlah != 0) {
            cout << menu[i].namaMenu << "\t" << jumlah << "\tRp " << order[i][2] << "  "; 
            decreaseNavigator(limit, input);
            cout << endl;
        }
        totalHarga += order[i][2];
    }
    if (totalHarga != 0) {
        cout << "================================" << endl;
        cout << "Total Harga\t: Rp " << totalHarga << endl;
    }
    
    if (input == 9) payOrder(totalHarga);  
    totalHarga = 0;
    handlerHolder = 0;
}

// fungsi menampilkan menu
int displayMenu(int &list) {
    int input;
    system("cls");

    cout << "Daftar Menu" << endl;
    for (int i = 0; i <= 5; i++) {
        cout << "[" << i+1 << "] " << menu[i+list].namaMenu;
        cout << "\t" << menu[i+list].hargaMenu;
        if (menu[i+list].diskonHarga != 0) 
            cout << "\t" << menu[i+list].diskonHarga;
        cout << endl;
    }
    cout << "[9] Buat Pesanan\n" << endl;
    cout << "[7] << Prev [8] Next >>" << endl;
    cout << "[11]up [12]down [0]<->" << endl;
    cout << "================================" << endl;
    displayOrder(input);

    cout << "pilih [1-9]: ";
    cin >> input;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
	return input;
}

// fungsi reset pesanan
void resetOrder() {
    for (int i = 0; i < 20; i++) {
        order[i][0] = 0;
        order[i][1] = 0;
        order[i][2] = 0;
    }
}