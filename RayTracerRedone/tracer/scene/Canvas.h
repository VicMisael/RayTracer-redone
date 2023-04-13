#pragma once
#include <cstdint>
#include "ViewPlane.h"
class Canvas
{	
protected:
	const uint32_t width;
	const uint32_t height;
public:

	Canvas(const uint32_t _w,const uint32_t _h):width(_w),height(_h){}

	float step_size_y(ViewPlane viewPlane) const{
		return viewPlane.hsize / (float)height;
	};
	float step_size_x(ViewPlane viewPlane) const {
		return viewPlane.wsize / (float)width;
	};
	uint32_t getWidth() const {
		return width;
	}
	uint32_t getHeight() const {
		return height;
	}
	virtual void write_pixel(int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a) = 0;
	virtual void draw()=0;
};

