#include "db_table.hpp"

const unsigned int kRowGrowthRate = 2;


void DbTable::AddColumn(const std::pair<std::string, DataType>& col_desc) {
  if (col_descs_.size() == row_col_capacity_) {
    row_col_capacity_ *= kRowGrowthRate;
    for (auto& pair : rows_) {
      void** new_array = new void*[row_col_capacity_];
      for (unsigned int i = 0; i < col_descs_.size(); i++) {
        new_array[i] = pair.second[i];
      }
      delete[] pair.second;
      pair.second = new_array;
    }
  }
  col_descs_.push_back(col_desc);
  for (auto& pair : rows_) {
    switch (col_desc.second) {
    case DataType::kString:
      pair.second[col_descs_.size() - 1] = new std::string("");
      break;
    case DataType::kInt:
      pair.second[col_descs_.size() - 1] = new int(0); 
      break;
    case DataType::kDouble:
      pair.second[col_descs_.size() - 1] = new double(0.0); 
      break;
    }
  }    
}

void DbTable::DeleteColumnByIdx(unsigned int col_idx) {
  if (col_idx >= col_descs_.size() || col_idx < 0) {
    throw std::out_of_range("invalid column index");
  }
  if (col_descs_.size() == 1 && !rows_.empty()) {
    throw std::runtime_error(
        "any table with at least one row must have at least one column");
  }
  for (auto& pair : rows_) {
    void** row_array = pair.second;
    void* col_val = row_array[col_idx];
    switch (col_descs_.at(col_idx).second) {
    case DataType::kString:
      delete static_cast<std::string*>(col_val);
      break;
    case DataType::kInt:
      delete static_cast<int*>(col_val);
      break;
    case DataType::kDouble:
      delete static_cast<double*>(col_val);
      break;
    }
    for (unsigned int i = col_idx; i < col_descs_.size() - 1; i++) {
      row_array[i] = row_array[i + 1];
    }
    row_array[col_descs_.size() - 1] = nullptr;
  }
  col_descs_.erase(col_descs_.begin() + col_idx);
}

void DbTable::AddRow(const std::initializer_list<std::string>& col_data) {
  if (col_data.size() != col_descs_.size()) {
    throw std::invalid_argument(
        "number of itmes in col data != number of columns in tables rows");
  }
  void** new_row = new void*[col_descs_.size()];
  size_t col_index = 0;
  for (const auto& data : col_data) {
    switch (col_descs_[col_index].second) {
    case DataType::kString:
      new_row[col_index] = new std::string(data);
      break;
    case DataType::kInt:
      new_row[col_index] = new int(std::stoi(data));
      break;
    case DataType::kDouble:
      new_row[col_index] = new double(std::stod(data));
      break;
    }
    col_index++;
  }
  rows_[next_unique_id_] = new_row;
  next_unique_id_++;
}
void DbTable::DeleteRowById(unsigned int id) {
  auto row_idx = rows_.find(id);
  if (row_idx == rows_.end()) {
    throw std::out_of_range("row with id doesnt exitst");
  }
  void** row = row_idx->second;
  for (size_t i = 0; i < col_descs_.size(); ++i) {
    switch (col_descs_[i].second) {
    case DataType::kString:
      delete static_cast<std::string*>(row[i]);
      break;
    case DataType::kInt:
      delete static_cast<int*>(row[i]);
      break;
    case DataType::kDouble:
      delete static_cast<double*>(row[i]);
      break;
    }
  }
  delete[] row;
  rows_.erase(row_idx);
}

DbTable::DbTable(const DbTable& rhs) {
  next_unique_id_ = rhs.next_unique_id_;
  row_col_capacity_ = rhs.row_col_capacity_;
  col_descs_ = rhs.col_descs_;

  for (const auto& pair : rhs.rows_) {
    unsigned int id = pair.first;
    void** row = pair.second;
    void** new_row = new void*[row_col_capacity_];
    for (size_t i = 0; i < col_descs_.size(); i++) {
      switch (col_descs_[i].second) {
      case DataType::kString:
        new_row[i] = new std::string(*static_cast<std::string*>(row[i]));
        break;
      case DataType::kInt:
        new_row[i] = new int(*static_cast<int*>(row[i]));
        break;
      case DataType::kDouble:
        new_row[i] = new double(*static_cast<double*>(row[i]));
        break;
      }
    }
    rows_[id] = new_row;
  }
} //here

DbTable& DbTable::operator=(const DbTable& rhs) {
  if (this == &rhs) {
    return *this;
  }
  for (auto& pair : rows_) {
    for (unsigned int i = 0; i < col_descs_.size(); i++) {
      if (col_descs_[i].second == DataType::kString) {
        delete static_cast<std::string*>(pair.second[i]);
      } else if (col_descs_[i].second == DataType::kInt) {
        delete static_cast<int*>(pair.second[i]);
      } else if (col_descs_[i].second == DataType::kDouble) {
        delete static_cast<double*>(pair.second[i]);
      }
    }
    delete[] pair.second;
  }
  rows_.clear();
  next_unique_id_ = rhs.next_unique_id_;
  row_col_capacity_ = rhs.row_col_capacity_;
  col_descs_ = rhs.col_descs_;
  for (const auto& pair : rhs.rows_) {
    void** data = new void*[row_col_capacity_];
    for (unsigned int i = 0; i < col_descs_.size(); ++i) {
      if (col_descs_[i].second == DataType::kString) {
        data[i] = new std::string(*static_cast<std::string*>(pair.second[i]));
      } else if (col_descs_[i].second == DataType::kInt) {
        data[i] = new int(*static_cast<int*>(pair.second[i]));
      } else if (col_descs_[i].second == DataType::kDouble) {
        data[i] = new double(*static_cast<double*>(pair.second[i]));
      }
    }
    rows_[pair.first] = data;
  }
  return *this;
}

DbTable::~DbTable() {
  for (auto& pair : rows_) {
    for (unsigned int i = 0; i < col_descs_.size(); i++) {
      if (col_descs_[i].second == DataType::kString) {
        delete static_cast<std::string*>(pair.second[i]);
      } else if (col_descs_[i].second == DataType::kDouble) {
        delete static_cast<double*>(pair.second[i]);
      } else if (col_descs_[i].second == DataType::kInt) {
        delete static_cast<int*>(pair.second[i]);
      }
    }
    delete[] pair.second;
  }
}

std::ostream& operator<<(std::ostream& os, const DbTable& table) {
  for (size_t i = 0; i < table.col_descs_.size(); i++) {
    os << table.col_descs_[i].first << "(";
    switch (table.col_descs_[i].second) {
    case DataType::kString:
      os << "std::string";
      break;
    case DataType::kDouble:
      os << "double";
      break;
    case DataType::kInt:
      os << "int";
      break;
    }
    os << ")";
    if (i < table.col_descs_.size() - 1) os << ", ";
    else os << "\n";
  }
  //os << std::endl;
  for (const auto& pair : table.rows_) {
    void** row_array = pair.second;
    for (unsigned int idx = 0; idx < table.col_descs_.size(); idx++) {
      switch (table.col_descs_[idx].second) {
      case DataType::kString:
        os << *(static_cast<std::string*>(row_array[idx]));
        break;
      case DataType::kDouble:
        os << *(static_cast<double*>(row_array[idx]));
        break;
      case DataType::kInt:
        os << *(static_cast<int*>(row_array[idx]));
        break;
      }
      if (idx < table.col_descs_.size() - 1) {
        os << ", ";
      }
    }
    os << std::endl;
  }
  return os;
}
