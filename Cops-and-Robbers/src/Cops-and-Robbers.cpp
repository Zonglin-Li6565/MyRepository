//============================================================================
// Name        : Cops-and-Robbers.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <cstdio>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

struct person {
public:
	person(int x, int y) {
		x_ = x;
		y_ = y;
	}
	void SetNewOrigin(int x, int y) {
		x_ -= x;
		y_ -= y;
	}
	double GetAngle() {
		if(x_ == 0) return std::numeric_limits<double>::max();
		return (y_ + 0.0) / x_;
	}
	int x_, y_;
};

bool operator<(person first_, person second_) {
	double _firstangle = first_.GetAngle();
	double _secondangle = second_.GetAngle();
	double _max = std::numeric_limits<double>::max();
	if(_firstangle == _max && _secondangle == _max) {
		return first_.y_ > second_.y_;
	}
	if(_firstangle == _secondangle)
		return first_.x_ < second_.x_;
	return first_.GetAngle() < second_.GetAngle();
}

bool operator==(person first_, person second_) {
	return (first_.x_ == second_.x_) && (first_.y_ == second_.y_);
}

int ccw(const person& _a, const person& _b, const person& _c) {
	int x1 = _b.x_ - _a.x_;
	int x2 = _c.x_ - _b.x_;
	int y1 = _b.y_ - _a.y_;
	int y2 = _c.y_ -_b.y_;
	return x1 * y2 - x2 * y1;
}

vector<person>& convexhull(vector<person>& people, vector<person>& newperson) {
	if(people.size() < 1) return newperson;
	int newx = std::numeric_limits<int>::max(), newy = std::numeric_limits<int>::max();
	//finding the left bottom most point.
	for(int i = 0; i < people.size(); i++) {
		person _person = people[i];
		if(_person.x_ < newx) {
			newx = _person.x_;
			newy = _person.y_;
		}else
		if(_person.x_ == newx) {
			if(_person.y_ < newy) newy = _person.y_;
		}
	}
	for(int i = 0; i < people.size(); i++) {
		people[i].SetNewOrigin(newx, newy);
	}
	std::sort(people.begin(), people.end());
	people.insert(people.begin(), people.back());
	newperson.push_back(people[0]);
	newperson.push_back(people[1]);
	for(int i = 2; i < people.size(); i++) {
		person _a = newperson[newperson.size() - 2];
		person _b = newperson[newperson.size() - 1];
		person _c = people[i];
		if(ccw(_a, _b, _c) < 0) {
			newperson.pop_back();
			i --;
			continue;
		}else{
			newperson.push_back(_c);
		}
	}
	for(int i = 0; i < newperson.size(); i++) {
		newperson[i].SetNewOrigin(-newx, -newy);
	}
	return newperson;
}

bool checkinside(vector<person>& hull, const person& citizen) {
	bool in_tran = false;
	if(hull.size() == 0) return false;
	if(hull.size() == 2) return hull[0] == citizen;
	for(int i = 0; i < hull.size() - 1; i++) {
		int crop_ = ccw(hull[i], hull[i + 1], citizen);
		if(crop_ == 0) {
			int range_ = hull[i + 1].x_ - hull[i].x_;
			int delta_ = citizen.x_ - hull[i].x_;
			if(range_ == 0) {
				range_ = hull[i + 1].y_ - hull[i].y_;
				delta_ = citizen.y_ - hull[i].y_;
			}
			double ratio_ = (0.0 + delta_) / range_;
			if(ratio_ >= 0 && ratio_ <= 1) 	//on boundary
				return true;
		}
		if(crop_ > 0) {
			in_tran = true;
		}
		if(crop_ < 0) {
			return false;
		}
	}
	return in_tran;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int nums[3];
	int count = 1;
	bool first = true, safe, rob;
	while (scanf("%d%d%d", &nums[0], &nums[1], &nums[2])) {
		if(nums[0] == nums[1] && nums[1] == nums[2] && nums[2] == 0) break;
		if(first) first = false; else printf("\n");
		safe = nums[0] > 2;
		rob = nums[1] > 2;
		vector<person> cops;
		vector<person> robbers;
		vector<person> citizen;
		for(int i = 0; i < 3; i++) {
			for(int j = 0; j < nums[i]; j++) {
				int x, y;
				bool add = true;
				scanf("%d%d", &x, &y);
				person next(x, y);
				switch(i) {
				case 0: {
					for(int t = 0; t < cops.size(); t++) {
						if (next == cops[t]){
							add = false;
							break;
						}
					}
					if(add) cops.push_back(next);
					break;
				}
				case 1: {
					for(int t = 0; t < robbers.size(); t++) {
						if (next == robbers[t]){
							add = false;
							break;
						}
					}
					if(add) robbers.push_back(next);
					break;
				}
				case 2: {
					if(add) citizen.push_back(next);
					break;
				}
				}
			}
		}
		vector<person> cophull;
		vector<person> robberhull;
		convexhull(cops, cophull);
		convexhull(robbers, robberhull);
		printf("Data set %d:\n", count);
		for(int i = 0; i < citizen.size(); i++) {
			if(checkinside(cophull, citizen[i]) && safe)
				printf("     Citizen at (%d,%d) is safe.\n", citizen[i].x_, citizen[i].y_);
			else
			if(checkinside(robberhull, citizen[i]) && rob)
				printf("     Citizen at (%d,%d) is robbed.\n", citizen[i].x_, citizen[i].y_);
			else
				printf("     Citizen at (%d,%d) is neither.\n", citizen[i].x_, citizen[i].y_);
		}
		count++;
	}
	printf("\n");
	return 0;
}
