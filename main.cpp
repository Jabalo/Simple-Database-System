#include<iostream>
#include<fstream>
#include<windows.h>
#include<string>
#include<conio.h>
#include <list>
#include <sstream>

using namespace std;

class AD {
    string title;
    string genre;
    int rating;

public:
    void set_title(string arg) {title = arg;};
    void set_genre(string arg) {genre = arg;};
    void set_rating(int arg) {rating = arg;};

    string get_title() {return title;};
    string get_genre() {return genre;};
    int get_rating() {return rating;};
};

list<AD> anime;

void objectify() {

    system("cls");
    ifstream myfile;
    myfile.open("mydb.dll");

    if (myfile.is_open()) {
        AD a;
        int count = 0;
        string line;

        while (myfile.good()) {
            getline(myfile, line);
            if (line != "") {

                string first = line.substr(0, line.find(" "));

                if (first == "TITLE:") {

                    istringstream({line.rbegin(), line.rend()}) >> line;
                    string last = {line.rbegin(), line.rend()};
                    a.set_title(last);
                    count+=1;

                } else if (first == "GENRE:") {

                    istringstream({line.rbegin(), line.rend()}) >> line;
                    string last = {line.rbegin(), line.rend()};
                    a.set_genre(last);
                    count+=1;

                } else if (first == "RATING:") {

                    istringstream({line.rbegin(), line.rend()}) >> line;
                    string last = {line.rbegin(), line.rend()};
                    a.set_rating(stoi(last));
                    count+=1;

                }

                if (count == 3) {
                    anime.push_back(a);
                    count = 0;
                }
            }
        }
    }

    myfile.close();
}

bool not_unique(string title){

    objectify();

    std::list<AD>::iterator it;
    for (it = anime.begin(); it != anime.end(); it++) {
        if (it->get_title() == title) {
            anime.clear();
            return true;
        }
    }
    anime.clear();
    return false;
}

void addItem() {
    string title;
    string genre;
    int rating;

    cout << "\nTITLE: ";
    cin >> title;

    if (not_unique(title)) {
        cout << "\nTHIS TITLE IS ALREADY IN THE DATABASE!";
        return;
    }

    cout << "\nGENRE: ";
    cin >> genre;

    cout << "\nRATING (_/10): ";
    cin >> rating;

    ofstream ofile;
    ofile.open("mydb.dll", ios::app);

    ofile << "\n";
    ofile << "TITLE: " + title;
    ofile << "\n";
    ofile << "GENRE: " + genre;
    ofile << "\n";
    ofile << "RATING: " + to_string(rating);


    ofile.close();
    cout << "\nSUCCESSFULLY ADDED!";
}

void deleteItem() {
    ifstream ifile;
    ofstream temp;

    string line;
    string delete_line;
    int count = 0;

    ifile.open("mydb.dll");
    temp.open("temp.dll", ios::app);
    cout << "ENTER TITLE TO DELETE: ";
    cin >> delete_line;

    while(ifile.good()) {
        getline(ifile, line);
        string full_line = "TITLE: " + delete_line;
        if ((line != full_line && count < 1) || count == 3) {
            temp << "\n" + line;
        }
        else {
            count += 1;
        }
    }
    temp.close();
    ifile.close();

    remove("mydb.dll");
    rename("temp.dll", "mydb.dll" );
    cout << "\nSUCCESSFULLY DELETED!";
}

void read() {
    system("cls");
    ifstream myfile;
    myfile.open("mydb.dll");
    if (myfile.is_open()) {
        string line;
        int count = 0;
        while(myfile.good()) {
            getline(myfile, line);
            cout << line << endl;
            count += 1;
            string first = line.substr(0, line.find(" "));
            if (first == "Rating:") {
                cout << "\n";
                count = 0;
            }

        }
        myfile.close();
    }
}

void getItem() {
    int choice;
    list<AD> items;

    ofstream list;
    list.open("list.dll", ios::app);

    string title;
    string genre;
    int rating;

    system("cls");
    objectify();

    cout << "WHAT ARE YOU SEARCHING FOR?" << endl;
    cout << "1. TITLE" << endl;
    cout << "2. GENRE" << endl;
    cout << "3. RATING" << endl;

    cin >> choice;
    switch (choice) {
        case 1: {
            cout << "ENTER TITLE: " << endl;
            cin >> title;

            std::list<AD>::iterator it;
            for (it = anime.begin(); it != anime.end(); it++) {
                if (it->get_title() == title) {
                    list << "\nTITLE: " + it->get_title();
                    list << "\nGENRE: " + it->get_genre();
                    list << "\nRATING: " + to_string(it->get_rating());
                    list << "\n";
                }
            }
            list.close();
            break;
        }
        case 2: {
            cout << "ENTER GENRE: " << endl;
            cin >> genre;

            std::list<AD>::iterator it;
            for (it = anime.begin(); it != anime.end(); it++) {
                if (it->get_genre() == genre) {
                    list << "\nTITLE: " + it->get_title();
                    list << "\nGENRE: " + it->get_genre();
                    list << "\nRATING: " + to_string(it->get_rating());
                    list << "\n";
                }
            }
            list.close();
            break;
        }
        case 3: {
            cout << "ENTER RATING: " << endl;
            cin >> rating;

            std::list<AD>::iterator it;
            for (it = anime.begin(); it != anime.end(); it++) {
                if (it->get_rating() == rating) {
                    list << "\nTITLE: " + it->get_title();
                    list << "\nGENRE: " + it->get_genre();
                    list << "\nRATING: " + to_string(it->get_rating());
                    list << "\n";
                }
            }
            list.close();
            break;
        }
        default:
            list.close();
            break;
    }

    ifstream ilist;
    ilist.open("list.dll");

    // Read elements in ilist.
    if (ilist.is_open()) {
        string line;
        while(ilist.good()) {
            getline(ilist, line);
            cout << line << endl;
        }
        ilist.close();
    }

    ifstream ifs("list.dll");
    ifs.close();
    ofstream ofs("list.dll", ios::out | ios::trunc);
    ofs.close();

    anime.clear();

}

void modify() {
    system("cls");

    string string_modify;
    string modified;

    cout << "\nWHAT WOULD YOU LIKE TO MODIFY? (TITLE, GENRE, RATING)";
    cin >> string_modify;

    string previous;
    cout << "\nWHAT WAS THE PREVIOUS ENTRY? ";
    cin >> previous;


    cout << "\n";
    cout << "CHANGE TO: ";
    cin >> modified;

    ifstream ifs;
    ofstream ofs;
    ifs.open("mydb.dll");
    ofs.open("mtemp.dll");

    if (ifs.is_open()) {
        string line;
        while(ifs.good()) {
            getline(ifs, line);
            string append = string_modify + ": " + previous;
            if (line == append) {
                string input = string_modify + ": " + modified;
                ofs << "\n";
                ofs << input;
            }
            else {
                ofs << "\n";
                ofs << line;
            }
        }
    }

    ifs.close();
    ofs.close();

    remove("mydb.dll");
    rename("mtemp.dll", "mydb.dll" );
    cout << "\nSUCCESSFULLY MODIFIED!";

}

void erase() {
    ifstream ifs("mydb.dll");
    ifs.close();
    ofstream ofs("mydb.dll", ios::out | ios::trunc);

    ofs.close();
    cout << "ALL DATA DELETED!" << endl;
}

void help() {
    system("cls");

    cout << "\n----------------------------------------------------------------------------------";
    cout << "\n";
    cout << "\nTHIS IS A SIMPLE DATABASE APPLICATION TO ORGANIZE THE ANIME TITLES I HAVE WATCHED.";
    cout << "\n";
    cout << "\n----------------------------------------------------------------------------------";
    cout << "\n";
    cout << "\nINTRUCTIONS: ";
    cout << "\n- ADD DATA will add new entries to database and requires a unique TITLE.";
    cout << "\n- DELETE DATA will delete an entry by TITLE.";
    cout << "\n- READ DATA will return a list of all entries in the database.";
    cout << "\n- GET DATA will filter all entries depending on TITLE, GENRE, or RATING.";
    cout << "\n- MODIFY DATA will allow user to modify an entry by TITLE, GENRE, or RATING.";
    cout << "\n- EMPTY DATABASE will clear everything in the database.";
    cout << "\n";
    cout << "\n----------------------------------------------------------------------------------";
}

int main(int argc, char* argv[])
{
    int choice;
    long double yes = 1;

    if(yes == 1) {
        system("cls");

        cout << "\n----------------------------------------------------------------------------------";
        cout << "\n----------------------------------------------------------------------------------";
        cout << "\n _____ _____ _____ _____ _____    ____  _____ _____ _____ _____ _____ _____ _____";
        cout << "\n|  _  |   | |     |     |   __|  |    ||  _  |_   _|  _  | __  |  _  |   __|   __|";
        cout << "\n|     | | | |-   -| | | |   __|  |  |  |     | | | |     | __ -|     |__   |   __|";
        cout << "\n|__|__|_|___|_____|_|_|_|_____|  |____/|__|__| |_| |__|__|_____|__|__|_____|_____|";
        cout << "\n";
        cout << "\n----------------------------------------------------------------------------------";
        cout << "\n----------------------------------------------------------------------------------";
        comp:
        cout << "\n\t\t\t------------------------------";
        cout << "\n\t\t\t\t1. ADD DATA" << endl;
        cout << "\n";
        cout << "\t\t\t\t2. DELETE DATA" << endl;
        cout << "\n";
        cout << "\t\t\t\t3. READ DATA" << endl;
        cout << "\n";
        cout << "\t\t\t\t4. GET DATA" << endl;
        cout << "\n";
        cout << "\t\t\t\t5. MODIFY DATA" << endl;
        cout << "\n";
        cout << "\t\t\t\t6. EMPTY DATABASE" << endl;
        cout << "\n";
        cout << "\t\t\t\t7. HELP" << endl;
        cout << "\n";
        cout << "\t\t\t\t8. EXIT" << endl;
        cout << "\n\t\t\t------------------------------";
        cout << "\n\t\t\t WHAT WOULD YOU LIKE TO DO?: ";
        cin >> choice;
        cout << "\n";

        switch (choice) {
            case 1: {
                addItem();
                goto comp;
            }
            case 2: {
                deleteItem();
                goto comp;
            }
            case 3: {
                read();
                goto comp;
            }
            case 4: {
                getItem();
                goto comp;
            }
            case 5: {
                modify();
                goto comp;
            }
            case 6: {
                erase();
                goto comp;
            }
            case 7: {
                help();
                goto comp;
            }
            case 8: {
                system("exit");
                break;
            }
            default: {
                system("exit");
            }
        }
    }

}