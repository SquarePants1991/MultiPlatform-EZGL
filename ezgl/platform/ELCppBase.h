//
// Created by wang yang on 2017/5/21.
//

#ifndef EZGL_ELCPPBASE_H
#define EZGL_ELCPPBASE_H

#include <stdio.h>
#include <memory>

#define ELClass(className) \
class className;\
typedef std::shared_ptr<className> className##Ptr;\
typedef std::weak_ptr<className> className##WeakPtr;\
class className

#define ELAlloc(className) \
public:\
className() {}\
private:\
std::weak_ptr<className> _weak_self;\
inline std::shared_ptr<className> _strong_self() { \
    return _weak_self.lock(); \
}\
public:\
static className##Ptr alloc() {\
    className *instance = new className();\
    auto ptr = std::shared_ptr<className>(instance);\
    instance->_weak_self = ptr;\
    return ptr;\
}

#define classDef(className) \
ELClass(className) { \
ELAlloc(className)

#define defEnd };

#define self _strong_self()

#endif //EZGL_ELCPPBASE_H
