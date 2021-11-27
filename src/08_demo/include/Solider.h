#pragma once
#include <string>
#include "Gun.h"

class Solider
{
private:
    std::string _name;
    Gun *_ptr_gun;

public:
    Solider(std::string name);
    ~Solider();
    void addGun(Gun *ptr_gun);
    void addBullectToGun(int num);
    bool fire();
};
