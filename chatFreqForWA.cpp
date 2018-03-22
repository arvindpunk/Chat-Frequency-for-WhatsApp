//TO-DO: Date ranges
//TO-DO: Graphs - weekly, bi-weekly, monthly, yearly etc.

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <regex>
#include <algorithm>
#include <string>
using namespace std;
 
#define CASES int t;cin>>t;while(t--)
#define REP(i, val, b) for (int i = val; i < b; ++i)
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);

bool pairSort(pair<int, string> A, pair<int, string> B) {
	return A.first > B.first;
}

int main() {
	fastio
	fstream fchat, fout;
	map<string, int> F;
	fchat.open("chat.txt", fstream::in);
	string str;
	int limit = 100000;
	int count = 0;
	string pattern = "\\d{2}/\\d{2}/\\d{2},\\s\\d{2}:\\d{2}\\s-\\s(.*?):";
	regex rgx (pattern);
	smatch m;
	while (getline(fchat, str) && limit) {
		// cout << str;
		if (regex_search(str, m, rgx)) { //current line is not continuation of previous line)
			F[m[1]]++; //name of person
		}
		limit--;
	}
	cout << "SORTED BY NAME" << endl;
	for (map<string, int>::iterator it = F.begin(); it!=F.end(); it++) {
		cout << it->first << ':' << ' ' << it->second << endl;
	}
	cout << endl;
	cout << "SORTED BY MESSAGE COUNT" << endl;
	vector< pair<int, string> > A;
	for (map<string, int>::iterator it = F.begin(); it!=F.end(); it++) {
		A.push_back(make_pair(it->second, it->first));	
	}
	sort(A.begin(), A.end(), pairSort);
	fout.open("output.txt", fstream::out);
	REP(i,0,A.size()) {
		cout << A[i].second << ':' << ' ' << A[i].first << endl;	//outputs to console
		fout << A[i].second << ':' << ' ' << A[i].first << endl;	//outputs to file
	}
	fout.close();
	fchat.close();
	return 0;
}