//This is an archimetic calulator

#include <iostream>
using namespace std;

//Functions
void decision(int, double);
double multiply(double);
double addition(double);
double division(double);
double subtraction(double);
void conditionChecker(char);

int main(){
    
    double number1, number2;
        int operation = 0;
        char condition;

    do{
        cout << "Enter number1 ~~ ";
        cin >> number1;

        decision(operation, number1);

        

        while (1){
            cout << "would  you like to use calulator again? (Y/N) ~~ ";
            cin >> condition; 
            conditionChecker(condition);
            if (condition == 'Y'){
                break;
            }
            if (condition == 'N'){
                break;
            }
        }
        
    } while(condition == 'Y');
    
    return 0;
}

void decision(int operation, double number1){
   while (1){
    cout << "choose operation " << endl << " 1. Addition    2. Subtractions     3. multiply     4. division " << endl;
    cin >> operation;

    if(operation == 1){
        addition(number1);
        break;
    }
    if(operation == 2){
    subtraction(number1);
        break;
    }
    if(operation == 3){
        multiply(number1);
        break;
    }
    if(operation == 4){
        division(number1);
        break;
    }
    else{
        cout << "Number is not a given operation. Try again" << endl;
    }
   }
}
double addition(double number1){
    double number2; 

    cout << "Enter number2 ~~ ";
    cin >> number2;
    
    double number3 = number1 + number2;
    cout << "New number is " << number3 << endl;

    if(number3 == 69){
            cout << "Nice! " << endl;
        }

    return number3;
}
double subtraction(double number1){
    double number2; 

    cout << "Enter number2 ~~ ";
    cin >> number2;
    
    double number3 = number1 - number2;
    cout << "New number is " << number3 << endl;

    if(number3 == 69){
            cout << "Nice! " << endl;
        }

    return number3;
}
double division(double number1){
    double number2; 

    cout << "Enter number2 ~~ ";
    cin >> number2;
    
    double number3 = number1 / number2;
    cout << "New number is " << number3 << endl;

    if(number3 == 69){
            cout << "Nice! " << endl;
        }

    return number3;
}
double multiply(double number1){
    double number2; 

    cout << "Enter number2 ~~ ";
    cin >> number2;
    
    double number3 = number1 * number2;
    cout << "New number is " << number3 << endl;

    if(number3 == 69){
            cout << "Nice! " << endl;
        }

    return number3;
}
void conditionChecker(char condition){
    if (condition == 'Y'){
    }
    else if (condition == 'N'){
    }
    else{
        cout << "Character chosen is not a given option try again " << endl;
    }
}