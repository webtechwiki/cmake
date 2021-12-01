#include "Gun.h"
#include "Solider.h"
#include "iostream"

void test()
{
    Solider sanduo("xusanduo");
    sanduo.addGun(new Gun("AK47"));
    sanduo.addBullectToGun(20);
    sanduo.fire();
}

int main(int argc, char const *argv[])
{
    std::cout << "this is a test stating" << std::endl;
    test();
    return 0;
}
