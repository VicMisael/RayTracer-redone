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
#include "tracer/scene/materials/Diffuse.h"

#include "tracer/scene/textures/CheckerTexture.h"
#include "tracer/scene/textures/PointCheckerTexture.h"
#include "tracer/scene/textures/ImageTexture.h"



std::vector<std::shared_ptr<VirtualObject>> generateObjects() {
    std::vector<std::shared_ptr<VirtualObject>> objects;

    const auto plane_material = std::make_shared<Phong>(ColorVec(0.4, 0.4, 0.8), 1, 1, 25);
    const auto plane_material2 = std::make_shared<Phong>(ColorVec(0.4, 0.9, 0.2), 1, 1, 25);
    const auto white_phong = std::make_shared<Phong>(Constants::WHITE, 1, 1, 25);
    const auto checkeredTexture=std::make_shared<CheckerTexture>(10);
    const auto blue_white_texture = std::make_shared<CheckerTexture>(ColorVec(0.4, 0.4, 0.8), Constants::WHITE, 0.01);
    const auto black_white_texture = std::make_shared<CheckerTexture>(Constants::BLACK, Constants::WHITE, 0.01);


    const auto textured =std::make_shared<TexturedPhong>(checkeredTexture);
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

    const auto textured_test_material2=std::make_shared<TexturedMaterial>(blue_white_texture, white_matte);
    const auto textured_test_material3=std::make_shared<TexturedMaterial>(black_white_texture, white_matte);

    const auto textured_test_material4=std::make_shared<TexturedMaterial>(black_white_texture, white_phong);

    objects.push_back(std::make_shared<Plane>(Point3(0, 0, -1600), Vector3(0, -1, 1), textured_test_material2));

    objects.push_back(std::make_shared<Plane>(Point3(0, 900, 1000), Vector3(0, 1, 1), yellow_matte));

    objects.push_back(
            std::make_shared<Ball>(Point3(0, -1000, -1000), 1000, white_matte));

    objects.push_back(std::make_shared<Ball>(Point3(1350, 0, -1000), 1000, phong_metal));

    objects.push_back(
            std::make_shared<Ball>(Point3(-1250, 0, -1000), 1000, textured));

    objects.push_back(std::make_shared<Ball>(Point3(5, -20, -625), 120, phong_metal));


    objects.push_back(std::make_shared<Ball>(Point3(-150, 55, -150), 40,
                                             white_matte));


    objects.push_back(std::make_shared<Ball>(Point3(0, 40, -650), 40,
                                             mirror));

    objects.push_back(std::make_shared<Ball>(Point3(0, 0, -195), 95,
                                             phong_black_reflective));


    objects.push_back(std::make_shared<Ball>(Point3(400, 150, -350), 150,
                                             textured));

    objects.push_back(std::make_shared<Ball>(Point3(0, 100, -925), 256,
                                             mirror));

    const auto textured_test_material=std::make_shared<TexturedMaterial>(checkeredTexture, phong_black_reflective);

    objects.push_back(std::make_shared<Ball>(Point3(0, 650, -125), 120,
                                             phong_reflective_higher_exp));

    const auto earthtexture=std::make_shared<ImageTexture>("assets/textures/earthmap.jpg");

    const auto earthmaterial=std::make_shared<TexturedMatte>(earthtexture,1);

    const auto _8balltexture=std::make_shared<ImageTexture>("assets/textures/8ball.jpg");
    const auto eight_ball_material = std::make_shared<TexturedPhongReflective>(_8balltexture,0.4);


    objects.push_back(std::make_shared<Ball>(Point3(-600, 450, -300), 280,
                                             eight_ball_material));


    objects.push_back(std::make_shared<Ball>(Point3(400, -20, -100), 120,
                                             earthmaterial));

    const auto checkeredTexture2 = std::make_shared<CheckerTexture>(10);
    const auto textured3 = std::make_shared<TexturedMaterial>(earthtexture,white_matte);

    auto cylinder = std::make_shared<OpenCylinder>(Vector3(1,1,0),Point3(400,-240,-200),450,80, textured3);
    auto mat=glm::rotate(Matrix4x4(1.0f),(float)glm::radians(15.0f),Vector3(0,1,0));
    //mat=glm::scale(mat,12.0f*Vector3(1));
    cylinder->transform(mat);
    objects.push_back(cylinder);



    return objects;
}

std::vector<std::shared_ptr<VectorialLight>> generate_vectorial_lights() {
    std::vector<std::shared_ptr<VectorialLight>> lights;
    //lights.push_back(std::make_shared<DirectionalLight>(Vector3(0, 1, 1), 3.15, ColorVec(1, 1, 1)));
    lights.push_back(std::make_shared<PointLight>(Point3(90, 0, 0), Constants::pi * 6, ColorVec(1, 1, 1)));

    return lights;
}


namespace worlds{
    World generateWorld1(){
        //True=Perspective False=parallel
        constexpr bool projection = false;

        const auto view_plane= std::make_shared<ViewPlane>(2000, 2000, 50, 01.0f);

        AmbientLight ab(0, ColorVec(1.0, 1.0, 1));
        return {view_plane, generateObjects(), generate_vectorial_lights(),
                ab, {0.9, 0.9, 1}, projection};
    }

    World generateWorld2(){
        constexpr bool projection = true;

        const auto view_plane = std::make_shared<ViewPlane>( 60, 60, 20, 0.50);

        AmbientLight ab(0, ColorVec(1.0, 1.0, 1));
        return {view_plane, generateObjects(), generate_vectorial_lights(),
                ab, {0.9, 0.9, 1}, projection};
    }
};
