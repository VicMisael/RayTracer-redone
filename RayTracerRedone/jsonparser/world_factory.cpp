//
// Created by Misael on 04/04/2025.
//

#include "world_factory.h"

#include <nlohmann/json_fwd.hpp>

#include "SceneParser.h"

World world_factory::fromJson(const std::string& jsonStr) {
    // Parse JSON string to JSON object
    nlohmann::json j = nlohmann::json::parse(jsonStr);


    // Parse components via SceneParser
    auto vp = SceneParser::parseViewPlane(j["viewPlane"]);

    if (j.contains("materials")) {
        SceneParser::loadMaterialTemplates(j["materials"]);
    }

    std::vector<std::shared_ptr<VirtualObject>> objects;
    for (const auto& obj : j["objects"]) {
        objects.push_back(SceneParser::parseObject(obj));
    }

    std::vector<std::shared_ptr<VectorialLight>> lights;
    for (const auto& light : j["vectorialLights"]) {
        lights.push_back(SceneParser::parseVectorialLight(light));
    }

    std::vector<std::shared_ptr<AreaLight>> arealights;
    for (const auto& alight : j["areaLights"]) {
        arealights.push_back(SceneParser::parseAreaLight(alight));
    }

    auto ambient = SceneParser::parseAmbientLight(j["ambient_light"]);
    auto bgColor = ColorVec(j["bgColor"][0], j["bgColor"][1], j["bgColor"][2]);

    auto cam = SceneParser::parseCamera(j["camera"]);

    // Build world
    std::string projection = j.contains("projection")?std::string(j["projection"]):std::string("perspective");

    bool proj = projection == std::string("perspective");
    auto world = World(vp, objects, lights, ambient, bgColor, proj);
    world.withCamera(cam);
    world.withAreaLights(arealights);

    return world;
}
