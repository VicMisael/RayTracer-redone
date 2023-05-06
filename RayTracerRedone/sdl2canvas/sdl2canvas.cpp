#include "sdl2canvas.h"

void sdl2canvas::write_pixel(const uint16_t x, const uint16_t y, const ColorRGBA colorRgba)
{
     this->rgba[y * this->width + x] = colorRgba.toRgba().rgba;
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
            std::cout << "should quit" << std::endl;
            SDL_RenderClear(renderer);
            SDL_DestroyTexture(framebuffer);
            SDL_DestroyWindow(window);
            SDL_Quit();
        	shouldstop=true;
            break;
        }
    }

}
