#ifndef ARTIST_HPP
#define ARTIST_HPP

#include <string>
#include <userver/formats/json.hpp>

struct Artist {
  long id;
  std::string name;
  int totalListeners;
  std::string photo_src;

  std::string json() {
    userver::formats::json::ValueBuilder builder;
    builder["id"] = this->id;
    builder["name"] = this->name;
    builder["total_listeners"] = this->totalListeners;
    builder["photo_src"] = this->photo_src;

    return ToString(builder.ExtractValue());
  }
};

#endif