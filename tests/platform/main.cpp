#include <stdio.h>
#include <iostream>
#include "ELPlatform.h"

int main(int argc, char **argv) {
    std::cout << "hello world" << std::endl;
    ELContextPtr context = ELContext::alloc()->init();
    context->print("Hello Context");
    return 0;
}