// RayTracerRedone.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <thread>
#include <random>
#include "sdl2canvas/sdl2canvas.h"
#include "tracer/scene/World.h"
#include "tracer/objects/Plane.h"
#include "tracer/objects/Ball.h"
#include "tracer/scene/Scene.h"
#include "tracer/scene/materials/Lambertian.h"
#include "tracer/utils/sampler/diagonal_point_sampler.h"
#include "tracer/utils/sampler/equidistant_point_sampler.h"
#include "tracer/utils/sampler/mt19937_point_sampler.h"
#include "tracer/utils/sampler/random_point_sampler.h"

int main(){
	std::cout << "STARTING SDL TRACER" << std::endl;
    static int display_in_use = 0; /* Only using first display */

    
    const uint32_t w = 650;
    const uint32_t h = 650;

    auto *canvas = new sdl2canvas(w,h);
    
    const ViewPlane view_plane(650, 650,100,01.0f);

    std::vector<std::shared_ptr<VirtualObject>> objects;

    sampler* sampler = new mt19937_point_sampler(32);
    objects.push_back(std::make_shared<Plane>(Point3(0, 0, -700), Vector3(0, 0, 1), std::make_shared<Lambertian>(ColorVec(0.3, 0.3, 0.3))));
    objects.push_back(std::make_shared<Ball>(Point3(0, -955, -900), 1000, std::make_shared<Lambertian>(ColorVec(0.5f, 0.5f, 0.5f))));
	objects.push_back(std::make_shared<Ball>(Point3(150, -160, -280), 60, std::make_shared<Lambertian>(ColorVec(0.0f, 1.0f, 0))));
    objects.push_back(std::make_shared<Ball>(Point3(0, -150, -225), 60, std::make_shared<Lambertian>(ColorVec(0.0f, 0, 1))));
    objects.push_back(std::make_shared<Ball>(Point3(-200, -50, -225), 90, std::make_shared<Lambertian>(ColorVec(0.5f, 0.4, 0.2))));
    objects.push_back(std::make_shared<Ball>(Point3(150, 55, -650), 40, std::make_shared<Lambertian>(ColorVec(1.0f, 1.0f, 0))));
	objects.push_back(std::make_shared<Ball>(Point3(-150, 55, -650), 40, std::make_shared<Lambertian>(ColorVec(0.0f, 1.0f, 1.0f))));
	objects.push_back(std::make_shared<Ball>(Point3(0, 105, -650), 40, std::make_shared<Lambertian>(ColorVec(1,1,1))));
    AmbientLight ab(1, ColorVec(1.0, 1.0, 1));
    //auto lights=std::vector<Light*>();
    World world(view_plane, objects, ab, { 0.3,0.3,0.3 }, sampler,false);
    const Scene scene(&world,canvas);



    auto draw = [&]
    {
        while (!canvas->should_stop())
        {
            auto t1 = std::chrono::high_resolution_clock::now();
            scene.render();

            auto t2 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> ms_double = t2 - t1;
            std::cout<<" Took" << ms_double.count()/1000 << "s" << std::endl;
        }
    };
    std::thread t(draw);

    while (!canvas->should_stop()) {

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
