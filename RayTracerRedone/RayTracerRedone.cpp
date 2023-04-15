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

int main(){
	std::cout << "STARTING SDL TRACER" << std::endl;
    static int display_in_use = 0; /* Only using first display */

    
    uint32_t w = 900;
    uint32_t h = 900;

    Canvas* canvas = new sdl2canvas(w,h);
    
    ViewPlane viewPlane(900, 900,1.0f);

    std::vector<VirtualObject*> objects;

    objects.push_back(new Plane(Point3(0, 0, 0), Vector3(0, 1, 1), Material(ColorVec(0.0, 0.3, 0.0))));
    objects.push_back(new Ball(Point3(0, 30, 0), 60, Material(ColorVec(1.0f, 0, 0))));
    objects.push_back(new Ball(Point3(0, -25, 0), 80, Material(ColorVec(1.0f, 1.0f, 0))));

  
    World world(viewPlane,objects,ColorVec(0,0,0.5f));
    Scene scene(&world,canvas);

    for (;;) {
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
