#include <iostream>
#include <vector>
using namespace std;

struct Person {
	string name;
	int age;
};

int main()
{
	// vector of Persons Pointers
	vector<Person*> v1;
	Person* p1 = new Person;
	p1->name = "Mohamed";
	p1->age = 23;

	v1.push_back(p1);
	
	for(int i=0; i < v1.size(); i++){
		Person* p = v1[i];
		cout << p->name << endl;
	}


	return 0;
}
