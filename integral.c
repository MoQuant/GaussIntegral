#include <stdio.h>
#include <math.h>

double FX(double x, double y, double rho)
{
  double factor = 1.0/(2.0*M_PI*sqrt(1 - pow(rho, 2)));
  double exponent = (pow(x, 2) - 2*x*y*rho + pow(y, 2))/(2.0*(1 - pow(rho, 2)));
  return factor*exp(-exponent);
}

int main()
{
  int n = 101;

  double X[n][n];
  double Y[n][n];
  double S[n][n];

  double rho = 0.3;

  double z1 = 2, z2 = 2;
  double y1 = -2, y2 = -2;

  double dZ1 = (z1 - y1)/(n - 1);
  double dZ2 = (z2 - y2)/(n - 1);

  for(int i = 0; i < n; ++i){
    for(int j = 0; j < n; ++j){
      X[i][j] = y1 + i*dZ1;
      Y[i][j] = y2 + j*dZ2;
    }
  }

  for(int i = 0; i < n; ++i){
    for(int j = 0; j < n; ++j){
      if(i == 0 || i == n - 1){
        if(j == 0 || j == n - 1){
          S[i][j] = 1.0;
        } else if(j % 2 == 0){
          S[i][j] = 2.0;
        } else {
          S[i][j] = 4.0;
        }
      } else if(i % 2 == 0){
        if(j == 0 || j == n - 1){
          S[i][j] = 2.0;
        } else if(j % 2 == 0){
          S[i][j] = 4.0;
        } else {
          S[i][j] = 8.0;
        }
      } else {
        if(j == 0 || j == n - 1){
          S[i][j] = 4.0;
        } else if(j % 2 == 0){
          S[i][j] = 8.0;
        } else {
          S[i][j] = 16.0;
        }
      }
    }
  }

  double total_prob = 0.0;
  for(int i = 0; i < n; ++i){
    for(int j = 0; j < n; ++j){
      total_prob += S[i][j]*FX(X[i][j], Y[i][j], rho);
    }
  }

  total_prob = total_prob*(dZ1*dZ2)/9.0;

  printf("%f\n", total_prob);

  return 0;
}
