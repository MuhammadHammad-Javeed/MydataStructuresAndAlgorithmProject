// MydataStructuresAndAlgorithmProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// \*Cinema Ticket Booth*\ 
//This program uses 2 pure dynamic data structures:
// *LINKED LIST
// *STRECHY ARRAY
//This Program is real time based and the availability of movies will depend on real time.

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <chrono>
#include <sstream>
#include <ctime>
using namespace std;

class cur_TIME {
public:
    string* st = new string[6];
    string tim;

    string Localtime() {
        time_t _tm = time(NULL);

        struct tm* curtime = localtime(&_tm);
        string time = asctime(curtime);
        return time;
    }
    string* get_time()
    {
        tim = Localtime();
        stringstream ss(tim);
        getline(ss, st[0], ' ');
        getline(ss, st[1], ' ');
        getline(ss, st[2], ' ');
        getline(ss, st[3], ':');
        getline(ss, st[4], ':');
        getline(ss, st[5], ' ');


        return st;
    }
};

class open {
public:
    string* movies() {
        string* M = new string[8];
        ifstream mf;
        mf.open("Movies.csv");
        for (int i = 0; i < 8; i++)
            getline(mf, M[i]);

        return M;
    }
    void closer(string* m, string file) {
        ofstream f;

        f.open(file);

        for (int i = 0; i < 22; i++) {
            f << m[i];
            if (i == 3 || i == 11 || i == 27) {
                f << endl;
            }
            else {
                f << ",";
            }
        }
    }
    string filer(string mov) {
        string kl = " ";
        if (mov == "Godzilla") {
            kl = "seats1.csv";
        }if (mov == "UP") {
            kl = "seats2.csv";
        }if (mov == "Avengers") {
            kl = "seats3.csv";
        }if (mov == "GODFATHER") {
            kl = "seats4.csv";
        }if (mov == "IP MAN") {
            kl = "seats5.csv";
        }if (mov == "Minions") {
            kl = "seats6.csv";
        }if (mov == "Dispecable me") {
            kl = "seats7.csv";
        }
        return kl;
    }
};

class search {
public:
    //****FUNCTIONS*****

      //Function for binary search
    int Binary_search(int Array[], int size, int input) {// -> This index is the return value from find()

        int index = find(Array, size);
        int INTEGER, count = 0, start = 0, end = 0;
        bool R = false; // BOOLEAN for checking
        int res = 0;

        INTEGER = input;

        //Giving appropriate values to 'start' and 'end' according to the size of element
        if (INTEGER >= Array[index]) {
            start = index;
            end = size;
        }
        else if (INTEGER < Array[index])
            end = index;

        for (int i = start; i <= end; i++) { // loop running based on limits provided by 'start' and 'end'
            count++;
            if (Array[i] == INTEGER) {
                //  cout << "Your integer is Found: " << Array[i] << endl;
                res = i;
                R = true; //to check integer is found or not
            }
        }
        if (R == false) {
            cout << "Currently we are not screaning\n";
            res = -1;
        }
        return res;
    }
    int find(int A[], int size) {
        int middle = size / 2;
        return middle; //index of middle number 'middle + 1 in case of even number size'
    }
};

class user_manager {
public:
    cur_TIME ct;
    search D1;
    open m;

    string selection() {
        string* t = ct.get_time();
        string* M;
        string* tim = new string[8];
        string* mov = new string[8];
        string movie;
        int* h = new int[8];
        int mi = 0;
        M = m.movies();
        for (int k = 1; k < 8; k++) {
            stringstream t_h(M[k]);

            getline(t_h, tim[k], ',');
            getline(t_h, mov[k], ',');
            getline(t_h, mov[k], ',');
            if (k > 0)
                h[k - 1] = stoi(tim[k]);
            t_h.flush();
            t_h.clear();
        }


        int time_h = stoi(t[3]);
        if (time_h % 2 == 1)
            time_h = time_h - 1;

        mi = D1.Binary_search(h, 7, time_h);
        if (mi != -1) {
            cout << "ONGOING MOVIE: \n" << mi + 1 << " :\t" << mov[mi + 1] << "\ttimmings: " << find_time(mi + 1) << endl << endl;
        }
        cout << "UPCOMING MOVIES: \n";
        for (int i = mi + 2; i < 8; i++)
            cout << i << " :\t" << mov[i] << "       " << " timmings: " << find_time(i) << endl;
        int sel;
        cin >> sel;
        if (sel < mi + 1 || sel > 7) {
            movie = "ERROR";
        }
        else {
            cout << "============================================\n";
            cout << "Your selected movie:  " << mov[sel] << "\n\n";
            movie = mov[sel];
        }
        return movie;
    }
    void get_cus() {
        ofstream s;
        s.open("ticket_records.csv", ios::app);
        string file = " ";
        string movie;
        string seat;
        string* pla;
        while (true) {
            cout << "Chose a movie you want to watch by pressing the respective number!\n\n";
            movie = selection();
            if (movie == "ERROR") {

                system("CLS");
                cout << "invalid selection!\n";
                cout << "Please try again\n\n";
            }
            else {
                break;
            }
        }
        file = m.filer(movie);
        cout << "============================================\n";
        cout << "Please type your name!\n";
        cin.clear();
        cin.ignore();

        string name;
        getline(cin, name);
        seats(file);

        cout << "============================================\n";
        cout << "Please chose a seat!\n";
        while (true) {
            cin >> seat;
            pla = seat_filler(seat, file);
            if (pla[0] == "ERROR") {
                cout << "Seat is either occupied or not available\n";
            }
            else {
                break;
            }
        }
        int price = 0;
        cout << "============================================\n";
        cout << "The ticket is worth 500/-.\nPay the price: ";
        cin >> price;
        while (price != 500) {
            cout << "Please pay the correct amount!\n";
            cin >> price;
        }

        int serial = hash(name);
        cout << "============================================\n";
        cout << "\nDetails:\n\n";
        cout << "ID:\t" << serial << endl
            << "NAME:\t" << name << endl
            << "Seat:\t" << seat << endl
            << "Movie:\t" << movie << endl
            << "Money paid:\t" << price << endl;
        string book;
        cout << "\nDo you want to book it? Y/N\n";
        cin >> book;


        if (book == "Y" || book == "y") {

            m.closer(pla, file);

            s << serial << "," << name << "," << seat << "," << movie << "," << price << endl;
            system("CLS");
            cout << "Booked!\n";
        }
        else {
            system("CLS");
            cout << "Canceled!\n";

        }
        cout << "============================================\n";
        cout << "*\*Thank you*/*\n";
    }

    void seats(string file) {
        string* m = seat_filler("*", file);
        ifstream sf;
        string row = "";
        int to = 0;
        int a = 4, sp1 = 3, sea = 0;
        cout << "                                       SCREEN                   \n";
        cout << "     ----------------------------------------------------------------------------\n\n\n";
        while (a < 16) {
            if (a <= 4) {
                row = "A";
                for (int k = 0; k < sp1; k++)
                    cout << "\t";
            }
            else if (a <= 8) {
                row = "B";
                for (int k = 0; k < sp1 - 2; k++)
                    cout << "\t";
            }
            else if (a <= 16) {
                row = "C";
            }
            for (int i = 1; i <= a; i++) {
                if (i == 1)
                    cout << "     || ||";
                else {
                    cout << "   || ||";
                }
                if (i == a) {
                    cout << endl;
                }
            }
            if (a <= 4) {
                for (int k = 0; k < sp1; k++)
                    cout << "\t";
            }
            else if (a <= 8) {
                for (int k = 0; k < sp1 - 2; k++)
                    cout << " \t";
            }
            for (int i = 1; i <= a; i++) {
                if (i == 1)
                    cout << "     ||=||";
                else {
                    cout << "   ||=||";
                }
                if (i == a) {
                    cout << endl;
                }
            }
            if (sea == 0) {
                cout << "\t\t\t      ";
                for (int i = 0; i < 4; i++) {
                    if (m[i] == "FULL") {
                        cout << m[i] << "    ";
                    }
                    else
                        cout << m[i] << "      ";
                }
            }
            if (sea == 1) {
                cout << "\t      ";
                for (int i = 4; i < 12; i++) {
                    if (m[i] == "FULL") {
                        cout << m[i] << "    ";
                    }
                    else
                        cout << m[i] << "      ";
                }
            }
            if (sea == 2) {
                cout << "      ";
                for (int i = 12; i < 28; i++) {
                    if (m[i] == "FULL") {
                        cout << m[i] << "    ";
                    }
                    else
                        cout << m[i] << "      ";
                }

            }
            sea++;
            a = a * 2;
            if (a == 16)
                a = 10;
            cout << "\n";
            cout << "               -------------------------------------------------------\n";
        }
    }
    string* seat_filler(string seat, string file) {
        string* lay = new string[3];
        string* seats = new string[17];
        bool fi = true;
        string* m = new string[28];
        ifstream sf;
        int num = 4, to = 0;
        sf.open(file);
        for (int i = 0; i < 3; i++) {
            getline(sf, lay[i]);

            stringstream st(lay[i]);
            for (int k = 0; k < num; k++) {
                getline(st, seats[k], ',');
                if (seats[k] == seat) {
                    seats[k] = "FULL";
                    fi = false;
                }
                if (seat == "*") {
                    fi = false;
                }

                m[to] = seats[k];
                to++;

            }

            st.flush();
            st.clear();
            num = num * 2;
        }
        if (fi == true) {

            m[0] = "ERROR";
        }
        sf.close();
        return m;

    }
    string find_time(int select) {
        string dura;
        if (select == 1) {
            dura = "12:00 am to 2:00 am";
        }
        else if (select == 2) {
            dura = "12:00 pm to 02:00 pm";
        }
        else if (select == 3) {
            dura = "02:00 pm to 04:00 pm";
        }
        else if (select == 4) {
            dura = "04:00 pm to 06:00 pm";
        }
        else if (select == 5) {
            dura = "06:00 pm to 08:00 pm";
        }
        else if (select == 6) {
            dura = "08:00 pm to 10:00 pm";
        }
        else if (select == 7) {
            dura = "10:00 pm to 12:00 am";
        }
        return dura;
    }
    int hash(string word)
    {
        int seed = 131;
        unsigned long hash = 0;
        for (int i = 0; i < word.length(); i++)
        {
            hash = (hash * seed) + word[i];
        }
        return hash % 2000;
    }
};

struct L_node { // node class to hold data as an array

    string data = " "; //data user inputs similar to array
    L_node* next = NULL; //pointer to link to the next node
};
class linklist {
    L_node* head = NULL; //reference as a start of array
    L_node* tail = NULL; //reference as the end of the array
    L_node* temp = NULL; //reference to temporary hold pointers for linking nodes
    L_node* temp2 = NULL; //2nd reference to temporary hold pointers for linking nodes
    int Intializer = 0;  //this one runs the array in a way that '0'  value means the start of the linked list
    bool stopper = true; //to stop if linklist is empty
public:
    void clears() {
        head = NULL; //reference as a start of array
        tail = NULL; //reference as the end of the array
        temp = NULL; //reference to temporary hold pointers for linking nodes
        temp2 = NULL; //2nd reference to temporary hold pointers for linking nodes
        Intializer = 0;  //this one runs the array in a way that '0'  value means the start of the linked list
        stopper = true; //to stop if linklist is empty
    }
    //insert funtion which adds value as a queue to the linked list
    void insert(string user) {
        L_node* n = new L_node; //initialized 'n' a node class object
        if (Intializer == 0) { //only for the first step
            n->data = user; //saving user provided data in the member of node
            temp = n; //temp pointer now points to n class object
            head = n; // head is initialized as the first node
        }
        else { //once head is been initialized move ahead
            n->data = user;//saving user provided data in the member of node
            temp->next = n; //temp pointer pointing to previous node saves pointer 'n' in member 'next'
            temp = n; //temp pointer now points to n class object
            tail = n; //tail reference added to define the end of the list
        }
        Intializer++; //increment

    }

    //view funtion which Displays the whole linked list
    void view() { //this is a little tweeked code
        int j = 0;
        cout << "Current Inputs:\n\n";
        if (head == NULL) { //the exception, in case of an empty list, can be handled now!

            cout << "The list is empty! Please chose 1 and then try again!\n";
            return;
        }
        temp2 = head; //first node
        while (true) { // true untill ...
            if (temp2->next == NULL) { //for last value output then break the loop
                cout << temp2->data << endl; //pick data and output
                break;
            }
            else {
                string v = temp2->data; //pick up data
                if (tail == temp2) {//... happens
                    cout << v << endl;//output
                    break;
                }
                cout << v << endl; //output
                temp2 = temp2->next; //shift to next value 
                j++; //incement
            }
        }
    }
};
class records {
public:

    linklist l;
    int size = 5;
    user_manager um;
    ifstream rec;
    string* data = new string[size];
    void menu() {
        char chose = ' ';
        string st;
        while (true) {
            cout << "Press 1 to search records using linked list and stretchy array\nPress 2 to display all the previous records1\nPress a random number to Exit!\n";
            cin >> chose;
            switch (chose)
            {
            case '1':
                open();
                break;
            case '2':
                system("CLS");
                show();
                break;
            default:
                system("CLS");
                return;

            }
        }

    }
    void open() {

        l.clears();
        int u = 0;
        rec.open("ticket_records.csv");
        while (!rec.eof())
        {
            getline(rec, data[u]);
            if (u >= size - 1)
            {
                size = size + 5;
                string* Stretched_Array = new string[size];
                for (int i = 0; i <= u; i++)
                    Stretched_Array[i] = data[i];
                data = Stretched_Array; // Array size Stretched
            }
            l.insert(data[u]);
            u++;
        }
        rec.close();
        finder(data, u - 1);

    }
    void finder(string* st, int siz) {
        string* s = st;
        bool found = false;
        user_manager mu;
        int hk = 0;
        string* keys = new string[siz];
        string t;
        for (int k = 0; k < siz; k++) {
            stringstream stre(s[k]);
            getline(stre, keys[k], ',');
            getline(stre, t, ' ');
        }
        cout << "Please Enter your name!\n";
        string name = "";
        cin.clear();
        cin.ignore();
        getline(cin, name);

        hk = mu.hash(name);
        t = to_string(hk);
        for (int k = 0; k < siz; k++) {
            if (t == keys[k]) {
                cout << "Record!\n" << st[k] << endl;
                found = true;
                break;
            }

        }
        if (!found) {
            cout << "Record not found!\n";
        }
        else {
            cout << "RECORD FOUND!\n";
        }
    }
    void show() {
        rec.open("ticket_records.csv");
        l.view();
        rec.close();
    }
};

int main() {
    user_manager u;
    linklist l;
    int chose = -1;
    records r;
    cout << "Muhammad Hammad_bsee19020-project!\n";
    cout << "*WELCOME TO CINEMA TICKET BOOTH*\n";
    cout << "----------------------------------------\n";

    while (true) {
        cout << "Press 1 to book a Ticket!\nPress 2 to view records!\n";
        cin >> chose;
        switch (chose)
        {
        case 1:
            system("CLS");
            cout << "Ticket Booth Section\n";
            cout << "----------------------------------------\n";
            u.get_cus();
            break;
        case 2:
            system("CLS");
            cout << "Ticket Booth Section\n";
            cout << "----------------------------------------\n";
            r.menu();
            break;
        default:
            exit(0);

        }
    }


}