#include <iostream>
#include <string>
#include <cstring>
#include <cctype>

using namespace std;

bool validname(char* name) {
	if(*name == '\0') return false;
	for(char* i = name; *i != '\0'; i++)
		if(!isalpha(*i) && *i != ' ' && *i != '-' && *i != '\'')
			return false;
	return true;
}

int main() {
	char name[1024];
	int age;
	int phone;
	
	// Read user's name
	do {
		cout << "Enter your name: ";
		fgets(name, sizeof(name), stdin);
		name[strlen(name) - 1] = '\0';
	} while (!validname(name));
	
	// Read user's age
	char agebuf[4];
	fgets(agebuf, sizeof(agebuf), stdin);
	age = atoi(agebuf);

	// Read phone number
	char number[11];
	for(int i = 0; i < 10; i++) {
		char c = getchar();
		if(!isdigit(c)) {
			i--;
			continue;
		}
		if(c == '1' &&  i == 0) {
			i--;
			continue;
		}
		number[i] = c;
	}
	phone = atoi(number);
}

