//
// Created by wang yang on 2017/5/21.
//

#include "ELContext.h"

ELContextPtr ELContext::init() {
    printf("Context Created");
}

void ELContext::print(char *msg) {
    printf(msg);
}