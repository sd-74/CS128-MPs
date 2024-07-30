#include "group.hpp"

#include "volunteer.hpp"

void Group::AddVolunteer(const Volunteer& vol) {
  volunteer_vect_.push_back(vol);
}

double Group::GetAvgBuildingExp() const {
  double sum = 0;
  if (volunteer_vect_.empty()) return 0;
  for (size_t i = 0; i < volunteer_vect_.size(); i++) {
    sum += volunteer_vect_.at(i).GetBuildingExperience();
  }
  auto vector_size = static_cast<double>(volunteer_vect_.size());
  return sum / vector_size;
}

int Group::GetReturningMembers() const {
  int returners = 0;
  for (size_t i = 0; i < volunteer_vect_.size(); i++) {
    if (volunteer_vect_.at(i).IsReturning()) returners++;
  }
  return returners;
}

double Group::GetAvgStamina() const {
  double sum = 0;
  if (volunteer_vect_.empty()) return 0;
  for (size_t i = 0; i < volunteer_vect_.size(); i++) {
    sum += volunteer_vect_.at(i).GetPhysicalStamina();
  }
  auto vector_size = static_cast<double>(volunteer_vect_.size());
  return sum / vector_size;
}

std::ostream& operator<<(std::ostream& os, const Group& g_in) {
  // os << "This is the start of a group" << std::endl;
  os << "averages: " << g_in.GetAvgBuildingExp() << " " << g_in.GetAvgStamina()
     << " " << g_in.GetReturningMembers() << std::endl;
  for (size_t i = 0; i < g_in.volunteer_vect_.size(); i++) {
    os << g_in.volunteer_vect_.at(i).GetName() << std::endl;
  }
  return os;
}

Volunteer& Group::GetRandomVolunteer() {
  size_t random = rand() % volunteer_vect_.size();
  return volunteer_vect_.at(random);
}
