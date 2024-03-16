#pragma once
#include "BodyDetails.h"

class User{
public:
	string name, gender, password, email;
	int user_id, yob;
	bool validation;

	User();
	~User();

	/* Methods for prompting user inputs*/
	void enterName();
	void enterGender();
	void enterYob(BodyDetails* bd);
	void enterEmail();
	void enterPassword();

	/* Methods for validations of inputs*/
	bool validateEmail(string input);
	bool validateGender(string input);
	bool validateYob(int input);
	template <class T>
	bool validateRange(T input, T min, T max);
	bool validatePswd(string& input);
};

