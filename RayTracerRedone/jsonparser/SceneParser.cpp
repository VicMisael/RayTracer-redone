#include "SceneParser.h"

#include "AmbientLight.h"
#include "AreaLight.h"
#include "Ball.h"
#include "Camera.h"
#include "Dielectric.h"
#include "Diffuse.h"
#include "DiffuseLight.h"
#include "DirectionalLight.h"
#include "Disk.h"
#include "Matte.h"
#include "Mirror.h"
#include "NullMaterial.h"
#include "OpenCylinder.h"
#include "Phong.h"
#include "PhongMetal.h"
#include "PhongReflective.h"
#include "Plane.h"
#include "PointLight.h"
#include "Rectangle.h"
#include "Transparent.h"
#include "ViewPlane.h"

// Initialize static material template map
std::unordered_map<std::string, std::shared_ptr<Material>> SceneParser::materialTemplates_;


std::shared_ptr<Material> SceneParser::parseMaterial(const json& j) {
    if (j.is_string()) {
        auto it = materialTemplates_.find(j.get<std::string>());
        if (it != materialTemplates_.end()) {
            return it->second;
        }
        throw std::runtime_error("Unknown material reference: " + j.get<std::string>());
    }

    std::string type = j.at("type");
    if (type == "Diffuse") {
        return std::make_shared<Diffuse>(ColorVec(j["color"][0], j["color"][1], j["color"][2]));
    } else if (type == "Matte") {
        return std::make_shared<Matte>(j["kd"], ColorVec(j["albedo"][0], j["albedo"][1], j["albedo"][2]));
    } else if (type == "Mirror") {
        return std::make_shared<Mirror>(j["reflectivity"]);
    } else if (type == "Phong") {
        return std::make_shared<Phong>(
            ColorVec(j["color"][0], j["color"][1], j["color"][2]),
            j["kspecular"], j["exp"]
        );
    } else if (type == "PhongMetal") {
        return std::make_shared<PhongMetal>(
            ColorVec(j["color"][0], j["color"][1], j["color"][2]),
            j["fuzz"]
        );
    } else if (type == "Transparent") {
        return std::make_shared<Transparent>(j["ior"], j["kt"]);
    } else if (type == "Dielectric") {
        return std::make_shared<Dielectric>(
            ColorVec(j["cf_in"][0], j["cf_in"][1], j["cf_in"][2]),
            ColorVec(j["cf_out"][0], j["cf_out"][1], j["cf_out"][2])
        );
    } else if (type == "DiffuseLight") {
        return std::make_shared<DiffuseLight>(
            ColorVec(j["color"][0], j["color"][1], j["color"][2]),
            j["intensity"]
        );
    } else if (type == "PhongReflective") {
        return std::make_shared<PhongReflective>();
    }

    return std::make_shared<NullMaterial>();
}

std::shared_ptr<ViewPlane> SceneParser::parseViewPlane(const json& j) {
    int width = j["width"];
    int height = j["height"];
    float zw = j["zw"];
    float pixelSize = j["pixelSize"];

    return std::make_shared<ViewPlane>(width, height,zw, pixelSize);
}

std::shared_ptr<VirtualObject> SceneParser::parseObject(const json& j) {
    std::string type = j["type"];
    auto mat = parseMaterial(j["material"]);

    if (type == "Ball") {
        auto c = j["center"];
        return std::make_shared<Ball>(Point3(c[0], c[1], c[2]), j["radius"], mat);
    }
    else if (type == "Plane") {
        auto p = j["point"];
        auto n = j["normal"];
        return std::make_shared<Plane>(Point3(p[0], p[1], p[2]), Vector3(n[0], n[1], n[2]), mat);
    }
    else if (type == "Rectangle1") {
        auto p0 = j["p0"];
        auto a = j["a"];
        auto b = j["b"];
        return std::make_shared<Rectangle>(Point3(p0[0], p0[1], p0[2]),
                                           Vector3(a[0], a[1], a[2]),
                                           Vector3(b[0], b[1], b[2]), mat);
    }
    else if (type == "Rectangle2") {
        auto p0 = j["p0"];
        auto normal = j["normal"];
        float side = j["side_length"];
        return std::make_shared<Rectangle>(Point3(p0[0], p0[1], p0[2]),
                                           Vector3(normal[0], normal[1], normal[2]),
                                           side, mat);
    }
    else if (type == "OpenCylinder") {
        auto axis = j["axis"];
        auto base = j["base"];
        return std::make_shared<OpenCylinder>(
            Vector3(axis[0], axis[1], axis[2]),
            Point3(base[0], base[1], base[2]),
            j["height"], j["radius"], mat
        );
    }
    else if (type == "Disk") {
        auto c = j["center"];
        auto n = j["normal"];
        return std::make_shared<Disk>(Point3(c[0], c[1], c[2]),
                                      Vector3(n[0], n[1], n[2]),
                                      j["radius"], mat);
    }

    throw std::runtime_error("Unknown object type: " + type);
}

std::shared_ptr<VectorialLight> SceneParser::parseVectorialLight(const json& j) {
    std::string type = j["type"];
    auto color = ColorVec(j["color"][0], j["color"][1], j["color"][2]);
    float intensity = j["intensity"];

    if (type == "PointLight") {
        auto pos = j["point"];
        return std::make_shared<PointLight>(Vector3(pos[0], pos[1], pos[2]), intensity, color);
    }
    else if (type == "DirectionalLight") {
        auto dir = j["direction"];
        return std::make_shared<DirectionalLight>(Vector3(dir[0], dir[1], dir[2]), intensity, color);
    }

    throw std::runtime_error("Unknown vectorial light type: " + type);
}

std::shared_ptr<AreaLight> SceneParser::parseAreaLight(const json& j) {
    auto obj = parseObject(j["object"]);
    return std::make_shared<AreaLight>(obj);
}


std::shared_ptr<Camera> SceneParser::parseCamera(const json& j) {
    const auto& eye = j["eye"];
    const auto& lookat = j["lookAt"];
    const auto& up = j["up"];

    return std::make_shared<Camera>(
        Point3(eye[0], eye[1], eye[2]),
        Point3(lookat[0], lookat[1], lookat[2]),
        Vector3(up[0], up[1], up[2])
    );
}


AmbientLight SceneParser::parseAmbientLight(const json& j) {
    float intensity = j["intensity"];
    auto color = j["color"];
    return AmbientLight(intensity, ColorVec(color[0], color[1], color[2]));
}



void SceneParser::loadMaterialTemplates(const json& j) {
    for (auto& [key, val] : j.items()) {
        materialTemplates_[key] = parseMaterial(val);
    }
}
