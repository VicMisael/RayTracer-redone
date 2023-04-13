#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include "../tracer/scene/Canvas.h"

class sdl2canvas:public Canvas
{
private:
    uint32_t* rgba;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* framebuffer;

public:
	sdl2canvas(const uint32_t w, const uint32_t h) :Canvas(w, h){
        assert(w <= 1000);
        assert(h <= 1000);
        std::cout << "STARTING SDL TRACER" << std::endl;
        static int display_in_use = 0; /* Only using first display */

        window = SDL_CreateWindow("RayCaster", 100, 100, w, h, 0);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        framebuffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, w, h);
        rgba = new uint32_t[w * h];
	}
	void write_pixel(int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a) override final;
	void draw() override final;
};

