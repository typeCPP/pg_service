#include "artists_service.hpp"
#include "../utility/common.hpp"
#include "../repositories/artists_repository.hpp"
#include <string>
#include <userver/formats/json.hpp>

std::string ArtistsService::getAllArtists(userver::storages::postgres::ClusterPtr pgCluster) {
    auto artists = ArtistsRepository::getAllArtists(pgCluster);

    std::string result = serialize_vector(artists);
    return result;
}

std::string ArtistsService::getArtistById(userver::storages::postgres::ClusterPtr pgCluster, long id) {
    return "";
}
