#ifndef _SINGLETON_HPP
#define _SINGLETON_HPP
#include <mutex>
#include <memory>
template <class T>
class Singleton
{
private:
	Singleton(){}
	static void  init()
	{
		single = new T();
		std::atexit(destroy);
	}
	static T* single;
	static std::once_flag single_created;
public:
	static T* instance()
	{
		std::call_once(single_created,init);
		return  single;
	}
	static void destroy()
	{
		delete single;
		single = nullptr;
	}
};
template<class T> T* Singleton<T>::single = nullptr;
template<class T> std::once_flag Singleton<T>::single_created; 

#endif