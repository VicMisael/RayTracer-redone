//
// Created by Misael on 05/06/2023.
//

#pragma once

#include <glm/ext.hpp>
#include <random>
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
#include "tracer/scene/materials/NullMaterial.h"

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
	const auto blue_white_texture = std::make_shared<CheckerTexture>(ColorVec(0.4, 0.4, 0.8), Constants::WHITE, 5);
	const auto black_white_texture = std::make_shared<CheckerTexture>(Constants::BLACK, Constants::WHITE, 10);

	const auto textured_bw = std::make_shared<TexturedMatte>(black_white_texture);
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


	//objects.push_back(std::make_shared<Plane>(Point3(0, 0, -1600), Vector3(0, -1, 1), textured_test_material2));

	//objects.push_back(std::make_shared<Plane>(Point3(0, 900, 1000), Vector3(0, 1, 1), plane_material));

	objects.push_back(
		std::make_shared<Ball>(Point3(0, -1000, -1000), 1000, white_matte));


	objects.push_back(std::make_shared<Ball>(Point3(1350, 0, -1000), 1000, phong_metal));

	objects.push_back(
		std::make_shared<Ball>(Point3(-1250, 0, -1000), 1000, textured));

	objects.push_back(std::make_shared<Ball>(Point3(0, 600, -195), 95,
		phong_black_reflective));


	objects.push_back(std::make_shared<Ball>(Point3(400, 150, -350), 150,
		textured));


	const auto textured_test_material = std::make_shared<TexturedMaterial>(checkeredTexture, textured_bw);


	const auto earthtexture = std::make_shared<ImageTexture>("assets/textures/earthmap.jpg");

	const auto earthmaterial = std::make_shared<TexturedMatte>(earthtexture, 1);

	const auto _8balltexture = std::make_shared<ImageTexture>("assets/textures/8ball.jpg");
	const auto eight_ball_material = std::make_shared<TexturedPhongReflective>(_8balltexture, 0.4);


	objects.push_back(std::make_shared<Ball>(Point3(-300, 650, -500), 280,
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

	const auto teste = std::make_shared<SampleDielectric>(6.9);
	objects.push_back(std::make_shared<Ball>(Point3(-450, 0, -800), 150, teste));

	const auto teste3 = std::make_shared<Dielectric>(Constants::YELLOW, Constants::BLACK, 1.24, 1.61, 1, 2);
	objects.push_back(std::make_shared<Ball>(Point3(120, 190, -200), 150, teste3));

	auto rng = std::default_random_engine{};
	std::shuffle(objects.begin(), objects.end(), rng);
	return objects;
}

std::vector<std::shared_ptr<VectorialLight>> generate_vectorial_lights() {
	std::vector<std::shared_ptr<VectorialLight>> lights;
	//lights.push_back(std::make_shared<DirectionalLight>(Vector3(0, 1, 1), 3.15, ColorVec(1, 1, 1)));
	lights.push_back(std::make_shared<PointLight>(Point3(0, 100, -1600), Constants::pi * 16, ColorVec(1, 1, 1)));

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


	World generateWorld1(bool projection = false) {
		//True=Perspective False=parallel


		const auto view_plane = !projection ? std::make_shared<ViewPlane>(4000, 2000, 50, 01.0f)
			: std::make_shared<ViewPlane>(320, 160, 100, 1);

		const auto objects = generateObjects();
		AmbientLight ab(0, ColorVec(1.0, 1.0, 1));
		auto camera = std::make_shared<Camera>(Point3(0, 1000, -3200), Point3(0, 0, 0), Vector3(0, 1, 0));
		World world = { view_plane, objects, generate_vectorial_lights(),
				ab, {0.1, 0.2, .5}, projection };
		world.withCamera(camera);
		return world;
	}

	World moonEarth() {
		constexpr bool projection = false;

		const auto view_plane = std::make_shared<ViewPlane>(2000, 2000, 50, 2.0f);

		AmbientLight ab(0, ColorVec(1.0, 1.0, 1));

		return { view_plane, generateObjectsMoonEarth(), generate_moon_earth_scenario_lights(),
				ab, {0.2, 0.2, 0.2}, projection };

	}

	World moonEarthPerspective() {
		constexpr bool projection = true;

		//objects.push_back(std::make_shared<Ball>(Point3(800, -14, -10000),6400,std::make_shared<PhongReflective>()));

		const auto view_plane = std::make_shared<ViewPlane>(120, 120, 60, 1);

		AmbientLight ab(0, ColorVec(1.0, 1.0, 1));

		return { view_plane, generateObjectsMoonEarth(), generate_moon_earth_scenario_lights(),
				ab, {0.2, 0.2, 0.2}, projection };

	}

	World refractanceTest() {

		//        constexpr bool projection = true;
		//
		//        const auto view_plane = std::make_shared<ViewPlane>(60, 60, 20, 0.50);
		//
		constexpr bool projection = true;
		const auto view_plane = std::make_shared<ViewPlane>(40, 20, 10, 0.5f);

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
		objects.push_back(std::make_shared<Ball>(Point3(180, 150, -255), 150, transparent));


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


		return { view_plane, objects, lights,
				ab, {1, 1, 1}, projection };

	}

	World meshTest() {
		constexpr bool projection = false;

		const auto view_plane = std::make_shared<ViewPlane>(2000, 2000, 50, 01.0f);

		std::vector<std::shared_ptr<VirtualObject>> objects;

		//const auto black_white_texture = std::make_shared<CheckerTexture>(Constants::BLACK, Constants::WHITE, 1);
		const auto white_phong = std::make_shared<Phong>(Constants::RED, 1, 1, 25);
		auto mesh = std::make_shared<Mesh>("assets/objs/building3.obj", white_phong);
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

		return { view_plane, objects, lights,
				ab, {0.9, 0.9, 1}, projection };
	}

	World testeFeatures(bool projection = false) {

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
		objects.push_back(std::make_shared<Ball>(Point3(900, -120, -800), 120, teste));
		const auto teste2 = std::make_shared<Transparent>(1.569, 0.61);
		objects.push_back(std::make_shared<Ball>(Point3(1500, 600, -800), 400, teste2));

		objects.push_back(std::make_shared<Ball>(Point3(0, -900, -800), 600, teste2));
		const auto teste3 = std::make_shared<Dielectric>(Constants::BLACK, Constants::WHITE, 1.24, 1.61, 0.1, 256);
		objects.push_back(std::make_shared<Ball>(Point3(720, -500, -500), 440, teste3));

		objects.push_back(
			std::make_shared<Rectangle>(Point3(0, 300, -100), Vector3(0.9, 0, 1), 400, earthmaterial));


		std::vector<std::shared_ptr<VectorialLight>> lights;
		lights.push_back(std::make_shared<PointLight>(Point3(7200, 0, -1000), Constants::pi * 250,
			normalize(ColorVec(1.2, 1.2, 1))));

		lights.push_back(std::make_shared<PointLight>(Point3(0, 0, 0), Constants::pi * 100, ColorVec(1, 1, 1)));

		return { view_plane, objects, lights,
				ab, {0.2, 0.2, 0.9}, projection };
	}

	World cornellBox() {
		auto red = std::make_shared<Matte>(2, ColorVec(0.65, .21, .21));;
		auto white = std::make_shared<Matte>(2, ColorVec(0.73, 0.73, 0.73));
		auto green = std::make_shared<Matte>(2, ColorVec(0.12, 0.45, 0.15));;
		auto diffuse = std::make_shared<Matte>(2, ColorVec(0.12, 0.45, 0.15));
		auto diffuse_light = std::make_shared<DiffuseLight>(Constants::WHITE, 0.25);

		std::vector<std::shared_ptr<VirtualObject>> objects;
		const auto side1 = std::make_shared<Rectangle>(Point3(0, 0, 0), Point3(0, 555, 0), Point3(0, 0, 555), green);
		const auto side2 = std::make_shared<Rectangle>(Point3(555, 0, 555), Vector3(1, 0, 0), 555, red);
		const auto floor = std::make_shared<Rectangle>(Point3(0, 0, 0), Vector3(0, 1, 0), 555, white);;
		const auto ceiling = std::make_shared<Rectangle>(Point3(0, 555, 0), Vector3(0, 0, 555), Point3(555, 0, 0),
			white);
		const auto back = std::make_shared<Rectangle>(Point3(555, 0, 555), Vector3(0, 0, -1), 555, white);
		const auto light = std::make_shared<Rectangle>(Point3(227, 554, 227), Vector3(0, -1, 0), 60,
			diffuse_light);


		const auto jupitertexture = std::make_shared<ImageTexture>("assets/textures/jupiter.jpg");
		const auto jupitermaterial = std::make_shared<TexturedPhong>(jupitertexture);

		const auto teste4 = std::make_shared<Mirror>();
		objects.push_back(std::make_shared<Ball>(Point3(450, 200, 320), 120, teste4));

		objects.push_back(std::make_shared<Ball>(Point3(120, 100, 300), 100,
			jupitermaterial));


		const auto phong_black_reflective = std::make_shared<PhongReflective>(Constants::WHITE, 1, 12, 1);
		objects.push_back(std::make_shared<Ball>(Point3(100, 400, 355), 50, std::make_shared<Mirror>()));

		const auto teste3 = std::make_shared<Dielectric>(Constants::YELLOW, Constants::BLACK, 1.24, 1.61, 1, 2);
		objects.push_back(std::make_shared<Ball>(Point3(320, 120, 200), 100, teste3));

		const auto balllight = std::make_shared<Ball>(Point3(420, 400, 400), 60,
			std::make_shared<DiffuseLight>(Constants::WHITE, 0.25));
		//objects.push_back(balllight);
//
//        auto cylinder = std::make_shared<OpenCylinder>(Vector3(0, 1, 0), Point3(00, 150, 400), 150, 20, diffuse_light);
//        objects.push_back(cylinder);

		objects.push_back(side1);
		objects.push_back(side2);
		objects.push_back(floor);
		objects.push_back(ceiling);
		objects.push_back(back);
		objects.push_back(light);

		const auto vp = std::make_shared<ViewPlane>(500, 500, 700, 1);
		std::vector<std::shared_ptr<VectorialLight>> lights;
		std::vector<std::shared_ptr<AreaLight>> arealights;
		arealights.push_back(std::make_shared<AreaLight>(light));
		//arealights.push_back(std::make_shared<AreaLight>(0.20, Constants::WHITE, balllight));

		auto cornell = std::make_shared<Camera>(Point3(278, 278, -800), Point3(278, 278, 0), Vector3(0, 1, 0));
		auto world = World(vp, objects, lights, AmbientLight(0, ColorVec(1, 1, 1)), ColorVec(0, 0, 0), true);
		world.withCamera(cornell);
		world.withAreaLights(arealights);
		return world;

	}

	World buildingsScene() {
		std::vector<std::shared_ptr<VirtualObject>> objects;
		std::vector<std::shared_ptr<VectorialLight>> lights;
		std::vector<std::shared_ptr<AreaLight>> arealights;
		const auto black_white_texture = std::make_shared<CheckerTexture>(Constants::BLACK, Constants::WHITE, 10);
		const auto mirror = std::make_shared<Mirror>();
		const auto bw_matte_textured = std::make_shared<TexturedPhong>(black_white_texture, 1, 25);
		const auto ground_texture = std::make_shared<ImageTexture>("assets/textures/ground.jpg");
		const auto textured = std::make_shared<TexturedPhong>(ground_texture, 1, 25);
		const auto ground_bm = std::make_shared<ImageTexture>("assets/normalmaps/ground_bm.png");

		const auto moontexture = std::make_shared<ImageTexture>("assets/textures/moon.jpg");
		const auto moonmaterial = std::make_shared<TexturedMatte>(moontexture, 1);

		const auto universe = std::make_shared<ImageTexture>("assets/textures/universe.jpg");
		const auto universematerial = std::make_shared<TexturedMatte>(universe, 1);

		const auto textured_bp = std::make_shared<BumpMapping>(textured, ground_bm);
		const auto phong_reflective_higher_exp = std::make_shared<PhongReflective>(ColorVec(Constants::BLACK), 1, 25,
			1);
		const auto phong_metal = std::make_shared<PhongMetal>(1.24);
		const auto building_material = std::make_shared<Phong>(ColorVec(0.5, 0.5, 0.5), 1, 1, 25);
		auto mat = Matrix4x4(1.0f);
		const auto transparent = std::make_shared<SampleDielectric>(0.7);

		const auto soccerball_texture = std::make_shared<ImageTexture>("assets/textures/football-diffuse-512.png");
		const auto soccerball = std::make_shared<TexturedPhong>(soccerball_texture, 1, 2);
		const auto socceball_bm = std::make_shared<BumpMapping>(soccerball, std::make_shared<ImageTexture>("assets/normalmaps/football-normals-512.png"));
		const auto textured_bw = std::make_shared<TexturedMatte>(black_white_texture);

		const auto dielectric = std::make_shared<SampleDielectric>(6.9);
		const auto dielectric2 = std::make_shared<Dielectric>(Constants::YELLOW, Constants::BLACK, 1.24, 1.61, 1, 2);


		//objects.push_back(std::make_shared<Plane>(Point3(0, 0, 0), Vector3(0, 1, 0), textured_bp));
		//objects.push_back(std::make_shared<Plane>(Point3(0, 0, 13509), Vector3(0, 1, -1), bw_matte_textured));
		objects.push_back(std::make_shared<Ball>(Point3(0, 3000, 11509), 1000, moonmaterial));

		constexpr float a = 100000;
		objects.push_back(std::make_shared<Ball>(Point3(0, -a - 0.2f, 0), a, building_material));

		//objects.push_back(std::make_shared<Ball>(Point3(10000, 6000, 100000), 80000, building_material));
		objects.push_back(std::make_shared<Ball>(Point3(0, 0, 0), 12450, universematerial));



		auto building1 = std::make_shared<Mesh>("assets/objs/building1.obj",
			dielectric);
		mat = Matrix4x4(1.0f);
		mat = glm::translate(mat, Vector3(20, 0, 55));
		mat = glm::scale(mat, Vector3(15));
		mat = glm::rotate(mat, (float)glm::radians(45.0f), Vector3(0, 1, 0));

		building1->transform(mat);

		auto building2 = std::make_shared<Mesh>("assets/objs/building2.obj",
			std::make_shared<SampleDielectric>(4.5));
		mat = Matrix4x4(1.0f);
		mat = translate(mat, Vector3(76, 0, 50));
		mat = scale(mat, Vector3(15));
		mat = rotate(mat, (float)glm::radians(45.0f), Vector3(0, 1, 0));
		building2->transform(mat);

		auto building3 = std::make_shared<Mesh>("assets/objs/building3.obj",
			building_material);

		mat = Matrix4x4(1.0f);
		mat = translate(mat, Vector3(130, 0, 60));
		mat = scale(mat, Vector3(15));
		mat = rotate(mat, (float)glm::radians(45.0f), Vector3(0, 1, 0));
		building3->transform(mat);


		auto building4 = std::make_shared<Mesh>("assets/objs/building4.obj",
			building_material);

		mat = Matrix4x4(1.0f);
		mat = translate(mat, Vector3(130, 0, 180));
		mat = scale(mat, Vector3(15));
		mat = rotate(mat, (float)glm::radians(-45.0f), Vector3(0, 1, 0));
		building4->transform(mat);


		auto house = std::make_shared<Mesh>("assets/objs/house.obj",
			building_material);

		mat = Matrix4x4(1.0f);
		mat = translate(mat, Vector3(230, 0, 0));
		mat = scale(mat, Vector3(15));
		mat = rotate(mat, (float)glm::radians(-45.0f), Vector3(0, 1, 0));
		house->transform(mat);
		objects.push_back(house);

		objects.push_back(building1);
		objects.push_back(building2);
		objects.push_back(building3);
		objects.push_back(building4);




		objects.push_back(std::make_shared<Ball>(Point3(-20, 25, 40), 10, socceball_bm));
		auto vp = std::make_shared<ViewPlane>(60, 30, 15, 1);
		//vp = std::make_shared<ViewPlane>(900, 450, 15, 1);


		objects.push_back(std::make_shared<Ball>(Point3(120, 60, 125), 35,
			phong_reflective_higher_exp));


		objects.push_back(std::make_shared<Ball>(Point3(20, 20, 0), 15, transparent));
		objects.push_back(std::make_shared<Ball>(Point3(-20, 50, 250), 60, std::make_shared<SampleDielectric>(4.5)));


		auto mesh = std::make_shared<Mesh>("assets/objs/cow.obj", building_material);
		mat = glm::translate(Matrix4x4(1.0f), Vector3(220, 30, 40));
		float angle = 1.5708;
		//mat = glm::rotate(mat, 3*angle / 2, Vector3(0, 1, 0));
		mat = glm::scale(mat, Vector3(6));
		mesh->transform(mat);
		objects.push_back(mesh);


		auto mesh2 = std::make_shared<Mesh>("assets/objs/teapot.obj", phong_reflective_higher_exp);
		mat = glm::translate(Matrix4x4(1.0f), Vector3(450, 0, 150));
		mat = glm::rotate(mat, angle / 2, Vector3(0, 1, 0));
		mat = glm::scale(mat, Vector3(20));
		mesh2->transform(mat);
		objects.push_back(mesh2);




		//lights.push_back(std::make_shared<PointLight>(Point3(90, 30, 90), Constants::pi * 6, ColorVec(1, 1, 1)));




		auto diffuse_light = std::make_shared<DiffuseLight>(ColorVec(1, 1, 0.4), 1);


		//light2
		auto col = ColorVec(1, 1, 0.6);
		diffuse_light = std::make_shared<DiffuseLight>(col, 0.015);
		auto light2 = std::make_shared<Ball>(Point3(-5900, 1690, 10090), 400, diffuse_light);

		objects.push_back(light2);
		arealights.push_back(std::make_shared<AreaLight>(light2));

		//light3

		col = ColorVec(0.4, 0.4, 0.9);
		diffuse_light = std::make_shared<DiffuseLight>(col, 0.051);
		light2 = std::make_shared<Ball>(Point3(5900, 1690, 10090), 400,
			diffuse_light);

		objects.push_back(light2);
		arealights.push_back(std::make_shared<AreaLight>(light2));



		auto world = World(vp, objects, lights, AmbientLight(0.2, ColorVec(1, 1, 1)), ColorVec(0.1, 0.1, 0.4), true);
		auto cam = std::make_shared<Camera>(Point3(180, 80, -150), Point3(170, 80, 0), Vector3(0, 1, 0));
		//cam = std::make_shared<Camera>(Point3(180, 210, -150), Point3(170, 200, 0), Vector3(0, 1, 0));
		world.withCamera(cam);
		world.withAreaLights(arealights);
		return world;

	}

	World insideTest() {
		std::vector<std::shared_ptr<VirtualObject>> objects;
		std::vector<std::shared_ptr<VectorialLight>> lights;
		std::vector<std::shared_ptr<AreaLight>> arealights;
		const auto vp = std::make_shared<ViewPlane>(60, 30, 15, 1);
		const auto mirror = std::make_shared<Mirror>();
		const auto building_material = std::make_shared<Phong>(ColorVec(0.5, 0.5, 0.5), 1, 1, 25);
		const auto blue_white_texture = std::make_shared<CheckerTexture>(ColorVec(0.4, 0.4, 0.8), Constants::WHITE, 5);
		const auto black_white_texture = std::make_shared<CheckerTexture>(Constants::BLACK, Constants::WHITE, 10);
		const auto white_matte = std::make_shared<Matte>(1, ColorVec(1, 1.0, 1));
		const auto textured_test_material2 = std::make_shared<TexturedMaterial>(blue_white_texture, white_matte);
		const auto red_specular_phong = std::make_shared<Phong>(ColorVec(0.4, 0.5, 0.5), ColorVec(1, 0, 0), 1, 1, 23);
		const auto soccerball_texture = std::make_shared<ImageTexture>("assets/textures/football-diffuse-512.png");
		const auto soccerball = std::make_shared<TexturedPhong>(soccerball_texture, 1, 2);
		const auto socceball_bm = std::make_shared<BumpMapping>(soccerball, std::make_shared<ImageTexture>("assets/normalmaps/football-normals-512.png"));


		const auto bw_matte_textured = std::make_shared<TexturedPhong>(black_white_texture, 1, 25);
		const auto dielectric = std::make_shared<SampleDielectric>(2.9);
		const auto dielectric2 = std::make_shared<Dielectric>(Constants::YELLOW, Constants::BLACK, 1.24, 1.61, 1, 2);


		constexpr float a = 100000;
		objects.push_back(std::make_shared<Ball>(Point3(0, -a, 0), a, dielectric));
		objects.push_back(std::make_shared<Ball>(Point3(0, 0, 0), 1450, bw_matte_textured));

		auto diffuse_light = std::make_shared<DiffuseLight>(ColorVec(1, 1, 0.4), 1);

		objects.push_back(std::make_shared<Ball>(Point3(0, 100, 40), 60, socceball_bm));

		//light2
		auto col = ColorVec(1, 1, 1);
		diffuse_light = std::make_shared<DiffuseLight>(col, 6);
		auto light2 = std::make_shared<Ball>(Point3(-20, 460, -20), 10, diffuse_light);

		objects.push_back(light2);
		arealights.push_back(std::make_shared<AreaLight>(light2));

		//light3

		col = ColorVec(0.3, 0.2, 0.9);
		diffuse_light = std::make_shared<DiffuseLight>(col, 3);
		light2 = std::make_shared<Ball>(Point3(220, 450, -20), 20,
			diffuse_light);

		objects.push_back(light2);
		arealights.push_back(std::make_shared<AreaLight>(light2));

		auto world = World(vp, objects, lights, AmbientLight(0.0, ColorVec(1, 1, 1)), ColorVec(0.0, 0.0, .0), true);
		auto cam = std::make_shared<Camera>(Point3(0, 280, -700), Point3(0, 80, 0), Vector3(0, 1, 0));
		world.withCamera(cam);
		world.withAreaLights(arealights);
		return world;
	}
};