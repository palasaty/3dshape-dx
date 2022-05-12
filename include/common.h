#pragma once

#include <clocale>
#include <ctime>

#include <string>
#include <list>
#include <vector>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <d3d11.h>
#include <directxmath.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#define _DELETE(p)		    { if(p) { delete (p);    (p) = nullptr;} }
#define _DELETE_ARRAY(p)	{ if(p) { delete[] (p);  (p) = nullptr;} }
#define _RELEASE(p)		    { if(p) {(p)->Release(); (p) = nullptr;} }
#define _CLOSE(p)		    { if(p) {(p)->Close(); delete (p); (p) = nullptr;} }
