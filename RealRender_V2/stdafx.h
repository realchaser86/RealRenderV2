// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#pragma warning ( disable : 4005 )

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: reference additional headers your program requires here
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#include <string>
#include <sstream>
#include <unordered_map>
#include <map>
#include <vector>
#include <array>
#include <algorithm>
#include <cassert>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")

using namespace std;