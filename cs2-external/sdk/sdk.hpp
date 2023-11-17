#pragma once
#include"process.hpp"

int ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
int ScreenHeight = GetSystemMetrics(SM_CYSCREEN);

struct Matrix
{
	float matrix[16];
};

struct Vector
{
	float x, y, z;

};

namespace sdk
{
	float toMeters(float x) {
		return x / 39.62;
	}
}