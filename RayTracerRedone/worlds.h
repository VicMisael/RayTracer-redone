//
// Created by Misael on 05/06/2023.
//

#pragma once

#include <glm/ext.hpp>
#include "sdl2canvas/sdl2canvas.h"

#include "tracer/scene/World.h"
#include "tracer/scene/World.h"
#include "tracer/objects/Plane.h"
#include "tracer/objects/Ball.h"
#include "tracer/objects/Mesh.h"
#include "tracer/objects/OpenCylinder.h"
#include "tracer/objects/Disk.h"
#include "tracer/objects/Rectangle.h"


#include "tracer/scene/Scene.h"
#include "tracer/scene/light/DirectionalLight.h"
#include "tracer/scene/light/PointLight.h"

#include "tracer/scene/materials/WhiteMetal.h"

#include "tracer/scene/materials/PhongReflective.h"
#include "tracer/scene/materials/PhongMetal.h"
#include "tracer/scene/materials/Matte.h"
#include "tracer/scene/materials/Mirror.h"
#include "tracer/scene/materials/Phong.h"
#include "tracer/scene/materials/TexturedPhong.h"
#include "tracer/scene/materials/TexturedMatte.h"
#include "tracer/scene/materials/TexturedMaterial.h"
#include "tracer/scene/materials/TexturedPhongReflective.h"
#include "tracer/scene/materials/BumpMapping.h"
#include "tracer/scene/materials/Diffuse.h"
#include "tracer/scene/materials/DiffuseLight.h"

#include "tracer/scene/textures/CheckerTexture.h"
#include "tracer/scene/textures/PointCheckerTexture.h"
#include "tracer/scene/textures/ImageTexture.h"
#include "tracer/scene/materials/SampleDielectric.h"
#include "tracer/scene/materials/Dielectric.h"
#include "tracer/scene/materials/Transparent.h"


std::vector<std::shared_ptr<VirtualObject>> generateObjects() {
    std::vector<std::shared_ptr<VirtualObject>> objects;

    const auto plane_material = std::make_shared<Phong>(ColorVec(0.4, 0.4, 0.8), 1, 1, 25);
    const auto plane_material2 = std::make_shared<Phong>(ColorVec(0.4, 0.9, 0.2), 1, 1, 25);
    const auto white_phong = std::make_shared<Phong>(Constants::WHITE, 1, 1, 25);
    const auto checkeredTexture = std::make_shared<CheckerTexture>(10);
    const auto blue_white_texture = std::make_shared<CheckerTexture>(ColorVec(0.4, 0.4, 0.8), Constants::WHITE, 1);
    const auto black_white_texture = std::make_shared<CheckerTexture>(Constants::BLACK, Constants::WHITE, 1);


    const auto textured = std::make_shared<TexturedPhong>(checkeredTexture);
    const auto red_specular_phong = std::make_shared<Phong>(ColorVec(0.4, 0.5, 0.5),
                                                            ColorVec(1, 0, 0), 1, 1,
                                                            23);
    const auto phong_metal = std::make_shared<PhongMetal>();
    const auto white_matte = std::make_shared<Matte>(1, ColorVec(1, 1.0, 1));
    const auto mirror = std::make_shared<Mirror>();
    const auto phong_black_reflective = std::make_shared<PhongReflective>(Constants::BLACK, 1, 12, 1);
    const auto phong_white_reflective = std::make_shared<PhongReflective>(Constants::WHITE, 1, 12, 1);
    const auto pink_matte = std::make_shared<Matte>(1, ColorVec(1, 0, 1));
    const auto phong_reflective_higher_exp = std::make_shared<PhongReflective>(ColorVec(Constants::BLACK), 1, 25, 1);
    const auto yellow_matte = std::make_shared<Matte>(1, ColorVec(1, 1, 0));

    const auto textured_test_material2 = std::make_shared<TexturedMaterial>(blue_white_texture, white_matte);


    objects.push_back(std::make_shared<Plane>(Point3(0, 0, -1600), Vector3(0, -1, 1), textured_test_material2));

    objects.push_back(std::make_shared<Plane>(Point3(0, 900, 1000), Vector3(0, 1, 1), yellow_matte));

    objects.push_back(
            std::make_shared<Ball>(Point3(0, -1000, -1000), 1000, white_matte));


    objects.push_back(std::make_shared<Ball>(Point3(1350, 0, -1000), 1000, phong_metal));

    objects.push_back(
            std::make_shared<Ball>(Point3(-1250, 0, -1000), 1000, textured));

    objects.push_back(std::make_shared<Ball>(Point3(0, 600, -195), 95,
                                             phong_black_reflective));


    objects.push_back(std::make_shared<Ball>(Point3(400, 150, -350), 150,
                                             textured));


    const auto textured_test_material = std::make_shared<TexturedMaterial>(checkeredTexture, phong_black_reflective);


    const auto earthtexture = std::make_shared<ImageTexture>("assets/textures/earthmap.jpg");

    const auto earthmaterial = std::make_shared<TexturedMatte>(earthtexture, 1);

    const auto _8balltexture = std::make_shared<ImageTexture>("assets/textures/8ball.jpg");
    const auto eight_ball_material = std::make_shared<TexturedPhongReflective>(_8balltexture, 0.4);


    objects.push_back(std::make_shared<Ball>(Point3(-600, 450, -300), 280,
                                             eight_ball_material));


    objects.push_back(std::make_shared<Ball>(Point3(400, -20, -100), 120,
                                             earthmaterial));

    const auto checkeredTexture2 = std::make_shared<CheckerTexture>(10);
    const auto textured3 = std::make_shared<TexturedMaterial>(checkeredTexture2, white_matte);

    auto cylinder = std::make_shared<OpenCylinder>(Vector3(0, 1, 0), Point3(400, -240, -200), 450, 80, textured3);
    // auto mat = glm::rotate(Matrix4x4(1.0f), (float)glm::radians(15.0f), Vector3(0, 1, 0));
    //mat=glm::scale(mat,12.0f*Vector3(1));
    //cylinder->transform(mat);
    objects.push_back(cylinder);

    objects.push_back(std::make_shared<Ball>(Point3(0, 100, -925), 256,
                                             phong_reflective_higher_exp));

    objects.push_back(std::make_shared<Ball>(Point3(0, 40, -650), 40,
                                             mirror));

    return objects;
}

std::vector<std::shared_ptr<VectorialLight>> generate_vectorial_lights() {
    std::vector<std::shared_ptr<VectorialLight>> lights;
    //lights.push_back(std::make_shared<DirectionalLight>(Vector3(0, 1, 1), 3.15, ColorVec(1, 1, 1)));
    lights.push_back(std::make_shared<PointLight>(Point3(90, 0, 0), Constants::pi * 6, ColorVec(1, 1, 1)));

    return lights;
}


std::vector<std::shared_ptr<VirtualObject>> generateObjectsMoonEarth() {
    std::vector<std::shared_ptr<VirtualObject>> objects;
    const auto earthtexture = std::make_shared<ImageTexture>("assets/textures/earthmap.jpg");
    const auto earthmaterial = std::make_shared<TexturedMatte>(earthtexture, 1);
    objects.push_back(std::make_shared<Ball>(Point3(-400, -20, -1000), 620,
                                             earthmaterial));

    const auto moontexture = std::make_shared<ImageTexture>("assets/textures/moon.jpg");
    const auto moonmaterial = std::make_shared<TexturedMatte>(moontexture, 1);
    objects.push_back(std::make_shared<Ball>(Point3(800, -14, -1000), 620 / 4,
                                             moonmaterial));

    const auto jupitertexture = std::make_shared<ImageTexture>("assets/textures/jupiter.jpg");
    const auto jupitermaterial = std::make_shared<TexturedPhong>(jupitertexture);
    objects.push_back(std::make_shared<Ball>(Point3(1400, -20, -6000), 1000,
                                             jupitermaterial));
    return objects;
}

std::vector<std::shared_ptr<VectorialLight>> generate_moon_earth_scenario_lights() {
    std::vector<std::shared_ptr<VectorialLight>> lights;
    lights.push_back(std::make_shared<PointLight>(Point3(7200, 0, -1000), Constants::pi * 1000,
                                                  normalize(ColorVec(1.2, 1.2, 1))));

    return lights;
}

namespace worlds {
    World generateWorld1(bool projection) {
        //True=Perspective False=parallel


        const auto view_plane = !projection ? std::make_shared<ViewPlane>(2000, 2000, 50, 01.0f)
                                            : std::make_shared<ViewPlane>(60, 60, 20, 0.50);


        AmbientLight ab(0, ColorVec(1.0, 1.0, 1));
        return {view_plane, generateObjects(), generate_vectorial_lights(),
                ab, {0.3, 0.3, 0.3}, projection};
    }

    World moonEarth() {
        constexpr bool projection = false;

        const auto view_plane = std::make_shared<ViewPlane>(2000, 2000, 50, 2.0f);

        AmbientLight ab(0, ColorVec(1.0, 1.0, 1));

        return {view_plane, generateObjectsMoonEarth(), generate_moon_earth_scenario_lights(),
                ab, {0.2, 0.2, 0.2}, projection};

    }

    World moonEarthPerspective() {
        constexpr bool projection = true;

        //objects.push_back(std::make_shared<Ball>(Point3(800, -14, -10000),6400,std::make_shared<PhongReflective>()));

        const auto view_plane = std::make_shared<ViewPlane>(120, 120, 60, 1);

        AmbientLight ab(0, ColorVec(1.0, 1.0, 1));

        return {view_plane, generateObjectsMoonEarth(), generate_moon_earth_scenario_lights(),
                ab, {0.2, 0.2, 0.2}, projection};

    }

    World refractanceTest() {

//        constexpr bool projection = true;
//
//        const auto view_plane = std::make_shared<ViewPlane>(60, 60, 20, 0.50);
//
        constexpr bool projection = false;
        const auto view_plane = std::make_shared<ViewPlane>(2000, 2000, 50, 0.5f);

        std::vector<std::shared_ptr<VirtualObject>> objects;

        const auto white_matte = std::make_shared<Matte>(1, ColorVec(1, 1.0, 1));
        const auto black_red_texture = std::make_shared<CheckerTexture>(Constants::BLACK, Constants::RED, 10);
        const auto black_white_texture = std::make_shared<CheckerTexture>(Constants::BLACK, Constants::WHITE, 10);
        const auto phong_metal = std::make_shared<PhongReflective>();
        const auto rw_matte = std::make_shared<TexturedMatte>(black_red_texture, 1);
        const auto ball = std::make_shared<Ball>(Point3(-500, 0, -950), 350.0f, rw_matte);
        const auto jupitertexture = std::make_shared<ImageTexture>("assets/textures/jupiter.jpg");
        const auto jupitermaterial = std::make_shared<TexturedPhong>(jupitertexture);
        const auto moontexture = std::make_shared<ImageTexture>("assets/textures/moon.jpg");
        const auto moonmaterial = std::make_shared<TexturedMatte>(moontexture, 1);

        const auto blue_matte = std::make_shared<Matte>(1, ColorVec(0.3, 0.9, 1));

        objects.push_back(ball);
        //const auto ball2 = std::make_shared<Ball>(Point3(500, 0, -1050), 350.0f, blue_matte);

        //objects.push_back(ball2);

        const auto dielectric = std::make_shared<SampleDielectric>(.93);

        objects.push_back(std::make_shared<Ball>(Point3(0, 0, -255), 150, dielectric));

        const auto dielectric2 = std::make_shared<SampleDielectric>(.6);
        objects.push_back(std::make_shared<Ball>(Point3(0, -150, -155), 150, dielectric2));

        const auto dielectric3 = std::make_shared<SampleDielectric>(.56);
        objects.push_back(std::make_shared<Ball>(Point3(350, 0, -455), 150, dielectric3));

        const auto transparent = std::make_shared<Transparent>();
        objects.push_back(std::make_shared<Ball>(Point3(0, 150, -255), 150, transparent));


        const auto tex_phong = std::make_shared<TexturedPhong>(black_white_texture);
        objects.push_back(std::make_shared<Ball>(Point3(350, 0, -655), 150, tex_phong));
        objects.push_back(std::make_shared<Ball>(Point3(50, 0, -655), 150, tex_phong));
        objects.push_back(std::make_shared<Ball>(Point3(-150, 0, -655), 150, blue_matte));
        objects.push_back(std::make_shared<Ball>(Point3(-450, 0, -655), 150, tex_phong));

        objects.push_back(
                std::make_shared<Ball>(Point3(0, -1000, -1000), 1000, moonmaterial));


        objects.push_back(
                std::make_shared<Ball>(Point3(0, 0, -3000), 1000, jupitermaterial));

        const auto bw_matte = std::make_shared<TexturedMatte>(black_white_texture, 1);

        objects.push_back(std::make_shared<Ball>(Point3(1350, 0, -1000), 1000, phong_metal));

        std::vector<std::shared_ptr<VectorialLight>> lights;
        //lights.push_back(std::make_shared<DirectionalLight>(Vector3(0, 1, 1), 3.15, ColorVec(1, 1, 1)));
        //lights.push_back(std::make_shared<PointLight>(Point3(0, 0, 0), Constants::pi * 62, ColorVec(1, 1, 1)));
        AmbientLight ab(0, ColorVec(1.0, 1.0, 1));


        return {view_plane, objects, lights,
                ab, {1, 1, 1}, projection};

    }

    World meshTest() {
        constexpr bool projection = false;

        const auto view_plane = std::make_shared<ViewPlane>(2000, 2000, 50, 01.0f);

        std::vector<std::shared_ptr<VirtualObject>> objects;

        //const auto black_white_texture = std::make_shared<CheckerTexture>(Constants::BLACK, Constants::WHITE, 1);
        const auto white_phong = std::make_shared<Phong>(Constants::RED, 1, 1, 25);
        auto mesh = std::make_shared<Mesh>("assets/objs/teapot.obj", white_phong);
        auto mat = glm::translate(Matrix4x4(1.0f), Vector3(0, -100, -300));
        float angle = 1.5708;
        mat = glm::rotate(mat, angle / 2, Vector3(0, 1, 0));
        mat = glm::scale(mat, Vector3(100));
        mesh->transform(mat);
        objects.push_back(mesh);

        const auto texture = std::make_shared<ImageTexture>("assets/textures/jupiter.jpg");
        const auto eight_ball_material = std::make_shared<TexturedPhongReflective>(texture, 0.4);

        mesh = std::make_shared<Mesh>("assets/objs/cow.obj", eight_ball_material);
        mat = glm::translate(Matrix4x4(1.0f), Vector3(-200, -400, -300));
        mat = glm::rotate(mat, angle / 2, Vector3(0, 1, 0));
        mat = glm::scale(mat, Vector3(20));
        mesh->transform(mat);
        objects.push_back(mesh);

        std::vector<std::shared_ptr<VectorialLight>> lights;
        //lights.push_back(std::make_shared<DirectionalLight>(Vector3(0, 1, 1), 3.15, ColorVec(1, 1, 1)));
//        lights.push_back(std::make_shared<PointLight>(Point3(0, 0, 0), Constants::pi * 60, ColorVec(1, 1, 1)));
        AmbientLight ab(0.2, ColorVec(1.0, 1.0, 1));


        auto mesh2 = std::make_shared<Mesh>("assets/objs/box_stack.obj", eight_ball_material);
        mat = glm::translate(Matrix4x4(1.0f), Vector3(-200, 400, -300));
        mat = glm::rotate(mat, angle / 2, Vector3(0, 1, 0));
        mat = glm::scale(mat, Vector3(20));
        mesh2->transform(mat);
        objects.push_back(mesh2);

        auto mesh3 = std::make_shared<Mesh>("assets/objs/test.obj", eight_ball_material);
        mat = glm::translate(Matrix4x4(1.0f), Vector3(400, -640, -900));
        mat = glm::scale(mat, Vector3(100));
        mesh3->transform(mat);
        objects.push_back(mesh3);

        return {view_plane, objects, lights,
                ab, {0.9, 0.9, 1}, projection};
    }

    World testeFeatures(bool projection) {

        const auto jupitertexture = std::make_shared<ImageTexture>("assets/textures/jupiter.jpg");
        const auto jupitermaterial = std::make_shared<TexturedPhong>(jupitertexture);
        const auto earthtexture = std::make_shared<ImageTexture>("assets/textures/earthmap.jpg");
        const auto earthmaterial = std::make_shared<TexturedMatte>(earthtexture, 1);
        const auto moontexture = std::make_shared<ImageTexture>("assets/textures/moon.jpg");
        const auto moonmaterial = std::make_shared<TexturedMatte>(moontexture, 1);


        const auto orangenormalmap = std::make_shared<ImageTexture>("assets/normalmaps/orangenm.jpg");
        const auto orangephong = std::make_shared<Phong>(ColorVec(1, .64705882352f, 0), Constants::WHITE,
                                                         1, 1, 10);
        const auto orangeBumpmappedPhong = std::make_shared<BumpMapping>(orangephong, orangenormalmap);

        const auto red_specular_phong = std::make_shared<Phong>(ColorVec(1, 0, 0),
                                                                ColorVec(1, 0, 0), 1, 1,
                                                                23);

        const auto _8balltexture = std::make_shared<ImageTexture>("assets/textures/8ball.jpg");
        const auto eight_ball_material = std::make_shared<TexturedPhongReflective>(_8balltexture, 0.4);


        const auto view_plane = projection ? std::make_shared<ViewPlane>(120, 120, 60, 1) : std::make_shared<ViewPlane>(
                2000, 2000, 50, 2.0f);

        AmbientLight ab(0, ColorVec(1.0, 1.0, 1));

        std::vector<std::shared_ptr<VirtualObject>> objects;

        const auto earthmaterialBumpMapped = std::make_shared<BumpMapping>(earthmaterial,
                                                                           std::make_shared<ImageTexture>(
                                                                                   "assets/normalmaps/earthbumpmap.png"));

        objects.push_back(std::make_shared<Ball>(Point3(-400, -60, -1600), 800,
                                                 earthmaterialBumpMapped));
        objects.push_back(std::make_shared<Ball>(Point3(800, -54, -1600), 620 / 4,
                                                 moonmaterial));
        objects.push_back(std::make_shared<Ball>(Point3(1400, -20, -6000), 1000,
                                                 jupitermaterial));
        objects.push_back(std::make_shared<Disk>(Point3(1400, -20, -1900), Vector3(0.5, 0.5, -1), 200, earthmaterial));

        objects.push_back(std::make_shared<Ball>(Point3(-1400, 600, -1900), 350,
                                                 orangeBumpmappedPhong));

        const auto teste = std::make_shared<SampleDielectric>(6.9);
        objects.push_back(std::make_shared<Ball>(Point3(900, 0, -800), 600, teste));
        const auto teste2 = std::make_shared<Transparent>(1.569, 0.61);
        objects.push_back(std::make_shared<Ball>(Point3(1500, 600, -800), 600, teste2));
        const auto teste3 = std::make_shared<Dielectric>(Constants::YELLOW, Constants::BLUE, 1.24, 1.61, 1, 2);
        objects.push_back(std::make_shared<Ball>(Point3(0, -900, -800), 600, teste2));

        objects.push_back(std::make_shared<Ball>(Point3(-600, 900, -800), 500));

        objects.push_back(
                std::make_shared<Rectangle>(Point3(0, 300, -100), Vector3(0.9, 0, 1), 400, earthmaterial));
        std::vector<std::shared_ptr<VectorialLight>> lights;
        lights.push_back(std::make_shared<PointLight>(Point3(7200, 0, -1000), Constants::pi * 250,
                                                      normalize(ColorVec(1.2, 1.2, 1))));

        lights.push_back(std::make_shared<PointLight>(Point3(0, 0, 0), Constants::pi * 100,ColorVec(1,1,1)));

        return {view_plane, objects, lights,
                ab, {0.2, 0.2, 0.9}, projection};
    }
};
