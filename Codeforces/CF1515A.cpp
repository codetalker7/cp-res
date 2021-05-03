
/*
	 template by: codetalker7
	 editor: sublime text 3
	 file name: CF1515
	 date created: 2021-05-02 20:12:00
*/
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<stack>
#include<unordered_set>
#include<cmath>
#include<numeric>
#include<iterator>
#include<set>
#include<unordered_map>
#include<map>
#include<queue>
#include<cstring>
#include<stdio.h>
#include<fstream>
#include<iomanip>
#include<functional>
#include<bitset>
#include<chrono>
#include<climits>
#include<assert.h>
using namespace std;

//type declarations
using ll = long long int;
using ull = unsigned long long int;
using vint = vector<int>;
using vll = vector<ll>;
using vch = vector<char>;
using vs = vector<string>;
using sll = set<ll>;
using msll = multiset<ll>;
using ldb = long double;

//constants
const ll MOD = 1000000007;
const ll INF = 1e18;
const int INFINT = 1e9 + 5;
const ldb PI = 3.14159265359;

//some useful algos
template <class T> T mceil(T a, T b){return (a % b == 0) ? a/b : a/b + 1;}
template <class T> T expo(T base , T exp , T mod){T res = 1;base = base % mod;while (exp > 0){if (exp & 1)res = (res*base) % mod;exp = exp>>1;base = (base*base) % mod;}return res;}
template <class T> ll maxpower(T a , T b){ll ans = 0;while(a > 0 && a % b == 0){ans++;a /= b;}return ans;}
template <class T> T extgcd(T a, T b , T &x , T &y) {x = 1, y = 0;T x1 = 0, y1 = 1, a1 = a, b1 = b; while (b1) { T q = a1 / b1; tie(x, x1) = make_tuple(x1, x - q * x1); tie(y, y1) = make_tuple(y1, y - q * y1); tie(a1, b1) = make_tuple(b1, a1 - q * b1);}return a1;}
template <class T> T modinv (T a , T m , T &x , T &y){T g = extgcd(a , m , x , y); if (g != 1) cerr << "Division by zero!"; else x = (x % m + m) % m; return x;}
template <class T> T signed_floor(T a , T b){if (a >= 0 && b >= 0) return a/b; else if (a < 0 & b < 0) return (-a)/(-b); else if (a < 0 & b >= 0){if (a % b == 0) return -((-a)/b); else return -((-a)/b) - 1;} else if (a >= 0 && b < 0){if(a % b == 0) return -(a/(-b)); else return -(a/(-b)) - 1;}}
//define global variables here

void solve(ll mcase){
	ll n , x;
	cin >> n >> x;

	vll w(n);
	for (ll i = 0; i < n; i++)
		cin >> w[i];

	//sorting the weights
	sort(w.begin() , w.end());

	//checking if sum of weights = x
	ll sum = 0;
	for (ll i = 0; i < n; i++)
		sum += w[i];
	if (sum == x){
		cout << "NO\n";
		return;
	}
	else if (sum < x){
		cout << "YES\n";
		for (ll i = 0; i < n; i++)
			cout << w[i] << " ";
		cout << "\n";
		return;
	}
	else{
		//k is the largest integer for which sum w_i <= x
		ll temp_sum = 0 , k;
		for (k = 0; k < n; k++){
			temp_sum += w[k];
			if (temp_sum > x)
				break;
		}
		temp_sum = temp_sum - w[k];
		k--;

		if (k == -1){
			cout << "YES\n";
			for (ll i = 0; i < n; i++)
				cout << w[i] << " ";
			cout << "\n";
			return;
		}
		if (temp_sum < x){
			cout << "YES\n";
			for (ll i = 0; i < n; i++)
				cout << w[i] << " ";
			cout << "\n";
			return;
		}	
		else{
			cout << "YES\n";
			for (ll i = 0; i < n; i++){
				if (i == k)
					cout << w[i + 1] << " ";
				else if (i == k + 1)
					cout << w[i - 1] << " ";
				else 
					cout << w[i] << " ";
			}
			cout << "\n";
			return;
		}
	}
}

//main function
int main(){
    //faster io
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

/*
    if there is an online judge, we use the
    standard io streams. Otherwise, we use custom
    io files.
*/
#ifndef ONLINE_JUDGE
    //works in codechef and codeforces
    FILE* inp = freopen("input.txt", "r" , stdin);
    FILE* err = freopen("error.txt", "w" , stderr);
    FILE* out = freopen("output.txt", "w" , stdout);
#endif

    //for testcases, use the below format
    
    ll t , mcase = 1; //testcases
    cin >> t;
    while(t > 0){
    	solve(mcase); //write a separate solve function
    	t--;
    	mcase++;
    }
    

    cerr << "time taken : " << (float)clock() / CLOCKS_PER_SEC << "seconds" << "\n";
    return 0;
}
