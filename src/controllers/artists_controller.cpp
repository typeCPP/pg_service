#include <userver/clients/dns/component.hpp>
#include <userver/formats/json.hpp>
#include <userver/server/handlers/exceptions.hpp>
#include <userver/server/handlers/http_handler_base.hpp>
#include <userver/storages/postgres/cluster.hpp>
#include <userver/storages/postgres/component.hpp>
#include <userver/utils/assert.hpp>

#include "../model/artist.hpp"
#include "../services/artists_service.hpp"
#include "../utility/common.hpp"
#include "artists_controller.hpp"

class ArtistsController final : public userver::server::handlers::HttpHandlerBase {
public:
    static constexpr std::string_view
    kName = "handler-artists";

    ArtistsController(const userver::components::ComponentConfig &config,
                      const userver::components::ComponentContext &component_context)
            : HttpHandlerBase(config, component_context),
              pgCluster(component_context.FindComponent<userver::components::Postgres>(DATABASE_NAME).GetCluster()) {}

    std::string HandleRequestThrow(const userver::server::http::HttpRequest &request,
                                   userver::server::request::RequestContext &context) const override {
      if (request.GetMethod() == userver::server::http::HttpMethod::kGet)
        return handleGetRequest(request, context);
      else
        return handlePostRequest(request, context);
    }

    std::string handleGetRequest(const userver::server::http::HttpRequest &request,
                                 userver::server::request::RequestContext &context) const {
      const auto &id = request.GetArg("id");
      if (!id.empty())
        return ArtistsService::getArtistById(pgCluster, std::stol(id));
      else
        return ArtistsService::getAllArtists(pgCluster);
    }

    std::string handlePostRequest(const userver::server::http::HttpRequest &request,
                                  userver::server::request::RequestContext &context) const {
      userver::formats::json::Value jsonBody = userver::formats::json::FromString(request.RequestBody());
      auto name = jsonBody["name"].As<std::string>("");
      int totalListeners = jsonBody["total_listeners"].As<int>(0);
      auto photoSrc = jsonBody["photo_src"].As<std::string>("");
      Artist artist = {0L, name, totalListeners, photoSrc};

      if (ArtistsService::insertArtist(pgCluster, artist)) {
        return "";
      } else {
        throw userver::server::handlers::ClientError();
      }
    }

    userver::storages::postgres::ClusterPtr pgCluster;
};

void appendArtistsController(userver::components::ComponentList &component_list) {
  component_list.Append<ArtistsController>();
}
