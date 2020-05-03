/*
 * we use segment tree , we implement it using pointers so we only save information about a node when we need it which save a lot of memory & time
 * every node will save the following informations about the range l , r : the sum of di in the interval , consider that the train will start at l what is the highest elevation the train will achieve in the interval 
 * to answer the query we use something similar to  finding the k'th element in an array using a binary tree
*/ 
#define fast ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <bits/stdc++.h>
using namespace std;
#define sqr 547
#define mp make_pair
#define mid (l+r)/2
#define pb push_back
#define ppb pop_back
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound
#define ins insert
#define era erase
#define C continue
#define mem(dp,i) memset(dp,i,sizeof(dp))
#define mset multiset
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef short int si;
typedef long double ld;
typedef pair<int,int> pi;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pi> vpi;
typedef vector<pll> vpll;
const ll inf=1e18;
const ll mod=1e9+7;
const ld pai=acos(-1);
int n ;
struct NODE {
	int mx , sum , lzy , yes , sz ;
	NODE *left , *right ;
	NODE () {
		mx = sum = lzy = yes = sz = 0;
		left = right = NULL ;
	}
} *root = new NODE ;
void open ( NODE *node ) {
	if ( node ->sz  > 1 && node -> left == NULL ) {
		node -> left = new NODE ;
		node -> right= new NODE ;
		int SZ = node-> sz ;
		node -> right-> sz = SZ / 2 ;
		node -> left -> sz = SZ - node -> right -> sz ;
	}
}
void lzyUPD ( NODE *node ) {
	open ( node ) ;
	if ( node -> yes && node -> right != NULL ) {
		node -> left -> lzy = node -> right -> lzy = node -> lzy ;
		node -> left -> mx = node -> left -> sum = node -> left -> sz * node -> lzy ;
		node -> right-> mx = node ->right -> sum = node ->right -> sz * node -> lzy ;
		node -> left -> yes = node -> right -> yes = 1 ;
	}
	node -> yes = 0 ;
}
void upd ( NODE *node , int l , int r , int s , int e , int x ) {
	lzyUPD ( node ) ;
	if ( s > r || e < l ) return ;
	if ( s <= l && e >= r ) {
		node -> lzy = x ;
		node -> yes = 1 ;
		node -> sum = node -> mx = node -> sz * x ;
		lzyUPD ( node ) ;
		return ;
	}
	upd ( node -> left , l , mid , s , e , x ) ;
	upd ( node -> right, mid+1 , r , s , e , x ) ;
	node -> sum = node -> left -> sum + node -> right -> sum ;
	node -> mx  = max ( node -> left -> mx , node -> left -> sum + node -> right -> mx ) ;
}
int query ( NODE *node , int l , int r , int h ) {
	lzyUPD ( node ) ;
	if ( l == r ) return l ;
	if ( node -> left -> mx > h ) return query ( node -> left , l , mid , h ) ;
	else return query ( node -> right , mid +1 , r , h - node -> left -> sum ) ;
}
int main () {
	cin >> n ;
	root -> sz = n ;
	while ( 1 ) {
		char t ;
		cin >> t ;
		if ( t == 'E' ) exit (0) ;
		if ( t == 'Q' ) {
			int h ; cin >> h ;
			if ( root -> mx <= h ) cout << n << endl ;
			else cout << query ( root , 0 , n - 1 , h ) << endl ; 
		}
		if ( t == 'I' ) {
			int l , r , x ;
			cin >> l >> r >> x ;
			l -- , r -- ;
			upd ( root , 0 , n - 1 , l , r , x ) ;
		}
	}
}
