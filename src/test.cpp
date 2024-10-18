/**
 * @file test.cpp
 * @author Daniel Sousa (danielm.sousads99@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-10-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <string>

using namespace std;

/**
 * @brief 
 * 
 * @return int 
 */
int main()
{
    vector<string> msg {"Hello", "C++", "World", "from", "VS Code", "and the C++ extension!"};

    for (const string& word : msg)
    {
        cout << word << " ";
    }
    cout << endl;

    return 0;
}

