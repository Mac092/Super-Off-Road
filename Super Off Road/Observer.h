#ifndef OBSERVER_H
#define OBSERVER_H
#define _CRT_SECURE_NO_DEPRECATE

class Subject;

class Observer
{
public:
	Observer() {};
	~Observer() {};
	virtual void Update(Subject* theChangeSubject) = 0;
};




#endif


