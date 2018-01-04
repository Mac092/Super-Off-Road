#ifndef SUBJECT_H
#define SUBJECT_H
#define _CRT_SECURE_NO_DEPRECATE

#include "Observer.h"
#include <vector>

class Observer;

class Subject
{
public:
	Subject() {};
	virtual ~Subject() {};
	void Subject::Attach(Observer* o)
	{
		_observers.push_back(o);
	}
	void Subject::Detach(Observer* o)
	{
		int count = _observers.size();
		int i;

		for (i = 0; i < count; i++) {
			if (_observers[i] == o)
				break;
		}
		if (i < count)
			_observers.erase(_observers.begin() + i);

	}

	void Subject::Notify()
	{
		int count = _observers.size();

		for (int i = 0; i < count; i++)
			(_observers[i])->Update(this);
	}


private:
	std::vector<Observer*> _observers;

};

#endif