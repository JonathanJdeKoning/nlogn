#include <iostream>
#include <vector>
#include <limits.h>
#include "garsia_wachs.h"

using std::cout;
using std::cin;
using std::min;
using std::atoi;
using std::vector;
vector<int> A;
vector<int> prefix;
vector<vector<int>> dp;

int N = 0;
int calls = 0;

void printMemo() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N-1; j++) {
			cout << dp[i][j] << " ";
		}
		cout << dp[i][N-1] << '\n';
	}
}

void makePrefixArray() {
	int total = 0;
	prefix.push_back(0);
	for (int num : A) {
		total += num;
		prefix.push_back(total);
	}
}

int rangeSum(int l, int r) {
	return prefix[r + 1] - prefix[l];
}

int minCostFuseRec(int l, int r) {
	calls++;
	if (l >= r) return 0;

	int segmentSum = rangeSum(l, r);

	int mnCost = INT_MAX;


	for (int k = l; k < r; k++) {
		int leftCost = minCostFuseRec(l, k);
		int rightCost = minCostFuseRec(k + 1, r);

		if (leftCost == INT_MAX || rightCost == INT_MAX) continue;

		int currTotal = leftCost + rightCost + segmentSum;
		mnCost = min(mnCost, currTotal);
	}
	return mnCost;
}

int minCostFuseMem(int l, int r) {
	if (dp[l][r] != -1)
		return dp[l][r];


	int segmentSum = rangeSum(l, r);

	int mnCost = INT_MAX;

	for (int k = l; k < r; k++) {
		int leftCost = minCostFuseMem(l, k);
		int rightCost = minCostFuseMem(k + 1, r);

		if (leftCost == INT_MAX || rightCost == INT_MAX) continue;

		int currTotal = leftCost + rightCost + segmentSum;
		mnCost = min(mnCost, currTotal);
	}
	dp[l][r] = mnCost;
	return mnCost;
}

int minCostFuseIter() {
	for (int n = 2; n <= N; n++) {
		for (int i = 0; i <= N - n; i++) {
			

			int j = i + n - 1;
			int segmentSum = rangeSum(i, j);
			
			dp[i][j] = INT_MAX;

			for (int k = i; k < j; k++) {
				int costA = dp[i][k];
				int costB = dp[k + 1][j];

				if (costA == INT_MAX or costB == INT_MAX) continue;

				int totalCost = costA + costB + segmentSum;
				dp[i][j] = min(dp[i][j], totalCost);


			}

		}
	}
	return dp[0][N - 1];

}
void fillMatrix(int N) {
	for (int i = 0; i < N;i++) {
		vector<int> newRow;
		for (int j = 0; j < N; j++) {

			if (i == j)
				newRow.push_back(0);
			else
				newRow.push_back(-1);
		}
		dp.push_back(newRow);
	}
}


int main(int argc, char* argv[]) {
	char op = argv[1][0];
	N = atoi(argv[2]);
        int total = 0;
	for (int i = 0; i < N; i++)
		A.push_back(atoi(argv[3 + i]));

	makePrefixArray();
	fillMatrix(N);

	switch (op) {
	case 'R':
		cout << minCostFuseRec(0, N-1) << '\n';
		break;
	case 'M':
		cout << minCostFuseMem(0, N-1) << '\n';
		break;
	case 'D':
		cout << minCostFuseIter() << '\n';
		break;

        case 'J':
                {
                    vector<int> depths = alphabetic_huffman_code(A);
                    for (int i = 0; i < depths.size(); i++) {
                        total += depths[i] * A[i];
                    }
                    cout << total << '\n';
                    break;
                }
        case 'r':
		minCostFuseRec(0, N - 1);
		cout << calls << '\n';
		break;
	case 'm':
		minCostFuseMem(0, N - 1);
		printMemo();
		break;
	case 'd':
		minCostFuseIter();
		printMemo();
		break;
	}



}
