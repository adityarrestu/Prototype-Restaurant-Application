#include <iostream>
#include <conio.h>
#include <limits>
#include <fstream>
#include <time.h>
#define Size 50

using namespace std;

// membuat class Menu
class Menu {
    
    public: 
        string namaMenu;
        int hargaMenu;
        int diskonHarga = 0;

};

// deklarasi variabel global
const int maxIndex = 20;
Menu menu[maxIndex];
int order[maxIndex][3];
int totalHarga;
int totalHargaHandler;
int totalBayar;
int totalKembalian;
int handler[maxIndex];
int handlerHolder;
int handlerSelector;

// fungsi membuat Menu
void createMenu(int limit, string namaMenu, int hargaMenu, int diskonHarga);

// fungsi waktu
string currentTime();

// membuat kelas database
class DBase {

    public: 
        ifstream in;
        ofstream out;
        string filename;

        DBase(const string filename) {
            DBase::filename = filename;
        }

        void save(string &index, string &namaMenu, string &hargaMenu, string &diskon) {
            DBase::out.open(this->filename,ios::app);
            DBase::out << index << endl;
            DBase::out << namaMenu << endl;
            DBase::out << hargaMenu << endl;
            DBase::out << diskon << endl;
            DBase::out.close();
        }

        void saveOrder(int &totalBayar, int &totalKembalian) {
            DBase::out.open(this->filename,ios::app);

            DBase::out << currentTime() << endl;
            DBase::out << "=======================================" << endl;
            for (int i = 0; i < maxIndex; i++) {
                int limit = order[i][0];
                int jumlah = order[i][1];
                order[i][2] = ((jumlah * menu[i].hargaMenu) - (jumlah * menu[i].hargaMenu * menu[i].diskonHarga/100)); 
                
                if (jumlah != 0) {
                    DBase::out << menu[i].namaMenu << "\t" << jumlah << "\t" << menu[i].hargaMenu << "   " << order[i][2] << endl;
                }
            }
            DBase::out << "=======================================" << endl;
            DBase::out << "Total Harga\t: " << totalHarga << endl;
            DBase::out << "Tunai\t\t: " << totalBayar << endl;
            DBase::out << "Kembalian\t: " << totalKembalian << endl;
            DBase::out << "\n";

            DBase::out.close();
        }

        void getData() {
            DBase::in.open(DBase::filename,ios::in);
            string index, namaMenu, hargaMenu, diskonHarga;
            int limit, harga, diskon;

            while (!DBase::in.eof()) {
                getline(in,index);
                getline(in,namaMenu);
                getline(in,hargaMenu);
                getline(in,diskonHarga);

                if (index != "") {
                    limit = stoi(index);
                    harga = stoi(hargaMenu);
                    diskon = stoi(diskonHarga);

                    menu[limit].namaMenu = namaMenu;
                    menu[limit].hargaMenu = harga;
                    menu[limit].diskonHarga = diskon;
                }
            }

            this->in.close();
        }

        void getOrder() {
            DBase::in.open(DBase::filename,ios::in);
            string data, output;

            while (!DBase::in.eof()) {
                getline(in, data);
                output.append("\n" + data);
            }

            cout << output;
            
            getch();
            DBase::in.close();
        }

};

// deklarasi object database
DBase database = DBase("menu.txt");
DBase databaseOrder = DBase("order.txt");

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

// fungsi menampilkan menu admin
int displayAdmin();

// fungsi menampilkan daftar menu
void displayMenuList();

// fungsi masuk admin daashboard
void dashboardAdmin();

int main() {
    int list = 0;
    char is_continue;
    database.getData();
    
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
                cout << "\nKonfirmasi Pesanan[y/n]?: ";
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

            case 777:
                dashboardAdmin();
                break;
            
            case 888:
                database.getData();
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
    cout << "Tunai\t\t: Rp ";
    cin >> totalBayar;

    totalKembalian = (totalBayar - totalHarga);
    cout << "Kembalian\t: Rp " << totalKembalian << endl;

    databaseOrder.saveOrder(totalBayar, totalKembalian);
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

    for (int i = 0; i < maxIndex; i++) {
        int limit = order[i][0];
        int jumlah = order[i][1];
        order[i][2] = ((jumlah * menu[i].hargaMenu) - (jumlah * menu[i].hargaMenu * menu[i].diskonHarga/100)); 
        if (jumlah != 0) {
            cout << menu[i].namaMenu << "\t" << jumlah << "\tRp " << order[i][2] << "  "; 
            decreaseNavigator(limit, input);
            cout << endl;
        }
        totalHarga += order[i][2];
    }
    if (totalHarga != 0) {
        cout << "=======================================" << endl;
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
        if (menu[i].hargaMenu != 0) {
            cout << "[" << i+1 << "] " << menu[i+list].namaMenu;
            cout << "\t\tRp " << menu[i+list].hargaMenu;
            if (menu[i+list].diskonHarga != 0) 
                cout << "  -" << menu[i+list].diskonHarga << "%";
            cout << endl;
        }
    }
    cout << "[9] Buat Pesanan\n" << endl;
    cout << "[7] << Prev [8] Next >>" << endl;
    cout << "[11]up [12]down [0]<->" << endl;
    cout << "=======================================" << endl;
    displayOrder(input);

    cout << "pilih [1-9]: ";
    cin >> input;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
	return input;
}

// fungsi reset pesanan
void resetOrder() {
    for (int i = 0; i < maxIndex; i++) {
        order[i][0] = 0;
        order[i][1] = 0;
        order[i][2] = 0;
    }
}

// fungsi admin
int displayAdmin() {
    int input;
    system("cls");

    cout << "DASHBOARD ADMIN" << endl;
    cout << "[1] Buat menu baru" << endl;
    cout << "[2] Tampilkan menu" << endl;
    cout << "[3] Tampilkan histori pesanan" << endl;
    cout << "[4] Kembali ke daftar menu" << endl;
    cout << "==============================" << endl;
    cout << "pilih [1-4]: ";
    cin >> input;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');

	return input;
}

void saveNewMenu() {
    string index, namaMenu, hargaMenu, diskonHarga;

    cout << "Masukkan data" << endl;
    cout << "Index menu\t: ";
    cin >> index;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');

    cout << "Nama menu\t: ";
    getline(cin, namaMenu);

    cout << "Harga menu\t: ";
    cin >> hargaMenu;

    cout << "Diskon harga\t: ";
    cin >> diskonHarga;

    database.save(index, namaMenu, hargaMenu, diskonHarga);
    database.getData();

    getch();
}

void displayMenuList() {
    cout << "Daftar Menu" << endl;
    for (int i = 0; i <= maxIndex; i++) {
        if (menu[i].hargaMenu != 0) {
            cout << "[" << i << "] " << menu[i].namaMenu;
            cout << "\t\tRp " << menu[i].hargaMenu;
            cout << "  -" << menu[i].diskonHarga << "%";
            cout << endl;
        }
    }
    getch();
}

// fungsi admin daashboard
void dashboardAdmin() {
    int pilihan = displayAdmin();

    while (pilihan != 4) {
        switch (pilihan) {
        case 1:
            saveNewMenu();
            break;
        
        case 2:
            displayMenuList();
            break;
        
        case 3:
            databaseOrder.getOrder();
            break;
        
        case 4:
            break;
        
        default:
            break;
        }

        pilihan = displayAdmin();
    }
}

// fungsi waktu
string currentTime() {
    time_t t ;
    struct tm *tmp ;
    char MY_TIME[Size];
    time( &t );

    tmp = localtime( &t );
     
    // using strftime to display time
    strftime(MY_TIME, sizeof(MY_TIME), "%a %x - %H:%M", tmp);

    return MY_TIME;
}