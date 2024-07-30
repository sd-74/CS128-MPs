#ifndef GROUP_HPP
#define GROUP_HPP

#include <iostream>
#include <vector>

#include "volunteer.hpp"

class Group {
public:
  void AddVolunteer(const Volunteer& vol);

  double GetAvgBuildingExp() const;

  int GetReturningMembers() const;

  double GetAvgStamina() const;

  friend std::ostream& operator<<(std::ostream& os, const Group& g_in);

  Volunteer& GetRandomVolunteer();

private:
  std::vector<Volunteer> volunteer_vect_;
};

std::ostream& operator<<(std::ostream& os, const Group& g_in);

#endif
