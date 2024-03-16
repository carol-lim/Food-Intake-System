#pragma once
#include "Diary.h"
#include "User.h"
#include "DiaryFood.h"

class DiaryManager {
public:
	int addNewDiary(Diary* diary, User* user);
	int updateDiary(int diary_id, DiaryFood* df, string action);
	void getCurrentDiary(int user_id, Diary* diary);
	int findCurrentDiary(int user_id);
};
