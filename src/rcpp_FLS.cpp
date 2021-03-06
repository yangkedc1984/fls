// [[Rcpp::depends(RcppArmadillo)]]
#include <RcppArmadillo.h>
using namespace Rcpp;

//' FLS fit
//'
//' This function is used to fit Time-Varying Linear Regression via Flexible least squares (FLS) as discribed in R. Kalaba and L. Tesfatsion (1989).
//'
//' @param X design matrix of dimensuin \eqn{n * K}.
//' @param y vector of observations of length \eqn{n}.
//' @param mu parameter controling relative weight of sum of dynamic errors (\eqn{r_D^2}) vs sums of squared residual measurement errors (\eqn{r_M^2}).
//' @param smooth logical. If TRUE, a smoothed estimate is provided.
//' @return A \eqn{n * K} matrix coefficient estimates.
//' @references
//' \insertRef{KALABA19891215}{fls}
//'
//' @export
// [[Rcpp::export(fls.fit)]]
arma::mat rcpp_FLS(arma::mat X, arma::vec y, double mu, bool smooth = false) {
  int K = X.n_cols;
  int n = X.n_rows;
  arma::mat Q(K, K, arma::fill::zeros);
  arma::mat B(n, K);
  B.fill(NA_REAL);
  arma::mat I(K, K, arma::fill::eye);
  arma::mat E(n, K, arma::fill::zeros);
  arma::colvec p = arma::zeros<arma::colvec>(K);
  arma::cube M(K, K, n, arma::fill::zeros);

  for(int i = 0; i < n; i++) {
    arma::vec p_ = p + X.row(i).t() * y(i);
    arma::mat Q_ = Q + X.row(i).t() * X.row(i);
    // One step update
    M.slice(i) = mu * arma::inv_sympd(Q_ + mu*I);
    Q = mu * (I - M.slice(i));
    p = M.slice(i) * p_;
    E.row(i) = 1/mu * p.t();
    // Beta estimate
    if(i == n-1) {
      B.row(i) = p_.t() * arma::inv_sympd(Q_);
    }
  }
  if(smooth) {
    for(int i = n-2; i >= 0; i--) {
      B.row(i) = E.row(i) + B.row(i+1) * M.slice(i);
    }
  }
  return(B);
}
