#ifndef ARTISTS_REPOSITORY_HPP
#define ARTISTS_REPOSITORY_HPP

#include <vector>
#include <userver/storages/postgres/cluster.hpp>

#include "../model/artist.hpp"

class ArtistsRepository {
public:
    static std::vector<Artist> getAllArtists(userver::storages::postgres::ClusterPtr pgCluster);
    static Artist getArtistById(userver::storages::postgres::ClusterPtr pgCluster, long id);
};

#endif
