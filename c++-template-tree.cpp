#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>

int main()
{
  constexpr auto npos = std::string::npos;
  using size_t = std::string::size_type;
  std::string line;

  while (std::getline(std::cin, line)) {
    unsigned depth = 0;
    auto pos = size_t{};
    auto next_pos = line.find_first_of('<', pos);
    if (next_pos == npos) {
      std::cout << line << "\n";
      continue;
    }

    auto next_pos2 = line.find_last_of(' ', next_pos);
    if (next_pos2 != npos) {
      ++next_pos2;
      std::cout.write(&line[0], next_pos2) << "\n";
      pos = next_pos2;
    }

    auto write = [&line](size_t pos1, size_t pos2) {
      if (line[pos1] == ' ') {
        ++pos1;
      }
      std::cout.write(&line[pos1], pos2 - pos1) << "\n";
    };

    while (next_pos != npos) {
      switch (line[next_pos]) {
        case '<':
          std::cout << std::setw(depth * 2) << "";
          next_pos2 = line.find_first_of("<,>", next_pos + 1);
          if (next_pos2 != npos && line[next_pos2] == '>') {
            next_pos2 = line.find_first_of("<,>", next_pos2 + 1);
            if (next_pos2 != npos) {
              next_pos2 -= (line[next_pos2] != ',');
              write(pos, next_pos2 + 1);
              next_pos = next_pos2;
            }
            else {
              write(pos, line.size());
              pos = line.size();
              next_pos = npos;
              continue;
            }
          }
          else {
            write(pos, next_pos + 1);
            ++depth;
            pos = next_pos + 1;
            next_pos = next_pos2;
            continue;
          }
          break;

        case ',':
          std::cout << std::setw(depth * 2) << "";
          write(pos, next_pos + 1);
          break;

        case '>':
          if (next_pos != pos) {
            std::cout << std::setw(depth * 2) << "";
            write(pos, next_pos);
          }
          --depth;
          std::cout << std::setw(depth * 2) << "";
          next_pos2 = line.find_first_of("<,>", next_pos + 1);
          if (next_pos2 != npos) {
            next_pos2 -= (line[next_pos2] != ',');
            std::cout << ">";
            write(next_pos + 1, next_pos2 + 1);
            next_pos = next_pos2;
          }
          else {
            write(next_pos, line.size());
            pos = line.size();
            next_pos = npos;
            continue;
          }
          break;
      }

      pos = next_pos + 1;
      next_pos = line.find_first_of("<,>", pos);
    }

    if (pos != line.size()) {
      std::cout.write(&line[pos], line.size() - pos) << "\n";
    }
  }
}
