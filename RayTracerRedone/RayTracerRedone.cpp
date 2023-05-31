// RayTracerRedone.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#define SDL_MAIN_HANDLED
#define GLM_FORCE_MESSAGES
#include <SDL2/SDL.h>
#include <thread>
#include <random>

#include "sdl2canvas/sdl2canvas.h"

#include "tracer/scene/World.h"
#include "tracer/objects/Plane.h"
#include "tracer/objects/Ball.h"
#include "tracer/objects/OpenCylinder.h"

#include "tracer/scene/Scene.h"
#include "tracer/scene/light/DirectionalLight.h"
#include "tracer/scene/light/PointLight.h"

#include "tracer/scene/materials/WhiteMetal.h"
#include "tracer/utils/sampler/diagonal_point_sampler.h"
#include "tracer/utils/sampler/equidistant_point_sampler.h"
#include "tracer/utils/sampler/mt19937_point_sampler.h"
#include "tracer/utils/sampler/random_point_sampler.h"
#include "tracer/utils/sampler/vertical_point_sampler.h"

#include "tracer/scene/materials/PhongReflective.h"
#include "tracer/scene/materials/PhongMetal.h"
#include "tracer/scene/materials/Diffuse.h"
#include "tracer/scene/materials/Matte.h"
#include "tracer/scene/materials/Mirror.h"
#include "tracer/scene/materials/Phong.h"


std::vector<std::shared_ptr<VirtualObject>> generateObjects()
{
	std::vector<std::shared_ptr<VirtualObject>> objects;
	const auto plane_material= std::make_shared<Phong>(ColorVec(0.4,0.4,0.8),1,1,25);
    const auto plane_material2= std::make_shared<Phong>(ColorVec(0.4,0.9,0.2),1,1,25);
    objects.push_back(std::make_shared<Plane>(Point3(0, 0, -1900), Vector3(0, -1, 1), plane_material));
	objects.push_back(std::make_shared<Plane>(Point3(0, 900, 1000), Vector3(0, 1, 1), plane_material2));

	objects.push_back(std::make_shared<Ball>(Point3(0, -955, -1000), 1000, std::make_shared<Matte>(1,ColorVec(1, 1.0,1))));
	objects.push_back(std::make_shared<Ball>(Point3(1350, 0, -900), 1000, std::make_shared<PhongMetal>()));
	objects.push_back(
		std::make_shared<Ball>(Point3(-1250, 0, -900), 1000, 
			std::make_shared<Phong>(ColorVec(0.4,0.5,0.5),ColorVec(1,0,0),1,1,23)));

	objects.push_back(std::make_shared<Ball>(Point3(5, -20, -625), 120, std::make_shared<PhongMetal>(1)));


	objects.push_back(std::make_shared<Ball>(Point3(-150, 55, -150), 40,
		std::make_shared<Matte>(1,Constants::WHITE)));

	objects.push_back(std::make_shared<Ball>(Point3(0, 40, -650), 40,
		std::make_shared<Mirror>()));

	objects.push_back(std::make_shared<Ball>(Point3(-90, -25, -350), 105,
		std::make_shared<Matte>(1,ColorVec(1, 0, 1))));

	objects.push_back(std::make_shared<Ball>(Point3(0, 0, -195), 95,
		std::make_shared<PhongReflective>(Constants::BLACK,1,12,1)));

	objects.push_back(std::make_shared<Ball>(Point3(400, 150, -350), 150,
		std::make_shared<Matte>(1, ColorVec(1, 1, 0))));

	objects.push_back(std::make_shared<Ball>(Point3(0, 100, -925), 256,
		std::make_shared<Mirror>()));

	objects.push_back(std::make_shared<Ball>(Point3(0, 650, -125), 120,
		std::make_shared<PhongReflective>(ColorVec(Constants::BLACK),1,25,1)));


    //objects.push_back(std::make_shared<OpenCylinder>(Vector3(0,1,0),Point3(100,0,-300),150,50,std::make_shared<PhongReflective>()));

	return objects;
}
std::vector<std::shared_ptr<VectorialLight>> generate_vectorial_lights()
{
	std::vector<std::shared_ptr<VectorialLight>> lights;
	//lights.push_back(std::make_shared<DirectionalLight>(Vector3(0, 1, 1), 3.15, ColorVec(1, 1, 1)));
	lights.push_back(std::make_shared<PointLight>(Point3(90, 0 ,0), Constants::pi*6, ColorVec(1, 1, 1)));

	return lights;
}


int main()
{
	static int display_in_use = 0; /* Only using first display */


	const uint32_t w = 900;
	const uint32_t h = 900;

	auto* canvas = new sdl2canvas(w, h);
	//True=Perspective False=parallel
	constexpr bool projection=false;

	const ViewPlane view_plane=projection? ViewPlane(60, 60,20, 01.0f): ViewPlane(1450, 1450, 50, 01.0f);

	sampler* sampler = new mt19937_point_sampler(90);

	AmbientLight ab(0, ColorVec(1.0, 1.0, 1));
	World world(view_plane, generateObjects(), generate_vectorial_lights(), ab, {0.9 , 0.9 , 1}, sampler, projection);


	const Scene scene(&world, canvas);

	constexpr int32_t recursion_depth_limit = 8;

	auto draw = [&]
	{
		while (!canvas->should_stop())
		{
			auto t1 = std::chrono::high_resolution_clock::now();
			scene.render(recursion_depth_limit);

			auto t2 = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> ms_double = t2 - t1;
			std::cout << " Took" << ms_double.count() / 1000 << "s" << std::endl;
		}
	};
	std::thread t(draw);

	while (!canvas->should_stop())
	{
		scene.draw();
	}
}

// Executar programa: Ctrl + F5 ou Menu Depurar > Iniciar Sem Depuração
// Depurar programa: F5 ou menu Depurar > Iniciar Depuração

// Dicas para Começar: 
//   1. Use a janela do Gerenciador de Soluções para adicionar/gerenciar arquivos
//   2. Use a janela do Team Explorer para conectar-se ao controle do código-fonte
//   3. Use a janela de Saída para ver mensagens de saída do build e outras mensagens
//   4. Use a janela Lista de Erros para exibir erros
//   5. Ir Para o Projeto > Adicionar Novo Item para criar novos arquivos de código, ou Projeto > Adicionar Item Existente para adicionar arquivos de código existentes ao projeto
//   6. No futuro, para abrir este projeto novamente, vá para Arquivo > Abrir > Projeto e selecione o arquivo. sln
