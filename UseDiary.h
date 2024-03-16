#pragma once

#include <string>
using namespace std;
#include "Diary.h"
#include "DiaryFood.h"
#include "Food.h"

class UseDiary{
private:
	bool validation, end;
	int menuOpt;
public:
	void useDiary(User* user, Goal* goal);

	template <class T>
	bool validateRange(T input, T min, T max);
	
	void searchFood(Diary* diary, int user_id);
	void editDiaryFood(int diary_id);
	void removeDiaryFood(int diary_id);
	void addNewFood(int user_id);
	void updateFood(int user_id);
	void addFoodToDiary(int diary_id);
};
