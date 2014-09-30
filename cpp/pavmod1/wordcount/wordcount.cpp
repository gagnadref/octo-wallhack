#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

multimap<int, string> swapMap(map<string, int> src) {
    multimap<int, string> destination;
    transform(src.begin(), src.end(), inserter(destination, destination.begin()),
            [] (pair<string, int> p) { return pair<int, string>(p.second, p.first); });
    return destination;
}

int main()
{
    ifstream is("cyrano.txt");
    if (!is)
    {
        cout << R"(Fichier "cyrano.txt" non trouvé)" << endl;
    }
    string mot;

    map<string, int> compteMots;
    while (is >> mot)
    {
        std::transform(mot.begin(), mot.end(), mot.begin(), [] (char item) { return std::tolower(item); });
        compteMots[mot]++;
    }

    multimap<int, string> multiMap = swapMap(compteMots);

    for(auto p : multiMap)
    {
        if (p.first > 5)
        {
            cout << setw(20) <<  p.first << '\t'
                << p.second << endl;
        }
    }
    return 0;
}

