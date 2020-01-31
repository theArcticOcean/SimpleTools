#ifndef MACRODEFINED_HPP
#define MACRODEFINED_HPP

#define CPP_SET_MACRO( name, type ) \
virtual void Set##name(type _arg) \
{ \
    if (_arg != this->name ) \
    { \
        this->name = _arg; \
    } \
}

#define CPP_GET_MACRO( name, type ) \
virtual type Get##name() { \
    return this->name; \
}

#define CPP_New(Var, Type)   Type *Var = new Type();

#define CPP_FREE(Object)   \
if(nullptr != Object) \
{ \
    delete Object;  \
    Object = nullptr; \
}

#endif // MACRODEFINED_HPP
