#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[])
{
    string line;
    int n;
    cin >> n;
    int index = 0;
    vector<pair<bool, bool>> flags(n);
    for (int i = 0; i < n; i++)
        flags[i] = {true, true};
    bool d1 = true, d2 = true;

    while (index < n)
    {
        cin >> line;
        for (int i = 0; i < n; i++)
        {
            if (line[i] == 'x')
            {
                flags[i].first = false;
                flags[index].second = false;
                if (i == index)
                    d1 = false;
                if (i == n - index - 1)
                    d2 = false;
            }
        }
        index++;
    }
    if (d1 or d2)
    {
        cout << "Yes\n";
        return 0;
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            if (flags[i].first or flags[i].second)
            {
                cout << "Yes\n";
                return 0;
            }
        }
        cout << "No\n";
    }
    return 0;
}