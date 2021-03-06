const int BASE[12] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

bool check(const long long &prime, const long long &base) {
	long long number = prime - 1;
	for (; ~number & 1; number >>= 1);
	long long result = power_mod(base, number, prime);
	for (; number != prime - 1 && result != 1 && result != prime - 1; number <<= 1) {
		result = multiply_mod(result, result, prime);
	}
	return result == prime - 1 || (number & 1) == 1;
}

bool miller_rabin(const long long &number) {
	if (number < 2) {
		return false;
	}
	if (number < 4) {
		return true;
	}
	if (~number & 1) {
		return false;
	}
	for (int i = 0; i < 12 && BASE[i] < number; ++i) {
		if (!check(number, BASE[i])) {
			return false;
		}
	}
	return true;
}
