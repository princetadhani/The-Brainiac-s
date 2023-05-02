#include <iostream>
#include <vector>
#include <math.h>
#include <conio.h>
#include <windows.h>
using namespace std;

class TT
{
public:
    void getNumberOfInputs(string input); // m1
    void makeTT();
    vector<char> vars;
    vector<vector<bool>> ourTT;
    vector<vector<bool>> result;
    vector<bool> intermediate;
    vector<bool> zero;
    int length;
    void printTT();
    void findalg(string input);
    bool getValue(char var, int j);
    int resultcounter;
    TT();
};

TT::TT()
{
    resultcounter = -1;
}

void TT::makeTT()
{
    length = pow(2, vars.size());
    int width = vars.size();
    vector<bool> temp;
    bool tempint;
    for (int i = 0; i < vars.size(); i++)
    {
        zero.clear();
        intermediate.clear(); // destroys the list by removing all elements from the list and sets size of list to zero.
        for (int j = 0; j < length; j++)
        {
            intermediate.push_back(false);
            zero.push_back(false);
            if (j % (int)pow(2, i + 1) < pow(2, i))
            {
                tempint = false;
            }
            else
            {
                tempint = true;
            }
            temp.push_back(tempint);
        }

        ourTT.push_back(temp);
        temp.clear();
    }
    result.push_back(zero);
    resultcounter++;
    // return;
}

void TT::printTT()
{
    cout << endl;
    // cout << endl;
    cout << "Loading";
    for (int i = 0; i < 6; i++)
    {
        cout << ".";
        Sleep(1000);
    }
    // Sleep();
    system("cls");
    cout<<"\t\t\t";
    for (int j = 0; j < vars.size(); j++)
    {
        
        cout << vars[j] << "  ";
    }
    cout << "F(output)" << endl;
    
    for (int j = 0; j < pow(2, vars.size()); j++)
    {
        cout<<"\t\t\t";
        for (int i = vars.size() - 1; i >= 0; i--)
        {
            
            cout << ourTT[i][j] << "  ";
        }
        cout << result[resultcounter][j] << endl;
    }
    cout << endl;
    cout << endl;
    return;
}

void TT::getNumberOfInputs(string input)
{
    int j = 0;
    cout << "Function: ";
    for (int i = 0; i < input.size(); i++)
    {
        cout << input[i];
        if (input[i] <= 'Z' && input[i] >= 'A')
        {
            for (j = 0; j < vars.size(); j++)
            {
                if (vars[j] == input[i])
                {
                    break;
                }
            }
            if (j == vars.size())
            {
                vars.push_back(input[i]);
            }
        }
    }
    cout << endl
         << "Number of inputs: " << vars.size(); // << endl;
    ;
    return;
}

void TT::findalg(string input)
{
    int i = 0;
    string newinput;
    while (i < input.size())
    {
        // cout << input[i] << "  " << i << "  " << input[i + 1] << endl;
        switch (input[i])
        {
        case '&': // for anding operation
            if (input[i + 1] != '(')
            {
                for (int j = 0; j < length; j++)
                {
                    result[resultcounter][j] = (result[resultcounter][j] & getValue(input[i + 1], j));
                }
                input.erase(i, 2);
            }
            else
            {
                newinput = input.substr(input.find("(") + 1, input.find(")") - input.find("("));
                newinput = "+" + newinput;
                // cout << newinput;
                result.push_back(zero);
                resultcounter++;
                findalg(newinput);
                intermediate = result[resultcounter];
                result.pop_back();
                resultcounter--;
                for (int j = 0; j < length; j++)
                {
                    result[resultcounter][j] = (result[resultcounter][j] & intermediate[j]);
                }
                input.erase(i, input.find(")") + i);
            }
            break;

        case '!': // for nand operation

            for (int j = 0; j < length; j++)
            {
                result[resultcounter][j] = !(result[resultcounter][j] & getValue(input[i + 1], j));
            }
            input.erase(i, 2);
            break;

        case '+': // for or operation
            for (int j = 0; j < length; j++)
            {
                result[resultcounter][j] = (result[resultcounter][j] | getValue(input[i + 1], j));
            }
            input.erase(i, 2);
            break;

        case '%': // for nor operation
            for (int j = 0; j < length; j++)
            {
                result[resultcounter][j] = !(result[resultcounter][j] | getValue(input[i + 1], j));
            }
            input.erase(i, 2);
            break;

        case '-': // for not gate_b
            for (int j = 0; j < length; j++)
            {
                result[resultcounter][j] = !(result[resultcounter][j]);
            }
            input.erase(i, 1);
            break;

        case '#': // EX-or gate
            for (int j = 0; j < length; j++)
            {
                result[resultcounter][j] = (result[resultcounter][j] ^ getValue(input[i + 1], j));
            }
            input.erase(i, 2);
            break;

        case '(':
        case ')':
        default:
            input.erase(i, 1);
            break;
        }
        // printTT();
        // cout << input << endl;
    }
    return;
}

bool TT::getValue(char var, int j)
{
    for (int i = 0; i < vars.size(); i++)
    {
        if (vars[vars.size() - i - 1] == var)
            return ourTT[i][j];
    }
    cout << "ERROR" << endl;
    return false;
}

int main()
{

label:
    system("cls");
    TT ourFunction;
    cout << "\t\t\t WELCOME TO LOGIC GATE OPERATION";
    for (int i = 0; i < 6; i++)
    {
        cout << ".";
        Sleep(1000);
    }

    cout << endl
         << endl
         << "-->THERE ARE SOME INSTRUCTIONS FOR USING SIGN:" << endl;
    cout << "use ' & ' sign for AND operation" << endl;
    cout << "use ' ! ' sign for NAND operation" << endl;
    cout << "use ' + ' sign for OR operation" << endl;
    cout << "use ' % ' sign for NOR operation" << endl;
    cout << "use ' # ' sign for EX-OR operation" << endl;
    string input;
    cout << endl
         << "Please enter a boolean expression: ";
    cin >> input;

    input = "+" + input;

    for (int i = 0; i < input.size(); i++)
        input[i] = toupper(input[i]);

    ourFunction.getNumberOfInputs(input);

    cout << " Inputs Counted" << endl;
    ourFunction.makeTT();
    cout << "Truth Table made" << endl;
    // ourFunction.printTT();
    ourFunction.findalg(input);
    ourFunction.printTT();
    cout << "PRESS ANY KEY TO CONTINUE....." << endl
         << "IF YOU WANT TO END THE PROGRAM PRESS E/e....." << endl;
    char q;
    cin >> q;
    // system("cls");
    if (q == 'e' || q == 'E')
    {
        cout << endl
             << "THANK YOU";
        for (int i = 0; i < 4; i++)
        {
            cout << ".";
            Sleep(1000);
        }
        // break;
    }
    else
    {
        goto label;
    }
    return 0;
}