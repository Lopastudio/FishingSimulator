#ifndef VARIABLES_H
#define VARIABLES_H
#include <fstream>
#include <string>
#include <vector>

extern std::ofstream outfile; // for writing
extern std::ifstream infile;  // for reading
extern int points;
extern int RodDurability;
extern std::vector<std::string> inventory;
extern std::vector<std::string>::iterator iter;

#endif
