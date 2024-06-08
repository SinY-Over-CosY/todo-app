#include <iostream>
#include <fstream>
#include "json.hpp"
using json = nlohmann::json;

void homeScreen(){
    std::cout << "Enter instruction number" << std::endl << "1. View reminders \n2. ";
}

int main(){
    std::ifstream file("tos.json");
    json data = json::parse(file);

    std::cout << data["day1"];
}
