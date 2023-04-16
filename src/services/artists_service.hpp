#ifndef ARTISTS_SERVICE_HPP
#define ARTISTS_SERVICE_HPP

#include <string>
#include <userver/storages/postgres/cluster.hpp>

class ArtistsService {
public:
    static std::string getAllArtists(userver::storages::postgres::ClusterPtr pgCluster);
    static std::string getArtistById(userver::storages::postgres::ClusterPtr pgCluster, long id);
};

#endif
