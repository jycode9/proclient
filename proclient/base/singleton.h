#ifndef SINGLETON_H
#define SINGLETON_H

#include <iostream>

template <typename T>
class Singleton{
protected:
    Singleton(){

    }
    ~Singleton(){

    }

private:
    Singleton(const Singleton&)=delete;
    Singleton& operator=(const Singleton&)=delete;
    static T* m_singleton;

public:
    static T* getInstance(){
        if(m_singleton==nullptr){
            m_singleton=new T();
        }
        return m_singleton;
    }
};

template <typename T>
T* Singleton<T>::m_singleton=nullptr;

#endif // SINGLETON_H
