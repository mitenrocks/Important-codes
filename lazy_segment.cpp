//Code copied: http://codeforces.com/contest/895/submission/32690864
#include<bits/stdc++.h>
using namespace std;
#define pi pair<ll,ll>
#define fr freopen("in.txt","r",stdin)
#define pb push_back
#define rep(i,n) for(int i=0;i<n;i++)
#define frep(i,n) for(int i=1;i<=n;i++)
#define ll long long
#define f first
#define s second

double lazym[400011];
double lazya[400011];
double tree[400011];
ll a[100011];
struct node
{   
    int l,r,id;
    node(){}
    node(int _l,int _r,int _id) {
        l = _l;
        r = _r;
        id = _id;
        lazy_update();
    }
    node left() {
        return node(l,(l+r)/2,2*id);
    }
    node right() {
        return node((l+r)/2+1,r,2*id+1);
    }
    void lazy_update() {
        tree[id] = tree[id] * lazym[id] + lazya[id]*(r-l+1);
        if(l!=r) {
            lazym[2*id] *= lazym[id];
            lazym[2*id+1] *= lazym[id];

            lazya[2*id] *= lazym[id];
            lazya[2*id+1] *= lazym[id];
            
            lazya[2*id] += lazya[id];
            lazya[2*id+1] += lazya[id];
            
        }
        lazym[id] = 1;
        lazya[id] = 0;
    }
    void update(int s, int e, double mv, double av) {
        if(s<=l and r<=e) {
            lazym[id] *= mv;
            lazya[id] *= mv;
            lazya[id] += av;
            lazy_update();
            return;
        }
        if(r<s or e<l) return;

        left().update(s,e,mv,av);
        right().update(s,e,mv,av);
        tree[id] = tree[2*id]+tree[2*id+1];
    }

    double query(int s,int e) {
        if(r<s or e<l) return 0;
        if(s<=l and r<=e) return tree[id];
        return left().query(s,e)+right().query(s,e);
    }

    void build() {
        if(l==r) {
            tree[id] = a[l];
            lazym[id] = 1;
            lazya[id] = 0;
            return;
        }
        left().build();
        right().build();
        tree[id] = tree[2*id]+tree[2*id+1];
        lazym[id] = 1;
        lazya[id] = 0;
    }
};
int main() {
    int n,q,l,r,l1,r1,l2,r2,t;
    cin >> n >> q;
    for(int i=1;i<=n;i++) {
        cin >> a[i];
    }
    node stree = node(1,n,1);
    stree.build();

    while(q--) {
        cin >> t;
        if(t==1) {
            cin >> l1 >> r1 >> l2 >> r2;
            double s2 = stree.query(l2,r2);
            double s1 = stree.query(l1,r1);
            s2/=(r2-l2+1);
            s1/=(r1-l1+1);
            

            double a1 = r1-l1;
            double a2 = r2-l2;
            a1/=(r1-l1+1);
            a2/=(r2-l2+1);

            stree.update(l1,r1,a1,s2*(1-a1));
            stree.update(l2,r2,a2,s1*(1-a2));
        }
        else{
            cin >> l >> r;
            cout << setprecision(10) << fixed << stree.query(l,r) << "\n";
        }
    }
}
