% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/fls.R
\docType{package}
\name{fls}
\alias{fls}
\alias{fls-package}
\title{Fitting Time-Varying Linear Models via FLS}
\usage{
fls(X, y, mu = 1, smooth = TRUE)
}
\arguments{
\item{X}{design matrix of dimensuin \eqn{n * K}.}

\item{y}{vector of observations of length \eqn{n}.}

\item{mu}{parameter controling relative weight of sum of dynamic errors (\eqn{r_D^2}) vs sums of squared residual measurement errors (\eqn{r_M^2}).}

\item{smooth}{logical. If TRUE, a smoothed coefficients are provided.}
}
\value{
Returns object of class "fls". An object of class "fls" is a list containing the following components:
\describe{
\item{coefficients}{A \eqn{n * K} matrix coefficient estimates.}
\item{fitted.values}{the fitted mean values.}
\item{r_D}{sum of dynamic errors.}
\item{r_M}{sum of squared residual measurement errors.}
}
}
\description{
\eqn{fls} is used to fit Time-Varying Linear Regression via Flexible least squares (FLS) as discribed in Kalaba and Tesfatsion (1989).
}
\references{
\insertRef{KALABA19891215}{fls}
}
