#include <iostream>
#include <string>
#include <fstream>
#include "json.hpp"
#include <conio.h>

using json = nlohmann::json;

// IMPORTANT
/*
    - use std::getline(std::cin, $variable) to handle inputs
        - std::cin delimits after spaces rather than line breaks
*/

// read all data from tos.json
json readJson(){
    std::ifstream file("tos.json");
    json data = json::parse(file);  // entire json file parsed into "data" json variable

    return data;
}

void nextScreen(){
    std::cout << std::endl << "Press any key to return to home screen";
    _getch();

    std::cout << std::endl << std::endl << "######################" << std::endl << std::endl;
}

// view all reminders
void viewRemindersAll(json& reminders){  // TODO: edit to include json parsing later
    std::cout << reminders.dump(4);

    nextScreen();
}

// create a new reminder
void createReminder(json& addReminder){
    std::string name;
    std::cout << "Enter reminder name: ";
    std::getline(std::cin, name);

    std::string date;  // change to date variable after including date library
    std::cout << "Enter date of reminder: ";
    std::getline(std::cin, date);

    std::string time;   // same as above for time library
    std::cout << "Enter reminder time: ";
    std::getline(std::cin, time);

    std::string description;
    std::cout << "Enter description (leave blank if nothing): ";
    std::getline(std::cin, description);

    addReminder[name]["date"] = date;
    addReminder[name]["time"] = time;
    addReminder[name]["description"] = description;

    std::ofstream file("tos.json");
    file << std::setw(4) << addReminder << std::endl; // write details to tos.json

    nextScreen();
}

void deleteReminder(json& deleteReminder){
    char delConf;
    std::string target;
    std::cout << "Enter reminder to delete: ";
    std::cin >> target;

    if (deleteReminder[target] == NULL) {    // validates target exists in json
        std::cout << "Reminder not found..." << std::endl;
    }
    else {  // if found, display reminder details and confirm deletion
        std::cout << "Reminder: " << target << std::endl << deleteReminder[target].dump(4) << std::endl;

        // get n or y from user to confirm deletion
        std::cout << "Are you sure you want to delete this reminder? (y/n)" << std::endl << "Confirm deletion: ";
        std::cin >> delConf;
    
        // confirm/cancel deletion
        if (delConf == 'n'){
            std::cout << "Cancelled deletion";
        }
        else if (delConf == 'y'){
            deleteReminder.erase(target);    // calls erase() method to delete target from deleteReminder json object

            std::ofstream file("tos.json");
            file << std::setw(4) << deleteReminder << std::endl;  // write new details to tos.json
        }
    }
    
    nextScreen();
}

void homeScreen(){
    json data = readJson();

    // get which instruction to execute by number
    std::cout << "Which instruction?" << std::endl << "1. View reminders \n2. Create reminder \n3. Delete reminder" << std::endl;
    std::string inst;

    bool validInst{false};

    while (validInst == false){
        std::cout << "Enter instruction: ";
        std::getline(std::cin, inst);

        if (inst == "1"){
            viewRemindersAll(data);
            validInst = true;
        }
        else if(inst == "2"){
            createReminder(data);
            validInst = true;
        }
        else if(inst == "3"){
            deleteReminder(data);
            validInst = true;
        }
        else{
            std::cout << "Please enter valid instruction" << std::endl;
        }
    }
}

int main(){
    bool running{true};

    while (running == true){
        homeScreen();
    }

    return 0;
}

// plan
//  EX - implement parsing to make reminders more readable