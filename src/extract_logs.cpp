#include <fstream>
#include <iostream>
#include <sstream>
#include <string_view>

// const std::string LOG_FILE_PATH = "../test_logs.log";
const std::string LOG_FILE_PATH = "../test_logs";
const std::string OUTPUT_LOG_FOLDER_PATH = "../output";

void extractAndPrintLogs(std::string_view date) {
  //   std::cout << date << std::endl;
  const std::string OUTPUT_LOG_FILE_PATH =
      OUTPUT_LOG_FOLDER_PATH + '/' + std::string(date.begin(), date.end());
  std::ifstream ifs(LOG_FILE_PATH, std::ifstream::in);
  std::ofstream ofs(OUTPUT_LOG_FILE_PATH, std::ofstream::trunc);

  std::string line;
  while (std::getline(ifs, line)) {
    std::istringstream iss(line);
    std::string log_date;
    iss >> log_date;
    if (log_date == date) {
      ofs << line << '\n';
    }
  }
  ifs.close();
  ofs.close();
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "Usage: ./extract_logs <yyyy-mm-dd>" << std::endl;
    return 1;
  }
  extractAndPrintLogs(argv[1]);
}
