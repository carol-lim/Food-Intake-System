#pragma once
#include "DiaryFood.h"
#include "User.h"
#include "Diary.h"
#include "Food.h"

class DiaryFoodManager {
public:
	int addNewDiaryFood(int diary_id, int food_id, DiaryFood* df);
	int updateDiaryFood(int diary_id, int food_id, DiaryFood* df);
	int removeDiaryFood(int diary_id, int food_id);
	int countDiaryFoodByDiaryId(int diary_id);
	vector<DiaryFood*> getCurrentDiaryFood(int diary_id);
	DiaryFood* getSingleDiaryFood(int diary_id, int food_id);
	int checkDiaryFoodByDiaryId(int diary_id, int food_id);
};
