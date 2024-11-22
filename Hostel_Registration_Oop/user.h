#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User {
private:
    string id;
    string password;
    string name;
    string gender;
    int year;
public:
    // Constructor with string parameters
    User(string userId = "", string userPassword = "", string username = "", string usergender = "", int year = 0)
        : id(userId), password(userPassword), name(username), gender(usergender), year(year) {}

    // Getter for id
    string getId() {
        return id;
    }

    // Getter for password
    string getPassword() {
        return password;
    }

    // Getter for name
    string getName() {
        return name;
    }

    // Getter for gender
    string getGender() {
        return gender;
    }

    // Getter for year
    int getYear() {
        return year;
    }
};

// Initialize the global array of User objects
User users[4] = {
    User("a305", "1234", "Praveen", "male", 2),
    User("AP23110011293", "1234", "Nikhil", "male", 2),
    User("294", "1234", "Anya", "female", 1),
    User("AP23110011295","12345678","Arella Praveen Kumar","male",2)
};

#endif // USER_H
