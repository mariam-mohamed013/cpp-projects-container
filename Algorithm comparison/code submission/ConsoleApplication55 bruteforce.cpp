#include <iostream>
#include <vector>
using namespace std;

int maxCuts;
int minCuts;

void tryCuts(int remaining, int count, const vector<int>& cuts) {
    if (remaining == 0) {

        if (count > maxCuts) maxCuts = count;
        if (count < minCuts) minCuts = count;
        return;
    }
    if (remaining < 0) return;

    for (int i = 0; i < (int)cuts.size(); ++i) {
        tryCuts(remaining - cuts[i], count + 1, cuts);
    }
}

int main() {
    int n;
    cout << "Enter total ribbon length (n): ";
    cin >> n;

    int k;
    cout << "Enter number of possible cut lengths: ";
    cin >> k;

    vector<int> cuts(k);
    cout << "Enter the cut lengths: ";
    for (int i = 0; i < k; ++i) {
        cin >> cuts[i];
        if (cuts[i] <= 0) {
            cout << "Cut lengths must be positive integers.\n";
            return 1;
        }
    }

    maxCuts = -1;
    minCuts = 1000000;

    tryCuts(n, 0, cuts);

    if (maxCuts == -1) {
        cout << "It is not possible to cut the ribbon using the given lengths." << endl;
    }
    else {
        cout << "Maximum number of pieces: " << maxCuts << endl;
        cout << "Minimum number of pieces: " << minCuts << endl;
    }

    return 0;
}