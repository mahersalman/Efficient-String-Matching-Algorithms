

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

struct Node {
	char data;
	Node* right;
    Node* left;
};

/* visualize tree as a graph*/
void generateDot(Node* node, std::ofstream& file, int& counter) {
    if (node == nullptr) {
        return;
    }

    int currentId = counter++;
    file << "\tNode" << currentId << " [label=\"" << node->data << "\"];\n";

    if (node->left) {
        int leftId = counter;
        file << "\tNode" << currentId << " -> Node" << leftId << ";\n";
        generateDot(node->left, file, counter);
    }

    if (node->right) {
        int rightId = counter;
        file << "\tNode" << currentId << " -> Node" << rightId << ";\n";
        generateDot(node->right, file, counter);
    }
}

void createDotFile(Node* root, const std::string& filename) {
    std::ofstream file(filename);
    file << "digraph G {\n";
    file << "\tnode [shape=circle];\n";
    int counter = 0;
    generateDot(root, file, counter);
    file << "}\n";
    file.close();
}





Node* newNode(char data) {
	Node* node = new Node();
	node->data = data;
	node->left = NULL;
	node->right = NULL;

	return node;
}

void Insert(Node* root, string str) {
    Node* temp = root;
    for (int i = 1; i < str.length(); i++) { // Start from the second character
        if (str[i] == '0') {
            if (temp->left == NULL) {
                temp->left = newNode('0');
            }
            temp = temp->left;
        }
        else {
            if (temp->right == NULL) {
                temp->right = newNode('1');
            }
            temp = temp->right;
        }
    }
}


Node* createTree(vector<string> lossyMCSs) {
    if (lossyMCSs.empty()) return nullptr; // Ensure there's at least one string
    Node* root = newNode(lossyMCSs[0][0]); // Use the first char of the first string
    for (const auto& mcs : lossyMCSs) {
        Insert(root, mcs);
    }
    return root;
}




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

    for (auto& pair : lossyMCS) {
        if (pair.second != 0) {
            string form = extractFirstNsovp(pair.first, Nsovp);
            result.push_back(form);
            pair.second = 0;
            for (auto& pair2 : lossyMCS) {
                if (pair2.second != 0) {
                    if (isSubstring(form, pair2.first)) {
                        pair2.second = 0;
                    }
                }
            }
        }
    }
    return result;
}

// Helper function to copy the structure of MCSs tree with placeholders
Node* copyMCSStructure(Node* root, const string& text, int textIndex) {
    if (root == nullptr) {
        return nullptr;
    }

    Node* newNode = new Node;
    if (root->data == '1') {
        newNode->data = (textIndex < text.length()) ? text[textIndex] : '_';
    }
    else {
        newNode->data = '_';
    }
    textIndex++;
    newNode->left = copyMCSStructure(root->left, text, textIndex);
    newNode->right = copyMCSStructure(root->right, text, textIndex);
    return newNode;
}

vector<Node*> BuildTextTreeBasedOnMCSs(string text, Node* root_MCSs, int N) {
    vector<Node*> textTree;

    for (int i = 0; i <= text.length() - N; i++) {
        int textIndex = i;
        Node* newTree = copyMCSStructure(root_MCSs, text, textIndex);
        textTree.push_back(newTree);
    }

    return textTree;
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


int main()
{
    int N = 10;
    int N_2 = int(0.6 * N);
    int Nsovp = 4;
    int testSize = 100;

    cout << "input :" << endl
        << "-N = " << N << endl
        << "-N_2 = " << N_2 << endl
        << "-Nsovp = " << Nsovp << endl
        << "-TextSize = " << testSize << endl
        << "______________________________" << endl;


    // 1. Get all Lossy MCSs +  Create Tree + Visualize
    auto stTimeMCS = high_resolution_clock::now();
    vector<string> lossyMCSs = findLossyMCSs(N, N_2, Nsovp);
    Node* rootMCS = createTree(lossyMCSs);
    createDotFile(rootMCS, "tree.dot");
    auto endTimeMCS = high_resolution_clock::now();
    auto TimeMCS = duration_cast<duration<double>>(endTimeMCS - stTimeMCS);
    cout << "\nFind and Build Tree based On Lossy MCSs -  time :  " << TimeMCS.count() << " seconds\n";


     // 2. Generete Random Text
     string text = "";
     char ch;
     int i, j;
     ofstream outText("Text.txt");
     for (i = 0; i < testSize; i++)
     {
         ch = 'a' + int(15 * double(rand()) / double(RAND_MAX));
         text = text + ch;
         outText << ch;

     }
     outText.close();

     //3.Create String Tree according to the MCSs Tree
     auto stTimeTree = high_resolution_clock::now();

     vector<Node*> TextTree = BuildTextTreeBasedOnMCSs(text, rootMCS, N);
     createDotFile(TextTree[0], "Texttree0.dot");
     createDotFile(TextTree[1], "Texttree1.dot");

     auto endTimeTree = high_resolution_clock::now();
     auto TimeTree = duration_cast<duration<double>>(endTimeTree - stTimeTree);
     cout << "Search BasedOn Text Tree -  time :  " << TimeTree.count() << " seconds\n";

     //5. Search Naive Algorithm

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


}


