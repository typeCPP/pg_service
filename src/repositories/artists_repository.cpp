#include <iostream>
#include <userver/storages/postgres/io/row_types.hpp>

#include "artists_repository.hpp"

std::vector<Artist> ArtistsRepository::getAllArtists(userver::storages::postgres::ClusterPtr pgCluster) {
  auto result = pgCluster->Execute(userver::storages::postgres::ClusterHostType::kMaster,
                                   "SELECT * FROM public.artists");
  return result.AsContainer<std::vector<Artist>>(userver::storages::postgres::kRowTag);
}

Artist ArtistsRepository::getArtistById(userver::storages::postgres::ClusterPtr pgCluster, long id) {
  auto result = pgCluster->Execute(userver::storages::postgres::ClusterHostType::kMaster,
                                   "SELECT * from public.artists WHERE id=$1", id);
  return result.AsSingleRow<Artist>(userver::storages::postgres::kRowTag);
}

bool ArtistsRepository::insertArtist(userver::storages::postgres::ClusterPtr pgCluster, std::string name,
                                     int totalListeners, std::string photoSrc) {
  auto result = pgCluster->Execute(userver::storages::postgres::ClusterHostType::kMaster,
                                   "INSERT INTO public.artists(name, total_listeners, "
                                   "photo_src) values ($1, $2, $3)",
                                   name, totalListeners, photoSrc);
  return result.RowsAffected() > 0;
}
