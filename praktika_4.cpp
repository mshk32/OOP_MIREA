#include <iostream>

using namespace std;

class BaseString
{
protected:
	char* p; int len; int capacity;
public:
	BaseString(int Capacity = 256)
	{
		cout << "\nBase Constructor 0\n";
		capacity = Capacity;
		p = new char[capacity];
		len = 0;
	}

	BaseString(char* ptr)
	{
		cout << "\nBase Constructor 1\n";
		len = strlen(ptr) + 1;
		capacity = 256;
		p = new char[capacity];
		for (int i = 0; i < len; i++)
		{
			p[i] = ptr[i];
		}
		p[len] = '\0';
	}

	BaseString(const char* ptr)
	{
		cout << "\nBase Constructor 2\n";
		int i = 0;
		while (ptr[i] != '\0')
			i++;
		len = i;
		capacity = len + 1 > 256 ? len + 1 : 256;
		p = new char[capacity];
		for (i = 0; ptr[i] != '\0'; i++)
			p[i] = ptr[i];

		p[len] = '\0';
	}

	BaseString(BaseString& s)
	{
		cout << "\nBase Copy Constructor\n";
		len = s.Length();
		p = new char[s.capacity];
		capacity = s.capacity;
		for (int i = 0; i < s.Length() - 1; i++)
		{
			p[i] = s[i];
		}
		p[len - 1] = '\0';
	}

	~BaseString()
	{
		cout << "\nBase Destructor\n";
		if (p != NULL)
			delete[] p;
		len = 0;
	}
	int Length() { return len; }
	int Capacity() { return capacity; }
	//char* get() {return p;}
	char& operator[](int i) { return p[i]; }
	BaseString& operator=(BaseString& s)
	{
		cout << "\nBase Operator = \n";
		len = s.Length();
		p = new char[s.capacity];
		capacity = s.capacity;
		for (int i = 0; i < s.Length(); i++)
		{
			p[i] = s[i];
		}
		//strcpy(p, s.get());
		p[len - 1] = '\0';
		return *this;
	}
	
	virtual void print()
	{
		cout << "\n";
		int i = 0;
		while (p[i] != '\0') { cout << p[i]; i++; }
	}

};

class String : public BaseString
{
public:
	String(int Capacity) : BaseString(Capacity) {}
	String(char* s) : BaseString(s) {}
	String(const char* s) : BaseString(s) {}
	String(String& s) : BaseString(s) {}
	~String()
	{
		cout << "\nBase Destructor\n";
		if (p != NULL)
			delete[] p;
		len = 0;
	}

	String& operator=(String& s)
	{
		cout << "\nBase Operator = \n";
		len = s.Length();
		p = new char[s.capacity];
		capacity = s.capacity;
		for (int i = 0; i < s.Length(); i++)
		{
			p[i] = s[i];
		}
		//strcpy(p, s.get());
		p[len - 1] = '\0';
		return *this;
	}
	
	bool is_palindrom()
	{
		char* start = p;
		char* end = p + len - 1;
		while (start < end) {
			if (*start != *end)
				return false;
			start++;
			end--;
		}
		return true;
	}
};
int main()
{
	String test0(50);
	char* ptr = new char[10];
	String test1(ptr);
	String test2("hello");
	String testcopy(test2);

	String s1("Obviously not a palindrom");
	String s2("madam");
	String s3("racecar");
	String s4("redder");

	cout << "is s1 string a palindrom? - " << (s1.is_palindrom() ? "Yes" : "No") << "\n";
	cout << "is s2 string a palindrom? - " << (s2.is_palindrom() ? "Yes" : "No") << "\n";
	cout << "is s3 string a palindrom? - " << (s3.is_palindrom() ? "Yes" : "No") << "\n";
	cout << "is s4 string a palindrom? - " << (s4.is_palindrom() ? "Yes" : "No") << "\n";


	return 0;
};
