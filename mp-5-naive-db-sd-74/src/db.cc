#include "db.hpp"

void Database::CreateTable(const std::string& table_name) {
  // if (tables_.contains(table_name)) {
  //   throw std::invalid_argument("has already");
  // }
  // tables_[table_name] = new DbTable();
  tables_.insert(std::make_pair(table_name, new DbTable()));
}
void Database::DropTable(const std::string& table_name) {
  if (tables_.contains(table_name)) {
    delete tables_[table_name];
    tables_.erase(table_name);
  } else {
    throw std::invalid_argument("doesnt have");
  }
}
DbTable& Database::GetTable(const std::string& table_name) {
  // if (tables_.contains(table_name)) {
  //   return *(tables_.at(table_name));
  // } else {
  //   throw std::invalid_argument("doesnt have");
  // }
  return *(tables_.at(table_name));
}

Database::Database(const Database& rhs) {
  for (const auto& [key, value] : rhs.tables_) {
    tables_[key] = new DbTable(*value);
  }
}
Database& Database::operator=(const Database& rhs) {
  if (this == &rhs) {
    return *this;
  }
  for (const auto& [key, value] : tables_) {
    delete value;
  }
  tables_.clear();

  for (const auto& [key, value] : rhs.tables_) {
    tables_[key] = new DbTable(*value);
  }
  return *this;
}
Database::~Database() {
  for (const auto& [key, value] : tables_) {
    delete value;
  }
  tables_.clear();
}

std::ostream& operator<<(std::ostream& os, const Database& db) {
  for (const auto& [key, value] : db.tables_) {
    os << value;
  }
  return os;
}
