/*
    template-by: codetalker7
    editor: sublime text 3
    Codeforces: 1494C (binary search version)
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

//reverses the vector y, assuming indexing in y starts at 1
void reverse_vector(vll &y){
    ll k = y.size() - 1;
    for (ll i = 1; i <= (k + 1)/2; i++){
        //swapping y[i] and y[k - i + 1]
        ll temp = y[i];
        y[i] = y[k - i + 1];
        y[k - i + 1] = temp;
    }
}

//binary search, assuming indexing of range starts at 1
ll bin_search(ll value , vll &range){
    ll lo = 1 , hi = range.size() - 1;

    while(lo <= hi){
        ll mid = lo + (hi - lo)/2;

        if (range[mid] == value)
            return 1;
        if (range[mid] < value)
            lo = mid + 1;
        else
            hi = mid - 1;
    }
    return 0;
}

//indexing of pos starts at 1
ll max_index_h(vll pos , ll bi){
    ll lo = 1 , hi = pos.size() - 1;
    ll mid , flag = 0;
    while(lo <= hi){
        mid = lo + (hi - lo + 1)/2;
        if (pos[mid] < bi + mid - 1){
            if (lo == mid){
                flag = 1;
                break;
            }
            else
                lo = mid;
        }
        else
            hi = mid - 1;
    }
    if (flag == 1)
        return mid;
    else
        return -1;
}

//indexing of spos starts at 1
ll compute_intersection(vll spos , ll I , ll h){
    ll upper = spos[I] + h - 1;
    //get max index J greater than I such that spos[J] <= upper
    ll lo = I , hi = spos.size() - 1 , mid;
    while(lo <= hi){
        mid = lo + (hi - lo + 1)/2;
        if (spos[mid] <= upper){
            if (lo == mid)
                break;
            else
                lo = mid;
        }
        else
            hi = mid - 1;
    }
    //mid now stores the required max index
    return mid - I + 1;
}

//assuming indexing in pos and spos both start at 1
ll get_max_possible(vll &pos , vll &spos){
    //if either of pos or spos is empty, simply return 0
    //since indexing starts at 1, we need to check if size is 1
    if (pos.size() == 1 || spos.size() == 1)
        return 0;
    ll n = pos.size() - 1 , m = spos.size() - 1;

    //prefix[i] for 1 <= i <= n will contain the number of elements in the
    //intersection of {a_i , ..., a_n} and {b_1,...,b_m}
    vll prefix; prefix.assign(n + 1 , 0);
    ll spos_counter = m;
    for (ll i = n; i >= 1; i--){
        if (spos_counter == 0){
            if (i == n)
                prefix[n] = 0;
            else
                prefix[i] = prefix[i + 1];
        }
        while (spos[spos_counter] > pos[i])
            spos_counter--;
        if (spos[spos_counter] == pos[i]){
            if (i == n)
                prefix[n] = 1;
            else
                prefix[i] = 1 + prefix[i + 1];
        }
        else{
            if (i == n)
                prefix[n] = 0;
            else
                prefix[i] = prefix[i + 1];
        }
    }

    //final answer will be stored in ans
    ll ans = prefix[1] , h = 1 , up = 1;

    //computing the final answer
    for (ll i = 1; i <= m; i++){
        if (spos[i] <= pos[1])
            continue;
        else {
            //computing max index h such that pos[h] < spos[i] + h - 1
            //h will be the number of consecutive blocks when we move
            //box at pos[1] to the position spos[i]
            while (pos[h] < spos[i] + h - 1 && h <= n)
                h++;
            h--;

            //computing intersection of {b_1,...,b_m} and the interval [spos[i] , spos[i] + h - 1]
            while (up < i)
                up++;
            while (up <= m && spos[up] <= spos[i] + h - 1)
                up++;
            up--;

            ll intersec = up - i + 1;
            //adding the above to prefix[h + 1]
            //taking max of ans and this quantity
            if (h == n)
                ans = max(ans , intersec);
            else
                ans = max(ans , intersec + prefix[h + 1]);
        }
    }
    return ans;
}

void solve(){
    ll n , m;
    cin >> n >> m;

    vll pos1 , pos2 , spos1 , spos2;
    pos1.push_back(0); pos2.push_back(0); spos1.push_back(0); spos2.push_back(0);

    //taking the input
    for (ll i = 1; i <= n; i++){
        ll a; cin >> a;
        if (a < 0)
            pos1.push_back(-a);
        else
            pos2.push_back(a);
    }
    for (ll i = 1; i <= m; i++){
        ll a; cin >> a;
        if (a < 0)
            spos1.push_back(-a);
        else
            spos2.push_back(a);
    }

    //reversing spos1 and pos1, since they are in non-increasing order
    reverse_vector(pos1); reverse_vector(spos1);
    //solving the problem separately for pos1 , spos1

    //solving the problem separately for pos2 , spos2

    //combining the solutions and printing
    cout << get_max_possible(pos1 , spos1) + get_max_possible(pos2 , spos2) << "\n";
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

    ll t; //testcases
    cin >> t;
    while(t > 0){
    	solve(); //write a separate solve function
    	t--;
    }

    cerr << "time taken : " << (float)clock() / CLOCKS_PER_SEC << "seconds" << "\n";
    return 0;
}
