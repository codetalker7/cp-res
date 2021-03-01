/*
    template-by: codetalker7
    editor: sublime text 3
    Training-Inoi 2017
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

//define global variables here
vll experience;
vector <vll> dp;
vll blank;
vll c;


void solve(){

}

ll sum_of_digits_cubed(ll x){
    ll ans = 0;
    while (x > 0){
        ans += x % 10;
        x /= 10;
    }
    return ans * ans * ans;
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
    /*
    ll t; //testcases
    cin >> t;
    while(t > 0){
    	solve(); //write a separate solve function
    	t--;
    }
    */
    ll n , S_in;
    cin >> n >> S_in;

    experience.assign(n + 1 , 0);
    for (ll i = 1; i <= n; i++)
        cin >> experience[i];

    //initialising the sequence
    c.push_back(-1);
    for (ll i = 1; i <= n; i++){
        if (i == 1){
            c.push_back(S_in);
            continue;
        }
        else{
            c.push_back(c[i - 1] + sum_of_digits_cubed(c[i - 1]));
        }
    }

    //initialising dp array
    dp.assign(n + 1 , blank);
    for (ll i = 1; i <= n; i++){
        dp[i].assign(n + 1 , 0);
    }

    //solving the dp
    for (ll i = n; i >= 1; i--){
        for (ll j = 1; j <= n; j++){
            if (i == n){
                dp[n][j] = experience[n] * c[j];
                continue;
            }
            if (j > i){
                dp[i][j] = -INF;
                continue;
            }
            else{
                dp[i][j] = max(experience[i]*c[j] + dp[i + 1][j] , dp[i + 1][j + 1]);
            }
        }
    }
    cout << dp[1][1];
    cerr << "time taken : " << (float)clock() / CLOCKS_PER_SEC << "seconds" << "\n";
    return 0;
}
