// RayTracerRedone.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>

#define SDL_MAIN_HANDLED
//#define GLM_FORCE_MESSAGES

#include <thread>
#include "tracer/scene/Scene.h"
#include "sdl2canvas/sdl2canvas.h"
#include "imageoutputcanvas/imagecanvas.h"
#include "worlds.h"


#include "tracer/utils/sampler/diagonal_point_sampler.h"
#include "tracer/utils/sampler/equidistant_point_sampler.h"
#include "tracer/utils/sampler/mt19937_point_sampler.h"
#include "tracer/utils/sampler/random_point_sampler.h"
#include "tracer/utils/sampler/vertical_point_sampler.h"
#include "tracer/utils/sampler/horizontal_point_sampler.h"

#include "tracer/utils/utility.h"

std::shared_ptr<sampler> generateSampler(int numsamples) {
    return std::make_shared<mt19937_point_sampler>(numsamples);
}

int main() {
    constexpr bool png = false;


    const uint32_t w = 1600;
    const uint32_t h = 1600;
    //TODO: ARea Lights, Refractance, BumpMapping,




    const auto sampler = generateSampler(1000);

    auto selectedWorld = worlds::testeFeatures(false);
    Canvas *drawcanvas;

    if (png) {
        drawcanvas = new imagecanvas(w,h);
    } else {
        drawcanvas = new sdl2canvas(w, h);
    }
    constexpr int32_t recursion_depth_limit = 10;

    Scene scene(selectedWorld, drawcanvas);

    if (!png) {
        auto *canvas = dynamic_cast<sdl2canvas*>(drawcanvas);
        auto draw = [&] {
            while (!canvas->should_stop()) {
                auto t1 = std::chrono::high_resolution_clock::now();
                scene.render(recursion_depth_limit, sampler);

                auto t2 = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> ms_double = t2 - t1;
                const auto seconds = ms_double.count() / 1000;
                std::cout << " Took";
                std::cout << seconds << "s" << std::endl;
                //std::cout << "Intersection Test with triangle called" << utility::counter << std::endl;
            }
        };

        std::thread t(draw);

        while (!canvas->should_stop()) {
            scene.draw();
        }

    }else{

        auto t1 = std::chrono::high_resolution_clock::now();
        scene.render(recursion_depth_limit, sampler);

        auto t2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> ms_double = t2 - t1;
        const auto seconds = ms_double.count() / 1000;

        scene.draw();

        std::cout << " Took";
        std::cout << seconds << "s" << std::endl;
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
