#include "header.h"
#include <limits>
using namespace std;

static void pauseLine(){
    cout << "\nPress ENTER to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main(){
    ios::sync_with_stdio(false);

    HealthMate app("userInfo.txt","dietPlans.txt","workoutPlans.txt");
    if(!app.loadAll()){
        cerr<<"Failed to load input files.\n";
        return 1;
    }

    while(true){
        cout<<"\n=== My HealthMate ===\n"
            <<"1) List users\n"
            <<"2) Compare BMI\n"
            <<"3) Diet preview\n"
            <<"4) Workout preview\n"
            <<"5) Auto meal plan (by user index)\n"
            <<"6) Log workout (user, activity, minutes)\n"
            <<"7) Update user & Save & Exit\n"
            <<"Select: ";
        int ch; if(!(cin>>ch)) return 0;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if(ch==1){
            app.listUsers(); pauseLine();
        } else if(ch==2){
            int a,b; cout<<"Index A: ";cin>>a; cout<<"Index B: ";cin>>b;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            app.compareTwoBMI(a,b); pauseLine();
        } else if(ch==3){
            app.showDiet(); pauseLine();
        } else if(ch==4){
            app.showWorkout(); pauseLine();
        } else if(ch==5){
            int u; cout<<"User index: ";cin>>u;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            app.autoMealForUser(u); pauseLine();
        } else if(ch==6){
            int u, m; string act;
            cout<<"User index: ";cin>>u; cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"Activity (exact name): "; getline(cin,act);
            cout<<"Minutes: "; cin>>m; cin.ignore(numeric_limits<streamsize>::max(), '\n');
            app.doWorkoutForUser(u, act, m); pauseLine();
        } else if(ch==7){
            int u; double w,h; string g;
            cout<<"User index: ";cin>>u;
            cout<<"New weight (>0 to change): ";cin>>w;
            cout<<"New height (>0 to change): ";cin>>h;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"New goal (blank keep): "; getline(cin,g);

            app.updateUser(u,w,h,g);
            if(app.saveUsers("userInfo.txt")) cout<<"Saved to userInfo.txt\n";
            cout<<"Bye!\n"; break;
        } else {
            cout<<"Invalid.\n";
        }
    }
    return 0;
}
