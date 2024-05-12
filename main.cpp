#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <vector>
#include <random>


using namespace std;
// Constants
const string admin_password = "abcxyz123";
const int seats = 40;
const int carts = 12;
const double ticket_price_a = 40;
const double ticket_price_b = 30;
const double ticket_price_c = 20;
const double pre_price = 10;
const double station_to_station_duration_a = 1; // in hours
const double station_to_station_duration_b = 1.5; // in hours
const double station_to_station_duration_c = 2; // in hours
const string stations[9] = {"Aswan", "Luxor", "Qena", "Sohag", "Assuit", "Elminia", "Beni suif", "Giza", "Cairo"};
const string days[7] = {"Sunday", "Monday", "Turesday", "Wednsday", "Thurday", "Friday","Saturday"};

// Classes
class Ticket {
private:
    int start;
    int end;
    int leavingTime;
    char trainClass;
    int day;
    double price;
    int id;
    int cart;
    int seat;

public:
    Ticket(int s, int e, char c, double p, int i, int l,int seat,int cart,int day) : start(s), end(e), trainClass(c), price(p), id(i), leavingTime(l),seat(seat),cart(cart),day(day) {}

    string getStart() { return stations[start - 1]; }
    string getEnd() { return stations[end - 1]; }
    char getClass() { return trainClass; }
    double getPrice() { return price; }
    int getId() { return id; }
    int getLeavingTime() { return leavingTime; }
    int getCart() { return cart; }
    int getSeat() { return seat; }
    int getDay() { return day; }
};

class Clerk {
private:
    string name;
    int id;
public:
    Clerk(string clerkName, int clerkId) : name(clerkName), id(clerkId) {}
    string getName() { return name; }
    int getId() { return id; }
};

// Data base
vector<Clerk> clerks = { Clerk("Bodbod", 1111) };
vector<Ticket> tickets;


bool signUp() {
    string adminId;
    cout << "Enter the admin password: ";
    cin >> adminId;

    if (adminId != admin_password) {
        cout << "Access denied." << endl;
        return false;
    }

    string name;
    cout << "Enter the new clerk's username: ";
    cin >> name;

    int id;
    cout << "Enter the new clerk's ID: ";
    cin >> id;

    for (auto clerk : clerks) {
        if (id == clerk.getId()) {
            cout << "This ID is already in use." << endl;
            return false;
        }
    }

    clerks.push_back(Clerk(name, id));
    cout << "Signing up completed! Welcome, " << name << "!" << endl;
    return true;
}
bool signIn() {
    string name;
    cout << "Enter your username: ";
    cin >> name;

    int id;
    cout << "Enter your ID: ";
    cin >> id;


    bool idIsTrue = false,nameIsTrue = false;

    for (auto clerk:clerks) {
        if(id == clerk.getId()) {
            idIsTrue = true;
                if(name == clerk.getName()) {
                    nameIsTrue = true;
                }
            break;
        }
    }

    if(idIsTrue&& nameIsTrue) {
        cout<<"Welcome "<<name<<"!!\n";
        return true;
    }else {
        cout<<"wrong username or password\n";
        return false;
    }

}



bool welcomeScreen() {
    cout << "Welcome to Aswan railways station" << endl;
    int choice;
    do {
        cout << "1 - Sign In\n2 - Sign Up\nChoose what you want: ";
        cin >> choice;
    } while (choice != 1 && choice != 2);

    return (choice == 1) ? signIn() : signUp();
}




double calculateTime(int leavingTime, double distance, char trainClass) {
    int time;
    leavingTime = (leavingTime - 1) * 2;
    leavingTime = (leavingTime < 0) ? 0 : leavingTime;

    switch (toupper(trainClass)) {
        case 'A':
            time = leavingTime + distance * station_to_station_duration_a;
        break;
        case 'B':
            time = leavingTime + distance * station_to_station_duration_b;
        break;
        case 'C':
            time = leavingTime + distance * station_to_station_duration_c;
        break;
    }

    return fmod(time, 24);
}

double calculatePrice(double distance, char trainClass) {
    int price;
    switch (trainClass) {
        case 'A':
            price = pre_price + distance * ticket_price_a;
        break;
        case 'B':
            price = pre_price + distance * ticket_price_b;
        break;
        case 'C':
            price = pre_price + distance * ticket_price_c;
        break;
    }
    return price;
}


int generateRandom(int start,int end) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(start, end);
    return dis(gen);
}



bool book_ticket(){
    int st ,end,leavingTime,cart,seat;double distance;char trainClass;
        distance =0;
         do{
            cout << "Departure stations:" << endl;
            for (int i = 0;i<9;i++)cout<<i+1<<" "<<stations[i]<<endl;
            cout << "Enter your departure station: ";
            cin>>st;
            }while (st >9 || st < 1);

    do {
        cout << "Arrival stations:" << endl;
        for (int i = 0; i < 9; i++)cout << i + 1 << " " << stations[i] << endl;
        cout << "Enter your arrival station: ";
        cin >> end;
    } while (end < 1 || end > 9 || end == st);

    distance = abs(end-st);

    do {
        cout << "Train classes:" << endl;
        for (int i = 0; i < 3; i++) {
            cout << i + 1 << " - Train " << char('A' + i) << " (Price: " << calculatePrice(distance, 'A' + i) << " L.E, Duration: " << calculateTime(0, distance, 'A' + i) << " hour)" << endl;
        }
        cout << "Choose train class (1-3): ";
        cin >> trainClass;
    } while (trainClass < '1' || trainClass > '3');

    trainClass = (trainClass == '1')?'A':(trainClass == '2')?'B':'C';

        do {
            for (int i = 0,j = 1;i<24;i+=2,j++) {
                if(i < 10&& j <10) {
                    cout<<"0"<<j<<" - 0"<<i<<":00\n";
                }else if(j< 10) {
                    cout<<"0"<<j<<" - "<<i<<":00\n";
                }else {
                    cout<<j<<" - "<<i<<":00\n";
                }
            }
            cout<<"choose your leaving time : \n";
            cin>>leavingTime;
        }while (leavingTime < 1||leavingTime >12);

        cart = generateRandom(1,carts);
        seat = generateRandom(1,seats);



    int id = generateRandom(100000,999999);

    int day;
    do {
        cout<<"enter the day within the folloing week (1-7): ";
        cin>>day;
    }while (day<1||day>7);



    int save;
    do {
        cout<<"from : "<<stations[st-1]<<endl;
        cout<<"to : "<<stations[end-1]<<endl;
        cout<<"Day : "<<days[day-1]<<endl;
        cout<<"ID : "<<id<<endl;
        cout<<"price : "<<calculatePrice(distance, trainClass)<<" L.E \n";
        cout<<"cart : "<<cart<<"\n";
        cout<<"seat : "<<seat<<"\n";
        if(leavingTime <= 5) {
            cout<<"leaving at : 0"<<(leavingTime-1)*2<<":00\n";
        }else {
            cout<<"leaving at : "<<(leavingTime-1)*2<<":00\n";
        }
        if(calculateTime(leavingTime,distance,trainClass) <= 9) {
            cout<<"arrives at : 0"<<calculateTime(leavingTime,distance,trainClass)<<":00\n";
        }else {
            cout<<"arrives at : "<<calculateTime(leavingTime,distance,trainClass)<<":00\n";
        }
        cout<<"1 - delete & back to menu\n2 - Save ticket\nSave : ";
        cin>>save;
    }while (save != 1 && save != 2 );

    if(save == 1) {
        return false;
    }else{
        tickets.push_back(Ticket(st,end,trainClass,calculatePrice(distance,trainClass),id,leavingTime,seat,cart,day));
        return true;
    }
    }


void inform_ticket() {
    int id;
    cout<<"Enter your id : ";
    cin>>id;
    bool isThere = false;
    for (auto ticket:tickets) {
        //search by id
        if (ticket.getId() == id) {
            isThere = true;
            cout<<
                "from : "<<ticket.getStart()
                <<"\nTo : "<<ticket.getEnd()
                <<"\nDay : "<<ticket.getDay()
                <<"\nClass : "<<ticket.getClass()
                <<"\nprice : "<<ticket.getPrice()
                <<"\nID: "<<ticket.getId()
                <<"\nleaving by : "<<ticket.getLeavingTime()
                <<"\nSeat : "<<ticket.getSeat()
                <<"\nCat : "<<ticket.getCart();
            break;

        }
    }
    if (!isThere) {
        cout<<"Not found";
    }
}

int main(){
    while(welcomeScreen()) {
        cout<<string(20,'*')<<endl;
        int choice;

        mainMenu:do {
        cout<<"1-Book ticket\n2-inform about ticket\nEnter your choice : ";
            cin>>choice;
        }while (choice <1 || choice > 2);

        if (choice == 1) {
            book_ticket();
        }else {
            inform_ticket();
        }

        do {
            cout<<"1-main menu\n 2-close program\n 3-Log out\n what do you want : ";
            cin>>choice;
        }while (choice < 1 || choice >3);

        if(choice == 1) {
            goto mainMenu;
        }else if(choice == 2) {
            break;
        }else {
            continue;
        }
    }
}