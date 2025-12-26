
1. Program Overview
----------------------------------------
HealthMate is a console-based application that manages users, diet plans,
and workout plans using Object-Oriented Programming (OOP) concepts.
It reads three text files which are as follows userInfo.txt, dietPlans.txt, workoutPlans.txt.
and allows user's to view, compare, and update health data via a menu.

Main features:
- Calculate and compare BMI for multiple users
- Auto-generate meal plans based on calorie limits
- Estimate calories burned from workouts
- Save updated user data back to file on exit


2. File Structure
----------------------------------------
header.h        -> Class declarations
header.cpp      -> Class implementations
driver.cpp      -> Main menu / program entry
userInfo.txt    -> User data
dietPlans.txt   -> Diet items
workoutPlans.txt-> Workout items


3. Compilation Instructions
----------------------------------------
Open PowerShell or terminal in the folder you have downloaded all the files:
copy and paste this command without changing anything."compiling"

  copy this : g++ -std=c++17 -O2 -o HealthMate driver.cpp header.cpp

This will produce an executable file named “HealthMate.exe”.


4. Execution Instructions
----------------------------------------
Run the program by typing:

   .\HealthMate

Follow the on-screen menu to:
  1) List users
  2) Compare BMI
  3) Show diet or workout plans
  4) Generate auto meal plan
  5) Log workouts
  6) Update user and save



5. Enjoy
---------------------------------
Thank you for reading :)
