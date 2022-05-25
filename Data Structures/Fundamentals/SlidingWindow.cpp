#include <deque>
#include <iostream>
#include <vector>
using namespace std;

vector<int> slidingWindow(vector<int>  listOfNumbers, int k){
	deque<int> q;
	vector<int> res;
	int n = listOfNumbers.size();

	for (int i = 0; i < k; i++) {
		while ((!q.empty()) && listOfNumbers[i] >= listOfNumbers[q.back()]) {
			q.pop_back();
		}

		q.push_back(i);
	}


	for (int i=k; i < n; i++) {
		res.push_back(listOfNumbers[q.front()]);

		while ((!q.empty()) && q.front() <= i - k) {
			q.pop_front();
		}


		while ((!q.empty()) && listOfNumbers[i] >= listOfNumbers[q.back()]) {
			q.pop_back();
		}

		q.push_back(i);
	}

	res.push_back(listOfNumbers[q.front()]);

	return res;
}
