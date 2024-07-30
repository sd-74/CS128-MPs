#include <iostream>

#include "functions.hpp"

int main(int argc, char** argv) {
  // Checks if arguments were passed correctly
  if (argc != 2) {
    std::cout << "Correct usage: ./bin/exec \"hawaiian word\"" << std::endl;
    return 1;
  }

  // initialize hawaiian_word with passed in argument
  std::string hawaiian_word = argv[1];
  // std::cout << GetPronunciation("aloha") << std::endl;
  //  prints the result of GetPronunciation to terminal
  std::cout << "how to pronounce the word " << GetPronunciation(hawaiian_word)
            << std::endl;
  // std::cout << "ProcessChar: " << ProcessCharacter('m', 'a', 'i') <<
  // std::endl; std::cout << "ProcessChar: " << ProcessCharacter('m', 'a', 'u')
  // << std::endl;
  //  std::cout << "to lower:   " << StringToLower("KAKAHIAKA") << std::endl;
  //   std::cout << "process character with h: " << ProcessCharacter('o', 'h',
  //   'a')
  //<< std::endl;
  //   std::cout << "pronounce:  " << Pronunciation("aloha") << std::endl;
}
