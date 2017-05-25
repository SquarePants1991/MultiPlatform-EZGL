//
// Created by wang yang on 2017/5/25.
//

#ifndef EZGL_ELFILEUTIL_H
#define EZGL_ELFILEUTIL_H

#include <string>

class ELFileUtil {
public:
    static std::string stringContentOfFile(std::string filePath);
    static std::string stringContentOfShader(std::string filePath);
};


#endif //EZGL_ELFILEUTIL_H
