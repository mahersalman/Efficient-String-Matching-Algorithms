

#include <iostream>
#include <vector>
#include <bitset>
#include <string>
#include <map>
#include <chrono>
#include <unordered_set>
#include <fstream>
using namespace std;
using namespace chrono;

struct www
{
    string word;
    vector<int> adr;
};

struct MP
{
    map<string, int> mp1;
    vector <www> mas;
};

void generateBinaryStrings(int N, int N_2, map<string, int>& binaryStringsMap) {
    int total = 1 << N;
    for (int i = 0; i < total; ++i) {
        std::string binaryString = "";
        int onesCount = 0; // Count the number of 1s in the binary string
        for (int j = N - 1; j >= 0; --j) {
            if (i & (1 << j)) {
                binaryString += '1';
                ++onesCount;
            }
            else {
                binaryString += '0';
            }
        }
        // Only add the string to the map if it has at least N_2 ones
        if (onesCount >= N_2) {
            binaryStringsMap[binaryString] = 1;
        }
    }
}



std::string extractFirstNsovp(const std::string& binaryString, int Nsovp) {
    std::string result;
    int count = 0;
    size_t i = 0;

    // Find the first occurrence of '1' and start the result with it
    while (i < binaryString.length() && count < Nsovp) {
        if (binaryString[i] == '1') {
            count++;
        }
        if (count > 0) { // Start adding to result only after finding the first '1'
            result += binaryString[i];
            i++;
            break;
        }
        i++;
    }

    // Continue adding characters until we have Nsovp ones
    while (i < binaryString.length() && count < Nsovp) {
        result += binaryString[i];
        if (binaryString[i] == '1') {
            count++;
        }
        i++;
    }
    return result;
}

bool isSubstring(const std::string& form, const std::string& MCS) {
    return MCS.find(form) != string::npos;
}

// Function to find lossy MCSs
vector<string> findLossyMCSs(int N, int N_2, int Nsovp) {
    map<string, int> lossyMCS;
    generateBinaryStrings(N, N_2, lossyMCS);
    vector<string> result;
    //int counter = 0;
   // int numElements = static_cast<int>(lossyMCS.size());


    for (auto& pair : lossyMCS) {
        if (pair.second != 0) {
            string form = extractFirstNsovp(pair.first, Nsovp);
            result.push_back(form);
            pair.second = 0;
            for (auto& pair2 : lossyMCS) {
                if (pair2.second != 0) {
                    if (isSubstring(form, pair2.first)) {
                        pair2.second = 0;
                        //counter++;
                    }
                }
            }
            //cout << "persentage : " << (counter * 100) / numElements << "%" << endl;
        }
    }
    return result;
}

vector<www> searchNaive(const string& text, int N, int N_2) {
    vector<www> results;
    www w;
    int i, j, n, j1;
    for (i = 0; i < text.size() - N + 1; i++)
    {
        w.word = text.substr(i, N);
        w.adr.clear();
        for (j = 0; j < text.size() - N + 1; j++)
        {
            n = 0;
            for (j1 = 0; j1 < N; j1++)
            {
                if (w.word[j1] != text[j + j1])
                {
                    n++;
                    if (n > N - N_2) break;
                }
            }

            if (n > N - N_2) continue;
            w.adr.push_back(j);
        }
        results.push_back(w);
    }

    return results;
}

vector<MP> searchMCSs(const string& text, const vector<string>& form, int N) {
    vector<MP> maps;
    for (const auto& f : form) {
        MP map1;
        map1.mp1.clear();
        map1.mas.clear();

        for (size_t i = 0; i <= text.size() - f.size()+1; ++i) {
            string pattern;
            pattern.reserve(f.size());
            pattern += text[i];

            for (size_t j = 1; j < f.size(); ++j) {
                if (f[j] == '1') {
                    pattern += text[i + j];
                }
                else {
                    pattern += "_";
                }
            }

            int n = map1.mas.size();
            auto ret = map1.mp1.insert({ pattern, n });

            if (ret.second) {
                www w;
                w.word = pattern;
                w.adr.clear();
                w.adr.push_back(i);
                map1.mas.push_back(w);
            }
            else {
                n = ret.first->second;
                map1.mas[n].adr.push_back(i);
            }
        }
        maps.push_back(map1);
    }
    return maps;
}

int main()
{
    int N = 20;
    int N_2 = int(0.6 * N);
    int Nsovp = 6;

    int testSize = 1000000;

    cout << "input :" << endl
        << "-N = " << N << endl
        << "-N_2 = " << N_2 << endl
        << "-Nsovp = " << Nsovp << endl
        << "-TextSize = " << testSize << endl
        << "______________________________" << endl;


    // 1. Get all Lossy MCSs
    auto stTimeMCS = high_resolution_clock::now();
    vector<string> lossyMCSs = findLossyMCSs(N, N_2, Nsovp);
    auto endTimeMCS = high_resolution_clock::now();
    auto TimeMCS = duration_cast<duration<double>>(endTimeMCS - stTimeMCS);
    cout << "\nFind Lossy MCSs time :  " << TimeMCS.count() << " seconds\n";


    ofstream outfile("Output_LossyMCSs.txt");
    for (const auto& mcs : lossyMCSs) {
        outfile << mcs << endl;
    }
    outfile << "\nFind Lossy MCSs time : " << TimeMCS.count() << " seconds\n";
    outfile.close();


    // 2. Generete Random Number

    string text = "";
    ofstream outfile1("Text1.txt");
    char ch;
    int i, j;
    for (i = 0; i < testSize; i++)
    {
        ch = 'a' + int(15 * double(rand()) / double(RAND_MAX));
        text = text + ch;
        outfile1 << ch;
    }
    outfile1.close();


    // 3. Search

    /*                      Search using MCSs Algorithm                 */


    auto stMCSs = high_resolution_clock::now();
    vector<MP> resultMCSs = searchMCSs(text, lossyMCSs, N);
    auto endMCSs = high_resolution_clock::now();
    auto SearchMCSsTime = duration_cast<duration<double>>(endMCSs - stMCSs);
    cout << "\n Search Based On MCSs algorithm time : " << SearchMCSsTime.count() << " seconds\n";


    ofstream outfile3("Output_MCSs.txt");
    outfile3 << "\n Search Based On MCSs algorithm time : " << SearchMCSsTime.count() << " seconds\n";

    
     for (int f= 0; f < resultMCSs.size(); f++)
       {
          for (i = 0; i < resultMCSs[f].mas.size(); i++)
           {
               outfile3 << "\n" << i << " " << resultMCSs[f].mas[i].word << ": ";
              for (j = 0; j < resultMCSs[f].mas[i].adr.size(); j++)
                   outfile3 << resultMCSs[f].mas[i].adr[j] << " ";
           }
     }
   outfile3.close();
    

    /*                      Naive Algorithm                 */
    
    auto stNaive = high_resolution_clock::now();
    vector<www> resultNive = searchNaive(text, N, N_2);
    auto endNaive = high_resolution_clock::now();
    auto TimeNive = duration_cast<duration<double>>(endNaive - stNaive);
    cout << "\n Naive algorithm time : " << TimeNive.count() << " seconds\n";

    ofstream outfile2("Output_naive.txt");
    outfile2 << "\n Naive algorithm time : " << TimeNive.count() << " seconds\n";

    for (i = 0; i < resultNive.size(); i++) {
        outfile2 << "\n" << " " << resultNive[i].word << ": ";
        for (j = 0; j < resultNive[i].adr.size(); j++)
            outfile2 << resultNive[i].adr[j] << " ";

    }
    outfile2.close();
    

    ofstream outfile4("Output.txt");
    outfile4 << "input :" << endl
        << "-N = " << N << endl
        << "-N_2 = " << N_2 << endl
        << "-Nsovp = " << Nsovp << endl
        << "-TextSize = " << testSize << endl
        << "______________________________" << endl;

    outfile4 << "\n Find Lossy MCSs time : " << TimeMCS.count() << " seconds\n";
	outfile4 << "\n Search Based On MCSs algorithm time : " << SearchMCSsTime.count() << " seconds\n";
    outfile4 << "\n Naive algorithm time : " << TimeNive.count() << " seconds\n";
    outfile4.close();

    return 0;
}

