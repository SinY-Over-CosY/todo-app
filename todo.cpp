#include <iostream>
#include <string>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;

// read all data from tos.json
json readJson(){
    std::ifstream file("tos.json");
    json data = json::parse(file);  // entire json file parsed into "data" json variable

    return data;
}

// view all reminders
void viewRemindersAll(json& reminders){  // TODO: edit to include json parsing later
    std::cout << reminders;
}

// create a new reminder
void createReminder(json& addReminder){
    std::string name;
    std::string date;  // change to date variable after including date library
    std::string time;   // same as above for time library
    std::string description;

    std::cout << "Enter reminder name: "; std::cin >> name;
    std::cout << "Enter date of reminder: "; std::cin >> date;
    std::cout << "Enter reminder time: "; std::cin >> time;
    std::cout << "Enter description (leave blank if nothing): "; std::cin >> description;

    addReminder[name]["date"] = date;
    addReminder[name]["time"] = time;
    addReminder[name]["description"] = description;

    std::ofstream file("tos.json"); // write details to tos.json
    file << std::setw(4) << addReminder << std::endl; 
}

void deleteReminder(json& deleteReminder){
    // sort json by name in alphabetical order (already in order lmao)
    // get name from user and use some search algo to find if it exists (don't need search algo, json handles itself)
    // testing json search
    std::string target;
    std::cout << "enter: ";
    std::cin >> target;
    std::cout << "Reminder: " << target << std::endl << deleteReminder[target] << std::endl;
    
    // if found, confirm deletion
    std::cout << "Are you sure you want to delete this reminder? (y/n)" << std::endl << "Confirm deletion: ";
    char delConf = ']';
    std::cin >> delConf;
    
    // delete from json
    if (delConf == 'n'){
        std::cout << "Cancelled deletion";
    }
    else if (delConf == 'y'){
        deleteReminder[target] = " ";
    }

}

void homeScreen(){
    json data = readJson();

    // get which instruction to execute by number
    std::cout << "Which instruction?" << std::endl << "1. View reminders \n2. Create reminder \n3. Delete reminder" << std::endl;
    int inst{0};
    std::cout << "Enter instruction: ";
    std::cin >> inst;

    if (inst == 1){
        viewRemindersAll(data);
    }
    else if(inst == 2){
        createReminder(data);
    }
    else if(inst == 3){

    }
}

int main(){
    //homeScreen();

    json data = readJson();
    deleteReminder(data);
}

// plan
//  - design and implement delete reminders
//  EX - implement parsing to make reminders more readable