#include "illini_book.hpp"

#include "utilities.hpp"

IlliniBook::IlliniBook(const std::string& people_fpath,
                       const std::string& relations_fpath) {
  std::ifstream uins(people_fpath);
  std::ifstream relationships(relations_fpath);
  std::string line;

  while (std::getline(uins, line)) {
    int uin = std::stoi(line);
    graph_[uin] = {};
    // line = "";
  }

  while (std::getline(relationships, line)) {
    std::vector<std::string> parts = utilities::Split(line, ',');
    int uin_1 = std::stoi(parts[0]);
    int uin_2 = std::stoi(parts[1]);
    std::string rel_type = parts[2];
    graph_[uin_1][uin_2] = rel_type;
    graph_[uin_2][uin_1] = rel_type;
  }
}

bool IlliniBook::AreRelated(int uin_1, int uin_2) const {
  std::set<int> visited;
  std::queue<int> q;

  q.push(uin_1);
  while (!q.empty()) {
    int current = q.front();
    if (current == uin_2) {
      return true;
    }
    visited.insert(current);
    for (auto i = graph_.at(current).begin(); i != graph_.at(current).end();
         i++) {
      if (!visited.contains(i->first)) {
        q.push(i->first);
      }
    }
    q.pop();
  }
  return false;
}
bool IlliniBook::AreRelated(int uin_1,
                            int uin_2,
                            const std::string& relationship) const {
  std::set<int> visited;
  std::queue<int> q;

  q.push(uin_1);
  while (!q.empty()) {
    int current = q.front();
    visited.insert(current);
    for (auto i = graph_.at(current).begin(); i != graph_.at(current).end();
         i++) {
      if (!visited.contains(i->first) && i->second == relationship) {
        if (i->first == uin_2) {
          return true;
        }
        q.push(i->first);
      }
    }
    q.pop();
  }
  return false;
}

int IlliniBook::GetRelated(int uin_1, int uin_2) const {
  if (uin_1 == uin_2) {
    return 0;
  }
  std::set<int> visited;
  std::queue<std::pair<int, int>> q;
  q.push({uin_1, 0});

  while (!q.empty()) {
    std::pair pair = q.front();
    int current = pair.first;
    int distance = pair.second + 1;
    if (current == uin_2) {
      return distance - 1;
    }
    visited.insert(current);
    for (auto i = graph_.at(current).begin(); i != graph_.at(current).end();
         i++) {
      if (!visited.contains(i->first)) {
        q.push({i->first, distance});
      }
    }
    q.pop();
  }
  return -1;
}
int IlliniBook::GetRelated(int uin_1,
                           int uin_2,
                           const std::string& relationship) const {
  std::set<int> visited;
  std::queue<std::pair<int, int>> q;
  q.push({uin_1, 0});

  while (!q.empty()) {
    std::pair pair = q.front();
    int current = pair.first;
    int distance = pair.second + 1;
    visited.insert(current);
    for (auto i = graph_.at(current).begin(); i != graph_.at(current).end();
         i++) {
      if (!visited.contains(i->first) && i->second == relationship) {
        if (i->first == uin_2) {
          return distance;
        }
        q.push({i->first, distance});
      }
    }
    q.pop();
  }
  return -1;
}

// bool IlliniBook::Contains(const std::vector<int>& vec, int value) const {
//   for (int element : vec) {
//     if (element == value) {
//       return true;
//     }
//   }
//   return false;
// }

std::vector<int> IlliniBook::GetSteps(int uin, int n) const {
  std::set<int> visited;
  std::set<int> steps_set;
  std::vector<int> steps;
  std::queue<std::pair<int, int>> q;

  q.push({uin, 0});
  visited.insert(uin);

  while (!q.empty()) {
    auto [current, distance] = q.front();
    q.pop();

    if (distance == n) {
      steps_set.insert(current);
    } else if (distance > n) {
      break;
    }
    for (const auto& edge : graph_.at(current)) {
      if (!visited.contains(edge.first)) {
        visited.insert(edge.first);
        q.push({edge.first, distance + 1});
      }
    }
  }
  steps.insert(steps.end(), steps_set.begin(), steps_set.end());
  return steps;
}

size_t IlliniBook::CountGroups() const {
  std::set<int> visited;
  size_t count = 0;

  for (auto const& current_edge : graph_) {
    if (!visited.contains(current_edge.first)) {
      std::queue<int> q;
      q.push(current_edge.first);
      while (!q.empty()) {
        int current = q.front();
        visited.insert(current);
        for (auto i = graph_.at(current).begin(); i != graph_.at(current).end();
             i++) {
          if (!visited.contains(i->first)) {
            q.push(i->first);
          }
        }
        q.pop();
      }
      count++;
    }
  }
  return count;
}
size_t IlliniBook::CountGroups(const std::string& relationship) const {
  std::set<int> visited;
  size_t count = 0;

  for (auto const& current_edge : graph_) {
    if (!visited.contains(current_edge.first)) {
      std::queue<int> q;
      q.push(current_edge.first);
      while (!q.empty()) {
        int current = q.front();
        visited.insert(current);
        for (auto i = graph_.at(current).begin(); i != graph_.at(current).end();
             i++) {
          if (!visited.contains(i->first) && i->second == relationship) {
            q.push(i->first);
          }
        }
        q.pop();
      }
      count++;
    }
  }
  return count;
}
size_t IlliniBook::CountGroups(
    const std::vector<std::string>& relationships) const {
  std::set<int> visited;
  size_t count = 0;

  for (auto const& current_edge : graph_) {
    if (!visited.contains(current_edge.first)) {
      std::queue<int> q;
      q.push(current_edge.first);
      while (!q.empty()) {
        int current = q.front();
        visited.insert(current);
        for (auto i = graph_.at(current).begin(); i != graph_.at(current).end();
             i++) {
          for (const auto& relation : relationships) {
            if (!visited.contains(i->first) && i->second == relation) {
              q.push(i->first);
              break;
            }
          }
        }
        q.pop();
      }
      count++;
    }
  }
  return count;
}
