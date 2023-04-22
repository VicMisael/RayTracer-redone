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
#include "tracer/utils/sampler/equidistant_point_sampler.h"
#include "tracer/utils/sampler/random_point_sampler.h"

int main(){
	std::cout << "STARTING SDL TRACER" << std::endl;
    static int display_in_use = 0; /* Only using first display */

    
    const uint32_t w = 650;
    const uint32_t h = 650;

    auto *canvas = new sdl2canvas(w,h);
    
    const ViewPlane view_plane(650, 650,100,1.0f);

    std::vector<VirtualObject*> objects;

    sampler* sampler = new equidistant_point_sampler(1);

    objects.push_back(new Plane(Point3(0, 0, -400), Vector3(1, 1, 1), Material(ColorVec(1.0, 1.0, 1.0))));
    objects.push_back(new Ball(Point3(150, -160, -280), 60, Material(ColorVec(0.0f, 1.0f, 0))));
    objects.push_back(new Ball(Point3(0, 0, -225), 20, Material(ColorVec(0.0f, 0, 1))));
    objects.push_back(new Ball(Point3(-200, -50, -225), 90, Material(ColorVec(0.5f, 0.4 , 0.2))));
    objects.push_back(new Ball(Point3(150, 105, -250), 40, Material(ColorVec(1.0f, 1.0f, 0))));

    AmbientLight ab(1, ColorVec(0.95, 0.95, 1));
    //auto lights=std::vector<Light*>();
    World world(view_plane,objects,ab, ColorVec(0.005f, 0.0f, 0.5f),sampler);
    const Scene scene(&world,canvas);

    while (!canvas->should_stop()) {
        scene.render();
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
