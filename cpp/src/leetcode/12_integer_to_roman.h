#include <string>

/*
	25
	
	3999


*/


namespace leetcode {

inline std::string intToRomanSubCase(int& num, int power, char oneCh, char fiveCh, char tenCh) {
	std::string result {};
	int one = 1;

	while (power-- > 0) {
		one *= 10;
	}

	int five = one * 5;
	int ten = one * 10;

	while (num >= one) {
		if (num / one == 4) {
			num -= one * 4;
			result.push_back(oneCh);
			result.push_back(fiveCh);
		} else if (num / one == 9) {
			num -= one * 9;
			result.push_back(oneCh);
			result.push_back(tenCh);
		} else if (num >= ten) {
			num -= ten;
			result.push_back(tenCh);
		} else if (num >= five) {
			num -= five;
			result.push_back(fiveCh);
		} else {
			num -= one;
			result.push_back(oneCh);
		}
	}

	return result;
}

inline std::string intToRoman(int num) {
	return
		intToRomanSubCase(num, 2, 'C', 'D', 'M') +
		intToRomanSubCase(num, 1, 'X', 'L', 'C') +
		intToRomanSubCase(num, 0, 'I', 'V', 'X');
}

}
