#pragma once
#include <ctime>
#include <string>
using namespace std;

class BodyDetails{
private:
	int  bd_id, tdee = 0, age, actLvlOpt ;
	double height = 0, weight = 0;
	string act_level, date;
	bool validation;
public:
	BodyDetails();
	~BodyDetails();

	// Validation
	template <class T>
	bool validateRange(T input, T min, T max);
	
	// Input and validation
	void enterHeight();
	void enterWeight();
	void enterActLvl();
	
	// Function
	void weightGraph(int user_id);
	string chooseActLvl(int num);

	// setters
	void setBdId(int bd_id);
	void setTdee(int tdee);
	void setAge(int age);
	void setHeight(double height);
	void setWeight(double weight);
	void setActLvl(string act_level);
	void setDate(string date);
	
	// getters
	int getTdee();
	int getAge();
	double getHeight();
	double getWeight();
	string getActLvl();
	string getDate();
};