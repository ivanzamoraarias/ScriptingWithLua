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

struct Player {
	std::string role;
	std::string name;
	std::string ability;
	int level;

} player;

bool checkLua(lua_State* L, int r) {
	if (r == LUA_OK)
		return true;

	std::string errorMessage = lua_tostring(L, -1);
	std::cout << errorMessage << std::endl;
	return false;
}

void finishLua(lua_State* L) {
	lua_close(L);
}

int getPlayerObjectFromLua(lua_State*& L, Player& player, bool& retflag);

int main()
{
	

	std::cout << "Lua Scripting !!!! !\n";

	lua_State* L = luaL_newstate(); // create lua virtual machine

	luaL_openlibs(L);

	int r = luaL_dofile(L, "script.lua");

	if (!checkLua(L, r)) {
		finishLua(L);
		return 0;
	}

	lua_getglobal(L, "addSomething");
	if (lua_isfunction(L, -1)) {
		lua_pushnumber(L, 3.5f); // a
		lua_pushnumber(L, 8.5f); // b

		if (checkLua(L, lua_pcall(L, 2, 1, 0))) {
			float result = (float)lua_tonumber(L, 1);
			std::cout << "called a function: result=  " << result << std::endl;
		}
	}

	/*if (getPlayerObjectFromLua(L, player) == 0)
		return 0;*/

	finishLua(L);
	return 0;
}

int getPlayerObjectFromLua(lua_State*& L, Player& player)
{
	
	lua_getglobal(L, "player");

	if (!lua_istable(L, -1)) {
		finishLua(L);
		return 0;
	}

	lua_pushstring(L, "Name");
	lua_gettable(L, -2);
	player.name = lua_tostring(L, -1);
	lua_pop(L, 1);

	lua_pushstring(L, "Role");
	lua_gettable(L, -2);
	player.role = lua_tostring(L, -1);
	lua_pop(L, 1);

	lua_pushstring(L, "Ability");
	lua_gettable(L, -2);
	player.ability = lua_tostring(L, -1);
	lua_pop(L, 1);

	lua_pushstring(L, "Level");
	lua_gettable(L, -2);
	player.level = (int)lua_tonumber(L, -1);
	lua_pop(L, 1);


	std::cout << player.name << " " << player.role << " " << player.ability << " " << player.level << std::endl;
	
	return 1;
}
