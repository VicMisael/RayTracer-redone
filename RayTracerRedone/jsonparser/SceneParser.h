#pragma once

#include <memory>
#include <unordered_map>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

#include "AmbientLight.h"
#include "ColorVec.h"

// Forward declarations of your classes
class Material;
class VirtualObject;
class VectorialLight;
class AreaLight;
class Camera;
class ViewPlane;
class AmbientLight;

using json = nlohmann::json;

class Scene {
public:
    std::shared_ptr<ViewPlane> viewPlane;
    std::vector<std::shared_ptr<VirtualObject>> objects_;
    std::vector<std::shared_ptr<VectorialLight>> lights_;
    std::vector<std::shared_ptr<AreaLight>> areaLights_;
    std::shared_ptr<Camera> camera;
    AmbientLight ambient_light;
    ColorVec bgColor;
};

class SceneParser {
public:
    static Scene parseScene(const json& j);

private:
    static std::shared_ptr<Material> parseMaterial(const json& j);
    static void loadMaterialTemplates(const json& j);

    static std::shared_ptr<VirtualObject> parseObject(const json& j);
    static std::shared_ptr<VectorialLight> parseVectorialLight(const json& j);
    static std::shared_ptr<AreaLight> parseAreaLight(const json& j);
    static std::shared_ptr<Camera> parseCamera(const json& j);
    static std::shared_ptr<ViewPlane> parseViewPlane(const json& j);
    static AmbientLight parseAmbientLight(const json& j);

    static std::unordered_map<std::string, std::shared_ptr<Material>> materialTemplates_;
};
