/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// Written By : Michael R. Nowak
// Date ......: 2023/05/29
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifdef CATCH_CONFIG_MAIN
#  undef CATCH_CONFIG_MAIN
#endif
#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>
#include <string>

#include "functions.hpp"

///////////////////////////////// StringToLower
////////////////////////////////////////////////

TEST_CASE("StringToLower", "[StringToLower]") {
  REQUIRE(StringToLower("aLOHA") == "aloha");
  REQUIRE(StringToLower("Kakahiaka") == "kakahiaka");
  REQUIRE(StringToLower("MaHALO") == "mahalo");
  REQUIRE(StringToLower("E Komo Mai") == "e komo mai");
  REQUIRE(StringToLower("humuhumunukunukuapua'a") == "humuhumunukunukuapua'a");
  REQUIRE(StringToLower("wahine") == "wahine");
}

///////////////////////////////// IsValidCharacter
////////////////////////////////////////////////

TEST_CASE("IsValidCharacter - Vowel",
          "[IsValidCharacter][IsValidCharacter - Vowel]") {
  REQUIRE(IsValidCharacter('a'));
  REQUIRE(IsValidCharacter('e'));
  REQUIRE(IsValidCharacter('i'));
  REQUIRE(IsValidCharacter('o'));
  REQUIRE(IsValidCharacter('u'));
}

TEST_CASE("IsValidCharacter - Consonant",
          "[IsValidCharacter][IsValidCharacter - Consonant]") {
  REQUIRE(IsValidCharacter('p'));
  REQUIRE(IsValidCharacter('k'));
  REQUIRE(IsValidCharacter('h'));
  REQUIRE(IsValidCharacter('l'));
  REQUIRE(IsValidCharacter('m'));
  REQUIRE(IsValidCharacter('n'));
  REQUIRE(IsValidCharacter('w'));
}

TEST_CASE("IsValidCharacter - Invalid",
          "[IsValidCharacter][IsValidCharacter - Invalid]") {
  REQUIRE_FALSE(IsValidCharacter('b'));
  REQUIRE_FALSE(IsValidCharacter('c'));
  REQUIRE_FALSE(IsValidCharacter('d'));
  REQUIRE_FALSE(IsValidCharacter('f'));
  REQUIRE_FALSE(IsValidCharacter('g'));
  REQUIRE_FALSE(IsValidCharacter('j'));
  REQUIRE_FALSE(IsValidCharacter('q'));
  REQUIRE_FALSE(IsValidCharacter('r'));
  REQUIRE_FALSE(IsValidCharacter('s'));
  REQUIRE_FALSE(IsValidCharacter('t'));
  REQUIRE_FALSE(IsValidCharacter('v'));
  REQUIRE_FALSE(IsValidCharacter('x'));
  REQUIRE_FALSE(IsValidCharacter('y'));
  REQUIRE_FALSE(IsValidCharacter('z'));
}

TEST_CASE("IsValidCharacter - Other",
          "[IsValidCharacter][IsValidCharacter - Other]") {
  REQUIRE(IsValidCharacter(' '));
  REQUIRE(IsValidCharacter('\''));
}

///////////////////////////////// IsValidWord
//////////////////////////////////////////////////////

TEST_CASE("IsValidWord", "[IsValidWord]") {
  REQUIRE(IsValidWord("aloha"));
  REQUIRE(IsValidWord("wahine"));
  REQUIRE(IsValidWord("mahalo"));
  REQUIRE(IsValidWord("humuhumunukunukuapua'a"));
  REQUIRE(IsValidWord("e komo mai"));
  REQUIRE_FALSE(IsValidWord("zebra"));
  REQUIRE_FALSE(IsValidWord("hello world"));
}

///////////////////////////////// IsVowelGroup
/////////////////////////////////////////////////////

TEST_CASE("IsVowelGroup - True", "[IsVowelGroup][IsVowelGroup - True]") {
  REQUIRE(IsVowelGroup('a', 'i'));
  REQUIRE(IsVowelGroup('a', 'e'));
  REQUIRE(IsVowelGroup('a', 'o'));
  REQUIRE(IsVowelGroup('a', 'u'));
  REQUIRE(IsVowelGroup('e', 'i'));
  REQUIRE(IsVowelGroup('e', 'u'));
  REQUIRE(IsVowelGroup('i', 'u'));
  REQUIRE(IsVowelGroup('o', 'i'));
  REQUIRE(IsVowelGroup('o', 'u'));
  REQUIRE(IsVowelGroup('u', 'i'));
}

TEST_CASE("IsVowelGroup - False", "[IsVowelGroup][IsVowelGroup - False]") {
  REQUIRE_FALSE(IsVowelGroup('a', 'a'));
  REQUIRE_FALSE(IsVowelGroup('e', 'o'));
  REQUIRE_FALSE(IsVowelGroup('o', 'a'));
  REQUIRE_FALSE(IsVowelGroup('u', 'e'));
  REQUIRE_FALSE(IsVowelGroup('u', 'a'));
  REQUIRE_FALSE(IsVowelGroup('k', 'a'));
  REQUIRE_FALSE(IsVowelGroup('u', 'w'));
  REQUIRE_FALSE(IsVowelGroup('d', 'a'));
  REQUIRE_FALSE(IsVowelGroup('x', 'z'));
}

///////////////////////////////// IsVowel
//////////////////////////////////////////////////////////

TEST_CASE("IsVowel - True", "[IsVowel][IsVowel - True]") {
  REQUIRE(IsVowel('a'));
  REQUIRE(IsVowel('e'));
  REQUIRE(IsVowel('i'));
  REQUIRE(IsVowel('o'));
  REQUIRE(IsVowel('u'));
}

TEST_CASE("IsVowel - False", "[IsVowel][IsVowel - False]") {
  REQUIRE_FALSE(IsVowel('b'));
  REQUIRE_FALSE(IsVowel('c'));
  REQUIRE_FALSE(IsVowel('d'));
  REQUIRE_FALSE(IsVowel('f'));
  REQUIRE_FALSE(IsVowel('g'));
  REQUIRE_FALSE(IsVowel('h'));
  REQUIRE_FALSE(IsVowel('j'));
  REQUIRE_FALSE(IsVowel('k'));
  REQUIRE_FALSE(IsVowel('l'));
  REQUIRE_FALSE(IsVowel('m'));
  REQUIRE_FALSE(IsVowel('n'));
  REQUIRE_FALSE(IsVowel('p'));
  REQUIRE_FALSE(IsVowel('q'));
  REQUIRE_FALSE(IsVowel('r'));
  REQUIRE_FALSE(IsVowel('s'));
  REQUIRE_FALSE(IsVowel('t'));
  REQUIRE_FALSE(IsVowel('v'));
  REQUIRE_FALSE(IsVowel('w'));
  REQUIRE_FALSE(IsVowel('x'));
  REQUIRE_FALSE(IsVowel('y'));
  REQUIRE_FALSE(IsVowel('z'));
  REQUIRE_FALSE(IsVowel(' '));
  REQUIRE_FALSE(IsVowel('\''));
}

///////////////////////////////// IsConsonant
//////////////////////////////////////////////////////

TEST_CASE("IsConsonant - True", "[IsConsonant][IsConsonant - True]") {
  REQUIRE(IsConsonant('p'));
  REQUIRE(IsConsonant('k'));
  REQUIRE(IsConsonant('h'));
  REQUIRE(IsConsonant('l'));
  REQUIRE(IsConsonant('m'));
  REQUIRE(IsConsonant('n'));
  REQUIRE(IsConsonant('w'));
}

TEST_CASE("IsConsonant - False", "[IsConsonant][IsConsonant - False]") {
  REQUIRE_FALSE(IsConsonant('a'));
  REQUIRE_FALSE(IsConsonant('b'));
  REQUIRE_FALSE(IsConsonant('c'));
  REQUIRE_FALSE(IsConsonant('d'));
  REQUIRE_FALSE(IsConsonant('e'));
  REQUIRE_FALSE(IsConsonant('f'));
  REQUIRE_FALSE(IsConsonant('g'));
  REQUIRE_FALSE(IsConsonant('i'));
  REQUIRE_FALSE(IsConsonant('j'));
  REQUIRE_FALSE(IsConsonant('o'));
  REQUIRE_FALSE(IsConsonant('q'));
  REQUIRE_FALSE(IsConsonant('r'));
  REQUIRE_FALSE(IsConsonant('s'));
  REQUIRE_FALSE(IsConsonant('t'));
  REQUIRE_FALSE(IsConsonant('u'));
  REQUIRE_FALSE(IsConsonant('v'));
  REQUIRE_FALSE(IsConsonant('x'));
  REQUIRE_FALSE(IsConsonant('y'));
  REQUIRE_FALSE(IsConsonant('z'));
  REQUIRE_FALSE(IsConsonant(' '));
  REQUIRE_FALSE(IsConsonant('\''));
}

///////////////////////////////// ConsonantPronunciation
///////////////////////////////////////////

TEST_CASE("ConsonantPronunciation", "[ConsonantPronunciation]") {
  REQUIRE(ConsonantPronunciation('p') == 'p');
  REQUIRE(ConsonantPronunciation('k') == 'k');
  REQUIRE(ConsonantPronunciation('l') == 'l');
  REQUIRE(ConsonantPronunciation('m') == 'm');
  REQUIRE(ConsonantPronunciation('n') == 'n');
  REQUIRE(ConsonantPronunciation('h') == 'h');
  REQUIRE(ConsonantPronunciation('w') == 'w');
  REQUIRE(ConsonantPronunciation('w', ' ') == 'w');
  REQUIRE(ConsonantPronunciation('w', 'a') == 'w');
  REQUIRE(ConsonantPronunciation('w', 'i') == 'v');
  REQUIRE(ConsonantPronunciation('w', 'e') == 'v');
  REQUIRE(ConsonantPronunciation('w', 'o') == 'w');
  REQUIRE(ConsonantPronunciation('w', 'u') == 'w');
}

///////////////////////////////// VowelGroupPronunciation
//////////////////////////////////////////

TEST_CASE("VowelGroupPronunciation", "[VowelGroupPronunciation]") {
  REQUIRE(VowelGroupPronunciation('a', 'i') == "eye");
  REQUIRE(VowelGroupPronunciation('a', 'e') == "eye");
  REQUIRE(VowelGroupPronunciation('a', 'o') == "ow");
  REQUIRE(VowelGroupPronunciation('a', 'u') == "ow");
  REQUIRE(VowelGroupPronunciation('e', 'i') == "ay");
  REQUIRE(VowelGroupPronunciation('e', 'u') == "eh-oo");
  REQUIRE(VowelGroupPronunciation('i', 'u') == "ew");
  REQUIRE(VowelGroupPronunciation('o', 'i') == "oy");
  REQUIRE(VowelGroupPronunciation('o', 'u') == "ow");
  REQUIRE(VowelGroupPronunciation('u', 'i') == "ooey");
}

///////////////////////////////// SingleVowelPronunciation
/////////////////////////////////////////

TEST_CASE("SingleVowelPronunciation", "[SingleVowelPronunciation]") {
  REQUIRE(SingleVowelPronunciation('a') == "ah");
  REQUIRE(SingleVowelPronunciation('e') == "eh");
  REQUIRE(SingleVowelPronunciation('i') == "ee");
  REQUIRE(SingleVowelPronunciation('o') == "oh");
  REQUIRE(SingleVowelPronunciation('u') == "oo");
}

///////////////////////////////// ProcessCharacter
/////////////////////////////////////////////////

TEST_CASE("ProcessCharacter - Consonant",
          "[ProcessCharacter][ProcessCharacter - Consonant]") {
  REQUIRE(ProcessCharacter('i', 'k', 'a') == "k");
  REQUIRE(ProcessCharacter('a', 'l', 'o') == "l");
  REQUIRE(ProcessCharacter('o', 'h', 'a') == "h");
  REQUIRE(ProcessCharacter('\0', 'm', 'a') == "m");
  REQUIRE(ProcessCharacter('u', 'n', 'u') == "n");
  REQUIRE(ProcessCharacter('a', 'p', 'u') == "p");
  REQUIRE(ProcessCharacter(' ', 'w', 'a') == "w");
  REQUIRE(ProcessCharacter('a', 'w', 'o') == "w");
  REQUIRE(ProcessCharacter('e', 'w', 'o') == "v");
  REQUIRE(ProcessCharacter('i', 'w', 'a') == "v");
}

TEST_CASE("ProcessCharacter - Vowel Group",
          "[ProcessCharacter][ProcessCharacter - Vowel Group]") {
  REQUIRE(ProcessCharacter('m', 'a', 'i') == "eye");
  REQUIRE(ProcessCharacter('m', 'a', 'u') == "ow");
  REQUIRE(ProcessCharacter('k', 'e', 'i') == "ay");
  REQUIRE(ProcessCharacter('a', 'a', 'i') == "eye");
  REQUIRE(ProcessCharacter('p', 'o', 'i') == "oy");
  REQUIRE(ProcessCharacter('i', 'a', 'o') == "ow");
  REQUIRE(ProcessCharacter('\'', 'e', 'u') == "eh-oo");
  REQUIRE(ProcessCharacter(' ', 'i', 'u') == "ew");
  REQUIRE(ProcessCharacter('\0', 'u', 'i') == "ooey");
}

TEST_CASE("ProcessCharacter - Single Vowel",
          "[ProcessCharacter][ProcessCharacter - Single Vowel]") {
  REQUIRE(ProcessCharacter('h', 'a', 'l') == "ah");
  REQUIRE(ProcessCharacter('u', 'a', 'a') == "ah");
  REQUIRE(ProcessCharacter('\0', 'e', 'k') == "eh");
  REQUIRE(ProcessCharacter('k', 'i', '\0') == "ee");
  REQUIRE(ProcessCharacter('m', 'o', ' ') == "oh");
  REQUIRE(ProcessCharacter('\'', 'u', 'n') == "oo");
}

TEST_CASE("ProcessCharacter - Other",
          "[ProcessCharacter][ProcessCharacter - Other]") {
  REQUIRE(ProcessCharacter('a', '\'', 'a') == "'");
  REQUIRE(ProcessCharacter('e', ' ', 'k') == " ");
  REQUIRE(ProcessCharacter('a', ' ', 'm') == " ");
}

///////////////////////////////// Pronunciation
////////////////////////////////////////////////////

TEST_CASE("Pronunciation - aloha", "[Pronunciation][Pronunciation - aloha]") {
  REQUIRE(Pronunciation("aloha") == "ah-loh-hah");
}

TEST_CASE("Pronunciation - e komo mai",
          "[Pronunciation][Pronunciation - e komo mai]") {
  REQUIRE(Pronunciation("e komo mai") == "eh koh-moh meye");
}

TEST_CASE("Pronunciation - aloha awakea",
          "[Pronunciation][Pronunciation - aloha awakea]") {
  REQUIRE(Pronunciation("aloha awakea") == "ah-loh-hah ah-wah-keh-ah");
}

TEST_CASE("Pronunciation - humuhumunukunukuapua'a",
          "[Pronunciation][Pronunciation - humuhumunukunukuapua'a]") {
  REQUIRE(Pronunciation("humuhumunukunukuapua'a") ==
          "hoo-moo-hoo-moo-noo-koo-noo-koo-ah-poo-ah'ah");
}

TEST_CASE("Pronunciation - mahalo", "[Pronunciation][Pronunciation - mahalo]") {
  REQUIRE(Pronunciation("mahalo") == "mah-hah-loh");
}

TEST_CASE("Pronunciation - wahine", "[Pronunciation][Pronunciation - wahine]") {
  REQUIRE(Pronunciation("wahine") == "wah-hee-neh");
}

TEST_CASE("Pronunciation - iwa", "[Pronunciation][Pronunciation - iwa]") {
  REQUIRE(Pronunciation("iwa") == "ee-vah");
}

///////////////////////////////// GetPronunciation
/////////////////////////////////////////////////

TEST_CASE("GetPronunciation - alOHA", "[GetPronunciation][alOHA]") {
  std::string hawaiian_word = "alOHA";
  std::string correct_pronunciation = "ah-loh-hah";
  REQUIRE(GetPronunciation(hawaiian_word) == correct_pronunciation);
}

TEST_CASE("GetPronunciation - Mahalo", "[GetPronunciation][Mahalo]") {
  std::string hawaiian_word = "Mahalo";
  std::string correct_pronunciation = "mah-hah-loh";
  REQUIRE(GetPronunciation(hawaiian_word) == correct_pronunciation);
}

TEST_CASE("GetPronunciation - kane", "[GetPronunciation][kane]") {
  std::string hawaiian_word = "kane";
  std::string correct_pronunciation = "kah-neh";
  REQUIRE(GetPronunciation(hawaiian_word) == correct_pronunciation);
}

TEST_CASE("GetPronunciation - awakea", "[GetPronunciation][awakea]") {
  std::string hawaiian_word = "awakea";
  std::string correct_pronunciation = "ah-wah-keh-ah";
  REQUIRE(GetPronunciation(hawaiian_word) == correct_pronunciation);
}

TEST_CASE("GetPronunciation - maui", "[GetPronunciation][maui]") {
  std::string hawaiian_word = "maui";
  std::string correct_pronunciation = "mow-ee";
  REQUIRE(GetPronunciation(hawaiian_word) == correct_pronunciation);
}

TEST_CASE("GetPronunciation - Kakahiaka", "[GetPronunciation][Kakahiaka]") {
  std::string hawaiian_word = "Kakahiaka";
  std::string correct_pronunciation = "kah-kah-hee-ah-kah";
  REQUIRE(GetPronunciation(hawaiian_word) == correct_pronunciation);
}

TEST_CASE("GetPronunciation - makua", "[GetPronunciation][makua]") {
  std::string hawaiian_word = "makua";
  std::string correct_pronunciation = "mah-koo-ah";
  REQUIRE(GetPronunciation(hawaiian_word) == correct_pronunciation);
}

TEST_CASE("GetPronunciation - keiki", "[GetPronunciation][keiki]") {
  std::string hawaiian_word = "keiki";
  std::string correct_pronunciation = "kay-kee";
  REQUIRE(GetPronunciation(hawaiian_word) == correct_pronunciation);
}

TEST_CASE("GetPronunciation - Hoaloha", "[GetPronunciation][Hoaloha]") {
  std::string hawaiian_word = "Hoaloha";
  std::string correct_pronunciation = "hoh-ah-loh-hah";
  REQUIRE(GetPronunciation(hawaiian_word) == correct_pronunciation);
}

TEST_CASE("GetPronunciation - kaiapuni", "[GetPronunciation][kaiapuni]") {
  std::string hawaiian_word = "kaiapuni";
  std::string correct_pronunciation = "keye-ah-poo-nee";
  REQUIRE(GetPronunciation(hawaiian_word) == correct_pronunciation);
}

TEST_CASE("GetPronunciation - wahine", "[GetPronunciation][wahine]") {
  std::string hawaiian_word = "wahine";
  std::string correct_pronunciation = "wah-hee-neh";
  REQUIRE(GetPronunciation(hawaiian_word) == correct_pronunciation);
}

TEST_CASE("GetPronunciation - iwa", "[GetPronunciation][iwa]") {
  std::string hawaiian_word = "iwa";
  std::string correct_pronunciation = "ee-vah";
  REQUIRE(GetPronunciation(hawaiian_word) == correct_pronunciation);
}

TEST_CASE("GetPronunciation - Huaai", "[GetPronunciation][Huaai]") {
  std::string hawaiian_word = "Huaai";
  std::string correct_pronunciation = "hoo-ah-eye";
  REQUIRE(GetPronunciation(hawaiian_word) == correct_pronunciation);
}

TEST_CASE("GetPronunciation - Aloha awakea",
          "[GetPronunciation][Aloha-awakea]") {
  std::string hawaiian_word = "Aloha awakea";
  std::string correct_pronunciation = "ah-loh-hah ah-wah-keh-ah";
  REQUIRE(GetPronunciation(hawaiian_word) == correct_pronunciation);
}

TEST_CASE("GetPronunciation - keikikane", "[GetPronunciation][keikikane]") {
  std::string hawaiian_word = "keikikane";
  std::string correct_pronunciation = "kay-kee-kah-neh";
  REQUIRE(GetPronunciation(hawaiian_word) == correct_pronunciation);
}

TEST_CASE("GetPronunciation - E Komo MAI", "[GetPronunciation][E-Komo-MAI]") {
  std::string hawaiian_word = "E Komo MAI";
  std::string correct_pronunciation = "eh koh-moh meye";
  REQUIRE(GetPronunciation(hawaiian_word) == correct_pronunciation);
}

TEST_CASE("GetPronunciation - humuhumunukunukuapua'a",
          "[GetPronunciation][humuhumunukunukuapua'a]") {
  std::string hawaiian_word = "humuhumunukunukuapua'a";
  std::string correct_pronunciation =
      "hoo-moo-hoo-moo-noo-koo-noo-koo-ah-poo-ah'ah";
  REQUIRE(GetPronunciation(hawaiian_word) == correct_pronunciation);
}

TEST_CASE("GetPronunciation - Hello, World!", "[GetPronunciation][invalid-1]") {
  std::string invalid_word = "Hello, World!";
  REQUIRE_THROWS(GetPronunciation(invalid_word));
}

TEST_CASE("GetPronunciation - Zebras", "[GetPronunciation][invalid-2]") {
  std::string invalid_word = "Zebras";
  REQUIRE_THROWS(GetPronunciation(invalid_word));
}