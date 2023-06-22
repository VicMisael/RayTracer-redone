#pragma once

#include <memory>
#include <optional>
#include <utility>

#include "../utils/Intersection.h"
#include "../scene/Ray.h"
#include "../scene/materials/Material.h"
#include "../utils/Constants.h"

#include "BoundingBox/AABB.h"

class VirtualObject {
protected:

public:
    std::optional<std::shared_ptr<Material>> material;

    explicit VirtualObject() = default;

    explicit VirtualObject(std::shared_ptr<Material> _material) {
        material = std::move(_material);
    };

    [[nodiscard]] virtual std::optional<intersectionRec> intersects(const Ray &ray) const = 0;

    virtual void transform(Matrix4x4 m) {};

    virtual std::shared_ptr<AABB> bounding_box() const;

    // the case where there is no bounding box is the edge case
    [[nodiscard]] virtual bool hasBoundingBox() const {
        return true;
    }

};

	