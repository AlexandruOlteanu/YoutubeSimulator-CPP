#include <bits/stdc++.h>
using namespace std;

struct date {
    int day, month, year;
};


struct location {
    char city[105];
    char country[105];
};

struct user { 
    char surname[105];
    char name[105];
    char username[105];
    char email[105];
    date birthday;
    location location;
    char password[105];
};

struct database {
    int nr_users;
    vector<user> users;
};

database db;


bool check_login(char email[105], char password[105]) {
     for(int i=0;i<db.nr_users; ++i) {
         if(strcmp(db.users[i].email, email) == 0 && strcmp(db.users[i].password, password) == 0) {
             return 1;
         }
     }
     return 0;
}

date extract_date(char val[105]) {
    date new_date;
    
    int p1 = -1, p2 = -1;
    for (int i = 0; i < strlen(val); ++i) {
        if (val[i] == '.') {
            if (p1 < 0) {
                p1 = i;
            }
            else if (p2 < 0) {
                p2 = i;
            }
        }
    }

    int x = 0;
    for (int i = 0; i < p1; ++i) {
        x = x * 10 + (val[i] - '0');
    }
    new_date.day = x;
    x = 0;
    for (int i = p1 + 1; i < p2; ++i) {
        x = x * 10 + (val[i] - '0');
    }
    new_date.month = x;
    x = 0;
    for (int i = p2 + 1; i < strlen(val); ++i) {
        x = x * 10 + (val[i] - '0');
    }
    new_date.year = x;

    return new_date;
}

location extract_location(char val[105]) {
    location new_location;
    int p=-1;
    for(int i=1;i<=strlen(val);i++){
        if(val[i]==','){
            p = i;
        }
    }
    char x[105];
    x[0] = '\0';
    for(int i=0;i<p;i++){
        x[i] = val[i];
    }
    x[p] = '\0';
    strcpy(new_location.country, x);
    x[0] = '\0';
    for(int i=p+2;i<strlen(val);i++){
        x[i - p - 2] = val[i];
    }
    x[strlen(val)] = '\0';
    strcpy(new_location.city, x);
    return new_location;
}

void login() {

}

int main() {


    ifstream fin("./Database/users.txt");
    fin >> db.nr_users;
    for (int i = 1; i <= db.nr_users; ++i) {
        user new_user;
        fin >> new_user.name;
        fin >> new_user.surname;
        fin >> new_user.username;
        fin >> new_user.email;
        char date1[105];
        fin >> date1;
        new_user.birthday = extract_date(date1);
        char loc[105];
        fin.get();
        fin.get(loc, 105);
        new_user.location = extract_location(loc);
        fin >> new_user.password;
        db.users.push_back(new_user);

    }


    cout << "############## Welcome to Youtube ##############\n\n";

    cout << "Plase choose your option:\n";
    cout << "1) Log In\n";
    cout << "2) Register\n";
    cout << "Enter Value... \n";
    string val;
    cin >> val;
    if (val == "1") {
        cout << "Please enter email and password\n";
        while (true) {
            cout << "Email: ";
            char email[105];
            cin >> email;
            cout << "Paswword: ";
            char password[105];
            cin >> password;
            if (!check_login(email, password)) {
                cout << "Sorry, wrong credentials, please try again:\n";
            }
            else {
                cout << "Logged In Succesfully\n";
                login();
                exit(0);
            }
        }
    }

}