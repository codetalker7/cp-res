
/*
	 template by: codetalker7
	 editor: sublime text 3
	 file name: 2.cpp
	 date created: 2021-10-16 17:44:55
	 problem link: https://codingcompetitions.withgoogle.com/kickstart/round/00000000004362d6/00000000008b3a1c
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
#include<random>

//for pbds
//#include <ext/pb_ds/assoc_container.hpp> // Common file
//#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update

//namespaces
using namespace std;

//for pbds
//using namespace __gnu_pbds;

//debugging functions
//var_name is used to give the variable name
void debug(char x){cerr << x;}
void debug(int x){cerr << x;}
void debug(unsigned int x){cerr << x;}
void debug(long long x){cerr << x;}
void debug(unsigned long long x){cerr << x;}
void debug(long double x){cerr << x;}
void debug(double x){cerr << x;}
void debug(string x){cerr << x;}
void debug(float x){cerr << x;}

template <class T, class V> void debug(pair <T, V> x){cerr << "(" << x.first << "," << x.second << ")";}
template <class T> void debug(vector <T> v){cerr<<"[ ";for(T i: v){debug(i);cerr<<" ";}cerr << "]";}
template <class T> void debug(set <T> v){cerr<<"{ ";for(T i: v){debug(i);cerr<<" ";}cerr << "}";}
template <class T> void debug(multiset <T> v){cerr<<"{ ";for(T i: v){debug(i);cerr<<" ";}cerr << "}";}
template <class T, class V> void debug(map <T, V> v){cerr<<"[ ";for(auto i: v){debug(i);cerr<<" ";}cerr << "]";}
//debug with a new line at the end
#define debugln(x) debug(x); cerr << "\n"

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

//ordered set; to be used with pbds
/*using ordered_set = tree<
                        ll,
                        null_type,
                        less<ll>,
                        rb_tree_tag,
                        tree_order_statistics_node_update
                    >;*/

//constants
const ll MOD = 1000000007;
const ll INF = 1e18;
const int INFINT = 1e9 + 5;
const ldb PI = 3.14159265359;

//Logical Operators
#define AND &&
#define OR ||
#define NOT(x) !x

//Bit Manipulation
#define LSB(x) x & (-x) //value of least significant bit

//macros
/*
	ssz refers to the signed size of an STL structure, because .size() function
	returns an unsigned integer
*/
#define ssz(x) (int)x.size()
#define forll(i, start, end, step) for(ll i = start; i <= end; i += step)
#define forllrev(i, start, end, step) for(ll i = start; i >= end; i -= step)
#define fortype(type, i, start, end, step) for(type i = start; i != end; i += step)

//some useful algos
template <class T> T mceil(T a, T b){return (a % b == 0) ? a/b : a/b + 1;}
template <class T> T expo(T base , T exp , T mod){T res = 1;base = base % mod;while (exp > 0){if (exp & 1)res = (res*base) % mod;exp = exp>>1;base = (base*base) % mod;}return res;}
template <class T> ll maxpower(T a , T b){ll ans = 0;while(a > 0 && a % b == 0){ans++;a /= b;}return ans;}
template <class T> T extgcd(T a, T b , T &x , T &y) {x = 1, y = 0;T x1 = 0, y1 = 1, a1 = a, b1 = b; while (b1) { T q = a1 / b1; tie(x, x1) = make_tuple(x1, x - q * x1); tie(y, y1) = make_tuple(y1, y - q * y1); tie(a1, b1) = make_tuple(b1, a1 - q * b1);}return a1;}
template <class T> T modinv (T a , T m , T &x , T &y){T g = extgcd(a , m , x , y); if (g != 1) cerr << "Division by zero!"; else x = (x % m + m) % m; return x;}
template <class T> T signed_floor(T a , T b){if (a >= 0 && b >= 0) return a/b; else if (a < 0 & b < 0) return (-a)/(-b); else if (a < 0 & b >= 0){if (a % b == 0) return -((-a)/b); else return -((-a)/b) - 1;} else if (a >= 0 && b < 0){if(a % b == 0) return -(a/(-b)); else return -(a/(-b)) - 1;}}
template <class T> pair<T,T> log_base_2(T n){T temp = 1 , k = 0; while(temp <= n){temp <<= 1; k++;} temp >>= 1; k--; return {k , temp};}
//define global variables here

void solve(ll mcase){
    ll K;
    scanf("%lld", &K);

    vll xs(1, 0), Xs(1, 0), ys(1, 0), Ys(1, 0); 
    vll prefx(1, 0), prefX(1, 0), prefy(1, 0), prefY(1, 0); 

    //solve the problem independently for X and Y
    forll(i, 1, K, 1){
        ll x, X, y, Y;
        scanf("%lld %lld %lld %lld", &x, &y, &X, &Y);

        xs.push_back(x);
        Xs.push_back(X);
        ys.push_back(y);
        Ys.push_back(Y);

        //we know that x < X and y < Y
    }

    //sort them all
    sort(xs.begin() + 1, xs.end());
    sort(Xs.begin() + 1, Xs.end());
    sort(ys.begin() + 1, ys.end());
    sort(Ys.begin() + 1, Ys.end());

    //setting the prefix sums
    forll(i, 1, K, 1){
        prefx.push_back(prefx[i - 1] + xs[i]);
        prefX.push_back(prefX[i - 1] + Xs[i]);
        prefy.push_back(prefy[i - 1] + ys[i]);
        prefY.push_back(prefY[i - 1] + Ys[i]);
    }

    ll xcost = INF, xbest = INF;

    //trying xs
    forll(i, 1, K, 1){
        //try xs[i]
        ll x = xs[i];

        //find last position X < x in XS 
        ll lo = 1, hi = K, mid;
        ll flag = 0;
        while (lo <= hi){
            mid = lo + (hi - lo + 1)/2;
            if (Xs[mid] < x){
                if (lo == mid){
                    flag = 1;
                    break;
                }
                else
                    lo = mid;
            }
            else{
                hi = mid - 1;
            }
        }
        //mid is the largest index such that Xs[mid] < x
        //take prefix sum of Xs from 1 to mid
        //take prefix sum of xs from i + 1 to K
        ll curr_cost = 0;
        if (flag == 0){
            curr_cost = prefx[K] - prefx[i] - (K - i)*x;
            if (curr_cost < xcost){
                xcost = curr_cost;
                xbest = x;
            }
            else if (curr_cost == xcost AND x < xbest){
                xbest = x;
            }
        }
        else{
            //flag is not 0, hence mid is something
            curr_cost = (prefx[K] - prefx[i] - (K - i)*x) + (mid*x- prefX[mid]);
            if (curr_cost < xcost){
                xcost = curr_cost;
                xbest = x;
            }
            else if (curr_cost == xcost AND x < xbest){
                xbest = x;
            }
        }
        debugln(curr_cost);
    }

    cerr << "\n";

    //trying Xs 
    forll(i, 1, K, 1){
        //try Xs[i]
        ll X = Xs[i];

        //find first position x > X in xS 
        ll lo = 1, hi = K, mid;
        ll flag = 0;
        while (lo <= hi){
            mid = lo + (hi - lo)/2;
            if (xs[mid] > X){
                if (lo == mid){
                    flag = 1;
                    break;
                }
                else
                    hi = mid;
            }
            else{
                lo = mid + 1;
            }
        }
        //mid is the smallest index such that xs[mid] > X
        //take prefix sum of Xs from 1 to i - 1
        //take prefix sum of xs from mid to K
        ll curr_cost = 0;
        if (flag == 0){
            curr_cost = (i - 1)*X - prefX[i - 1];
            if (curr_cost < xcost){
                xcost = curr_cost;
                xbest = X;
            }
            else if (curr_cost == xcost AND X < xbest){
                xbest = X;
            }
        }
        else{
            //flag == 1, so mid is something
            curr_cost = ((i - 1)*X - prefX[i - 1]) + (prefx[K] - prefx[mid - 1] - (K - mid + 1)*X);
            if (curr_cost < xcost){
                xcost = curr_cost;
                xbest = X;
            }
            else if (curr_cost == xcost AND X < xbest){
                xbest = X;
            }
        }
        debugln(curr_cost);
    }

    ll ycost = INF, ybest = INF;

    //trying ys
    forll(i, 1, K, 1){
        //try xs[i]
        ll y = ys[i];

        //find last position Y < y in XS 
        ll lo = 1, hi = K, mid;
        ll flag = 0;
        while (lo <= hi){
            mid = lo + (hi - lo + 1)/2;
            if (Ys[mid] < y){
                if (lo == mid){
                    flag = 1;
                    break;
                }
                else
                    lo = mid;
            }
            else{
                hi = mid - 1;
            }
        }
        //mid is the largest index such that Ys[mid] < y
        //take prefix sum of Ys from 1 to mid
        //take prefix sum of ys from i + 1 to K
        ll curr_cost = 0;
        if (flag == 0){
            curr_cost = prefy[K] - prefy[i] - (K - i)*y;
            if (curr_cost < ycost){
                ycost = curr_cost;
                ybest = y;
            }
            else if (curr_cost == ycost AND y < ybest){
                ybest = y;
            }
        }
        else{
            //flag is not 0, hence mid is something
            curr_cost = (prefy[K] - prefy[i] - (K - i)*y) + (mid*y- prefY[mid]);
            if (curr_cost < ycost){
                ycost = curr_cost;
                ybest = y;
            }
            else if (curr_cost == ycost AND y < ybest){
                ybest = y;
            }
        }
    }

    //trying Ys 
    forll(i, 1, K, 1){
        //try Ys[i]
        ll Y = Ys[i];

        //find first position y > Y in yS 
        ll lo = 1, hi = K, mid;
        ll flag = 0;
        while (lo <= hi){
            mid = lo + (hi - lo)/2;
            if (ys[mid] > Y){
                if (lo == mid){
                    flag = 1;
                    break;
                }
                else
                    hi = mid;
            }
            else{
                lo = mid + 1;
            }
        }
        //mid is the smallest index such that ys[mid] > Y
        //take prefix sum of Ys from 1 to i - 1
        //take prefix sum of ys from mid to K
        ll curr_cost = 0;
        if (flag == 0){
            curr_cost = (i - 1)*Y - prefY[i - 1];
            if (curr_cost < ycost){
                ycost = curr_cost;
                ybest = Y;
            }
            else if (curr_cost == ycost AND Y < ybest){
                ybest = Y;
            }
        }
        else{
            //flag == 1, so mid is something
            curr_cost = ((i - 1)*Y - prefY[i - 1]) + (prefy[K] - prefy[mid - 1] - (K - mid + 1)*Y);
            if (curr_cost < ycost){
                ycost = curr_cost;
                ybest = Y;
            }
            else if (curr_cost == ycost AND Y < ybest){
                ybest = Y;
            }
        }
    }

    printf("%lld %lld\n", xbest, ybest);
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
    /*
        Uncomment the next line to use the
        Mersenne Twister Random Number 
        Generator, with the current system 
        time as the seed. 
        The first line is for 32-bit
        Second line is for 64-bit
    */
    //mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    //mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());


    //for testcases, use the below format
    
    ll t , mcase = 1; //testcases
    scanf("%lld\n", &t);
    while(t > 0){
        printf("Case #%lld: ", mcase);
    	solve(mcase); //write a separate solve function
    	t--;
    	mcase++;
    }
    
    cerr << "time taken : " << (float)clock() / CLOCKS_PER_SEC << "seconds" << "\n";
    return 0;
}
