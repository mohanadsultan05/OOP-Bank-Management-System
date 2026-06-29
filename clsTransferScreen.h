#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "Global.h"

class clsTransferScreen : protected clsScreen
{
private:

    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n________________________";
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n________________________\n";
    }

    static string _ReadAccountNumber(string Message)
    {
        string AccountNumber;

        cout << Message;
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, enter another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        return AccountNumber;
    }

    static float ReadAmount(clsBankClient SourceClient)
    {
        float Amount;

        cout << "\nEnter Transfer Amount: ";
        Amount = clsInputValidate::ReadNumber<float>();

        while (Amount > SourceClient.AccountBalance)
        {
            cout << "\nAmount exceeds available balance, enter another amount: ";
            Amount = clsInputValidate::ReadNumber<float>();
        }

        return Amount;
    }

public:

    static void ShowTransferScreen()
    {
        _DrawScreenHeader("\tTransfer Screen");

        clsBankClient SourceClient =
            clsBankClient::Find(_ReadAccountNumber("\nPlease Enter Source Account Number: "));

        _PrintClient(SourceClient);

        string DestinationAccount;

        do
        {
            DestinationAccount =
                _ReadAccountNumber("\nPlease Enter Destination Account Number: ");

            if (DestinationAccount == SourceClient.AccountNumber())
            {
                cout << "\nYou cannot transfer to the same account.\n";
            }

        } while (DestinationAccount == SourceClient.AccountNumber());

        clsBankClient DestinationClient =
            clsBankClient::Find(DestinationAccount);

        _PrintClient(DestinationClient);

        float Amount = ReadAmount(SourceClient);

        cout << "\nAre you sure you want to perform this operation? (Y/N): ";

        char Answer;
        cin >> Answer;

        if (toupper(Answer) == 'Y')
        {
            if (SourceClient.Transfer(Amount, DestinationClient, CurrentUser.UserName))
            {
                cout << "\nTransfer done successfully.\n";
            }
            else
            {
                cout << "\nTransfer failed.\n";
            }

            _PrintClient(SourceClient);
            _PrintClient(DestinationClient);
        }
    }

};