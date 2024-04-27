// RayTracerRedone.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>

#define SDL_MAIN_HANDLED

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
#include "splash.h"

std::shared_ptr<sampler> generateSampler(const int numsamples) {
    return std::make_shared<equidistant_point_sampler>(numsamples);
}

int main(int argc, char *argv[]) {
    for (unsigned char c: splash_txt)
        std::cout << c;
    std::cout << std::endl;
//    auto result = utility::ONBTransform( {0, -1, 0}, {-0.681978881f, 0.676145434f, -0.278804928});
//    assert(utility::nanBugCheck(glm::vec4(result, 1)));
    constexpr bool png = false;
    if (argc == 1 || argc > 1 && std::string("all") != argv[1]) {


        const uint32_t w = 400;
        const uint32_t h = 200;


        const auto sampler = generateSampler(20);


        const auto selectedWorld = worlds::buildingsScene();
        Canvas *drawcanvas;

        if (png) {
            drawcanvas = new imagecanvas(w, h, "buildingsfinalnonm");
        } else {
            drawcanvas = new sdl2canvas(w, h);
        }
        constexpr int32_t recursion_depth_limit = 10;

        Scene scene(selectedWorld, drawcanvas);
        //auto cam = std::make_shared<Camera>(Point3(690, 710, 180), Point3(40, 30, 105), Vector3(0, 1, 0));
        if (!png) {
            auto *canvas = dynamic_cast<sdl2canvas *>(drawcanvas);
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

        } else {

            auto t1 = std::chrono::high_resolution_clock::now();
            scene.render(recursion_depth_limit, sampler);

            auto t2 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> ms_double = t2 - t1;
            const auto seconds = ms_double.count() / 1000;

            scene.draw();

            std::cout << " Took";
            std::cout << seconds << "s" << std::endl;
        }
    } else if (argc == 2 && std::string("all") == argv[1]) {
        const uint32_t w = 750;
        const uint32_t h = 750;

        const auto worlds = {worlds::generateWorld1(false), worlds::generateWorld1(true), worlds::cornellBox(),
                             worlds::buildingsScene(), worlds::refractanceTest(),
                             worlds::testeFeatures(false), worlds::testeFeatures(true), worlds::moonEarth(),
                             worlds::moonEarthPerspective(), worlds::meshTest()};

        const std::vector<std::string> worldsname = {"generateWorld1O", "generateWorld1P", "cornellBox",
                                                     "buildingsScene", " refractanceTest",
                                                     "testeFeaturesO", "testeFeaturesP", "moonEarth",
                                                     "moonEarthPerspective", "meshTest"};

        const auto sampler = generateSampler(60);
        int it = 0;
        for (auto selectedWorld: worlds) {
            auto name = worldsname[it++];

            std::cout << "name:" << name << std::endl;

            Canvas *drawcanvas = new imagecanvas(w, h, name);

            constexpr int32_t recursion_depth_limit = 10;

            Scene scene(selectedWorld, drawcanvas);

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
