#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <vector>
#include<filesystem>
#include<iomanip>
#include <cstdlib> 
#include <windows.h>
#include "user.h"

using namespace std;

#define OLIVE_GREEN "\033[38;5;100m"  // Closest olive green shade
#define RESET_COLOR "\033[0m"         // Reset color to default

extern User users[4];
bool relogin(const string& userId) {
    ifstream file("students_data.csv");
    string line;

    while (getline(file, line)) {
        if (line.find(userId) != string::npos) {
            return true;
        }
    }
    return false;
     }

class Hostel {
protected:
    virtual void loadRoomData(map<string, pair<int, int>>& roomOccupancy) = 0;
    virtual void saveRoomData(const string& roomNumber, int currentOccupants) = 0;

public:
    string name,Rollnumber;
    int year;
    string room_number,hostelname;
    int level;
    int sharing;
    string type;

   

    virtual void selectLevel(int year, const string& type) {
        if (year > 1 && type == "Non-Ac") {
            cout << "Choose level from 7 to 10:" << endl;
            do {
                cin >> level;
                if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number between 7 and 10." << endl;
            } else if (level >7 || level > 10) {
                    cout << "Select a correct level between 7 and 10." << endl;
                }
            } while (level < 7 || level > 10);
        } else if (year > 1 && type == "Ac") {
            cout << "Choose level from 11 to 15:" << endl;
            do {
                cin >> level;
                if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number between 7 and 10." << endl;
            }else if (level < 11 || level > 15) {
                    cout << "Select a correct level between 11 and 15." << endl;
                }
            } while (level < 11 || level > 15);
        } else if (year == 1 && type == "Non-Ac") {
            cout << "Choose level from 1 to 5:" << endl;
            do {
                cin >> level;
                if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number between 7 and 10." << endl;
            } else if (level < 1 || level > 5) {
                    cout << "Select a correct level between 1 and 5." << endl;
                }
            } while (level < 1 || level > 5);
        } else if (year == 1 && type == "Ac") {
            level =6;
            cout << "Only 6th floor is AC for first-year students." << endl;
        }
        cout << "You selected level " << level << "." << endl;
    }

    string roomType() {
        cout << "Select room type:" << endl;
        cout << "1. AC" << endl << "2. Non-AC" << endl;

        string choice;
       

        while (true) {
            cin >> choice;
            if (choice == "1") {
                type = "Ac";
                break;
            } else if (choice == "2") {
                type = "Non-Ac";
                break;
            } else {
                cout << "Please select a correct option." << endl;
            }
        }
        return type;
    }
     void selectRoom() {
        map<string, pair<int, int>> roomOccupancy;
        loadRoomData(roomOccupancy);

        cout << "Rooms with vacancies:" << endl;
         cout << left << setw(15) << "Room Number" 
                     << setw(20) << "Available Beds" 
                     << setw(15) << "Room Sharing" 
                     << endl<<endl;
        for (const auto& room : roomOccupancy) {
            int currentOccupants = room.second.first;
            int maxCapacity = room.second.second;
              
            int available=maxCapacity-currentOccupants;
            if (currentOccupants < maxCapacity) {
                cout << left << setw(20) << room.first 
                             << setw(20) << available 
                             << setw(15) << maxCapacity 
                             << endl << endl;
            }
        }

        string roomNumber;
        cout << "Enter the room number you wish to select: ";
        bool found=false;
       while(!found){
        cin >> roomNumber;
        room_number=roomNumber;
        if (roomOccupancy.find(roomNumber) != roomOccupancy.end()) {
            int& currentOccupants = roomOccupancy[roomNumber].first;
            int& maxCapacity = roomOccupancy[roomNumber].second;
            sharing=maxCapacity;

            found=true;

            if (currentOccupants >= maxCapacity) {
                cout << "Room " << roomNumber << " is full. Please choose another room." << endl;
            } else {
                currentOccupants++;
                cout << "Room " << roomNumber << " selected successfully. Current occupants: " 
                     << currentOccupants << endl;
                saveRoomData(roomNumber, currentOccupants);
            }
            break;
        } if(!found) {
            cout << "Room " << roomNumber << " does not exist." << endl;
            
        }
       }
    }
     void display(string n,int y,string r,string s){
        name = n;
        year = y;
        Rollnumber = r;
        hostelname = s;

        // Open a CSV file for appending (creates if not exists)
       bool file_exists = std::filesystem::exists("students_data.csv");
        bool file_empty = (file_exists && std::filesystem::file_size("students_data.csv") == 0);

        // Open the CSV file for appending (creates it if it doesn’t exist)
        ofstream file("students_data.csv", ios::app);

        // If the file is open, write data to it
        if (file.is_open()) {
            // Write the headers if the file is empty or newly created
            if (!file_exists || file_empty) {
                file << "Name,Year,Roll Number,Hostel Name,Room Number,Room Type" << endl;
            }

            // Writing the student details to the CSV file
            file << name << "," << year << "," << Rollnumber << "," << hostelname << "," << room_number << "," << sharing << "-sharing " << type << endl;

            // Also print details to console
            cout << "Name: " << name << endl;
            cout << "Roll Number: " << Rollnumber << endl;
            cout << "Year: " << year << endl;
            cout << "Hostel Name: " << hostelname << endl;
            cout << "Room Number: " << room_number << endl;
            cout << "Room Type: " << sharing << "-sharing " << type << endl;
        } else {
            cerr << "Unable to open file" << endl;
        }

        // Close the file after writing
        file.close();
    }
    
    void payment(){
        if(sharing== 2 && type=="Non-Ac"){
            cout<<endl<<"\t\t\t\t\t"<<"**Pay amount Rs:1,80,000 at finance department**";
        }else if(sharing==2 && type=="Ac"){
            cout<<endl<<"\t\t\t\t\t"<<"**Pay amount Rs:2,00,000 at finance department**";
        }else if(sharing==3 && type=="Non-Ac"){
            cout<<endl<<"\t\t\t\t\t"<<"**Pay amount Rs:1,55,000 at finance department**";
        }else if(sharing ==3 && type=="Ac"){
            cout<<endl<<"\t\t\t\t\t"<<"**Pay amount Rs:1,80,000 at finance department**";
        }else if(sharing==4 && type=="Non-Ac"){
            cout<<endl<<"\t\t\t\t\t"<<"**Pay amount Rs:1,35,000 at finance department**";
        }else if(sharing==4 && type=="Ac"){
            cout<<endl<<"\t\t\t\t\t"<<"**Pay amount Rs:1,55,000 at finance department**";
        }else if(sharing==5 && type=="Non-Ac"){
            cout<<endl<<"\t\t\t\t\t"<<"**Pay amount Rs:1,25,000 at finance department**";
        }else if(sharing==5 && type=="Ac"){
            cout<<endl<<"\t\t\t\t\t"<<"**Pay amount Rs:1,35,000 at finance department**";
        }else if(sharing==10 && type=="Non-Ac"){
            cout<<endl<<"\t\t\t\t\t"<<"**Pay amount Rs:1,05,000 at finance department**";
        }else if(sharing==10 && type=="Ac"){
            cout<<endl<<"\t\t\t\t\t"<<"**Pay amount Rs:1,25,000 at finance department**";
        }
        Sleep(10000);
        cout<<endl<<endl<<endl<<endl;
        cout <<"\t\t\t\t\t\t"<< "╭━━━━┳╮╱╱╱╱╱╱╱╭╮╱╱╭╮╱╱╭╮" << endl;
        cout <<"\t\t\t\t\t\t"<< "┃╭╮╭╮┃┃╱╱╱╱╱╱╱┃┃╱╱┃╰╮╭╯┃" << endl;
        cout <<"\t\t\t\t\t\t"<< "╰╯┃┃╰┫╰━┳━━┳━╮┃┃╭╮╰╮╰╯╭┻━┳╮╭╮" << endl;
        cout <<"\t\t\t\t\t\t"<< "╱╱┃┃╱┃╭╮┃╭╮┃╭╮┫╰╯╯╱╰╮╭┫╭╮┃┃┃┃" << endl;
        cout <<"\t\t\t\t\t\t"<< "╱╱┃┃╱┃┃┃┃╭╮┃┃┃┃╭╮╮╱╱┃┃┃╰╯┃╰╯┃" << endl;
        cout <<"\t\t\t\t\t\t"<< "╱╱╰╯╱╰╯╰┻╯╰┻╯╰┻╯╰╯╱╱╰╯╰━━┻━━╯" << endl;
        
        Sleep(5000);
        system("CLS");
        system("project1.exe");

    }


    
};

class Ganga : public Hostel {
protected:
    void loadRoomData(map<string, pair<int, int>>& roomOccupancy) override {
        ifstream inputFile("ganga_rooms.txt");
        if (inputFile.is_open()) {
            string roomNumber;
            int occupants, maxCapacity;
            while (inputFile >> roomNumber >> occupants >> maxCapacity) {
               if (roomNumber.substr(0, to_string(level).length()) == to_string(level)) {
                    string roomNumberPart = roomNumber.substr(to_string(level).length());
                if (roomNumberPart.length() == 2 && stoi(roomNumberPart) > 0) {
                    roomOccupancy[roomNumber] = {occupants, maxCapacity};
                }
                }
            }
            inputFile.close();
        } else {
            cout << "Error loading Ganga room data." << endl;
        }
    }

    void saveRoomData(const string& roomNumber, int currentOccupants) override {
        ifstream inputFile("ganga_rooms.txt");
        if (!inputFile.is_open()) {
            cout << "Error opening file for reading data." << endl;
            return;
        }

        vector<string> lines;
        string line;
        bool updated = false;

        while (getline(inputFile, line)) {
            istringstream iss(line);
            string currentRoom;
            int occupants, maxCapacity;

            iss >> currentRoom >> occupants >> maxCapacity;

            if (currentRoom == roomNumber) {
                line = roomNumber + " " + to_string(currentOccupants) + " " + to_string(maxCapacity);
                updated = true;
            }
            lines.push_back(line);
        }
        inputFile.close();

        if (!updated) {
            cout << "Room number not found in file." << endl;
            return;
        }

        ofstream outputFile("ganga_rooms.txt", ios::trunc);
        if (!outputFile.is_open()) {
            cout << "Error opening file for writing data." << endl;
            return;
        }

        for (const auto& updatedLine : lines) {
            outputFile << updatedLine << endl;
        }
        outputFile.close();
    }


};

class Vedhavathi : public Hostel {
protected:
    void loadRoomData(map<string, pair<int, int>>& roomOccupancy) override {
        ifstream inputFile("vedhavathi_rooms.txt");
        if (inputFile.is_open()) {
            string roomNumber;
            int occupants, maxCapacity;
            while (inputFile >> roomNumber >> occupants >> maxCapacity) {
               if (roomNumber.substr(0, to_string(level).length()) == to_string(level)) {
                    string roomNumberPart = roomNumber.substr(to_string(level).length());
                if (roomNumberPart.length() == 2 && stoi(roomNumberPart) > 0) {
                    roomOccupancy[roomNumber] = {occupants, maxCapacity};
                }
                }
            }
            inputFile.close();
        } else {
            cout << "Error loading Vedhavathi room data." << endl;
        }
    }

    void saveRoomData(const string& roomNumber, int currentOccupants) override {
        ifstream inputFile("vedhavathi_rooms.txt");
        if (!inputFile.is_open()) {
            cout << "Error opening file for reading data." << endl;
            return;
        }

        vector<string> lines;
        string line;
        bool updated = false;

        while (getline(inputFile, line)) {
            istringstream iss(line);
            string currentRoom;
            int occupants, maxCapacity;

            iss >> currentRoom >> occupants >> maxCapacity;

            if (currentRoom == roomNumber) {
                line = roomNumber + " " + to_string(currentOccupants) + " " + to_string(maxCapacity);
                updated = true;
            }
            lines.push_back(line);
        }
        inputFile.close();

        if (!updated) {
            cout << "Room number not found in file." << endl;
            return;
        }

        ofstream outputFile("vedhavathi_rooms.txt", ios::trunc);
        if (!outputFile.is_open()) {
            cout << "Error opening file for writing data." << endl;
            return;
        }

        for (const auto& updatedLine : lines) {
            outputFile << updatedLine << endl;
        }
        outputFile.close();
    }


};
class Narmadha : public Hostel {
protected:
    void loadRoomData(map<string, pair<int, int>>& roomOccupancy) override {
        ifstream inputFile("narmadha_rooms.txt");
        if (inputFile.is_open()) {
            string roomNumber;
            int occupants, maxCapacity;
            while (inputFile >> roomNumber >> occupants >> maxCapacity) {
                 if (roomNumber.substr(0, to_string(level).length()) == to_string(level)) {
                    string roomNumberPart = roomNumber.substr(to_string(level).length());
                if (roomNumberPart.length() == 2 && stoi(roomNumberPart) > 0) {
                    roomOccupancy[roomNumber] = {occupants, maxCapacity};
                }
                }
            }
            inputFile.close();
        } else {
            cout << "Error loading Narmadha room data." << endl;
        }
    }

    void saveRoomData(const string& roomNumber, int currentOccupants) override {
        ifstream inputFile("narmadha_rooms.txt");
        if (!inputFile.is_open()) {
            cout << "Error opening file for reading data." << endl;
            return;
        }

        vector<string> lines;
        string line;
        bool updated = false;

        while (getline(inputFile, line)) {
            istringstream iss(line);
            string currentRoom;
            int occupants, maxCapacity;

            iss >> currentRoom >> occupants >> maxCapacity;

            if (currentRoom == roomNumber) {
                line = roomNumber + " " + to_string(currentOccupants) + " " + to_string(maxCapacity);
                updated = true;
            }
            lines.push_back(line);
        }
        inputFile.close();

        if (!updated) {
            cout << "Room number not found in file." << endl;
            return;
        }

        ofstream outputFile("narmadha_rooms.txt", ios::trunc);
        if (!outputFile.is_open()) {
            cout << "Error opening file for writing data." << endl;
            return;
        }

        for (const auto& updatedLine : lines) {
            outputFile << updatedLine << endl;
        }
        outputFile.close();
    }


};

class Godhavari : public Hostel {
protected:
    void loadRoomData(map<string, pair<int, int>>& roomOccupancy) override {
        ifstream inputFile("godhavari_rooms.txt");
        if (inputFile.is_open()) {
            string roomNumber;
            int occupants, maxCapacity;
            while (inputFile >> roomNumber >> occupants >> maxCapacity) {
               if (roomNumber.substr(0, to_string(level).length()) == to_string(level)) {
                    string roomNumberPart = roomNumber.substr(to_string(level).length());
                if (roomNumberPart.length() == 2 && stoi(roomNumberPart) > 0) {
                    roomOccupancy[roomNumber] = {occupants, maxCapacity};
                }
                }
            }
            inputFile.close();
        } else {
            cout << "Error loading Godhavari room data." << endl;
        }
    }

    void saveRoomData(const string& roomNumber, int currentOccupants) override {
        ifstream inputFile("godhavari_rooms.txt");
        if (!inputFile.is_open()) {
            cout << "Error opening file for reading data." << endl;
            return;
        }

        vector<string> lines;
        string line;
        bool updated = false;

        while (getline(inputFile, line)) {
            istringstream iss(line);
            string currentRoom;
            int occupants, maxCapacity;

            iss >> currentRoom >> occupants >> maxCapacity;

            if (currentRoom == roomNumber) {
                line = roomNumber + " " + to_string(currentOccupants) + " " + to_string(maxCapacity);
                updated = true;
            }
            lines.push_back(line);
        }
        inputFile.close();

        if (!updated) {
            cout << "Room number not found in file." << endl;
            return;
        }

        ofstream outputFile("godhavari_rooms.txt", ios::trunc);
        if (!outputFile.is_open()) {
            cout << "Error opening file for writing data." << endl;
            return;
        }

        for (const auto& updatedLine : lines) {
            outputFile << updatedLine << endl;
        }
        outputFile.close();
    }


};

class Krishna : public Hostel {
protected:
    void loadRoomData(map<string, pair<int, int>>& roomOccupancy) override {
        ifstream inputFile("krishna_rooms.txt");
        if (inputFile.is_open()) {
            string roomNumber;
            int occupants, maxCapacity;
            while (inputFile >> roomNumber >> occupants >> maxCapacity) {
               if (roomNumber.substr(0, to_string(level).length()) == to_string(level)) {
                    string roomNumberPart = roomNumber.substr(to_string(level).length());
                if (roomNumberPart.length() == 2 && stoi(roomNumberPart) > 0) {
                    roomOccupancy[roomNumber] = {occupants, maxCapacity};
                }
                }
            }
            inputFile.close();
        } else {
            cout << "Error loading Krishna room data." << endl;
        }
    }

    void saveRoomData(const string& roomNumber, int currentOccupants) override {
        ifstream inputFile("krishna_rooms.txt");
        if (!inputFile.is_open()) {
            cout << "Error opening file for reading data." << endl;
            return;
        }

        vector<string> lines;
        string line;
        bool updated = false;

        while (getline(inputFile, line)) {
            istringstream iss(line);
            string currentRoom;
            int occupants, maxCapacity;

            iss >> currentRoom >> occupants >> maxCapacity;

            if (currentRoom == roomNumber) {
                line = roomNumber + " " + to_string(currentOccupants) + " " + to_string(maxCapacity);
                updated = true;
            }
            lines.push_back(line);
        }
        inputFile.close();

        if (!updated) {
            cout << "Room number not found in file." << endl;
            return;
        }

        ofstream outputFile("krishna_rooms.txt", ios::trunc);
        if (!outputFile.is_open()) {
            cout << "Error opening file for writing data." << endl;
            return;
        }

        for (const auto& updatedLine : lines) {
            outputFile << updatedLine << endl;
        }
        outputFile.close();
    }


};

Ganga ganga;
Vedhavathi vedhavathi;
Narmadha narmadha;
Godhavari godhavari;
Krishna krishna;



int main() {
    string id, pass;
    bool found = false;

    cout << OLIVE_GREEN;
     cout << "                               			 ░██████╗██████╗░███╗░░░███╗░░░░░░░█████╗░██████╗░" << endl;
    cout << "                              		         ██╔════╝██╔══██╗████╗░████║░░░░░░██╔══██╗██╔══██╗" << endl;
    cout << "                              			 ╚█████╗░██████╔╝██╔████╔██║█████╗███████║██████╔╝" << endl;
    cout << "                              	    		 ░╚═══██╗██╔══██╗██║╚██╔╝██║╚════╝██╔══██║██╔═══╝░" << endl;
    cout << "                              			 ██████╔╝██║░░██║██║░╚═╝░██║░░░░░░██║░░██║██║░░░░░" << endl;
    cout << "                             		         ╚═════╝░╚═╝░░╚═╝╚═╝░░░░░╚═╝░░░░░░╚═╝░░╚═╝╚═╝░░░░░" << endl;
    cout << RESET_COLOR;

    while (!found) {
        cout << "Enter ID: ";
        cin >> id;
        cout << "Enter password: ";
        cin >> pass;

        for (int i = 0; i < 4; i++) {
            if (id == users[i].getId() && pass == users[i].getPassword()) {
                cout << "Yes, user authenticated!" << endl;
                found = true;
                cout << "Name: " << users[i].getName() << endl;
                cout << "Gender: " << users[i].getGender() << endl;
                cout << "Year: " << users[i].getYear() << endl;
              

                string choice;
                string type;

                // Male Hostel Selection
                if(relogin(id)){
                    cout<<"User already Booked";

                }else{
                if (users[i].getGender() == "male") {
                    cout << "Select your hostel:" << endl;
                    cout << "1. Ganga" << endl;
                    cout << "2. Vedhavathi" << endl;

                    while (true) {
                        cin >> choice;
                        if (choice == "1") {
                           
                            type = ganga.roomType();
                            ganga.selectLevel(users[i].getYear(), type);
                            ganga.selectRoom();
                            string s="Ganga";
                            ganga.display(users[i].getName(),users[i].getYear(),users[i].getId(),s);
                            ganga.payment();
                            break;
                        } else if (choice == "2") {
                          
                            type = vedhavathi.roomType();
                            vedhavathi.selectLevel(users[i].getYear(), type);
                            vedhavathi.selectRoom();
                            string s="Vedhavathi";
                            vedhavathi.display(users[i].getName(),users[i].getYear(),users[i].getId(),s);
                            vedhavathi.payment();
                            break;
                        } else {
                            cout << "Invalid choice. Please enter 1 or 2: ";
                        }
                    }
                } 
                // Female Hostel Selection
                else if (users[i].getGender() == "female") {
                    cout << "Select your hostel:" << endl;
                    cout << "1. Narmadha" << endl;
                    cout << "2. Godhavari" << endl;
                    cout << "3. Krishna" << endl;

                    while (true) {
                        cin >> choice;
                        if (choice == "1") {
                           
                            type = narmadha.roomType();
                            narmadha.selectLevel(users[i].getYear(), type);
                            narmadha.selectRoom();
                            string s="Narmadha";
                            narmadha.display(users[i].getName(),users[i].getYear(),users[i].getId(),s);
                            narmadha.payment();
                            break;
                        } else if (choice == "2") {
                            
                            type = godhavari.roomType();
                            godhavari.selectLevel(users[i].getYear(), type);
                            godhavari.selectRoom();
                            string s="Godhavari";
                            godhavari.display(users[i].getName(),users[i].getYear(),users[i].getId(),s);
                            godhavari.payment();
                            break;
                        } else if (choice == "3") {
                           
                            type = krishna.roomType();
                            krishna.selectLevel(users[i].getYear(), type);
                            krishna.selectRoom();
                            string s="Krishna";
                            krishna.display(users[i].getName(),users[i].getYear(),users[i].getId(),s);
                            krishna.payment();
                            break;
                        } else {
                            cout << "Invalid choice. Please enter 1, 2, or 3: ";
                        }
                   
                    }
                }
                }
                }
       
        }
        if (!found) {
            cout << "Invalid ID or password. Please try again." << endl;
        }
    }
    return 0;
}
