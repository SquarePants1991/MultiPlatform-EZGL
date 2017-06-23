#include <stdio.h>
#include <iostream>
#include "ELRenderer.h"

int main(int argc, char **argv) {
    std::cout << "hello world" << std::endl;
    ELRendererPtr context = ELRenderer::alloc()->init();
    return 0;
}