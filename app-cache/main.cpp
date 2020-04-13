#include <iostream>
#include "Cache.h"
int main() {
    std::cout << "Hello, World!" << std::endl;
    Cache * t1 = Cache::shared();
    return 0;
}
