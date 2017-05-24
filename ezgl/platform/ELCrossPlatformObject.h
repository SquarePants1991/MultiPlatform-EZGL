//
// Created by wangyang on 2017/5/23.
//

#ifndef EZGL_ELCROSSPLATFORMOBJECT_H
#define EZGL_ELCROSSPLATFORMOBJECT_H

#include <stdio.h>
#include <string>
#include <map>
#include "types/EZGLTypes.h"

#define crossplatform_var(type, name) \
    type name##Get(ELCrossPlatformObject * instance) {\
        return instance->__crossplatformFetchInt("##name##");\
    }\
    void name##Set(ELCrossPlatformObject * instance, type val) {\
        return instance->__crossplatformAttach("framebuffer", val);\
    }

class ELCrossPlatformObject {
private:
    std::map<std::string, ELInt> _intAttachments;
    std::map<std::string, ELFloat > _floatAttachments;
    std::map<std::string, std::string> _stringAttachments;
    std::map<std::string, void *> _objAttachments;
public:
    void __crossplatformAttach(std::string _attachKey, ELInt _val) {
        _intAttachments[_attachKey] = _val;
    }
    void __crossplatformAttach(std::string _attachKey, ELFloat _val) {
        _floatAttachments[_attachKey] = _val;
    }
    void __crossplatformAttach(std::string _attachKey, std::string _val) {
        _stringAttachments[_attachKey] = _val;
    }
    void __crossplatformAttach(std::string _attachKey, void * _val) {
        _objAttachments[_attachKey] = _val;
    }

    ELInt __crossplatformFetchInt(std::string _attachKey) {
        return _intAttachments[_attachKey];
    }

    ELFloat __crossplatformFetchFloat(std::string _attachKey) {
        return _floatAttachments[_attachKey];
    }

    std::string __crossplatformFetchString(std::string _attachKey) {
        return _stringAttachments[_attachKey];
    }

    void * __crossplatformFetchObject(std::string _attachKey) {
        return _objAttachments[_attachKey];
    }

    bool __crossplatformIntExist(std::string _attachKey) {
        return _intAttachments.find(_attachKey) != _intAttachments.end();
    }
    bool __crossplatformFloatExist(std::string _attachKey) {
        return _floatAttachments.find(_attachKey) != _floatAttachments.end();
    }
    bool __crossplatformStringExist(std::string _attachKey) {
        return _stringAttachments.find(_attachKey) != _stringAttachments.end();
    }
    bool __crossplatformObjectExist(std::string _attachKey) {
        return _objAttachments.find(_attachKey) != _objAttachments.end();
    }
};


#endif //EZGL_ELCROSSPLATFORMOBJECT_H
