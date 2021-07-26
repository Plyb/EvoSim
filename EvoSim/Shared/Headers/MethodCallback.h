#ifndef METHOD_CALLBACK_H
#define METHOD_CALLBACK_H

template <typename T, typename R>
class MethodCallback {
private:
    T* object;
    R (*callback)(T*);

public:
    MethodCallback<T, R>(T* object, R (*callback)(T*)) : object(object), callback(callback) {}

    operator MethodCallback<void, R>() const {
        return MethodCallback<void, R>((void*)object, (R (*)(void*)) callback);
    }

    R operator()() {
       return callback(object);
    }
};

#endif // !METHOD_CALLBACK_H


