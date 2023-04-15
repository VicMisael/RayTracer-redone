cmake_minimum_required(VERSION 3.24)
project(RayTracerRedone)

set(CMAKE_CXX_STANDARD 20)

include_directories(sdl2canvas)
include_directories(tracer/config)
include_directories(tracer/objects)
include_directories(tracer/scene)
include_directories(tracer/scene/light)
include_directories(tracer/utils)

add_executable(RayTracerRedone
        sdl2canvas/sdl2canvas.cpp
        sdl2canvas/sdl2canvas.h
        tracer/config/glm_definitions.h
        tracer/objects/Ball.cpp
        tracer/objects/Ball.h
        tracer/objects/Plane.cpp
        tracer/objects/Plane.h
        tracer/objects/VirtualObject.h
        tracer/scene/light/Light.h
        tracer/scene/Canvas.h
        tracer/scene/Ray.cpp
        tracer/scene/Ray.h
        tracer/scene/Scene.cpp
        tracer/scene/Scene.h
        tracer/scene/ViewPlane.cpp
        tracer/scene/ViewPlane.h
        tracer/scene/World.cpp
        tracer/scene/World.h
        tracer/utils/ColorRGBA.h
        tracer/utils/ColorVec.h
        tracer/utils/Constants.h
        tracer/utils/Intersection.h
        tracer/utils/IntersectionData.h
        tracer/utils/Material.h
        tracer/utils/Types.h
        RayTracerRedone.cpp)
