#include <iostream>
#include <userver/storages/postgres/io/row_types.hpp>

#include "artists_repository.hpp"

std::vector<Artist> ArtistsRepository::getAllArtists(
    userver::storages::postgres::ClusterPtr pgCluster) {
  auto result =
      pgCluster->Execute(userver::storages::postgres::ClusterHostType::kMaster,
                         "SELECT * FROM public.artists");
  return result.AsContainer<std::vector<Artist>>(
      userver::storages::postgres::kRowTag);
}

Artist ArtistsRepository::getArtistById(
    userver::storages::postgres::ClusterPtr pgCluster, long id) {
  return {};
}
