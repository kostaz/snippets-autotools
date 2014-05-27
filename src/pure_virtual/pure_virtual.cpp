#include <iostream>

using namespace std;

class B
{
public:
	virtual void foo() = 0;
};

class C : public B
{
public:
	virtual void foo()
	{
		cout << __func__ << ": " << __LINE__ << endl;
	}
};

int main()
{
	C c;
	B& b = c;

	c.foo();
	b.foo();

	return 0;
}

