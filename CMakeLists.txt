cmake_minimum_required(VERSION 3.22)
project(RayTracer_redone)

set(CMAKE_CXX_STANDARD 20)

find_package(glm REQUIRED)
find_package(SDL2 REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(OpenMP)
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
include(FetchContent)
FetchContent_Declare(
        json
        URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)

FetchContent_MakeAvailable(json)

add_executable(RayTracer_redone
        RayTracerRedone/sdl2canvas/sdl2canvas.cpp
        RayTracerRedone/sdl2canvas/sdl2canvas.h
        RayTracerRedone/tracer/config/glm_definitions.h
        RayTracerRedone/tracer/objects/Ball.cpp
        RayTracerRedone/tracer/objects/Ball.h
        RayTracerRedone/tracer/objects/Plane.cpp
        RayTracerRedone/tracer/objects/Plane.h
        RayTracerRedone/tracer/objects/VirtualObject.h
        RayTracerRedone/tracer/objects/Mesh.cpp
        RayTracerRedone/tracer/objects/Mesh.h
        RayTracerRedone/tracer/objects/OpenCylinder.cpp
        RayTracerRedone/tracer/objects/OpenCylinder.h
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
        RayTracerRedone/tracer/objects/BoundingBox/AABB.h
        RayTracerRedone/tracer/objects/BoundingBox/AABB.cpp
        RayTracerRedone/tracer/objects/VirtualObject.cpp
        RayTracerRedone/tracer/objects/BoundingBox/BVH.cpp
        RayTracerRedone/tracer/objects/BoundingBox/BVH.h
        RayTracerRedone/tracer/scene/materials/TexturedPhong.cpp
        RayTracerRedone/tracer/scene/materials/TexturedPhong.h
        RayTracerRedone/tracer/scene/textures/Texture.cpp
        RayTracerRedone/tracer/scene/textures/Texture.h
        RayTracerRedone/tracer/scene/textures/CheckerTexture.cpp
        RayTracerRedone/tracer/scene/textures/CheckerTexture.h
        RayTracerRedone/tracer/scene/materials/TexturedMatte.cpp
        RayTracerRedone/tracer/scene/materials/TexturedMatte.h
        RayTracerRedone/tracer/scene/materials/TexturedMaterial.cpp
        RayTracerRedone/tracer/scene/materials/TexturedMaterial.h
        RayTracerRedone/tracer/scene/textures/PointCheckerTexture.cpp
        RayTracerRedone/tracer/utils/stb/stb_image.h
        RayTracerRedone/tracer/scene/textures/ImageTexture.cpp
        RayTracerRedone/tracer/scene/textures/ImageTexture.h
        RayTracerRedone/RayTracerRedone.cpp
        RayTracerRedone/tracer/utils/stb/rtr_stb_image.h
        RayTracerRedone/tracer/scene/materials/TexturedPhongReflective.cpp
        RayTracerRedone/tracer/scene/materials/TexturedPhongReflective.h
        RayTracerRedone/worlds.h
        RayTracerRedone/tracer/scene/Camera.cpp
        RayTracerRedone/tracer/scene/Camera.h
        RayTracerRedone/tracer/scene/materials/SampleDielectric.cpp
        RayTracerRedone/tracer/scene/materials/SampleDielectric.h
        RayTracerRedone/tracer/scene/BxDF/PerfectTransmitter.cpp
        RayTracerRedone/tracer/scene/BxDF/PerfectTransmitter.h
        RayTracerRedone/tracer/scene/BxDF/BTDF.h
        RayTracerRedone/tracer/scene/BxDF/FresnelTransmitter.cpp
        RayTracerRedone/tracer/scene/BxDF/FresnelTransmitter.h
        RayTracerRedone/tracer/scene/materials/Transparent.h
        RayTracerRedone/tracer/scene/materials/Transparent.cpp
        RayTracerRedone/tracer/scene/BxDF/FresnelReflector.h
        RayTracerRedone/tracer/scene/BxDF/FresnelReflector.cpp
        RayTracerRedone/imageoutputcanvas/imagecanvas.cpp
        RayTracerRedone/imageoutputcanvas/imagecanvas.h
        RayTracerRedone/imageoutputcanvas/stb/image_canvas_stb_image.h
        RayTracerRedone/imageoutputcanvas/stb/stb_image_write.h
        RayTracerRedone/tracer/objects/Disk.cpp RayTracerRedone/tracer/objects/Disk.h
        RayTracerRedone/tracer/scene/materials/BumpMapping.cpp
        RayTracerRedone/tracer/scene/materials/BumpMapping.h
        RayTracerRedone/tracer/scene/materials/Dielectric.cpp
        RayTracerRedone/tracer/scene/materials/Dielectric.h RayTracerRedone/tracer/utils/ColorVec.cpp
        RayTracerRedone/tracer/scene/materials/DiffuseLight.cpp RayTracerRedone/tracer/scene/materials/DiffuseLight.h
        RayTracerRedone/tracer/objects/Rectangle.cpp
        RayTracerRedone/tracer/objects/Rectangle.h
        RayTracerRedone/tracer/scene/light/AreaLight.cpp
        RayTracerRedone/tracer/scene/light/AreaLight.h
        RayTracerRedone/tracer/utils/OrthonormalBase.cpp
        RayTracerRedone/tracer/utils/OrthonormalBase.h
        RayTracerRedone/tracer/scene/materials/NullMaterial.cpp
        RayTracerRedone/tracer/scene/materials/NullMaterial.h
        RayTracerRedone/tracer/utils/utility.cpp
        RayTracerRedone/splash.h
        RayTracerRedone/jsonparser/world_factory.cpp
        RayTracerRedone/jsonparser/world_factory.h
        RayTracerRedone/jsonparser/SceneParser.cpp
        RayTracerRedone/jsonparser/SceneParser.h)


target_link_libraries(RayTracer_redone PRIVATE glm::glm)
target_link_libraries(RayTracer_redone PRIVATE assimp::assimp)
target_link_libraries(RayTracer_redone PRIVATE ${SDL2_LIBRARIES})
target_link_libraries(RayTracer_redone PRIVATE OpenMP::OpenMP_CXX)
target_link_libraries(RayTracer_redone PRIVATE nlohmann_json::nlohmann_json)

add_definitions(-DGLM_ENABLE_EXPERIMENTAL)

set_property(TARGET RayTracer_redone PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)


file(COPY RayTracerRedone/assets DESTINATION ${CMAKE_BINARY_DIR})