// ScriptingWithLua.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
extern "C" {
	#include "Lua/include/lua.h"
	#include "Lua/include/lauxlib.h"
	#include "Lua/include/lualib.h"
}
#ifdef _WIN32
#pragma comment(lib, "Lua/liblua53.a")
#endif

bool checkLua(lua_State *L, int r) {
	if (r == LUA_OK)
		return true;

	std::string errorMessage = lua_tostring(L, -1);
	std::cout << errorMessage << std::endl;
	return false;
}

void finishLua(lua_State* L) {
	lua_close(L);
}
int main()
{
    std::cout << "Lua Scripting !!!! !\n";

	//std::string cmd = "a = 3 + 5 + math.sin(45.0)";

	lua_State* L = luaL_newstate(); // create lua virtual machine

	luaL_openlibs(L);


	//int r = luaL_dostring(L, cmd.c_str());
	int r = luaL_dofile(L, "script.lua");

	if (!checkLua(L, r)) {
		finishLua(L);
		return 0;
	}

	int sss = lua_getglobal(L, "a");
	if (lua_isnumber(L, -1)) {
		float aInCpp = (float)lua_tonumber(L, -1);
		std::cout << "a in Cplusplus: " << aInCpp << std::endl;
	}
	

	finishLua(L);
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
