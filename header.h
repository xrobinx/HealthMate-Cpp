#ifndef HEALTHMATE_HEADER_H
#define HEALTHMATE_HEADER_H

#include <iostream>
#include <string>
using namespace std;


const int MAX_USERS = 50;
const int MAX_DIET  = 50;
const int MAX_WORK  = 50;

//  Person -> User Inheritance) 
class Person {
protected:
    string name; int age; char gender; // 'M' or 'F'
public:
    Person();
    Person(const string& n, int a, char g);
    virtual ~Person();
    const string& getName() const; int getAge() const; char getGender() const;
    virtual void print() const;
};

class User : public Person {
private:
    double weight;  // kg
    double height;  // m
    string goal;    // "lose" | "maintain" | "gain"
public:
    User();
    User(const string& n, int a, char g, double w, double h, const string& g0);

    double getWeight() const; double getHeight() const; const string& getGoal() const;

    void setWeight(double w); void setHeight(double h); void setGoal(const string& g1);

    double bmi() const;               // weight / (height*height)
    int    minIntake() const;         // F>=1200, M>=1500
    int    burnCap() const;           // F<=400,  M<=500
    void   print() const override;
    bool   operator<(const User& other) const; // compare BMI
    friend double compareBMI(const User& a, const User& b);
};


double compareBMI(const User& a, const User& b);

// Diet 
struct DietItem {
    string mealType;  // Breakfast | Lunch | Dinner | Snack
    string food;
    int    calories;
    // operator+ (operator overloading)
    DietItem operator+(const DietItem& rhs) const;
};

class DietPlan {
private:
    DietItem items[MAX_DIET];
    int count;
public:
    DietPlan();
    bool add(const DietItem& it);
    int  size() const;
    const DietItem& at(int i) const;

    // Pick first Breakfast /Lunch /Dinner /Snack if present; returns total kcal
    int pickDay(int outIdx[4]) const;
    void printSome() const;
};

// Workout
struct WorkoutItem {
    string activity;
    int    intensity;    // 1..4
    int    kcalPerMin;
};

class WorkoutPlan {
private:
    WorkoutItem items[MAX_WORK];
    int count;
public:
    WorkoutPlan();
    bool add(const WorkoutItem& it);
    int  size() const; 
    const WorkoutItem& at(int i) const;
    int  findByName(const string& act) const;         // exact match
    int  estimateBurnCapped(const User& u, int idx, int minutes) const;
    void printSome() const;
};

// HealthMate (Composition) 
class HealthMate {
private:
    User users[MAX_USERS]; int userCount;
    DietPlan diet;
    WorkoutPlan workout;
    string userFile, dietFile, workFile;

public:
    // userfile --diet file --- workout file
    HealthMate(const string& uf, const string& df, const string& wf);

    bool loadAll();
    bool loadUsers(const string& path);
    bool loadDiet(const string& path);
    bool loadWorkout(const string& path);

    bool saveUsers(const string& path) const;

    // Menu actions
    void listUsers() const;
    void compareTwoBMI(int i, int j) const;
    void showDiet() const;
    void showWorkout() const;
    void autoMealForUser(int ui) const;
    void doWorkoutForUser(int ui, const string& act, int minutes) const;
    void updateUser(int ui, double w, double h, const string& g);
};

#endif
