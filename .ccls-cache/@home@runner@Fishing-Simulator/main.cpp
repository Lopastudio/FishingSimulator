//(C) Patrik Nagy 2022-2024

#include "loadsave.cpp"
#include "variables.h"
#include <fstream>
#include <iostream>
#include <time.h>
using namespace std;
std::ofstream outfile;
std::ifstream infile;
std::vector<std::string> inventory;
std::vector<std::string>::iterator iter;

// ANSI escape codes for colors
const std::string RESET = "\033[0m";
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string CYAN = "\033[36m";
const std::string MAGENTA = "\033[35m";

bool save(const std::string &fname) {
  outfile.open(fname, std::ios::binary);
  if (!outfile.is_open()) {
    return false;
  }
  outfile.write(reinterpret_cast<const char *>(&points), sizeof(int));
  outfile.write(reinterpret_cast<const char *>(&RodDurability), sizeof(int));

  // Save the inventory size
  int inventorySize = inventory.size();
  outfile.write(reinterpret_cast<const char *>(&inventorySize), sizeof(int));

  // Save each item in the inventory
  for (const std::string &item : inventory) {
    int itemSize = item.size();
    outfile.write(reinterpret_cast<const char *>(&itemSize), sizeof(int));
    outfile.write(item.c_str(), itemSize);
  }

  outfile.close();
  return true;
}

void load(const std::string &fname) {
  infile.open(fname, std::ios::binary);
  if (!infile.is_open()) {
    std::cerr << RED << "Error opening file for reading. Maybe corrupted file?"
              << RESET << std::endl;
    return;
  }
  infile.read(reinterpret_cast<char *>(&points), sizeof(int));
  infile.read(reinterpret_cast<char *>(&RodDurability), sizeof(int));

  // Clear the inventory before loading
  inventory.clear();

  // Load the inventory size
  int inventorySize;
  infile.read(reinterpret_cast<char *>(&inventorySize), sizeof(int));

  // Load each item in the inventory
  for (int i = 0; i < inventorySize; ++i) {
    int itemSize;
    infile.read(reinterpret_cast<char *>(&itemSize), sizeof(int));
    std::string item;
    item.resize(itemSize);
    infile.read(&item[0], itemSize);
    inventory.push_back(item);
  }

  infile.close();
}

int points = 0;
int RodDurability = 250;

string asciiArt = CYAN +
                  "   _.-=-._     .-,  \n"
                  " .'       \"-.,' /  \n"
                  "(          _.  <   \n"
                  " `=.____.=\"  `._\\ \n" +
                  RESET;

string fishBoat =
    YELLOW + "                   v  ~.      v\n" +
    "          v           /|\n" + "                     / |          v\n" +
    "              v     /__|__\n" + "                  \\--------/\n" +
    "~~~~~~~~~~~~~~~~~~~`~~~~~~'~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" + RESET;

void print(string print) { cout << print; }
void helpm() { // im lazy to type cout <<
  print(CYAN + "HELP MENU\n\n" + RESET);
  print(CYAN + "fish - go fishing\n" + RESET);
  print(CYAN + "shop - go shopping\n" + RESET);
  // print("");
  print(CYAN + "stats - show your stats\n" + RESET);
  print(CYAN + "loadC - Load Custom GameSave\n" + RESET);
  print(CYAN + "save - save your progress\n" + RESET);
  print(CYAN + "saveC - save your progress into custom binary file.\n" + RESET);
  print(CYAN + "(Rev. Alpha 1.3)\n" + RESET);
}

void shop() {
  string shopinput;
  cout << MAGENTA << "SHOP\n\n" << RESET;
  cout << MAGENTA << "Item   -   Cost   -   ID\n" << RESET;
  cout << MAGENTA << "New Rod - 8 Points - rod\n" << RESET;
  cin >> shopinput;
  if (shopinput == "rod") {
    if (points > 8) {
      points -= 8;
      RodDurability += 550;
      cout << GREEN << "You bought a new rod!\n" << RESET;
    } else {
      cout << RED << "Not enough points!\n" << RESET;
    }
  }
}

void RandomFishName() {
  srand(time(NULL));
  // cout << RodDurability;
  if ((RodDurability < 0) || (RodDurability == 0)) {
    RodDurability = 0;
    cout << RED << "Your rod just broke :(. \n" << RESET;
  } else {
    int RandomIndex = rand() % 5;
    if ((RandomIndex == 1) || (RandomIndex == 2)) {
      string arrayNames[6] = {"Salmon", "Trout",   "Shark",
                              "Carp",   "Sardine", "Shit"};
      int arrayPoints[6] = {2, 3, 5, 3, 1, 3};
      int RanIndex = rand() % 5;
      points += arrayPoints[RanIndex];
      RodDurability -= 40;
      cout << CYAN << arrayNames[RanIndex] + "\n" << RESET;

      // Add the fish name to the inventory
      inventory.push_back(arrayNames[RanIndex]);
    } else {
      if ((RodDurability < 0) || (RodDurability == 0)) {
        cout << RED
             << "Your fishing rod just broke :( You need to buy a new one. \n"
             << RESET;
      } else {
        RodDurability -= 8;
        cout << YELLOW << "Nothing\n" << RESET;
      }
    }
  }
}

void goFishing() {
  cout << fishBoat;
  RandomFishName();
}

int main() {
  load("data.bin");
  int x;
  cout << asciiArt;
  cout << RED << "Fishing Simulator!\n" << RESET;
  cout << YELLOW << "By Patrik Nagy (https://lopastudio.sk)\n" << RESET;
  cout << GREEN
       << "Made in 2022-2024 as a learning project / introduction to C++ and I "
          "regret it, I should have chosen C but whatever\n"
       << RESET;
  cout << "\n\n\n\n";
  helpm();
  int i = 0;
  while (i < 5) {
    string uinput;
    cout << "Operation: \n";
    cin >> uinput;
    if (uinput == "fish") {
      goFishing();
    } else if (uinput == "points") {
      cout << "Points: ";
      cout << points;
      cout << "\n";
    } else if (uinput == "shop") {
      shop();
    } else if (uinput == "inv") {
      for (iter = inventory.begin(); iter != inventory.end(); iter++)
        cout << *iter << " ";
      cout << "\n";
    } else if (uinput == "stats") {
      cout << CYAN << "YOUR STATS\n" << RESET;
      cout << CYAN << "points: " << points << "\n" << RESET;
      cout << CYAN << "Rod Durability: " << RodDurability << "\n" << RESET;
    } else if (uinput == "save") {
      cout << "Saving data";
      if (!save("data.bin")) {
        cout << RED << "Error saving data\n" << RESET;
      } else {
        cout << GREEN << "Data saved successfully\n" << RESET;
      }
    } else if (uinput == "saveC") {
      string uuis;
      // cout << "Enter name of the new file to save: ";
      cin >> uuis;
      if (save(uuis)) {
        cout << GREEN << "Data saved successfully to " << uuis << "\n" << RESET;
      } else {
        cout << RED << "Error saving data to " << uuis << "\n" << RESET;
      }
    } else if (uinput == "loadC") {
      string uui;
      // cout << "Enter name of the binary file that contains your Custom Save:
      // ";
      cin >> uui;
      load(uui);
    } else if (uinput == "help") {
      helpm();
    } else {
      cout << RED << "Invalid Input!\n" << RESET;
    }

    getchar(); // Press any key to continue
  }
  return 0;
}
