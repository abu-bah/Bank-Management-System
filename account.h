#include <sstream>
#include <fstream>

#ifndef _NODES
#define _NODES

using namespace std;

ofstream accountsList("accountslist.txt");

//*************************************************************//
//                   CLASSES USED IN PROJECT                   //
//*************************************************************//

//this will be used as the superclass/main class where the data will be stored in a LINKED LIST
class bankAccount { 
      public:
             string name, tempName;
             char accountType, tempAccountType;
             int pin, accountNumber, tempAccountNumber, tempAccountPin;          
             double initial, tempInitial, balance, tempBalance, tempAmount;
             typedef bankAccount* nodePtr;
             
             nodePtr link; //next node
             
             nodePtr headPtr;
             nodePtr currPtr;
             nodePtr tempPtr;
             //CLASS ENDS HERE
};

//this will be used to hold the methods that will access and/or modify the data. It inherits from the "bankAccount" superclass as public
class accountHolder:public bankAccount { 
      public:
              accountHolder(); //default constructor
              void entNewAccount(); //method to create new account
              int getAccountNumber() const; //method to get account number
              int getPinNumber() const; //method to get pin number
              string getAccountHolder(); //method to get account holder name
              char getAccountType(); //method to get account type
              double getAccountBalance(); //method to get account balance
              void depositAmount(); //method to deposit amount
              bool withdrawAmount(); //method to withdraw amount
              bool checkAccountNumber(); //method to enter and validate account number
              bool checkAccountPin(); //method to enter and validate pin number
              void closeAccount(); //method to close account
              void modifyAccount(); //method to modify account
              ~accountHolder() {}; //empty destructor
              //CLASS ENDS HERE
};

//ALL CLASSES END HERE

//*************************************************************//
//                       default constructor                       //
//*************************************************************//

accountHolder::accountHolder() {
     headPtr = NULL; //set the head pointer to NULL
     currPtr = NULL; //set the current pointer to NULL
     tempPtr = NULL; //set the temp pointer to NULL
}

//*************************************************************//
//       method to create a new account                        //
//*************************************************************//

void accountHolder::entNewAccount() {
     cout << "============================NEW ACCOUNT ENTRY FORM==============================\n";  
     cout << setw(18) << "Account Holder: ";  
     
     nodePtr newLink = new bankAccount; //create a new node to be used
     newLink->link = NULL; //set the next node in the list to NULL
     
     cin.ignore(); //we use this here in order to clear the input buffer - this is necessary in this case
     getline(cin, tempName); 
      
     newLink->name = tempName; 
     
     cout << setw(22) << "Account Type (C/S): ";     
     
     cin >> tempAccountType; 
 
     newLink->accountType = toupper(tempAccountType);
     
     cout << setw(14) << "Pin Number: "; 
     
     cin >> tempAccountPin; 
    
     stringstream pinString; //this is used as an efficient way to convert the user's pin to string in order to be used for validation 
     pinString << tempAccountPin; //load the pin to the string stream
     
     //validate user's pin
     do {
         if (pinString.str().length() > 4) {
            while (pinString.str().length() > 4) {
                  cout << setw(53) << "Pin cannot be greater than 4 digits. Please retry: ";
                  cin >> tempAccountPin;
                  pinString.str("");
                  pinString << tempAccountPin;
            }
        }
        
        if (pinString.str().length() < 4) {
            while (pinString.str().length() < 4) {
                  cout << setw(50) << "Pin cannot be less than 4 digits. Please retry: ";
                  cin >> tempAccountPin;
                  pinString.str("");
                  pinString << tempAccountPin;
            }
        }
    } while (pinString.str().length() > 4 || pinString.str().length() < 4);
    //end of user pin validation
    
    newLink->pin = tempAccountPin;
             
    cout << setw(18) << "Initial Amount: ";     
    
    cin >> tempInitial;
    tempBalance = tempInitial;
    
    newLink->balance = tempBalance;
    
    //generate a random account number for the user
    srand((unsigned)time(0)); 
    int random_integer; 
    random_integer = 0;
    for(int index = 0; index < 20; index++){ 
            random_integer = random_integer + (rand()%10)+1; 
    } 
    //end of random account number generation
     
    accountNumber = random_integer; //assign random number to accountNumber
    
    newLink->accountNumber = accountNumber;
    
    if (headPtr == NULL) { 
        headPtr = newLink;
     } 
     else {
          currPtr = headPtr;
          while (currPtr->link != NULL) {
                currPtr = currPtr->link;      
          }   
          currPtr->link = newLink;  
    }

    cout << "\n  Your new account number is " << accountNumber << "\n\n";
    
}

//*************************************************************//
//       method to enter and validate account number           //
//*************************************************************//

bool accountHolder::checkAccountNumber() {
    cin.ignore(); //once again we clear the input buffer, just in case
    
    //request and validate user's account number
    do {
        cin >> tempAccountNumber;
        
        if (headPtr == NULL) {
             cout << "  No accounts in database.";
             return false;
        }
        else {
             currPtr = headPtr;
             while (currPtr != NULL) {
                   if (currPtr->accountNumber == tempAccountNumber)
                      return true;                           
                   else 
                        currPtr = currPtr->link;
             }
             if (currPtr == NULL) {
                   cout << "  Account not in database. Please try again: ";
             }    
        }
    } while (currPtr == NULL);
    //end of user account number validation
}

//*************************************************************//
//       method to enter and validate pin number               //
//*************************************************************//

bool accountHolder::checkAccountPin() {
    cin.ignore(); //once again we clear the input buffer, just in case
    
    //request and validate user's pin
    do {
        cin >> tempAccountPin;
        
        currPtr = headPtr;
        while (currPtr != NULL) {
              if (currPtr->pin == tempAccountPin) {
                 return true;                           
              }
              else 
                   currPtr = currPtr->link;
        }
             if (currPtr == NULL) {
                   cout << "  Invalid pin number. Please try again: "; 
             }
    
    } while (currPtr == NULL);
    //end of user pin validation
}

//*************************************************************//
//       method to return account number                       //
//*************************************************************//

int accountHolder::getAccountNumber() const {
     return tempAccountNumber;
}

//*************************************************************//
//       method to return pin number                           //
//*************************************************************//

int accountHolder::getPinNumber() const {
     return tempAccountPin;
}

//*************************************************************//
//       method to return account number                       //
//*************************************************************//

string accountHolder::getAccountHolder() {
     currPtr = headPtr;
     
     while (currPtr != NULL) {
           if (currPtr->accountNumber == tempAccountNumber && currPtr->pin == tempAccountPin) //if the records match...
              return currPtr->name;
           else
               currPtr = currPtr->link; //proceed traversing the list                         
     }
}

//*************************************************************//
//       method to return account type                         //
//*************************************************************//

char accountHolder::getAccountType() {
     currPtr = headPtr;
     
     while (currPtr != NULL) {
           if (currPtr->accountNumber == tempAccountNumber && currPtr->pin == tempAccountPin) //if the records match...
              return currPtr->accountType;
           else
               currPtr = currPtr->link; //proceed traversing the list                           
     }
}

//*************************************************************//
//       method to return account balance                      //
//*************************************************************//

double accountHolder::getAccountBalance() {
     currPtr = headPtr;
     
     while (currPtr != NULL) {
           if (currPtr->accountNumber == tempAccountNumber && currPtr->pin == tempAccountPin) //if the records match...
              return currPtr->balance;
           else
               currPtr = currPtr->link; //proceed traversing the list                           
     }
}

//*************************************************************//
//       method to deposit amount                              //
//*************************************************************//

void accountHolder::depositAmount() {
     cin.ignore(); //again we clear the input buffer, just in case
     cin >> tempAmount; 
     
     currPtr = headPtr;
     
     while (currPtr != NULL) {
           if (currPtr->accountNumber == tempAccountNumber && currPtr->pin == tempAccountPin) { //if the records match...
              currPtr->balance += tempAmount;
              break; //exit the loop
           }
           else
               currPtr = currPtr->link; //proceed traversing the list                           
     }  
}

//*************************************************************//
//       method to withdraw amount                             //
//*************************************************************//

bool accountHolder::withdrawAmount() {
     cin.ignore(); //again we clear the input buffer, just in case
     cin >> tempAmount;  
     
        currPtr = headPtr;
        
        while (currPtr != NULL) {
              if (currPtr->accountNumber == tempAccountNumber && currPtr->pin == tempAccountPin) { //if the records match...
                 if (tempAmount < currPtr->balance) { //only allow withdrawal if the amount to be withdrawn is less than the actual balance
                     currPtr->balance -= tempAmount;
                     return true;
                 }
                 else 
                      return false;
              }
              else
                 currPtr = currPtr->link; //proceed traversing the list                          
        }
}

//*************************************************************//
//       method to close account                               //
//*************************************************************//

void accountHolder::closeAccount() {
     cin.ignore(); //again we clear the input buffer, just in case
     
     //request and validate user's account and pin numbers
     cout << "  Enter account number: ";
     if (checkAccountNumber()) {
        cout << "  Enter pin number: ";
        checkAccountPin();
     }
     //end of user account and pin number validation
     
     nodePtr delPtr = NULL; //create a new node and initialize it to NULL
     tempPtr = headPtr;
     currPtr = headPtr;
     
     while (currPtr != NULL && currPtr->accountNumber != tempAccountNumber && currPtr->pin != tempAccountPin) {
         tempPtr = currPtr;
         currPtr = currPtr->link;                         
     }
     delPtr = currPtr;
     //the next two lines basically patch the hole in the list
     currPtr = currPtr->link; 
     tempPtr->link = currPtr;
     
     delete delPtr; //remove this node from the list
    
     cout << "  Your account was successfully deleted.";
}

//*************************************************************//
//       method to modify account                              //
//*************************************************************//

void accountHolder::modifyAccount() {
     cin.ignore(); //clear the input buffer,
     
     //request and validate user's account and pin numbers
     cout << "  Enter account number: ";
     if (checkAccountNumber()) {
        cout << "  Enter pin number: ";
        
        if (checkAccountPin()) {
             currPtr = headPtr;
     
             while (currPtr != NULL) {
                   if (currPtr->accountNumber == tempAccountNumber && currPtr->pin == tempAccountPin) { //if the records match...
                      cout << "\n  -----ACCOUNT STATUS-----\n";
                      cout << "\n  Account No. :    " << getAccountNumber();
                      cout << "\n  Pin No. :        " << getPinNumber();
                      cout << "\n  Account Holder:  " << getAccountHolder();
                      cout << "\n  Account Type:    " << getAccountType();
                      cout << "\n  Account Balance: " << getAccountBalance();   
                      cout << "\n\n";
                      cout << "  -----Enter new details-----\n\n";
                      
                      //start of user account modification
                      cout << "  Modify Pin No. : ";
                      cin >> tempAccountPin;
                      cout << "  Modify Account Holder: ";
                      cin.ignore();
                      getline(cin, tempName);
                      cout << "  Modify Account Type: ";
                      cin >> tempAccountType;
                      
                      currPtr->pin = tempAccountPin;
                      currPtr->name = tempName;
                      currPtr->accountType = tempAccountType;
                      //end of user account modification
                      
                      cout << "  Your account was successfully updated.";
                      
                      break; //exit the loop              
                   } 
                   else
                       currPtr = currPtr->link; //proceed traversing the list  
             }                    
        }
     }
}

#endif
