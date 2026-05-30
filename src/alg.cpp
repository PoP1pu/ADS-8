// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cout << "File error!" << std::endl;
    return;
  }

  std::string word;
  word.reserve(32);

  while (!file.eof()) {
    int ch = file.get();
    if (ch == EOF) break;
    if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
      word += static_cast<char>(ch | 0x20);
    } else {
      if (!word.empty()) {
        tree.insert(word);
        word.clear();
      }
    }
  }

  if (!word.empty()) {
    tree.insert(word);
  }
  file.close();
}

void printFreq(BST<std::string>& tree) {
  std::vector<std::pair<std::string, int>> freq = tree.sortedByFrequency();
  std::ofstream out("result/freq.txt");
  if (!out) {
    std::cout << "Cannot open result/freq.txt for writing!" << std::endl;
  }
  for (const auto& p : freq) {
    std::cout << p.first << " : " << p.second << "\n";
    if (out) out << p.first << " : " << p.second << "\n";
  }
  if (out) out.close();
}
