//
// Created by Misael on 04/04/2025.
//

#ifndef JSON_TO_SCENE_H
#define JSON_TO_SCENE_H
#include "World.h"


namespace world_factory{
  World fromJson(const std::string json);
};


#endif //JSON_TO_SCENE_H
