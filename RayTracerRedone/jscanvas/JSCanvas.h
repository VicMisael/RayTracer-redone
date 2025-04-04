//
// Created by Misael on 04/04/2025.
//

#ifndef JSCANVAS_H
#define JSCANVAS_H
#include "../tracer/scene/Canvas.h"
#include <vector>
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>
#include <emscripten/val.h>

class JSCanvas: Canvas {

private:
    std::vector<uint8_t> pixelBuffer;

public:
    JSCanvas(uint32_t _w, uint32_t _h)
        : Canvas(_w, _h), pixelBuffer(_w * _h * 4, 255) {}  // Default alpha = 255

    void write_pixel(uint16_t x, uint16_t y, const ColorRGBA color) override {
        if (x >= width || y >= height) return;

        size_t idx = 4 * (y * width + x);
        pixelBuffer[idx + 0] = static_cast<uint8_t>(color.r);  // R
        pixelBuffer[idx + 1] = static_cast<uint8_t>(color.g);  // G
        pixelBuffer[idx + 2] = static_cast<uint8_t>(color.b);  // B
        pixelBuffer[idx + 3] = static_cast<uint8_t>(color.a);  // A
    }

    void draw() override {
        using namespace emscripten;
        val document = val::global("document");
        val ctx = document.call<val>("getElementById", val("canvas"))
                         .call<val>("getContext", val("2d"));

        // Create JS Uint8ClampedArray from C++ vector
        val uint8ClampedArray = val::global("Uint8ClampedArray").new_(typed_memory_view(pixelBuffer.size(), pixelBuffer.data()));

        // Create ImageData and put on canvas
        val imageData = val::global("ImageData").new_(uint8ClampedArray, val(width), val(height));
        ctx.call<void>("putImageData", imageData, val(0), val(0));
    }
};



#endif //JSCANVAS_H
