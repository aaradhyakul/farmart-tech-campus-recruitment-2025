#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>

const std::string LOG_FILE_PATH = "../test_logs";
const std::string OUTPUT_LOG_FOLDER_PATH = "../output";

bool isDateFormatValid(std::string date) {
  if (date.size() != 10) {
    return false;
  }
  if (date[4] != '-' || date[7] != '-') {
    return false;
  }
  try {
    int year = stoi(date.substr(0, 4));
    int month = stoi(date.substr(5, 2));
    int day = stoi(date.substr(8, 2));
    // std::cout << year << " " << month << " " << day << std::endl;
    return month > 0 && month < 13 && day > 0 && day < 32;
  } catch (const std::invalid_argument &e) {
    return false;
  } catch (const std::out_of_range &e) {
    return false;
  }
  return true;
}

void extractAndPrintLogs(std::string_view date) {
  //   std::cout << date << std::endl;
  const std::string OUTPUT_LOG_FILE_PATH =
      OUTPUT_LOG_FOLDER_PATH + '/' + std::string(date.begin(), date.end());
  std::ifstream ifs(LOG_FILE_PATH, std::ifstream::in);
  if (!ifs) {
    std::cout << "Could not open " << LOG_FILE_PATH << " for reading"
              << std::endl;
    return;
  }
  std::ofstream ofs(OUTPUT_LOG_FILE_PATH, std::ofstream::trunc);
  if (!ofs) {
    std::cout << "Could not open " << OUTPUT_LOG_FILE_PATH << " for logging"
              << std::endl;
    return;
  }

  std::string line;
  while (std::getline(ifs, line)) {
    std::istringstream iss(line);
    std::string log_date;
    iss >> log_date;
    if (log_date == date) {
      ofs << line << '\n';
    }
  }
  std::cout << "Succesfully extracted logs to " << OUTPUT_LOG_FILE_PATH
            << std::endl;
  ifs.close();
  ofs.close();
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "Usage: ./extract_logs <yyyy-mm-dd>" << std::endl;
    return 1;
  }
  if (isDateFormatValid(argv[1]) == false) {
    std::cout << "Error:Invalid date format, specify date as <yyyy-mm-dd>"
              << std::endl;
    return 1;
  }
  extractAndPrintLogs(argv[1]);
}
