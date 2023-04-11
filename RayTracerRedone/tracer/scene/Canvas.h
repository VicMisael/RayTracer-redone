#pragma once
#include <cstdint>
#include "ViewPlane.h"
class Canvas
{
public:
	const uint32_t hsize;
	const uint32_t vsize;
	float step_size_x(ViewPlane viewPlane) {

	};
	float step_size_y(ViewPlane viewPlane) {};

	virtual void write_pixel(int x,int y,uint8_t r, uint8_t g, uint8_t b)=0;
	virtual void draw()=0;
};

