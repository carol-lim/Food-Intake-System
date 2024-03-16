#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "User.h"
#include "Food.h"
#include "Diary.h"
#include "UseDiary.h"
#include "DiaryFood.h"
#include "Calculation.h"
#include "FoodManager.h"
#include "DiaryManager.h"
#include "DiaryFoodManager.h"

/// <summary>
/// The main function for Diary module
/// </summary>
/// <param name="user">Object of User</param>
/// <param name="goal">Object of Goal</param>
void UseDiary::useDiary(User* user, Goal* goal) {
	Diary* diary = new Diary();

	while (true) {
		while (true) {
			system("CLS");
			DiaryManager* dm = new DiaryManager();

			// Get current diary
			int status = dm->findCurrentDiary(user->user_id);
			if (status != 0) {
				dm->getCurrentDiary(user->user_id, diary);
			}
			else {
				dm->addNewDiary(diary, user);
			}

			// Get current date
			time_t t = time(0);
			tm* now = localtime(&t);

			end = false;
			cout << "-------------------------------------------------------" << endl;
			cout << "\t"<<user->name << "'s Diary of the Day ("<< (now->tm_mday) << "-" << (now->tm_mon) + 1 << "-" << (now->tm_year) + 1900 <<")" << endl;
			cout << "-------------------------------------------------------" << endl;
			
			// Display progress of daily intake and goal
			diary->displayProgress(goal);

			// Check existence of and display food in the diary
			bool hvFood = diary->displayDiaryFood();
			
			cout << "-------------------------------------------------------" << endl;
			cout << "---------------------- Your action --------------------" << endl;
			cout << "-------------------------------------------------------" << endl;
			
			// Option menu - when there is food in the diary
			if (hvFood) {
				cout << "1. Search Food / Manage Food in storage" << endl;
				cout << "2. Edit food in diary" << endl;
				cout << "3. Remove food in diary" << endl;
				cout << "0. Back" << endl;
				cout << endl;

				cout << "Please enter your choice: ";
				// User input and validate input
				if (!(cin >> menuOpt)) {
					cout << "Please enter number only." << endl << endl;
					system("pause");
					cout << endl;
				}
				else {
					// Validate input range
					validation = validateRange(menuOpt, 0, 3);
					if (validation) break;
					else cout << "Invalid option. Please enter valid option." << endl << endl;
				}
			}

			// Option menu - when there no food in the diary
			else {
				cout << "1. Search Food / Manage Food in storage" << endl;
				cout << "0. Back" << endl;
				cout << endl;

				cout << "Please enter your choice: ";
				// User input and validate input
				if (!(cin >> menuOpt)) {
					cout << "Please enter number only." << endl << endl;
					system("pause");
					cout << endl;
				}
				else {
					// Validate input range
					validation = validateRange(menuOpt, 0, 1);
					if (validation) break;
					else cout << "Invalid option. Please enter valid option." << endl << endl;
				}
			}
			cin.clear();
			cin.ignore(10, '\n');
		}

		// Invoke module correspond to option
		switch (menuOpt) {
		case 1:
			searchFood(diary, user->user_id);
			end = false;
			break;

		case 2:
			editDiaryFood(diary->getDiaryId());
			end = false;
			break;

		case 3:
			removeDiaryFood(diary->getDiaryId());
			end = false;
			break;

		case 0:
			end = true;
			break;
		}

		if (end) break;
	}
	return;
}

/// <summary>
/// Validate range of input
/// Reusable for option menu validation or data input to customized its maximum and minimum value 
/// </summary>
/// <typeparam name="T">Identifier for general type</typeparam>
/// <param name="input">User's input</param>
/// <param name="min">Minimum value</param>
/// <param name="max">Maximum value</param>
/// <returns></returns>
template <class T>
bool UseDiary::validateRange(T input, T min, T max) {
	if (input >= min && input <= max) return true;
	else return false;
}

/// <summary>
/// Edit food from the diary
/// 2 objects are instantiate for both old and new diary food details
/// because the diary accumulation also needs to be updated by 
/// removing the old one and adding the new one
/// </summary>
/// <param name="diary_id">Diary ID</param>
void UseDiary::editDiaryFood(int diary_id) {
	while (true) {
		end = false;
		int foodId;
		cout << endl;
		cout << "-------------------------------------------------------" << endl;
		cout << "---------------- Edit Food from Diary -----------------" << endl;
		cout << "-------------------------------------------------------" << endl;
		cout << "Please enter the food ID : #";
		// User input and validate input
		if (!(cin >> foodId)) {
			cout << "Please enter number only." << endl << endl;
			system("pause");
			cout << endl;
		}
		else {
			DiaryFoodManager* dfm = new DiaryFoodManager();
			// Check food existence in diary
			int status = dfm->checkDiaryFoodByDiaryId(diary_id, foodId);
			
			// The food exists in diary
			if (status != 0) {
				// Get the specific diary food from DB
				DiaryFood* df = dfm->getSingleDiaryFood(diary_id, foodId);
				cout << "#" << foodId << endl;
				cout << "Original Portion: " << df->getPortion() << endl;
				cout << "Calories\t: " << df->getDfKcal() << endl;
				cout << "Protein\t: " << df->getDfProtein() << endl;
				cout << "Carbs\t: " << df->getDfCarbs() << endl;
				cout << "Fats\t: " << df->getDfFats() << endl;
				cout << endl;

				// Instantiate new object for Diary Food updating
				DiaryFood* dfNew = new DiaryFood();
				dfNew->setDfKcal(df->getDfKcal());
				dfNew->setDfProtein(df->getDfProtein());
				dfNew->setDfCarbs(df->getDfCarbs());
				dfNew->setDfFats(df->getDfFats());

				// Input new portion
				double p = dfNew->enterPortion();
				dfNew->setPortion(p);

				// Re-calculate the diary food details with original food details
				FoodManager* fm = new FoodManager();
				Food* food = fm->searchFoodById(foodId);
				Calculation* calc = new Calculation();
				dfNew = calc->calculateDiaryFood(dfNew, food);

				// Update diary food into DB
				int statusEdit = dfm->updateDiaryFood(diary_id, foodId, dfNew);

				// Update diary intake accumulation
				DiaryManager* dm = new DiaryManager();
				int statusDiaryRem = dm->updateDiary(diary_id, df, "remove");
				int statusDiaryAdd = dm->updateDiary(diary_id, dfNew, "add");

				// Display message - success or fail 
				cout << "**********************************************" << endl;
				if (statusEdit == 1 && statusDiaryRem == 1 && statusDiaryAdd==1) {
					cout << "Edit food from diary successfully." << endl;
					end = true;
				}
				else if (statusEdit != 1) {
					cout << " Fail to edit food from diary." << endl << endl;
				}
				else if (statusDiaryRem != 1) {
					cout << " Fail to subtract food from diary." << endl << endl;
				}
				else if (statusDiaryAdd != 1) {
					cout << " Fail to update diary progress." << endl << endl;
				}
				cout << "**********************************************" << endl;
				system("pause");
			}

			// The food not exist in diary
			else {
				cout << "**********************************************" << endl;
				cout << " The food is not in diary. Please try again." << endl;
				cout << "**********************************************" << endl;
			}
		}
		cin.clear();
		cin.ignore(10, '\n');
		if (end == true) break;
	}
}

/// <summary>
/// Remove a food from diary
/// </summary>
/// <param name="diary_id">Diary ID</param>
void UseDiary::removeDiaryFood(int diary_id) {
	while (true) {
		end = false;
		int foodId;
		cout << endl;
		cout << "-------------------------------------------------------" << endl;
		cout << "---------------- Remove Food from Diary ---------------" << endl;
		cout << "-------------------------------------------------------" << endl;
		cout << "Please enter the food ID : #";
		// User input and validate input
		if (!(cin >> foodId)) {
			cout << "Please enter number only." << endl << endl;
			system("pause");
			cout << endl;
		}
		else {
			DiaryFoodManager* dfm = new DiaryFoodManager();
			// Check food existence in diary
			int status = dfm->checkDiaryFoodByDiaryId(diary_id, foodId);
			if (status != 0) {
				
				// Get the specific diary food from DB
				DiaryFood* df = dfm->getSingleDiaryFood(diary_id, foodId);

				// Remove the food from diary
				int statusRemove= dfm->removeDiaryFood(diary_id, foodId);

				// Update diary intake accumulation
				DiaryManager* dm = new DiaryManager();
				int statusUpDiary = dm->updateDiary(diary_id, df, "remove");

				// Display message - success or fail 
				cout << "**********************************************" << endl;
				if (statusRemove == 1 && statusUpDiary == 1) {
					cout << "Remove food from diary successfully." << endl;
					end = true;
				}
				else if (statusRemove != 1) {
					cout << " Fail to remove food from diary." << endl << endl;
				}
				else if (statusUpDiary != 1) {
					cout << " Fail to update diary progress." << endl << endl;
				}
				cout << "**********************************************" << endl;
			}

			// The food not exist in diary
			else {
				cout << "**********************************************" << endl;
				cout << " The food is not in diary. Please try again." << endl;
				cout << "**********************************************" << endl;
				end = true;

			}
			system("pause");
		}
		cin.clear();
		cin.ignore(10, '\n');
		if (end == true) break;
	}
}

/// <summary>
/// Search a food from the system database
/// </summary>
/// <param name="diary">Object of Diary</param>
/// <param name="user_id">User ID</param>
void UseDiary::searchFood(Diary* diary, int user_id) {
	while (true) {
		system("CLS");
		Food* food = new Food();
		FoodManager* fm = new FoodManager();
		end = false;

		cout << "-------------------------------------------------------" << endl;
		cout << "--------------------- Search Food ---------------------" << endl;
		cout << "-------------------------------------------------------" << endl;
		
		// User input - food name
		food->enterFoodName();
		
		// Invoke search food function - return a vector
		vector<Food*> searchedFood = fm->searchFoodByName(food->getFoodName());
	
		cout << "------ Search Result  ------" << endl;
		
		// Food found from system - vector is not empty
		if (!searchedFood.empty()) {
			// Display all the listed food and details
			food->displayFoodDetails(searchedFood);
			cout << endl;

			cout << "-------------------------------------------------------" << endl;
			cout << "---------------------- Your action --------------------" << endl;
			cout << "-------------------------------------------------------" << endl;
			cout << "1. Store new food" << endl;
			cout << "2. Update food details" << endl;
			cout << "3. Add food to diary" << endl;
			cout << "0. Back" << endl;
			cout << endl;
		}

		// No such food found from system - vector is empty
		else {
			// Invite user to store new food
			cout << "The food is not stored in the system. \n You may be the first to store it! " << endl;
			cout << endl;
			cout << "-------------------------------------------------------" << endl;
			cout << "---------------------- Your action --------------------" << endl;
			cout << "-------------------------------------------------------" << endl;
			cout << "1. Store new food" << endl;
			cout << "0. Back" << endl;
			cout << endl;
		}

		cout << "Please enter your choice: ";
		// User input and validate input
		if (!(cin >> menuOpt)) {
			cout << "Please enter number only." << endl << endl;
			system("pause");
			cout << endl;
		}
		else {
			// Validate input range
			validation = validateRange(menuOpt, 0, 3);
			if (validation) break;
			else cout << "Invalid option. Please enter valid option." << endl << endl;
		}
		cin.clear();
		cin.ignore(10, '\n');
	}

	// Invoke module correspond to option
	switch (menuOpt) {
	case 1:
		addNewFood(user_id);
		end = false;
		break;

	case 2:
		updateFood(user_id);
		end = false;
		break;

	case 3:
		addFoodToDiary(diary->getDiaryId());
		end = false;
		break;

	case 0:
		end = true;
		break;
	}
}

/// <summary>
/// Add food to diary
/// Can't be added if the selected food already in diary
/// 
/// User need to input the portion taken
/// System will calculate the portion of calories and macronutrient taken
/// and accumulate to diary progress
/// </summary>
/// <param name="diary_id">Diary ID</param>
void UseDiary::addFoodToDiary(int diary_id) {
	while (true) {
		end = false;
		int foodId;
		cout << endl;
		cout << "-------------------------------------------------------" << endl;
		cout << "------------------ Add Food to Diary ------------------" << endl;
		cout << "-------------------------------------------------------" << endl;
		cout << "Please enter the food ID : #";
		// User input and validate input
		if (!(cin >> foodId)) {
			cout << "Please enter number only." << endl << endl;
			system("pause");
			cout << endl;
		}
		else {
			// Get and display selected food details 
			Food* f = new Food();
			vector<Food*> foodVec = f->displayFoodVecById(foodId);
			// Food found from system - vector is not empty
			if (!foodVec.empty()) {

				for (int i = 0; i < foodVec.size(); i++) {
					f->setFoodId(foodVec[i]->getFoodId());
					f->setFoodName(foodVec[i]->getFoodName());
					f->setServingSize(foodVec[i]->getServingSize());
					f->setKcal(foodVec[i]->getKcal());
					f->setProtein(foodVec[i]->getProtein());
					f->setCarbs(foodVec[i]->getCarbs());
					f->setFats(foodVec[i]->getFats());
				}

				// Check if the selected food already in diary
				DiaryFoodManager* dfm = new DiaryFoodManager();
				int status = dfm->checkDiaryFoodByDiaryId(diary_id, foodId);
				// The selected food is not in diary
				if (status == 0) {
					// User input portion taken
					DiaryFood* df = new DiaryFood();
					double p = df->enterPortion();
					df->setPortion(p);

					// Calculation
					Calculation* calc = new Calculation();
					df = calc->calculateDiaryFood(df, f);

					// Add to diary food in DB
					DiaryFoodManager* dfm = new DiaryFoodManager();
					int statusAdd = dfm->addNewDiaryFood(diary_id, foodId, df);

					// Update diary intake accumulation
					DiaryManager* dm = new DiaryManager();
					int statusUpDiary = dm->updateDiary(diary_id, df, "add");

					// Display message - success or fail 
					cout << "**********************************************" << endl;
					if (statusAdd == 1 && statusUpDiary == 1) {
						cout << "Add food to diary successfully." << endl;
						end = true;
					}
					else if (statusAdd != 1) {
						cout << " Fail to add food to diary." << endl << endl;
					}
					else if (statusUpDiary != 1) {
						cout << " Fail to update diary progress." << endl << endl;
					}
					cout << "**********************************************" << endl;
				}

				// The selected food is in diary
				else {
					cout << "**********************************************" << endl;
					cout << " The food is in diary. \n Please edit from your diary." << endl;
					cout << "**********************************************" << endl;
					end = true;

				}
			}
			// No such food found from system - vector is empty
			else {
				cout << "**********************************************" << endl;
				cout << " The food is not stored in the system. \n You may be the first to store it! " << endl;
				cout << "**********************************************" << endl;
				end = true;
			}
			system("pause");
		}
		cin.clear();
		cin.ignore(10, '\n');
		if (end == true) break;
	}
}

/// <summary>
/// Store New Food to System database
/// Can't be added if the input food already in database
/// </summary>
/// <param name="user_id">User ID</param>
void UseDiary::addNewFood(int user_id){
	while (true) {
		Food* food = new Food();
		end = false;
		cout << endl;
		cout << "-------------------------------------------------------" << endl;
		cout << "-------------- Store New Food to System ---------------" << endl;
		cout << "-------------------------------------------------------" << endl;
		
		// User input food name
		food->enterFoodName();
		
		// Check if the food exists in system database
		FoodManager* fm = new FoodManager();
		int checkFood = fm->checkFoodByName(food->getFoodName());
		if (checkFood == 0) {
			// User input food details
			food->enterServingSize();
			food->enterKcal();
			food->enterProtein();
			food->enterCarbs();
			food->enterFats();

			// Set the user as the author
			food->setCreatedBy(user_id);

			// Add new food to DB
			int statusAdd = fm->addNewFood(food);

			// Display message - success or fail 
			cout << "**********************************************" << endl;
			if (statusAdd == 1) {
				cout << " New food is stored in the system successfully! \n Thank you!" << endl;
				end = true;
			}
			else {
				cout << " Failed to store new food \n Please try again." << endl;

			}
			cout << "**********************************************" << endl;
		}

		// The input food exists in system database
		else {
			cout << "**********************************************" << endl;
			cout << " The food is in the system. \n Please store another food or edit the details." << endl;
			cout << "**********************************************" << endl;
			end = true;
		}
		
		system("pause");
		cin.ignore(10, '\n');
		if (end == true) break;
	}
}

/// <summary>
/// Update food details to system database
/// </summary>
/// <param name="user_id">User ID</param>
void UseDiary::updateFood(int user_id){
	while (true) {
		end = false;
		int foodId;
		cout << endl;
		cout << "-------------------------------------------------------" << endl;
		cout << "----------------- Update Food Details -----------------" << endl;
		cout << "-------------------------------------------------------" << endl;
		cout << "Please enter the food ID : #";
		// User input and validate input
		if (!(cin >> foodId)) {
			cout << "Please enter number only." << endl << endl;
			system("pause");
			cout << endl;
		}
		else {
			Food* food = new Food();
			// Get selected food details 
			//food = food->displayFoodById(foodId);
			vector<Food*> foodVec = food->displayFoodVecById(foodId);
			// Food found from system - vector is not empty
			if (!foodVec.empty()) {

				for (int i = 0; i < foodVec.size(); i++) {
					food->setFoodId(foodVec[i]->getFoodId());
					food->setFoodName(foodVec[i]->getFoodName());
					food->setServingSize(foodVec[i]->getServingSize());
					food->setKcal(foodVec[i]->getKcal());
					food->setProtein(foodVec[i]->getProtein());
					food->setCarbs(foodVec[i]->getCarbs());
					food->setFats(foodVec[i]->getFats());
				}

				while (true) {
					cout << "------ Choose detail to edit ------" << endl;
					cout << "1. Serving size" << endl;
					cout << "2. Calories" << endl;
					cout << "3. Protein" << endl;
					cout << "4. Carbohydrates" << endl;
					cout << "5. Fats" << endl;
					cout << "6. Edit All" << endl;
					cout << "0. Back" << endl;
					cout << endl;
					cout << "Please enter your choice: ";
					// User input and validate input
					if (!(cin >> menuOpt)) {
						cout << "Please enter number only." << endl << endl;
						system("pause");
						cout << endl;
					}
					else {
						// Validate input range
						validation = validateRange(menuOpt, 0, 6);
						if (validation) break;
						else cout << "Invalid option. Please enter valid option." << endl << endl;
						system("pause");
					}
				}

				// Invoke module correspond to option
				switch (menuOpt) {
				case 1:
					food->enterServingSize();
					end = false;
					break;

				case 2:
					food->enterKcal();
					end = false;
					break;

				case 3:
					food->enterProtein();
					end = false;
					break;

				case 4:
					food->enterCarbs();
					end = false;
					break;

				case 5:
					food->enterFats();
					end = false;
					break;

				case 6:
					food->enterServingSize();
					food->enterKcal();
					food->enterProtein();
					food->enterCarbs();
					food->enterFats();
					end = false;
					break;

				case 0:
					end = true;
					break;
				}

				if (!end) {

					// Set user as person who updated the details
					food->setLastUpdatedBy(user_id);

					// Update food in database
					FoodManager* fm = new FoodManager();
					int statusUp = fm->updateFood(food);

					// Display message - success or fail 
					cout << "**********************************************" << endl;
					if (statusUp == 1) {
						cout << " The food is updated successfully! \n Thank you!" << endl;
					}
					else {
						cout << " Failed to update food \n Please try again." << endl;
					}
					cout << "**********************************************" << endl;
					end = true;
				}
			}
			// No such food found from system - vector is empty
			else {
				cout << "**********************************************" << endl;
				cout << " The food is not stored in the system. \n You may be the first to store it! " << endl;
				cout << "**********************************************" << endl;
				end = true;
			}
		}
		system("pause");
		cin.clear();
		cin.ignore(10, '\n');
		if (end == true) break;
	}
}