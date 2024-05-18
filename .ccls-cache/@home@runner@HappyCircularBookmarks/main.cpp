#include <iostream>
#include <time.h>
using namespace std;

int points;
string asciiArt = "   _.-=-._     .-,  \n"
                  " .'       \"-.,' /  \n"
                  "(          _.  <   \n"
                  " `=.____.=\"  `._\\ \n";

void RandomFishName() {
  srand(time(NULL));

  string arrayNames[5] = {"Salmon", "Trout", "Shark", "Carp", "Sardine"};
  int arrayPoints[5] = {2, 3, 5, 3, 1};
  int RanIndex = rand() % 5;
  points += arrayPoints[RanIndex];
  cout << arrayNames[RanIndex] + "\n";
}

int main() {
  int x;
  cout << asciiArt;
  cout << "Fishing Simulator!\n";
  int i = 0;
  while (i < 5) {
    string uinput;
    cout << "Operation: \n";
    cin >> uinput;
    if (uinput == "fish") {
      RandomFishName();
    } else if (uinput == "points") {
      cout << "Points: ";
      cout << points;
      cout << "\n";
    } else {
      cout << "Invalid Input!";
    }

    getchar();
  }
  return 0;
}