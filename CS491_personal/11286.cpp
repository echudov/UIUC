#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

typedef unordered_map<int, int> umii;
typedef long long ll;

int main() {
	vector<int> results;
	umii courseCounts;
	int studentCount;
	cin >> studentCount;

	while(studentCount != 0) {

		for (int i = 0; i < studentCount; ++i) {
			int courses[5];
			for (int course = 0; course < 5; ++course) {
				cin >> courses[course];
			}
			std::sort(courses, courses + 5);

			ll uniqueId = 0;
			for (int course = 0; course < 5; ++course) {
				uniqueId += courses[course] * std::pow(10, 3 * course);
			}
			
			if (courseCounts.find(uniqueId) == courseCounts.end()) {
				courseCounts[uniqueId] = 1;
			} else {
				courseCounts[uniqueId] += 1;
			}
		}
		int max = std::max_element(
				std::begin(courseCounts), std::end(courseCounts), 
				[] (const std::pair<int, int> & p1, const std::pair<int, int> & p2) {
        		return p1.second < p2.second;
    			})->second;
		
		int students = 0;
		for (std::pair<int, int> element : courseCounts) {
			if (element.second == max) {
				students += max;
			}
		}
		results.push_back(students);
		cin >> studentCount;
		courseCounts.clear();
	}
	for (int result : results) {
		cout << result << endl;
	}

	return 0;
}