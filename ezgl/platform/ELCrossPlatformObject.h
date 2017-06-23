//
// Created by wangyang on 2017/5/23.
//

#ifndef EZGL_ELCROSSPLATFORMOBJECT_H
#define EZGL_ELCROSSPLATFORMOBJECT_H

#include <stdio.h>
#include <string>
#include <map>
#include "types/EZGLTypes.h"

#define Stringify(str) #str

#define crossplatform_var_int(name) \
    ELInt name##Get(ELCrossPlatformObject * instance) {\
        return instance->__crossplatformFetchInt(Stringify(name));\
    }\
    void name##Set(ELCrossPlatformObject * instance, ELInt val) {\
        return instance->__crossplatformAttach(Stringify(name), val);\
    }

#define crossplatform_var_float(name) \
    ELFloat name##Get(ELCrossPlatformObject * instance) {\
        return instance->__crossplatformFetchFloat(Stringify(name));\
    }\
    void name##Set(ELCrossPlatformObject * instance, ELFloat val) {\
        return instance->__crossplatformAttach(Stringify(name), val);\
    }

#define crossplatform_var_string(name) \
    std::string name##Get(ELCrossPlatformObject * instance) {\
        return instance->__crossplatformFetchString(Stringify(name));\
    }\
    void name##Set(ELCrossPlatformObject * instance, std::string val) {\
        return instance->__crossplatformAttach(Stringify(name), val);\
    }

#define crossplatform_var_obj(name) \
    void * name##Get(ELCrossPlatformObject * instance) {\
        return instance->__crossplatformFetchObject(Stringify(name));\
    }\
    void name##Set(ELCrossPlatformObject * instance, void * val) {\
        return instance->__crossplatformAttach(Stringify(name), val);\
    }

#define crossplatform_var_bool(name) \
    bool name##Get(ELCrossPlatformObject * instance) {\
        return instance->__crossplatformFetchBool(Stringify(name));\
    }\
    void name##Set(ELCrossPlatformObject * instance, bool val) {\
        return instance->__crossplatformAttach(Stringify(name), val);\
    }


class ELCrossPlatformObject {
private:
    std::map<std::string, ELInt> _intAttachments;
    std::map<std::string, ELFloat > _floatAttachments;
    std::map<std::string, std::string> _stringAttachments;
    std::map<std::string, void *> _objAttachments;
    std::map<std::string, bool> _boolAttachments;
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
    void __crossplatformAttach(std::string _attachKey, bool _val) {
        _boolAttachments[_attachKey] = _val;
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
    
    bool __crossplatformFetchBool(std::string _attachKey) {
        return _boolAttachments[_attachKey];
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
    bool __crossplatformBoolExist(std::string _attachKey) {
        return _boolAttachments.find(_attachKey) != _boolAttachments.end();
    }
};


#endif //EZGL_ELCROSSPLATFORMOBJECT_H
