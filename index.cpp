#include <iostream>
#include <conio.h>
#include <limits>

using namespace std;


class Menu {
    
    public: 
        string namaMenu;
        int hargaMenu;
        int diskonHarga = 0;

};

Menu menu[20];
int order[20][2];
int handler[20];
int handlerHolder;
int handlerSelector;

void createMenu(int limit, string namaMenu, int hargaMenu, int diskonHarga) {
    menu[limit].namaMenu = namaMenu;
    menu[limit].hargaMenu = hargaMenu;
    menu[limit].diskonHarga = diskonHarga;
}

void decreaseNavigator(int &limit) {
    handler[handlerHolder] = limit;
    handlerHolder++;

    if (limit == handler[handlerSelector]) {
        cout << " [-]" << handlerSelector;
    }
}

void displayOrder() {
    for (int i = 0; i < 20; i++) {
        int limit = order[i][0];
        int jumlah = order[i][1];
        if (jumlah != 0) {
            

            cout << menu[limit].namaMenu << "\t" << jumlah << "\t"; 
            decreaseNavigator(limit);
            cout << endl;
        }
    }

    handlerHolder = 0;
}

int displayMenu(int &list) {
    int input;
    // system("cls");

    cout << "Daftar Menu" << endl;
    for (int i = 0; i <= 5; i++) {
        cout << "[" << i+1 << "] " << menu[i+list].namaMenu;
        cout << "\t" << menu[i+list].hargaMenu;
        if (menu[i+list].diskonHarga != 0) 
            cout << "\t" << menu[i+list].diskonHarga;
        cout << endl;
    }
    cout << "[7] Next >>" << endl;
    cout << "[8] << Prev" << endl;
    cout << "[9] Selesai" << endl;
    cout << "================================" << endl;
    displayOrder();

    cout << "pilih [1-9]: ";
    cin >> input;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
	return input;
}

int main() {
    int list = 0;
    int &listChange = list;

    createMenu(0, "Nasi Goreng", 12000, 0);
    createMenu(1, "Mie Goreng", 12000, 0);
    createMenu(2, "Nasi Gila", 13000, 0);
    createMenu(3, "Mie Godok", 15000, 0);
    createMenu(4, "Mie Gledek", 15000, 0);
    createMenu(5, "Ayam Gledek", 15000, 0);
    createMenu(6, "Ayam Geprek", 15000, 0);
    createMenu(7, "Mie Geprek", 15000, 0);
    createMenu(8, "Mie Jago", 15000, 0);
    createMenu(9, "Kwetiaw\t", 15000, 0);
    createMenu(10, "Rawon\t", 15000, 0);
    createMenu(11, "Karaage\t", 15000, 0);
 
    int pilihan = displayMenu(list);

    while (pilihan != 9) {

        switch (pilihan) {
            case 1:
                order[0+list][0] = (0+list);
                order[0+list][1] += 1;
                break;
            
            case 2:
                order[1+list][0] = (1+list);
                order[1+list][1] += 1;
                break;
            
            case 3:
                order[2+list][0] = (2+list);
                order[2+list][1] += 1;
                break;
            
            case 4:
                order[3+list][0] = (3+list);
                order[3+list][1] += 1;
                break;
            
            case 5:
                order[4+list][0] = (4+list);
                order[4+list][1] += 1;
                break;

            case 6:
                order[5+list][0] = (5+list);
                order[5+list][1] += 1;
                break;
            
            case 7:
                if (list == 0 && list < 12) list += 6;
                break;

            case 8:
                list != 0 ? list -= 6 : list += 6;
                break;

            case 0:
                handlerSelector < (sizeof(handler)/sizeof(*handler)) ? handlerSelector++ : handlerSelector = 0;
                cout << sizeof(handler) << endl;
                break;

            default:
                break;
        }

        pilihan = displayMenu(list);
    }
    
    return 0;
}