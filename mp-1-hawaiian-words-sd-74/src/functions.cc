#include "functions.hpp"

#include <cctype>
#include <iostream>
#include <stdexcept>

/**
 * TODO: Implement this function
 * @param word word to change to lowercase
 * @return result of changing every character in word to lowercase
 */
std::string StringToLower(const std::string& word) {
  std::string lowered;
  for (size_t i = 0; i < word.size(); i++) {
    lowered += static_cast<char>(std::tolower(word.at(i)));
  }
  return lowered;
}

/**
 * TODO: Implement this function
 * @param v1 first character in potential vowel group
 * @param v2 second character in potential vowel group
 * @return true if v1 and v2 form a valid vowel group
 */
bool IsVowelGroup(const char& v1, const char& v2) {
  char check1 = static_cast<char>(std::tolower(v1));
  char check2 = static_cast<char>(std::tolower(v2));
  if (check1 == 'a') {
    return (check2 == 'e' || check2 == 'i' || check2 == 'o' || check2 == 'u');
  } else if (check1 == 'e' || check1 == 'o') {
    return (check2 == 'i' || check2 == 'u');
  } else if (check1 == 'i') {
    return (check2 == 'u');
  } else if (check1 == 'u') {
    return (check2 == 'i');
  } else {
    return false;
  }
}

/**
 * TODO: Complete this function
 * @param v potential vowel character
 * @return true if v is a vowel
 */
bool IsVowel(const char& v) {
  char check = static_cast<char>(std::tolower(v));
  return (check == 'a' || check == 'e' || check == 'i' || check == 'o' ||
          check == 'u');
}

/**
 * TODO: Complete this function
 * @param c potential consonant character
 * @return true if c is a consonant
 */
bool IsConsonant(const char& c) {
  char check = static_cast<char>(std::tolower(c));
  return (check == 'p' || check == 'k' || check == 'h' || check == 'l' ||
          check == 'm' || check == 'n' || check == 'w');
}

/**
 * TODO: Implement this function
 * @param c character to check validity of
 * @return true if input c is a valid character in the Hawaiian language, false
 * otherwise
 */
bool IsValidCharacter(const char& c) {
  return (IsVowel(c) || IsConsonant(c) || c == ' ' || c == '\'');
}

/**
 * TODO: Implement this function
 * @param word word to check validity of
 * @return true if every character in word is a valid character in the Hawaiian
 * language, false otherwise
 */
bool IsValidWord(const std::string& word) {
  for (char c : word) {
    if (!(IsValidCharacter(c))) {
      return false;
    }
  }
  return true;
}

/**
 * TODO: Implement this function
 * @param c consonant to get pronunciation of
 * @param prev character before c, used for determining w translation
 *    set to null character as default if no value is passed in
 * @return pronunciation of the consonant c as a char
 */
char ConsonantPronunciation(const char& c, const char& prev) {
  if (c == 'w' && (prev == 'i' || prev == 'e')) {
    return 'v';
  } else {
    return c;
  }
}

/**
 * TODO: Implement this function
 * @param v1 first vowel in a vowel grouping
 * @param v2 second vowel in a vowel grouping
 * @return the pronunciation of the vowel grouping made up of v1 and v2
 * as a string
 */
std::string VowelGroupPronunciation(const char& v1, const char& v2) {
  if (v1 == 'a') {
    if (v2 == 'e' || v2 == 'i') {
      return "eye";
    } else if (v2 == 'o' || v2 == 'u') {
      return "ow";
    }
  } else if (v1 == 'e') {
    if (v2 == 'i') {
      return "ay";
    } else if (v2 == 'u') {
      return "eh-oo";
    }
  } else if (v1 == 'i' && v2 == 'u') {
    return "ew";
  } else if (v1 == 'o') {
    if (v2 == 'i') {
      return "oy";
    } else if (v2 == 'u') {
      return "ow";
    }
  } else if (v1 == 'u' && v2 == 'i') {
    return "ooey";
  }
  return "";
}

/**
 * TODO: Implement this function
 * @param v single vowel to get pronunciation of
 * @return the pronunciation of v as a string
 */
std::string SingleVowelPronunciation(const char& v) {
  if (v == 'a') {
    return "ah";
  } else if (v == 'e') {
    return "eh";
  } else if (v == 'i') {
    return "ee";
  } else if (v == 'o') {
    return "oh";
  } else if (v == 'u') {
    return "oo";
  }
  return "";
}

/**
 * TODO: Implement this function
 * @param prev first character in set of three passed to function
 * @param curr second character in set of three passed to function
 * @param next third character in set of three passed to function
 * @return pronunciation of curr using next and prev as needed to determine
 * result
 */
std::string ProcessCharacter(const char& prev,
                             const char& curr,
                             const char& next) {
  if (IsValidCharacter(curr)) {
    if (IsVowelGroup(curr, next)) {
      return VowelGroupPronunciation(curr, next);
    } else if (IsVowel(curr)) {
      return SingleVowelPronunciation(curr);
    } else if (IsConsonant(curr)) {
      return {ConsonantPronunciation(curr, prev)};
    } else if (curr == ' ' || curr == '\'') {
      return {curr};
    }
  }
  return "";
}

/**
 * TODO: Implement this function
 * @param word string to get pronunciation of
 * @return pronunciation of word
 */
std::string Pronunciation(const std::string& word) {
  std::string returning;
  char prev = ' ';
  char curr = word[0];
  char next = word[1];
  bool flag = false;
  bool include_last = true;
  returning += ProcessCharacter(prev, curr, next);
  if ((IsVowelGroup(curr, next) || IsVowel(curr)) &&
      (next != ' ' && next != '\'')) {
    returning += "-";
  }
  if (IsVowelGroup(curr, next)) {
    flag = true;
  }
  for (unsigned int i = 1; i < word.size() - 1; i++) {
    if (flag) {
      i++;
      flag = false;
    }
    prev = word.at(i - 1);
    curr = word.at(i);
    next = word.at(i + 1);
    returning += ProcessCharacter(prev, curr, next);
    if ((IsVowelGroup(curr, next) || IsVowel(curr)) &&
        (next != ' ' && next != '\'')) {
      returning += "-";
      if (IsVowelGroup(curr, next)) {
        i++;
        if (i == word.size() - 1) {
          include_last = false;
        }
      }
    }
  }
  if (include_last)
    returning += ProcessCharacter(word[word.size() - 2], word.back(), '8');
  if (returning.back() == '-') return returning.substr(0, returning.size() - 1);
  return returning;
}

/**
 * TODO: Implement this function
 * @param hawaiian_word word to get pronunciation of
 * @return the pronunciation of hawaiian_word as a string if valid
 *  and throws an invalid_argument error if not valid
 */
std::string GetPronunciation(const std::string& hawaiian_word) {
  std::string returning;
  std::string last = StringToLower(hawaiian_word);
  if (IsValidWord(last)) {
    std::string substring;

    std::string returning = Pronunciation(last);
    if (returning.back() == '-') {
      return returning.substr(0, returning.size() - 1);
    } else {
      return returning;
    }
  } else {
    throw std::invalid_argument("invalid");
  }
  return returning;
}