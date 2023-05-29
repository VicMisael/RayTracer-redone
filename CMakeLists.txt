cmake_minimum_required(VERSION 3.22)
project(RayTracer_redone)

set(CMAKE_CXX_STANDARD 20)

find_package(glm REQUIRED)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

include_directories(RayTracerRedone/sdl2canvas)
include_directories(RayTracerRedone/tracer)
include_directories(RayTracerRedone/tracer/config)
include_directories(RayTracerRedone/tracer/objects)
include_directories(RayTracerRedone/tracer/scene)
include_directories(RayTracerRedone/tracer/scene/BxDF)
include_directories(RayTracerRedone/tracer/scene/light)
include_directories(RayTracerRedone/tracer/scene/materials)
include_directories(RayTracerRedone/tracer/utils)
include_directories(RayTracerRedone/tracer/utils/sampler)

add_executable(RayTracer_redone
        RayTracerRedone/sdl2canvas/sdl2canvas.cpp
        RayTracerRedone/sdl2canvas/sdl2canvas.h
        RayTracerRedone/tracer/config/glm_definitions.h
        RayTracerRedone/tracer/objects/Ball.cpp
        RayTracerRedone/tracer/objects/Ball.h
        RayTracerRedone/tracer/objects/Plane.cpp
        RayTracerRedone/tracer/objects/Plane.h
        RayTracerRedone/tracer/objects/VirtualObject.h
        RayTracerRedone/tracer/scene/BxDF/BxDF.h
        RayTracerRedone/tracer/scene/BxDF/GlossySpecular.cpp
        RayTracerRedone/tracer/scene/BxDF/GlossySpecular.h
        RayTracerRedone/tracer/scene/BxDF/Lambertian.cpp
        RayTracerRedone/tracer/scene/BxDF/Lambertian.h
        RayTracerRedone/tracer/scene/BxDF/MetallicSpecular.cpp
        RayTracerRedone/tracer/scene/BxDF/MetallicSpecular.h
        RayTracerRedone/tracer/scene/BxDF/PerfectSpecular.cpp
        RayTracerRedone/tracer/scene/BxDF/PerfectSpecular.h
        RayTracerRedone/tracer/scene/light/AmbientLight.cpp
        RayTracerRedone/tracer/scene/light/AmbientLight.h
        RayTracerRedone/tracer/scene/light/DirectionalLight.cpp
        RayTracerRedone/tracer/scene/light/DirectionalLight.h
        RayTracerRedone/tracer/scene/light/Light.h
        RayTracerRedone/tracer/scene/light/PointLight.cpp
        RayTracerRedone/tracer/scene/light/PointLight.h
        RayTracerRedone/tracer/scene/light/VectorialLight.cpp
        RayTracerRedone/tracer/scene/light/VectorialLight.h
        RayTracerRedone/tracer/scene/materials/Diffuse.cpp
        RayTracerRedone/tracer/scene/materials/Diffuse.h
        RayTracerRedone/tracer/scene/materials/Material.h
        RayTracerRedone/tracer/scene/materials/Matte.cpp
        RayTracerRedone/tracer/scene/materials/Matte.h
        RayTracerRedone/tracer/scene/materials/Mirror.cpp
        RayTracerRedone/tracer/scene/materials/Mirror.h
        RayTracerRedone/tracer/scene/materials/Phong.cpp
        RayTracerRedone/tracer/scene/materials/Phong.h
        RayTracerRedone/tracer/scene/materials/PhongMetal.cpp
        RayTracerRedone/tracer/scene/materials/PhongMetal.h
        RayTracerRedone/tracer/scene/materials/PhongReflective.cpp
        RayTracerRedone/tracer/scene/materials/PhongReflective.h
        RayTracerRedone/tracer/scene/materials/WhiteMetal.cpp
        RayTracerRedone/tracer/scene/materials/WhiteMetal.h
        RayTracerRedone/tracer/scene/Canvas.h
        RayTracerRedone/tracer/scene/Projection.h
        RayTracerRedone/tracer/scene/Ray.cpp
        RayTracerRedone/tracer/scene/Ray.h
        RayTracerRedone/tracer/scene/Scene.cpp
        RayTracerRedone/tracer/scene/Scene.h
        RayTracerRedone/tracer/scene/ViewPlane.cpp
        RayTracerRedone/tracer/scene/ViewPlane.h
        RayTracerRedone/tracer/scene/World.cpp
        RayTracerRedone/tracer/scene/World.h
        RayTracerRedone/tracer/utils/sampler/diagonal_point_sampler.cpp
        RayTracerRedone/tracer/utils/sampler/diagonal_point_sampler.h
        RayTracerRedone/tracer/utils/sampler/equidistant_point_sampler.cpp
        RayTracerRedone/tracer/utils/sampler/equidistant_point_sampler.h
        RayTracerRedone/tracer/utils/sampler/horizontal_point_sampler.cpp
        RayTracerRedone/tracer/utils/sampler/horizontal_point_sampler.h
        RayTracerRedone/tracer/utils/sampler/mt19937_point_sampler.cpp
        RayTracerRedone/tracer/utils/sampler/mt19937_point_sampler.h
        RayTracerRedone/tracer/utils/sampler/random_point_sampler.cpp
        RayTracerRedone/tracer/utils/sampler/random_point_sampler.h
        RayTracerRedone/tracer/utils/sampler/sampler.h
        RayTracerRedone/tracer/utils/sampler/vertical_point_sampler.cpp
        RayTracerRedone/tracer/utils/sampler/vertical_point_sampler.h
        RayTracerRedone/tracer/utils/ColorRGBA.h
        RayTracerRedone/tracer/utils/ColorVec.h
        RayTracerRedone/tracer/utils/Constants.h
        RayTracerRedone/tracer/utils/Intersection.h
        RayTracerRedone/tracer/utils/Types.h
        RayTracerRedone/tracer/utils/utility.h
        RayTracerRedone/RayTracerRedone.cpp)


target_link_libraries(RayTracer_redone glm::glm)

target_link_libraries(RayTracer_redone ${SDL2_LIBRARIES})
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast -Wall -march=native")
set_property(TARGET RayTracer_redone PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)