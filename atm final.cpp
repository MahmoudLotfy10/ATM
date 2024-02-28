#include<iostream>
#include<cctype>
#include<cstring>
#include<stdio.h>
# include <limits>
using namespace std;
float only_number_amount()
{
    float number;
    while (1)
    {

        cin >> number;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input " << endl;
        }
        else
            break;
        cout << "Try again" << endl;
    }
    return number;
}
int only_number()
{
    int number;
    while (1)
    {

        cin >> number;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input " << endl;
            return -1;
        }
        else
            break;
        cout << "Try again" << endl;
    }
    return number;
}

class ATM
{
private:
    char account_name[101];
    int card_number[10];
    float amount;
    float total;
public:
    void create_new_acc()
    {
        bool cond1 = false;
        bool cond2 = false;
        cout << "please enter account name :" << endl;
        fgets(account_name, 100, stdin);
        fgets(account_name, 100, stdin);
        while (!cond1)
            for (int i = 0; i < strlen(account_name); i++)
                if (!(isalpha(account_name[i]) || isspace(account_name[i])))
                {
                    cout << "please enter a valid account name it must be alphabet or spaces only:" << endl;
                    fgets(account_name, 100, stdin);
                    cond1 = false;
                    break;
                }
                else cond1 = true;
        cout << "Please enter card number separated by space:" << endl;
        for (int i = 0; i < 10; i++)
            card_number[i] = only_number();

        while (!cond2)
            for (int i = 0; i < 10; i++)
                if (card_number[i] > 9 || card_number[i] < 0)
                {
                    cout << " in card number each number must be an integer from 0 to 9 , please enter a valid number" << endl;
                    for (int i = 0; i < 10; i++)
                        card_number[i] = only_number();
                    cond2 = false;
                    break;
                }

                else cond2 = true;
        total = 0;


    }
    int* card_num_getter()
    {
        return card_number;
    }
    void deposie()
    {
        cout << "please enter the amount you want to deposit: " << endl;
        amount = only_number_amount();
        total = total + amount + amount * .01;
    }
    void transfer(ATM& acc_reciever)
    {
        cout << "please enter the amount you want to transfer: " << endl;
        amount = only_number_amount();
        if (amount + amount * (.015) > total)
            cout << "this account does not have enough money for this operation" << endl;
        else {
            total = total - amount - amount * (.015);
            acc_reciever.total = acc_reciever.total + amount - (.015) * amount;
        }
    }
    void withdrawal()
    {
        cout << " please enter amount of money you want to withdraw: " << endl;
        amount = only_number_amount();
        if (amount + .03 * amount > total)
            cout << "invalid operation,this account does not have enough money for this process" << endl;
        else { total = total - amount - (.03) * amount; }
    }

    void print_acc_data()
    {
        cout << "account name is : " << endl;
        for (int i = 0; i < strlen(account_name); i++)
            cout << account_name[i];
        cout << endl;
        cout << "card number is: " << endl;
        for (int i = 0; i < 10; i++)
            cout << card_number[i] << " ";
        cout << endl;
        cout << "The amount is: " << total;
        cout << endl;
    }


};
class ATM client[100];
int searching(int* our_acc_num, int operation_no, int account, ATM client[100])
{
    int* temp;
    int j, k, target;
    for (j = 0; j < account; j++)
    {
        temp = client[j].card_num_getter();
        for (k = 0; k < 10; k++)
        {
            if (!(our_acc_num[k] == *(temp + k)))
                break;
        }
        if ((k == 10) && (operation_no == 1))
        {
            return -1;
        }
        else if ((k == 10) && ((operation_no == 2) || (operation_no == 3) || (operation_no == 4)))
            return j;
    }
    if ((j == account) && (operation_no == 1))
        return 1;
    else if ((j == account) && ((operation_no == 2) || (operation_no == 3) || (operation_no == 4)))
        cout << "this card number does not exist" << endl;
    return -1;
}


int main()
{
    bool exit = false;
    int confirm, operation_no, account = 0;
    int* seeker;
    int our_acc_num[10];
    int our_acc2_num[10];
    ATM client[100];
    int confirm2;

    while (!exit)
    {
        cout << "1----create new account" << endl;
        cout << "2----Deposit" << endl;
        cout << "3----transfer to another account" << endl;
        cout << "4----Withdrawal" << endl;
        cout << "5----Exit" << endl;
        cout << "please Enter number of operation: ";
        operation_no = only_number();
        switch (operation_no) {
        case 1:
            client[account].create_new_acc();
            seeker = client[account].card_num_getter();
            confirm = searching(seeker, operation_no, account, client);
            if (confirm == 1)
            {
                client[account].print_acc_data();
                account++;
            }
            else { cout << "invalid,This card number already exists" << endl; }
            break;

        case 2:
            cout << "enter card number of account :" << endl;
            for (int i = 0; i < 10; i++)
            {
                cin >> our_acc_num[i];
            }
            confirm = searching(our_acc_num, operation_no, account, client);
            if (confirm == -1)
                cout << "invalid,This card number does not exist" << endl;
            else
            {
                client[confirm].deposie();
                client[confirm].print_acc_data();
            }
            break;


        case 3:
            cout << "enter card number of the sender" << endl;
            for (int i = 0; i < 10; i++)
            {
                cin >> our_acc_num[i];
            }
            confirm = searching(our_acc_num, operation_no, account, client);
            if (confirm == -1) cout << "invalid,This card number" << endl;
            else
            {
                cout << "enter id reciver" << endl;
                for (int i = 0; i < 10; i++)
                {
                    cin >> our_acc2_num[i];
                }
                confirm2 = searching(our_acc2_num, operation_no, account, client);
                if (confirm2 == -1) cout << "invalid,This card number does not exist" << endl;
                else if (confirm == confirm2)
                {
                    cout << "invalid process , it is already the same account of the sender " << endl;
                    break;
                }
                else
                {
                    client[confirm].transfer(client[confirm2]);
                    client[confirm].print_acc_data();
                }
            }
            break;
        case 4:

            cout << "enter id" << endl;
            for (int i = 0; i < 10; i++)
            {
                cin >> our_acc_num[i];
            }
            confirm = searching(our_acc_num, operation_no, account, client);
            if (confirm == -1)
                cout << "invalid,This card number" << endl;
            else
            {
                client[confirm].withdrawal();
                client[confirm].print_acc_data();
            }
            break;
        case 5:
            cout << "Thank you for being our customer" << endl;
            exit = true;
            break;
        default:
            cout << ",please enter a propriate choice :" << endl;
        }
    }

}

