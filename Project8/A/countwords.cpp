/*
 *
 * Darian Marvel
 * 12/1/2021
 * Completing Project 8, Exercise A for CS311
 *
*/

#include <iostream>
#include <fstream>
#include <map>

using std::ifstream;
using std::map;
using std::cout;
using std::cin;
using std::endl;
using std::getline;
using std::string;

int main() {

  string filename;

  // Get the name of the file

  cout << "Enter the name of the file to read: ";
  getline(cin, filename);
  cout << endl;
  cout << "Attempting to read \"" << filename << "\"..." << endl;

  // Open the File

  ifstream file(filename);
  if(!file) {
    cout << "Could not open the file for reading." << endl;
    return 1;
  }

  map<string, int> words;
  string word;

  // Read the entire file, counting how many times each word appears

  while(true) {

    file >> word;

    if(!file) {
      if(file.eof()) {
        //End of file
        break;
      }

      cout << "Error during file read" << endl;
      return 1;
    }

    words[word]++;
  }

  cout << "Finished reading." << endl;
  cout << endl;

  // Print how many times each word appears,
  // keeping track of the number of distinct words

  int distinct = 0;
  for(auto i = words.begin(); i != words.end(); ++i) {
    ++distinct;
    cout << i->first << ": " << i->second << endl;
  }

  cout << endl << endl;
  cout << "Number of distinct words: " << distinct << endl;

  return 0;
}
