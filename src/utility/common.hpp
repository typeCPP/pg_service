#ifndef COMMON_HPP
#define COMMON_HPP

#include <string>
#include <vector>

static const std::string DATABASE_NAME = "music_db";

template <class T>
static std::string serialize_vector(std::vector<T>& data) {
  if (data.empty()) return "";
  
  auto begin = data.begin();
  auto end = data.end();
  std::string result = "[";
  
  for (; begin != end; ++begin) {
    result.append(begin->json());
    if (begin != end - 1) result.push_back(',');
  }
  result.push_back(']');
  return result;
}

#endif
