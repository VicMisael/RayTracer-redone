#include "sdl2canvas.h"

void sdl2canvas::write_pixel(int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    union {
        uint32_t rgba;
        struct {
            uint8_t  _r, _g, _b, _a;
        };
    } rgbaCol;
    rgbaCol._r = r;
    rgbaCol._g = g;
    rgbaCol._b = b;
    rgbaCol._a = a;

    this->rgba[y * this->width + x]=rgbaCol.rgba;
}

void sdl2canvas::draw()
{
    SDL_UpdateTexture(framebuffer, NULL, rgba, this->width * sizeof(uint32_t));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, framebuffer, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        switch (e.type)
        {

        case SDL_QUIT:
            //std::cout<<"Sai pora"<<std::endl;
            SDL_RenderClear(renderer);
            SDL_DestroyTexture(framebuffer);
            SDL_DestroyWindow(window);
            SDL_Quit();
            break;
        }
    }

}
