#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef vector <LL> VL;
typedef vector <VL> VVL;

struct Matrix{
    int n, m;
    VVL a;

    Matrix(){}
    Matrix(int n, int m){
        this->n = n;
        this->m = n;
        this->a.resize(n, VL(m));
    }

    friend Matrix operator*(Matrix &a, Matrix &b){
        Matrix c(a.n, b.m);
        VVL &x = a.a, &y = b.a, &z = c.a;

        for(int i = 0; i < c.n; ++i){
            for(int j = 0; j < c.m; ++j){
                z[i][j] = 0;
                for(int k = 0; k < b.n; ++k){
                    z[i][j] += x[i][k] * y[k][j];
                }
            }
        }
        return c;
    }
};

Matrix pow(Matrix a, int p){
    if(p == 1) return a;
    if(p & 1){
        Matrix b = pow(a, p - 1);
        return a * b;
    }
    
    Matrix c = pow(a, p / 2);
    return c * c;
}

int main(){
    Matrix a(2, 2), b(2, 1);
    a.a[0][0] = a.a[0][1] = a.a[1][0] = 1; a.a[1][1] = 0;
    b.a[0][0] = 1; b.a[1][0] = 0;

    a = pow(a, 5);
    Matrix c = a * b;

    printf("6th: %lld, 5th: %lld\n", c.a[0][0], c.a[1][0]);

    return 0;
}
