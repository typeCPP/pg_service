#include "artists_service.hpp"
#include <string>
#include <userver/formats/json.hpp>
#include "../repositories/artists_repository.hpp"
#include "../utility/common.hpp"

std::string ArtistsService::getAllArtists(userver::storages::postgres::ClusterPtr pgCluster) {
  auto artists = ArtistsRepository::getAllArtists(pgCluster);
  std::string result = serialize_vector(artists);
  return result;
}

std::string ArtistsService::getArtistById(userver::storages::postgres::ClusterPtr pgCluster, long id) {
  Artist artist = ArtistsRepository::getArtistById(pgCluster, id);
  return artist.json();
}

bool ArtistsService::insertArtist(userver::storages::postgres::ClusterPtr pgCluster, const Artist &artist) {
  return ArtistsRepository::insertArtist(pgCluster, artist.name, artist.totalListeners, artist.photoSrc);
}
