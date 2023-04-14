// RayTracerRedone.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <thread>
#include <random>
#include "sdl2canvas/sdl2canvas.h"
int main(){
	std::cout << "STARTING SDL TRACER" << std::endl;
    static int display_in_use = 0; /* Only using first display */

    
    uint32_t w = 1280;
    uint32_t h = 720;

    Canvas* canvas = new sdl2canvas(w,h);

    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<float> dis(0.0, 1.0);
    RGBA rgba;
    auto draw = [&]() {
        for(;;){
      
        for (unsigned int y = 0; y < h; y++)
        {
           
            for (unsigned int x = 0; x < w; x++)
            {
               
                
                canvas->write_pixel(x, y, ColorRGBA(rgba));
                rgba.rgba++;
            }
            rgba.rgba++;
        }
        rgba.rgba++;
        }
    };

    std::thread t(draw);

    for (;;) {
        canvas->draw();
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
