#include <iostream>
#include<fstream>
#include<iomanip>
using namespace std;
//q2 fuctions
void UpdateFile(int id[], char name[], char department[], double gpa[], const int maximum_size, const int records)
{
	ofstream filewriting("Records.txt");        // Open file for writing
	filewriting << records << endl;              // Write the number of records to the file
	for (int i = 0; i < records; i++)     // Loop through each record and write information to the file
	{
		filewriting << id[i] << ",";
		// Write the name to the file, excluding trailing spaces
		for (int j = 0; j < (maximum_size); j++)
			if (name[i * (maximum_size)+j] != ' ')filewriting << name[i * (maximum_size)+j];
		filewriting << ",";
		// Write the department to the file, excluding trailing spaces
		for (int j = 0; j < maximum_size; j++)
			if (department[i * maximum_size + j] != ' ') filewriting << department[i * maximum_size + j];
		// Write GPA to the file with 1 decimal place
		filewriting << "," << showpoint << fixed << setprecision(1) << gpa[i] << endl;
	}
	filewriting.close();
}
// Function to read student records from the file
void Input(int id[], char name[], char department[], double gpa[], const int maximum_size, const int records)
{
	ifstream filereading("Records.txt");     // Open file for reading
	if (filereading.fail())                  //Check
	{
		cout << "Could not open the file!";
		system("pause");
		exit(0);
	}

	int temp;
	filereading >> temp;                  // Read the number of records from the fil

	char chr;
	filereading.get(chr);               // Consume the newline character
	// Loop through each record and read information from the file
	for (int i = 0; i < records; i++)
	{
		// Read and extract ID from the file
		filereading.get(chr);
		while (chr != ',')
		{
			id[i] = id[i] * 10 + (int)(chr - '0');
			filereading.get(chr);
		}

		// Read and extract Name from the file
		filereading.get(chr);
		for (int j = 0; chr != ','; j++)
		{
			name[i * (maximum_size)+j] = chr;
			filereading.get(chr);
		}

		// Read and extract Department from the file
		filereading.get(chr);
		for (int j = 0; chr != ','; j++)
		{
			department[i * maximum_size + j] = chr;
			filereading.get(chr);
		}

		// Read and extract GPA from the file
		filereading.get(chr);
		gpa[i] = (double)(chr - '0');
		filereading.get(chr);
		filereading.get(chr);
		gpa[i] += (int)(chr - '0') / 10.0;

		filereading.get(chr);
	}
	filereading.close();
}
void Viewing_all_records(int id[], char name[], char department[], double gpa[], const int maximum_size, const int records)
{
	cout << left << "RECORD   ID      NAME                                            DEPARTMENT                    GPA\n";
	// Loop through each record and display information
	for (int i = 0; i < records; i++)
	{
		cout << setw(7) << i + 1 << setw(8) << id[i];
		// Display the name
		for (int j = 0; j < maximum_size; j++) cout << name[i * (maximum_size)+j];
		// Display the department
		for (int j = 0; j < maximum_size; j++) cout << department[i * maximum_size + j];
		// Display GPA with 1 decimal place
		cout << showpoint << setprecision(1) << fixed << gpa[i] << "\n\n";
	}
}
void Search_student(int id[], char name[], char department[], double gpa[], const int maximum_size, const int records)
{
	int F;
	bool validator;

	cout << "Which ID would you like to search? ";
	cin >> F;

	do            //validity chec
	{
		validator = true;      //initi true


		if (F < 10000 || F>99999) //Check for valid 5 digits
		{
			cout << "Please enter valid 5 digit Id ";
			cin >> F;
			validator = false;
		}
	} while (!validator);

	bool found = false;
	int i = 0;
	for (; i < records; i++) if (id[i] == F) { found = true; break; }
	if (!found) { cout << " Your given Id could not be found. \n\n"; return; }
	cout << left << "\nRECORD ID      NAME                      DEPARTMENT                    GPA\n";
	cout << setw(7) << i + 1 << setw(8) << id[i];
	// Display the name
	for (int j = 0; j < 15; j++) cout << name[i * maximum_size + j];
	// Display the department
	for (int j = 0; j < maximum_size; j++) cout << department[i * maximum_size + j];
	// Display GPA with 1 decimal place
	cout << showpoint << setprecision(1) << fixed << gpa[i] << "\n\n";
}
void Add_new_record(int id[], char name[], char department[], double gpa[], const int maxsize, int& records, int maxstudents)
{
	int A;
	bool validator, found;
	// Check if there is space for more students
	if (records == maxstudents) { cout << "There is no more space .\n\n";return; }

	cout << "\nEnter the following:\n\n";

	// ID input
	cout << "ID: ";
	cin >> A;
	do         //    Validity Check on Id
	{
		validator = true; //Initially True


		if (A < 10000 || A>99999) //Check for valid 5 digits
		{
			cout << "Please enter a valid 5 digit Id! (12345) ";
			cin >> A;
			validator = false;
			continue;
		}

		found = false;
		for (int j = 0; j < records; j++) if (id[j] == A)
		{
			found = true;
			break;
		}
		if (found)
		{
			cout << "Please enter a unique Id! This one already exists before. ";
			cin >> A;
			validator = false;
		}
	} while (!validator);
	id[records] = A;

	// Name input
	char temp[500] = { '\0' };
	cout << "Name: ";
	cin >> temp;
	// Check name length
	while (strlen(temp) > maxsize)
	{
		cout << "Please enter a name <= " << maxsize << " letters at most. Try again: ";
		cin >> temp;
	}
	// Copy name to the array
	for (int j = 0; j < strlen(temp); j++) name[records * (maxsize)+j] = temp[j];

	// Department input
	cout << "DEPARTMENT: ";
	cin >> temp;
	// Check department length
	while (strlen(temp) > maxsize)
	{
		cout << "Please enter a department <= " << maxsize << " letters at most. Try again: ";
		cin >> temp;
	}

	// Copy department to the array
	for (int j = 0; j < strlen(temp); j++) department[records * maxsize + j] = temp[j];

	// GPA input
	cout << "GPA: ";
	cin >> A;

	do          // Check 
	{
		validator = true;

		if (A < 0 || A>4) //Check for valid Gpa
		{
			cout << "Please enter a valid Gpa (0-4) ";
			cin >> A;
			validator = false;
			continue;
		}
		A = A * 10;
		if (A != A * 10) //Check for decimal nums
		{
			cout << "Please enter valid Gpa upto 1 d.p! (3.7) ";
			cin >> A;
			validator = false;
		}
	} while (!validator);
	gpa[records] = A;

	records++;
	UpdateFile(id, name, department, gpa, maxsize, records);
	cout << "\nField is Added!\n\n";
}
void Update_student_info(int id[], char name[], char department[], double gpa[], const int maximum_size, const int records)
{
	int F;
	bool validator;
	// Prompt the user to enter an ID for updating
	cout << "Which ID would you like to update? ";
	cin >> F;

	do
	{
		validator = true;


		if (F < 10000 || F>99999)     //C heck  5 digits
		{
			cout << "Please enter a valid 5 digit Id! (12345) ";
			cin >> F;
			validator = false;
		}
	} while (!validator);
	// Search for the student with the given ID
	bool found = false;
	int i = 0;
	for (; i < records; i++) if (id[i] == F) { found = true; break; }
	// Display an error message if the student is not found
	if (!found) { cout << "\nYour given Id not found. \n\n"; return; }

	int task;
	cout << "What attribute would you like to update?\n1. Id\n2. Name\n3. Department\n4. Gpa\n5. All\n";
	cin >> task;

	do // Check on User Input Action Number
	{
		validator = true; //Initial True

		if (task <= 0) //Check for negative nums
		{
			cout << "Please enter a valid positive number! From 1 to 5 ";
			cin >> task;
			validator = false;
			continue;
		}




		if (task < 1 || task>5) //Check for valid action number
		{
			cout << "Please enter a valid action number! From 1 to 5 ";
			cin >> task;
			validator = false;
		}
	} while (!validator);
	// Flags to determine which attributes to update
	bool cid, cname, cdepartment, cgpa;
	cid = cname = cdepartment = cgpa = false;
	if (task == 1)cid = true;
	else if (task == 2) cname = true;
	else if (task == 3) cdepartment = true;
	else if (task == 4) cgpa = true;
	else cid = cname = cdepartment = cgpa = true;
	// Prompt the user to enter the updated values
	cout << "\nEnter the updated values:\n\n";

	if (cid)
	{
		cout << "ID: ";             // Update ID
		cin >> F;

		do          // Check user Input Id
		{
			validator = true;
			//F = F;
			if (F != F) //Check for decimal nums
			{
				cout << "Please enter a valid Id! (34567) ";
				cin >> F;
				validator = false;
				continue;
			}

			if (F < 10000 || F>99999) //     Check for valid 5 digits
			{
				cout << "Please enter a valid 5 digit Id! (12345) ";
				cin >> F;
				validator = false;
				continue;
			}
			// Check for a unique ID
			found = false;
			for (int j = 0; j < records; j++)
				if (id[j] == F)
				{
					found = true;
					break;
				}
			if (found)
			{
				cout << "Please enter a unique Id! This one already exists. ";
				cin >> F;
				validator = false;
			}
		} while (!validator);

		id[i] = F;
	}
	if (cname)
	{        // Update Name
		char temp[500] = { '\0' };
		cout << "NAME: ";
		cin >> temp;
		while (strlen(temp) > maximum_size)
		{
			cout << "Please enter name <= " << maximum_size << " letters at most. Try again : ";
			cin >> temp;
		}
		for (int j = 0; j < strlen(temp); j++)
			name[i * (maximum_size)+j] = temp[j];        //Copy Characters from temp to name
		for (int j = strlen(temp); j < (maximum_size); j++)
			name[i * (maximum_size)+j] = ' ';              //Fill the Remaining Space with Spaces
	}
	if (cdepartment)
	{
		char temp[500] = { '\0' };
		cout << "DEPARTMENT: ";
		cin >> temp;
		while (strlen(temp) > maximum_size)
		{
			cout << "Please enter a department <= " << maximum_size << " letters at most. Try again: ";
			cin >> temp;
		}
		for (int j = 0; j < strlen(temp); j++)
			department[i * maximum_size + j] = temp[j];   //Copy Characters from temp to department  
		for (int j = strlen(temp); j < maximum_size; j++)
			department[i * maximum_size + j] = ' ';          //Fill the Remaining Space with Spaces
		if (cgpa)
		{
			cout << "GPA: ";
			cin >> F;

			do // Check on Input Gpa
			{
				validator = true;

				if (F < 0 || F>4)
				{
					cout << "Please enter a valid Gpa (0-4) ";
					cin >> F;
					validator = false;
					continue;
				}
				F = F * 10;
				if (F != F * 10) //Check for decimal nums
				{
					cout << "Please enter a valid Gpa upto 1 decimal place! (4.0) ";
					cin >> F;
					validator = false;
				}
			} while (!validator);
			gpa[i] = F;
		}
		UpdateFile(id, name, department, gpa, maximum_size, records);
		cout << "\nField Updated!\n\n";

	}
}

int main()
	


	//q2
	{		cout << ".......................Q2............................" << endl;

	const int maximumsize = 40, maximumstudents = 100;
	int id[maximumstudents] = { 0 };
	int records;
	char name[maximumstudents * (maximumsize)], department[maximumstudents * maximumsize];
	double gpa[maximumstudents] = { 0 };
	for (char& ch : name)
		ch = ' ';
	for (char& ch : department)
		ch = ' ';

	ifstream filename("Records.txt");
	if (filename.fail())
	{
		cout << "Could not open the file";
		system("pause");
		return 0;
	}
	filename >> records;
	filename.close();
	Input(id, name, department, gpa, maximumsize, records);

	int what_to_do;
	bool validator;
	cout << "What would you like to do?" << endl;
	cout << "1. View Records" << endl;
	cout << "2. Search Records" << endl;
	cout << "3.Add Records" << endl;
	cout << "4.Update Records" << endl;

	cin >> what_to_do;

	do // check userr input
	{
		validator = true;         //initial true

		if (what_to_do <= 0)
		{
			cout << "Please enter a valid positive number! From 1 to 5 ";
			cin >> what_to_do;
			validator = false;
			continue;
		}



		if (what_to_do < 1 || what_to_do>5)
		{
			cout << "Please enter a valid action number! From 1 to 5 ";
			cin >> what_to_do;
			validator = false;
		}
	} while (!validator);

	if (what_to_do == 1) Viewing_all_records(id, name, department, gpa, maximumsize, records); //    vieew records
	else if (what_to_do == 2)Search_student(id, name, department, gpa, maximumsize, records); //  searching records
	else if (what_to_do == 3)Add_new_record(id, name, department, gpa, maximumsize, records, maximumstudents); // adding records
	else if (what_to_do == 4)Update_student_info(id, name, department, gpa, maximumsize, records); //     updating recordd
	}