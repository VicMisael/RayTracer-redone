#include <cstdint>
#include <ratio>

#include "mt19937_point_sampler.h"
#include "Scene.h"
#include "worlds.h"
#include "imageoutputcanvas/imagecanvas.h"
#include <chrono>

#include "jscanvas/JSCanvas.h"
#include "jsonparser/world_factory.h"


std::shared_ptr<sampler> generateSampler(const int numsamples) {
    return std::make_shared<mt19937_point_sampler>(numsamples);
}
#ifndef __EMSCRIPTEN__
int main() {
    constexpr int32_t recursion_depth_limit = 3;
    constexpr uint32_t w = 1920;
    constexpr uint32_t h = w/2;
    auto drawcanvas = new imagecanvas(w, h, "biuding");
    auto selectedWorld = worlds::generateWorld1();
    Scene scene(selectedWorld, drawcanvas);

    const auto sampler = generateSampler(50);

    auto t1 = std::chrono::high_resolution_clock::now();
    scene.render(recursion_depth_limit, sampler);

    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> ms_double = t2 - t1;
    const auto seconds = ms_double.count() / 1000;

    scene.draw();

    std::cout << " Took";
    std::cout << seconds << "s" << std::endl;

}
#endif

#ifdef __EMSCRIPTEN__
extern "C"{
    EMSCRIPTEN_KEEPALIVE
    void render_scene_from_json(const char* jsonStr) {
        constexpr int32_t recursion_depth_limit = 3;
        constexpr uint32_t w = 800;
        constexpr uint32_t h = 600;

        try {
            std::string json(jsonStr);

            // auto world = world_factory::fromJson(json);
            auto world =  worlds::generateWorld1();
            auto canvas = new JSCanvas(w, h);

            Scene scene(world, canvas);

            auto sampler = generateSampler(1); // change if you want higher sampling

            auto t1 = std::chrono::high_resolution_clock::now();
            scene.render(recursion_depth_limit, sampler);
            auto t2 = std::chrono::high_resolution_clock::now();

            scene.draw();

            std::chrono::duration<double, std::milli> ms_double = t2 - t1;
            double seconds = ms_double.count() / 1000.0;

            printf("Render took %.3f seconds\n", seconds);

        } catch (const std::exception& ex) {
            emscripten_log(EM_LOG_ERROR, "Render error: %s", ex.what());
        }
    }
}

#endif




