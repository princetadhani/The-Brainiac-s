#include <iostream>
#include <vector>
#include <math.h>
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
    // void exception(string input);
    int resultcounter;
    TT();
};

TT::TT()
{
    resultcounter = 0;
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
    // resultcounter++;
    //  return;
}

void TT::printTT()
{
    cout << endl;
    // cout << endl;
    for (int j = 0; j < vars.size(); j++)
    {
        cout << vars[j] << "  ";
    }
    cout << "   F(output)" << endl;

    for (int j = 0; j < pow(2, vars.size()); j++)
    {
        for (int i = vars.size() - 1; i >= 0; i--)
        {
            cout << ourTT[i][j] << "  ";
        }
        cout << "   " << result[resultcounter][j] << endl;
    }
    cout << endl;
    cout << endl;
    return;
}

// void TT::exception(string input)
//{
//     for (int i = 0; i < length; i++)
//     {
//        if (input[i] == '_')
//        {
//            for (int j = 0; j < length; j++)
//            {
//               if (ourTT[0][0] == 0)
//               {
//                   cout << 1 << " " << endl;
//              }
//              else
//              {
//                  cout << 2 << " " << endl;
//              }
//          }
//      }
//  }
//}

void TT::getNumberOfInputs(string input) // 1
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
                vars.push_back(input[i]); // adding the remaining variable
            }
        }
    }
    cout << endl
         << "Number of inputs: " << vars.size() << endl;
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
            cout << input[i] << endl;
        case '^': // for Anding operation
            cout << "and case :";
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

        case '*': // for nand operation
            cout << "nand :";

            for (int j = 0; j < length; j++)
            {
                result[resultcounter][j] = !(result[resultcounter][j] & getValue(input[i + 1], j));
            }
            input.erase(i, 2);
            break;

        case '+': // for or operation
            cout << "or case :";

            for (int j = 0; j < length; j++)
            {
                cout << result[resultcounter][j];
                result[resultcounter][j] = (result[resultcounter][j] | getValue(input[i + 1], j));
            }
            input.erase(i, 2);
            break;

        case '%': // for nor operation
            cout << "nor :";
            for (int j = 0; j < length; j++)
            {
                result[resultcounter][j] = !(result[resultcounter][j] | getValue(input[i + 1], j));
            }
            input.erase(i, 2);
            break;

        case '-':
            cout << "ans :";
            for (int j = 0; j < length; j++)
            {
                // result[resultcounter][j] = !getValue(input[i + 1], j);
                result[resultcounter][j] = (getValue(input[i], j + 1));
                // cout << "ans :" << (~result[resultcounter][j]);

                // result[resultcounter][j] = (!(getValue(input[i + 1], j)));

                // for (int m = 0; m < length; m++)
                //{
                //    if (ourTT[j][m] == 0)
                //    {
                //        result[resultcounter][j] = 1;
                //    }
                //    else
                //    {
                //        result[resultcounter][j] = 0;
                //    }
                //}
            }
            input.erase(i, 1);
            break;

        case '#': // EX-or gate
            cout << "ex or :";
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
        // i++;
    }
    return;
}

bool TT::getValue(char var, int j)
{
    for (int i = 0; i < vars.size(); i++)
    {
        // cout << "in loop";
        if (vars[vars.size() - i - 1] == var)
        {
            // cout << "in if";
            return ourTT[i][j];
        }
    }
    cout << "ERROR" << endl;
    return false;
}

int main()
{
    TT ourFunction;
    cout << "-->THERE ARE SOME INSTRUCTIONS FOR USING SIGN:" << endl;
    cout << "use ' ^ ' sign for AND operation" << endl;
    cout << "use ' ! ' sign for NAND operation" << endl;
    cout << "use ' + ' sign for OR operation" << endl;
    cout << "use ' % ' sign for NOR operation" << endl;
    cout << "use ' # ' sign for EX-OR operation" << endl;
    string input;
    cout << "Please enter a boolean expression: ";
    getline(cin, input);
    // for (int h = 0; h < input.size(); h++)
    //{
    //     if (input[h] == '_')
    //     {
    //         exception(input);
    //     }
    // }
    input = "+" + input;
    for (int i = 0; i < input.size(); i++)
        input[i] = toupper(input[i]);

    ourFunction.getNumberOfInputs(input);
    cout << "Inputs Counted" << endl;
    ourFunction.makeTT();
    cout << "TT made" << endl;
    // ourFunction.printTT();
    ourFunction.findalg(input);
    ourFunction.printTT();
    return 0;
}
