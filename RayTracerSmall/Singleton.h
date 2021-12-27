#ifndef _SINGLETON_H_
#define _SINGLETON_H_

class singleton
{
public:
	static singleton& getInstance()
	{
		static singleton instance;
		return instance;
	}
	singleton() {};

	singleton(singleton const&) = delete;
	void operator=(singleton const&) = delete;

};

#endif

