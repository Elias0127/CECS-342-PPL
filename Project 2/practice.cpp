#include <iostream>
using namespace std;

class Date{
    private:
        int day, month, year;
    public:
        // Date(month = 1,  day = 1, year = 1970) {}
        Date(){
            month = 1;
            year = 1970;
            day = 1;
        }
        Date(int M, int D, int Y) : month(M), day(D), year(Y) {}
        
        void display(){
            cout << "Today is " << month << "/" << day << "/" << year << endl;
        }
        
        
        int g2j()
        {
            int JD;
            int I = year, K = month, J = day;
            JD= K-32075+1461*(I+4800+(J-14)/12)/4+367*(J-2-(J-14)/12*12)/12-3*((I+4900+(J-
            14)/12)/100)/4;
            return JD;
        }
        int operator-(Date& d) {
            return g2j() - d.g2j();
        }
                
};

int main(){
    Date today(9,19,2023);
    Date bday(7,4,1776);
    
    int JT = today.g2j();
    int JB = bday.g2j();
    
    int goldLife = today - bday;
    
    cout << "Today in Julian: " << JT << endl;
    cout << "Birthday in Julian: " << JB << endl;
    cout << "Gold Life: " << goldLife << " days." << endl;
}
