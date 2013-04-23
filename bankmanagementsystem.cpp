/*
BANK MANAGEMENT SYSTEM APPLICATION
Original Author:   Abu-Bakar Bah
Date:              4/21/2013
Program Objective: This application serves as a banking system in which users
                   can create and maintain as many accounts as they wish. Some 
                   of the functions of this program include: creating a new 
                   account, depositing and withdrawing funds and modifying 
                   accounts. 
*/

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "account.h" //class header file

using namespace std;

//START OF PROGRAM
int main()
{
    accountHolder customer; //create a new account holder class
    char userOption1, userOption2, answer1, answer2;
    
    //intro
    cout << "================================================================================\n";
    cout << setw(53) << "BANK MANAGEMENT SYSTEM\n\n\n";
    cout << setw(52) << "DEVELOPED BY: Your name here";
    cout << "\n\n================================================================================\n";
    cout << "Press Enter to continue...";
    
    if (cin.get() == '\n') {
       system("CLS");
       
       do {
           system("CLS");
           //top menu
           cout << setw(22) << "Main Menu\n\n";
           cout << setw(26) << "1. New Account\n";
           cout << setw(31) << "2. Existing Account\n";
           cout << setw(28) << "3. Close Account\n";
           cout << setw(32) << "4. Modify an Account\n";
           cout << setw(20) << "5. Exit\n\n";
           cout << setw(35) << "Select an option (1-5): ";
           cin >> userOption1;
           
           if (toupper(userOption1) == '1') {
              system("CLS");
              customer.entNewAccount(); 
              
              cout << setw(42) << "Do you want to do something else (Y/N)? ";
              cin >> answer1;
           }
           else if (toupper(userOption1) == '2') {
                do {
                   system("CLS"); 
                   //sub menu for existing users only
                   cout << setw(33) << "Modify Existing Account\n\n";
                   cout << setw(26) << "1. Deposit Amount\n";
                   cout << setw(27) << "2. Withdraw Amount\n";
                   cout << setw(24) << "3. View Balance\n";
                   cout << setw(20) << "4. Go Back\n\n";
                   cout << setw(32) << "Select an option (1-4): ";
                   cin >> userOption2;
                   
                   if (toupper(userOption2) == '1' || toupper(userOption2) == '2' || toupper(userOption2) == '3') {
                        system("CLS");
                        cout << "============================ACCOUNT TRANSACTION FORM============================\n"; 
                        cout << setw(29) << "Enter your account number: ";
                        
                        if (customer.checkAccountNumber()) { //first check if account number is valid/correct 
                           cout << "\n" << "  Enter the pin number: ";
                           if (customer.checkAccountPin()) { //then check if pin number is valid for account                     
                                cout << "\n  -----ACCOUNT STATUS-----\n";
                                cout << "\n  Account No. :    " << customer.getAccountNumber();
                                cout << "\n  Pin No. :        " << customer.getPinNumber();
                                cout << "\n  Account Holder:  " << customer.getAccountHolder();
                                cout << "\n  Account Type:    " << customer.getAccountType();
                                cout << "\n  Account Balance: " << customer.getAccountBalance();
                                if (toupper(userOption2) == '1') {
                                   cout << "\n\n  The amount to deposit: ";
                                   customer.depositAmount();
                                   cout << "\n  Record Updated.";
                                }
                                else if (toupper(userOption2) == '2') {
                                    cout << "\n\n  The amount to withdraw: ";
                                    if (customer.withdrawAmount()) 
                                       cout << "\n  Record Updated.";
                                    else
                                        cout << "\n  Cannot withdraw, balance is too low.";  
                                }
                                else if (toupper(userOption2) == '4') {
                                     break; //exit loop
                                } 
                           }
                        }
                        
                        cout << "\n\n" << setw(32) << "Do another transaction (Y/N)? ";
                        cin >> answer2;                                                                                     
                   }
                   
                   
                } while(toupper(answer2) == 'Y');
           }
           else if (toupper(userOption1) == '3') {
                system("CLS");
                cout << "==================================CLOSE ACCOUNT=================================\n";
                customer.closeAccount();
                
                cout << "\n\n" << setw(32) << "Do another transaction (Y/N)? ";
                cin >> answer1;
           }
           else if (toupper(userOption1) == '4') {
                system("CLS");
                cout << "==================================MODIFY ACCOUNT================================\n";
                customer.modifyAccount();
                
                cout << "\n\n" << setw(32) << "Do another transaction (Y/N)? ";
                cin >> answer1;
           }
           else if (toupper(userOption1) == '5') {
                exit(0);
           }
       } while (toupper(answer1) == 'Y' && toupper(answer2) != 'Y');
    }
    else 
        cout << "I meant ONLY the Enter key... Oh well."; //message for slow users.....
    
    cin.get();
    cin.ignore();
    return 0; 
    //END OF PROGRAM  
}
