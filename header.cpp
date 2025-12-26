#include "header.h"
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

// Person --safe default 
Person::Person(): name(""), age(0), gender('M') {}
//set all person field from arguments
Person::Person(const string& n, int a, char g): name(n), age(a), gender(g) {}

//handles cleanup 
Person::~Person() {}

const string& Person::getName() const { return name; }
int  Person::getAge() const { return age; }
char Person::getGender() const { return gender; }
void Person::print() const { cout << name << " (" << age << ", " << gender << ")"; }

// User
User::User(): Person(), weight(0.0), height(1.0), goal("maintain") {}
// passig name | age | gender to person; set weight | height | goal
User::User(const string& n, int a, char g, double w, double h, const string& g0): Person(n,a,g), weight(w), height(h), goal(g0) {}

//encapsulation 
double User::getWeight() const { return weight; }
double User::getHeight() const { return height; }
const string& User::getGoal() const { return goal; }

// validation -- only accept positive 
void User::setWeight(double w){ 
    if(w>0) weight=w; }

void User::setHeight(double h){ 
    if(h>0) height=h; }
void User::setGoal(const string& g1){ goal=g1; }

double User::bmi() const {
    if (height<=0) return 0.0;
    return weight/(height*height);
}

int User::minIntake() const {
    if (gender=='F' || gender=='f') 
        return 1200; else return 1500;
}

int User::burnCap() const {
    if (gender=='F' || gender=='f') 
        return 400; else return 500;
}
// print user with BMI and goal
void User::print() const {
    cout << fixed 
         << left
         << setw(12) << name << " | "
         << "Age: "    << right << setw(3) << setprecision(0) << age    << " | "
         << "Gender: " <<               gender                         << " | "
         << "W/H: "    << setprecision(1) << setw(5) << weight << "kg / "
         << setprecision(2) << setw(5) << height << "m"
         << " | BMI: " << setprecision(2) << setw(6) << bmi()
         << " | Goal: " << left << goal;
}
//overload -- compare users by BMI -- sorting and comparing 
bool User::operator<(const User& other) const { return bmi() < other.bmi(); }
double compareBMI(const User& a, const User& b){ return a.bmi() - b.bmi(); }

// Diet -- friend function in header.h campare 2 users 
DietItem DietItem::operator+(const DietItem& rhs) const {
    DietItem r;
    if (mealType == rhs.mealType) r.mealType = mealType; else r.mealType = "Mixed";
    r.food     = food + " + " + rhs.food;
    r.calories = calories + rhs.calories;
    return r;
}
// found and sum calories for breakfast | lunch | Dinner | snack 
DietPlan::DietPlan(): count(0) {}
bool DietPlan::add(const DietItem& it){ if(count>=MAX_DIET) return false; items[count++]=it; return true; }
int  DietPlan::size() const { return count; }
const DietItem& DietPlan::at(int i) const { return items[i]; }

int DietPlan::pickDay(int outIdx[4]) const {
    outIdx[0]=outIdx[1]=outIdx[2]=outIdx[3]=-1; // B,L,D,S
    for (int i=0;i<count;i++){
        const string& m = items[i].mealType;
        if (outIdx[0]<0 && (m=="Breakfast"  ||m=="breakfast")) outIdx[0]=i;
        else if (outIdx[1]<0 && (m=="Lunch" ||m=="lunch"))     outIdx[1]=i;
        else if (outIdx[2]<0 && (m=="Dinner"||m=="dinner"))    outIdx[2]=i;
        else if (outIdx[3]<0 && (m=="Snack" ||m=="snack"))     outIdx[3]=i;
    }
    int total=0;
    for(int k=0;k<4;k++) if(outIdx[k]>=0) total+=items[outIdx[k]].calories;
    return total;
}

//peint and preview of diet items
void DietPlan::printSome() const {
    cout << "Diet items (" << count << "):\n";
    cout << left
         << "  " << setw(4) << "Idx"
         << setw(12) << "Meal"
         << setw(32) << "Food"
         << right << setw(8) << "Kcal" << "\n";
    cout << "  " << string(4+12+32+8, '-') << "\n";

    for (int i=0;i<count;i++){
        cout << left
             << "  " << setw(4)  << i
             << setw(12) << items[i].mealType
             << setw(32) << items[i].food
             << right << setw(8) << items[i].calories << "\n";

        if (i>=10){ 
            cout << "  ... (" << (count-i-1) << " more)\n"; 
            break; 
        }
    }
}

// Workout
WorkoutPlan::WorkoutPlan(): count(0) {}
// add workout ite if space is available 
bool WorkoutPlan::add(const WorkoutItem& it){ 
    if(count>=MAX_WORK) return false; items[count++]=it; 
    return true; }

int  WorkoutPlan::size() const { return count; }
const WorkoutItem& WorkoutPlan::at(int i) const { return items[i]; }

// find exact name match; -1 if not found
int WorkoutPlan::findByName(const string& act) const {
    for (int i=0;i<count;i++) if (items[i].activity==act) return i;
    return -1;
}
//Eastimate total calories burned = kcalPerMin * minutes | but cap for user.burncap
int WorkoutPlan::estimateBurnCapped(const User& u, int idx, int minutes) const {
    if (idx<0 || idx>=count || minutes<=0) return 0;
    int burn = items[idx].kcalPerMin * minutes;
    int cap  = u.burnCap();
    if (burn > cap) burn = cap;
    return burn;
}
//print a preview of workout items 
void WorkoutPlan::printSome() const {
    cout << "Workout items (" << count << "):\n";
    cout << left
         << "  " << setw(4)  << "Idx"
         << setw(20) << "Activity"
         << setw(10) << "Intensity"
         << right << setw(12) << "Kcal/min" << "\n";
    cout << "  " << string(4+20+10+12, '-') << "\n";

    for (int i=0;i<count;i++){
        cout << left
             << "  " << setw(4)  << i
             << setw(20) << items[i].activity
             << setw(10) << items[i].intensity
             << right << setw(12) << items[i].kcalPerMin << "\n";

        if (i>=10){ 
            cout << "  ... (" << (count-i-1) << " more)\n"; 
            break; 
        }
    }
}

// HealthMate- recieve 3 from main and stores them 
//usercount starts at 0; arrays are empty until loadAll() runs.
HealthMate::HealthMate(const string& uf, const string& df, const string& wf)
: userCount(0), userFile(uf), dietFile(df), workFile(wf) {}

bool HealthMate::loadAll(){
    return loadUsers(userFile) && loadDiet(dietFile) && loadWorkout(workFile);
}

//Read User from text 
bool HealthMate::loadUsers(const string& path){
    ifstream fin(path.c_str());
    if(!fin){ 
        cerr<<"Open fail "<<path<<"\n"; 
        return false; }
    userCount=0;
    string nm, goal; int age; char gen; double w,h;
    while(fin && userCount<MAX_USERS){
        fin >> nm >> age >> gen >> w >> h >> goal;
        if(!fin) break;
        users[userCount++] = User(nm,age,gen,w,h,goal);
    }
    fin.close(); return true;
}

//Read diet items from file 
bool HealthMate::loadDiet(const string& path){
    ifstream fin(path.c_str());
    if(!fin){ cerr<<"Open fail "<<path<<"\n"; return false; }
    string line;
    while(getline(fin,line)){
        if(line.empty()) continue; // skip blank lines
        stringstream ss(line);
        string meal, food, calStr;
        if(!getline(ss,meal,',')) continue; // parse MealType
        if(!getline(ss,food,',')) continue; //parse Food
        if(!getline(ss,calStr,',')) continue; //parse calories as string
        DietItem it; it.mealType=meal; it.food=food; it.calories=stoi(calStr);
        diet.add(it);// push into array if got space
    }
    fin.close(); return true;
}
//Read workout items
bool HealthMate::loadWorkout(const string& path){
    ifstream fin(path.c_str());
    if(!fin){ cerr<<"Open fail "<<path<<"\n"; return false; }
    string line;
    while(getline(fin,line)){
        if(line.empty()) continue;
        stringstream ss(line);
        string act, iStr, kStr;
        if(!getline(ss,act,',')) continue; //parse activity
        if(!getline(ss,iStr,',')) continue; //parse Intensity
        if(!getline(ss,kStr,',')) continue; //parse Kcal/min
        WorkoutItem w; w.activity=act; w.intensity=stoi(iStr); w.kcalPerMin=stoi(kStr);
        workout.add(w); //push into array if space
    }
    fin.close(); return true;
}

//write user back to file 
bool HealthMate::saveUsers(const string& path) const {
    ofstream fout(path.c_str());
    if(!fout){ cerr<<"Save fail "<<path<<"\n"; return false; }
    for(int i=0;i<userCount;i++){
        const User& u=users[i];
        fout<<u.getName()<<" "<<u.getAge()<<" "<<u.getGender()<<" "
            <<fixed<<setprecision(1)<<u.getWeight()<<" "
            <<fixed<<setprecision(2)<<u.getHeight()<<" "
            <<u.getGoal()<<"\n";
    }
    fout.close(); return true;
}

// Menu ops - write users with indexs so user can pick index in menu
void HealthMate::listUsers() const {
    cout << "Users ("<<userCount<<"):\n";
    cout << left << "  " << setw(4) << "Idx" << "User\n";
    cout << "  " << string(4 + 4 + 60, '-') << "\n"; 

    for(int i=0;i<userCount;i++){ 
        cout << left << "  " << setw(4) << i; 
        users[i].print(); 
        cout << "\n"; 
    }
}

 // Compare BMI of two users by index; uses friend compareBMI() function.
void HealthMate::compareTwoBMI(int i, int j) const {
    if(i<0||i>=userCount||j<0||j>=userCount){ 
        cout<<"Bad index.\n"; 
        return; 
    }
    const User& a=users[i]; 
    const User& b=users[j];

    cout << left
         << setw(10) << "User"
         << setw(10) << "BMI" << "\n";
    cout << string(20, '-') << "\n";

    cout << left << setw(10) << a.getName()
         << right << setw(10) << fixed << setprecision(2) << a.bmi() << "\n";

    cout << left << setw(10) << b.getName()
         << right << setw(10) << fixed << setprecision(2) << b.bmi() << "\n";

    double d=compareBMI(a,b);
    if(d==0)      cout<<"Same BMI.\n";
    else if(d<0)  cout<<a.getName()<<" LOWER than "<<b.getName()<<"\n";
    else          cout<<a.getName()<<" HIGHER than "<<b.getName()<<"\n";
}

// Show a short list of diet items (for user to see what's loaded).
void HealthMate::showDiet() const { diet.printSome(); }
// Show a short list of workout items
void HealthMate::showWorkout() const { workout.printSome(); }

// Auto-pick the first Breakfast/Lunch/Dinner/Snack for the selected user and advise.
void HealthMate::autoMealForUser(int ui) const {
    if(ui<0||ui>=userCount){ cout<<"Bad user.\n"; return; }
    const User& u=users[ui];

    cout<<"Auto meal plan for "; 
    u.print(); 
    cout<<"\n";

    int picks[4]; 
    int total=diet.pickDay(picks);
    const char* tag[4]={"Breakfast","Lunch","Dinner","Snack"};

    // header
    cout << left
         << "  " << setw(12) << "Meal"
         << setw(32) << "Food"
         << right << setw(8) << "Kcal" << "\n";
    cout << "  " << string(12+32+8, '-') << "\n";

    for(int k=0;k<4;k++) if(picks[k]>=0){
        const DietItem& it=diet.at(picks[k]);
        cout << left
             << "  " << setw(12) << tag[k]
             << setw(32) << it.food
             << right << setw(8)  << it.calories << "\n";
    }

    cout << left << "  " << setw(44) << "Total"
         << right << setw(8) << total << "\n";

    cout<<"  Safe minimum: "<<u.minIntake()<<" kcal\n";
    if(total<u.minIntake()) 
        cout<<"  Advice: add snack / bigger portions.\n";
    else if(total>u.minIntake()+600) 
        cout<<"  Advice: choose lighter options.\n";
    else 
        cout<<"  Looks okay.\n";
}

// Estimate calories burned for an activity and minutes, capped by gender rule.
void HealthMate::doWorkoutForUser(int ui, const string& act, int minutes) const {
    if(ui<0||ui>=userCount){
         cout<<"You sure about this ? Try Again.\n"; return; 
        }

    int idx = workout.findByName(act);
    if(idx<0){ 
        cout<<"Activity not found.\n"; 
        return; }

    int burned = workout.estimateBurnCapped(users[ui], idx, minutes);
    cout<<"Workout: "<<act<<" for "<<minutes<<" min\n";
    cout<<"Calories burned (capped): "<<burned<<" kcal (cap "<<users[ui].burnCap()<<")\n";
}

// Update weight/height/goal for a user
void HealthMate::updateUser(int ui, double w, double h, const string& g){
    if(ui<0||ui>=userCount){ 
        cout<<"Bad user.\n"; return; 
    }
    if(w>0) users[ui].setWeight(w);
    if(h>0) users[ui].setHeight(h);
    if(!g.empty()) users[ui].setGoal(g);
    cout<<"Updated: "; users[ui].print(); cout<<"\n";
}
