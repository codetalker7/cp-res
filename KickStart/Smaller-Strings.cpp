
/*
	 template by: codetalker7
	 editor: sublime text 3
	 file name: Smaller-Strings
	 date created: 2021-05-23 16:55:16
	 problem link: https://codingcompetitions.withgoogle.com/kickstart/round/0000000000435c44/00000000007ebe5e
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

//macros
/*
	ssz refers to the signed size of an STL structure, because .size() function
	returns an unsigned integer
*/
#define ssz(x) (int)x.size()

//some useful algos
template <class T> T mceil(T a, T b){return (a % b == 0) ? a/b : a/b + 1;}
template <class T> T expo(T base , T exp , T mod){T res = 1;base = base % mod;while (exp > 0){if (exp & 1)res = (res*base) % mod;exp = exp>>1;base = (base*base) % mod;}return res;}
template <class T> ll maxpower(T a , T b){ll ans = 0;while(a > 0 && a % b == 0){ans++;a /= b;}return ans;}
template <class T> T extgcd(T a, T b , T &x , T &y) {x = 1, y = 0;T x1 = 0, y1 = 1, a1 = a, b1 = b; while (b1) { T q = a1 / b1; tie(x, x1) = make_tuple(x1, x - q * x1); tie(y, y1) = make_tuple(y1, y - q * y1); tie(a1, b1) = make_tuple(b1, a1 - q * b1);}return a1;}
template <class T> T modinv (T a , T m , T &x , T &y){T g = extgcd(a , m , x , y); if (g != 1) cerr << "Division by zero!"; else x = (x % m + m) % m; return x;}
template <class T> T signed_floor(T a , T b){if (a >= 0 && b >= 0) return a/b; else if (a < 0 & b < 0) return (-a)/(-b); else if (a < 0 & b >= 0){if (a % b == 0) return -((-a)/b); else return -((-a)/b) - 1;} else if (a >= 0 && b < 0){if(a % b == 0) return -(a/(-b)); else return -(a/(-b)) - 1;}}
template <class T> pair<T,T> log_base_2(T n){T temp = 1 , k = 0; while(temp <= n){temp <<= 1; k++;} temp >>= 1; k--; return {k , temp};}
//define global variables here
string S;
vll is_palindrome;

ll strictly_less(ll i , ll j , ll K){
    ll lesser_usable = min(K , (ll)(S[i] - 'a'));
    if (i == j){
        return lesser_usable % MOD;
    }
    ll final_ans = 0;
    ll mid = (j - i + 1) / 2;

    if ((j - i + 1) % 2 == 0){  
        final_ans = (final_ans + (lesser_usable % MOD) * expo(K , mid - 1 , MOD) + MOD) % MOD; 
    }
    else {
        final_ans = (final_ans + (lesser_usable % MOD) * expo(K , mid , MOD) + MOD) % MOD;
    }
    // now we fix the i and j coordinates to be S[i]
    if (i + 1 <= j - 1){
        if (S[j] <= S[i])
            final_ans = (final_ans + strictly_less(i + 1 , j - 1 , K) + MOD) % MOD;
        else {
            if (is_palindrome[i + 1])
                final_ans = (final_ans + 1 + strictly_less(i + 1 , j - 1 , K) + MOD) % MOD;
            else 
                final_ans = (final_ans + strictly_less(i + 1 , j - 1 , K) + MOD) % MOD;
        }
    }
    else {  
        if (S[j] > S[i])
            final_ans = (final_ans + 1 + MOD) % MOD;
    }
    return final_ans;
}

void palindrome_check(){
    ll flag = 1;
    ll i , j;
    if (ssz(S) % 2 == 0){
        i = ssz(S)/2 - 1; 
        j = i + 1;
    }
    else {
        i = ssz(S)/2;
        j = i;
    }   
    while (i >= 0){
        if (S[i] != S[j])
            flag = 0;
        is_palindrome[i] = flag;
        i--;
        j++;
    }
}

void solve(ll mcase){
    ll N , K;
    cin >> N >> K;

    cin >> S;
    is_palindrome.assign(N , 0);

    //setting is_palindrome
    palindrome_check();

    ll ans = strictly_less(0 , N - 1 , K);
    //if S is a palindrome
    cout << "Case #" << mcase << ": " << ans << "\n";  
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
