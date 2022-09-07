#include <string>
#include <iostream>
#include <filesystem>

extern "C" {
    #include "lua.h"
    #include "lauxlib.h"
}


int GetFiles(lua_State *L) {

    std::string path = lua_tostring(L, 1);

    std::filesystem::path currentpath = std::filesystem::current_path();

    currentpath.append(path);


    if (std::filesystem::exists(currentpath) && std::filesystem::is_directory(currentpath)) {
        lua_newtable(L);
        int i = 1;
        for (auto &p : std::filesystem::directory_iterator(currentpath)) {
            lua_pushnumber(L, i);
            lua_pushstring(L, p.path().filename().string().c_str());
            lua_settable(L, -3);
            i++;
        }
        return 1;
    }
    

    lua_pushnil(L);
    return 1;
}

int GetDirectories(lua_State *L) {

    std::string path = lua_tostring(L, 1);

    std::filesystem::path currentpath = std::filesystem::current_path();


    currentpath.append(path);


    if (std::filesystem::exists(currentpath) && std::filesystem::is_directory(currentpath)) {
        lua_newtable(L);
        int i = 1;
        for (auto &p : std::filesystem::directory_iterator(currentpath)) {
            if (std::filesystem::is_directory(p)) {
                lua_pushnumber(L, i);
                lua_pushstring(L, p.path().filename().string().c_str());
                lua_settable(L, -3);
                i++;
            }
        }
        return 1;
    }


    lua_pushnil(L);
    return 1;
}




extern "C" int luaopen_nanofile (lua_State *L) { 

    luaL_Reg nanofile[] = {
        {"GetFiles", GetFiles},
        {"GetDirectories", GetDirectories},
        {NULL, NULL}
    };

    lua_newtable(L);

    lua_getglobal(L, "File");
    lua_pushnil(L);
    while (lua_next(L, -2) != 0) {
        lua_pushvalue(L, -2);
        lua_insert(L, -2);
        lua_settable(L, -5);
    }
    lua_pop(L, 1);

    luaL_setfuncs(L, nanofile, 0);

    lua_setglobal(L, "File");

    return 0;
}