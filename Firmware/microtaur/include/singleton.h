#pragma once

template <typename T>
class Singleton 
{
    public: 
        static T& instance(){
            static T p_instance;
            return p_instance;
        }
        Singleton(const Singleton &) = delete;
        Singleton(Singleton&&) = delete;
        Singleton& operator=(const Singleton &) = delete;
        Singleton& operator=(Singleton &&) = delete;
    protected:
        Singleton(){};
        ~Singleton(){};

};
