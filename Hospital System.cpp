
#include <iostream>
using namespace std;

const int max_specialization = 20;
const int max_queue = 5;

struct hospital_queue
{
	string names[max_queue];
	int status[max_queue];
	int length;
	int spec;

	hospital_queue()
	{
		length = 0;
	}
	hospital_queue(int _spec)
	{
		length = 0;
		spec = _spec;
	}

	bool add_end(string name, int st)
	{
		if (length == max_queue)
			return false;

		names[length] = name;
		status[length] = st;
		length++;

		return true;
	}

	bool add_front(string name, int st)
	{
		if (length == max_queue)
			return false;

		for (int i = length; i >= 1; i--)
		{
			names[i] = names[i - 1];
			status[i] = status[i - 1];
		}
		names[0] = name;
		status[0] = st;
		length++;

		return true;
	}

	void remove_front()
	{
		cout << names[0] << " please go with the dr" << "\n";
		for (int i = 0; i < length - 1; i++)
		{
			names[i] = names[i + 1];
			status[i] = status[i + 1];
		}
		length--;
	}

	void print_patients()
	{
		cout << "There are " << length << " patients in specialization " << spec << "\n";
		for (int i = 0; i < length; i++)
		{
			cout << names[i] << ((status[i] == 1) ? " urgent" : " regular") << "\n";
		}
	}




};

struct hospital_system
{
	hospital_queue queue[max_specialization + 1];

	hospital_system()
	{
		for (int sp = 0; sp < max_specialization + 1; sp++)
			queue[sp] = hospital_queue(sp);
	}

	void addPatients()
	{
		string name;
		int st;
		int spc;

		cout << "Enter specialization , name , status: ";
		cin >> spc >> name >> st;

		bool status;
		if (st == 1)
			status = queue[spc].add_front(name, st);
		else
			status = queue[spc].add_end(name, st);

		if (!status)
			cout << "Sorry we can't add more patients for this specialization" << "\n";
	}

	void Print()
	{
		cout << "********************************************" << "\n";
		for (int sp = 1; sp <= max_specialization; sp++)
		{
			if (queue[sp].length != 0)
				queue[sp].print_patients();
		}
	}

	void getNext()
	{
		int spc;
		cout << "Enter specialization: ";
		cin >> spc;
		if (queue[spc].length == 0)
		{
			cout << "No patients at the moment. Have rest, Dr" << "\n";
			return;
		}
		queue[spc].remove_front();
	}

	int menu()
	{
		cout << "\n";
		cout << "Enter your choices: " << "\n";
		cout << "1) Add new patients" << "\n";
		cout << "2) Print all patients" << "\n";
		cout << "3) Get next patient" << "\n";
		cout << "4) Exit" << "\n";

		int choice;
		cin >> choice;
		return choice;
	}

	void hospital_run()
	{
		while (true)
		{
			int choice = menu();

			if (choice == 1)
				addPatients();
			else if (choice == 2)
				Print();
			else if (choice == 3)
				getNext();
			else
				return;
		}
	}
};


int main()
{

	hospital_system h = hospital_system();
	h.hospital_run();

	return 0;
}

