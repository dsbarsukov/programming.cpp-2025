#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "RPNCalculator.h"

using namespace std;

int main(int argc, char* argv[]) {
  if (argc != 3) {
    cout << "Использование: " << argv[0] << " <input_file> <output_file>\n";
    return 1;
  }

  string inputFile = argv[1];
  string outputFile = argv[2];

  ifstream inFile(inputFile);
  if (!inFile.is_open()) {
    cerr << "Не удалось открыть входной файл";
    return 1;
  }

  ofstream outFile(outputFile);
  if (!outFile.is_open()) {
    cerr << "Не удалось создать выходной файл";
    return 1;
  }

  string line;
  while (getline(inFile, line)) {
    if (line.length() == 0) {
      continue;
    }

    try {
      double result = evaluateRPN(line);
      outFile << line << " = " << result << "\n";

    } catch (const exception& e) {
      cerr << "Ошибка при вычислении '" << line << "': " << e.what() << "\n";
      outFile << line << " = ERROR: " << e.what() << "\n";
    }
  }

  inFile.close();
  outFile.close();

  return 0;
}