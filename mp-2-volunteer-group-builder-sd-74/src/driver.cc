#include <ctime>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

#include "constants.hpp"
#include "group.hpp"

/*Write your main driver in this file! Remember to seperate
out things into functions to help with readability and reusability.

See specifications for how to get started and
go to office hours if you need help!*/

void SwapElements(std::vector<Group>& groups) {
  size_t g1_index = rand() % groups.size();
  size_t g2_index = rand() % groups.size();
  while (g1_index == g2_index) {
    g2_index = rand() % groups.size();
  }
  Group& group1 = groups[g1_index];
  Group& group2 = groups[g2_index];
  Volunteer& vol1 = group1.GetRandomVolunteer();
  Volunteer& vol2 = group2.GetRandomVolunteer();
  std::swap(vol1, vol2);
}

bool AllSatisfied(const std::vector<Group>& groups) {
  for (const auto& group : groups) {
    if (group.GetAvgStamina() < kMinAvgStamina ||
        group.GetAvgBuildingExp() < kMinAvgBuildingExp ||
        group.GetReturningMembers() < kMinReturning) {
      return false;
    }
  }
  return true;
}

int main(int argc, char* argv[]) {
  // DO NOT EDIT THIS LINE or add another srand call.
  srand(time(nullptr));
  if (argc != 4) {
    return 1;
  }
  std::string in_file = argv[1];
  int no_volunteers = std::stoi(argv[2]);
  std::string out_file = argv[3];
  // sort into starting groups
  std::ifstream input{in_file};
  if (!input.is_open()) {
    return 1;
  }
  int num_groups = no_volunteers / kSizeGroups;
  std::vector<Group> groups(num_groups);
  std::string name;
  int building_experience = 0;
  int physical_stamina = 0;
  bool returning = false;
  int group_index = 0;
  while (input >> name >> building_experience >> physical_stamina >>
         returning) {
    Volunteer vol(name, building_experience, physical_stamina, returning);
    groups[group_index].AddVolunteer(vol);
    group_index = (group_index + 1) % num_groups;
  }
  unsigned int iterations = 0;
  while (!AllSatisfied(groups) && iterations < kMaxIterations) {
    SwapElements(groups);
    iterations++;
  }
  // open output file
  std::ofstream output(out_file);
  for (const auto& group : groups) {
    output << group << std::endl;
    output << std::endl;
  }
}