//
// Created by suhuiyuzhou on 31/05/2020.
//

#ifndef MAI_SERDES_H
#define MAI_SERDES_H

#include "../lib/utils.h"

#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <array>

namespace mai {

  namespace fs = std::filesystem;

  auto test_ser_des()
  {
      std::cout << "current " << fs::current_path() << "\n";

      std::string root = "/Users/sushuiyuzhou/tmp";
      std::cout << "exists? " << fs::exists(root) << "\n";

      std::string file = root+"/testFile.txt";

      if (!fs::exists(fs::path(root))) {
          if (!fs::create_directory(fs::path(root))) {
              throw "not created";
          }
      }

      std::cout << "file: " << file << "\n";
      std::ofstream fs(file);

      if (!fs.is_open()) {
          throw std::runtime_error("file not opened");
      }
      else {
          fs << 42 << "\n";
          fs << 43 << "\n";
          fs << 44 << "\n";
          fs << 45 << "\n";
      }
      fs.close();

      std::ifstream inf(file);
      int r, e, a, d;
      inf >> r >> e >> a >> d;
      inf.close();

      std::cout << "read value: " << r << ", " << e << ", " << a << ", " << d << "\n";
  }

}

#endif //MAI_SERDES_H
