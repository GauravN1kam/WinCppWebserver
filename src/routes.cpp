#include "../include/routes.h"

void addRoute(std::map<std::string, std::string> &router, std::string path, std::string res)
{
    router[path] = res;
}
