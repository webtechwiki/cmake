#include "Solider.h"

Solider::Solider(std::string name)
{
    this->_name = name;
    this->_ptr_gun = nullptr;
}

void Solider::addGun(Gun *ptr_gun)
{
    this->_ptr_gun = ptr_gun;
}

void Solider::addBullectToGun(int num)
{
    this->_ptr_gun->addBullet(num);
}

bool Solider::fire()
{
    return this->_ptr_gun->shoot();
}

Solider::~Solider()
{
    if (this->_ptr_gun == nullptr)
    {
        return;
    }
    delete this->_ptr_gun;
    this->_ptr_gun = nullptr;
}