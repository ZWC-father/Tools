#include<bits/stdc++.h>
#define W 8
#define carry 100000000
#define re register
using namespace std;
typedef long long ll;
FILE* file;
struct bign {
	vector<ll>p;
	bool sign; // 0 for positive and 1 for negetive
	bign() {
		clean();
	}
	bign(ll k) {
		clean();
		sign = (k < 0 ? 1 : 0);
		k = (sign ? -k : k);
		while (k)p.push_back(k % carry), k /= carry;
		if (p.empty())p.push_back(0);
	}
	void ofs() {
		if (sign)fprintf(file, "-");
		fprintf(file, "%lld", p[p.size() - 1]);
		for (re int i = p.size() - 2, num; i >= 0; i--) {
			num = (p[i] ? W - (int)log10(p[i]) - 1 : W - 1);
			while (num--)fprintf(file, "0");
			fprintf(file, "%lld", p[i]);
		}
	}
	void clean() {
		p.clear(), sign = 0;
	}
};
const bign one = bign(1);
bign tmp;

inline bign operator * (bign &a, bign &b) {
	bign c;
	int x, la = a.p.size(), lb = b.p.size(), lc = la + lb - 1;
	for (re int i = 0; i <= lc; i++)c.p.push_back(0);
	for (re int i = 0; i < la; i++) {
		for (re int j = 0; j < lb; j++) {
			x = i + j;
			c.p[x] += a.p[i] * b.p[j];
			c.p[x + 1] += c.p[x] / carry;
			c.p[x] %= carry;
		}
	}
	c.sign = b.sign ^ a.sign;
	while (!c.p[lc])c.p.pop_back(), lc--;
	if (c.p.empty())c.p.push_back(0), c.sign = 0;
	return c;
}

bign qpow(ll x, ll n) {
	if (!n) {
		printf("Rank: %lld\n", n);
		return one;
	}
	if (n & 1) {
		bign t;
		t = qpow(x, n - 1);
		printf("Rank: %lld\n", n);
		return t * tmp;
	} else {
		bign t;
		t = qpow(x, n >> 1);
		printf("Rank: %lld\n", n);
		return t * t;
	}
}

int main() {
	ll a, n;
	scanf("%lld%lld", &a, &n);
	tmp = bign(a);
	file = fopen("data.out", "w");
	qpow(a, n).ofs();
	fclose(file);
	printf("Finished!");
	while (1);
	return 0;
}
