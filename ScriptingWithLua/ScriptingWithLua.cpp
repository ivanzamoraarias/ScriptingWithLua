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

int getPlayerObjectFromLua(lua_State*& L, Player& player);

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

	lua_getglobal(L, "getPlayer");
	if (lua_isfunction(L, -1)) {
		lua_pushnumber(L, 0); // index 0 as parameter  

		if (checkLua(L, lua_pcall(L, 1, 1, 0))) { // call function with one argument , it is the second argument of lua_pcal
			if (lua_istable(L, -1)) {
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

			}
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
