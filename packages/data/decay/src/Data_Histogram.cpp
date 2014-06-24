//---------------------------------------------------------------------------//
//!
//! \file   Data_Histogram.cpp
//! \author CJ Solomon
//! \brief  Histogram
//!
//---------------------------------------------------------------------------//

#include "Data_Histogram.hpp"

namespace data {

Histogram::Histogram() {
  m_uflow = 0.0;
  m_oflow = 0.0;
  m_uflow_err = 0.0;
  m_oflow_err = 0.0;
}

Histogram::Histogram(const double &lo, const double &hi, const int &n, bool islog){
  using namespace std;
  m_uflow = 0.0;
  m_oflow = 0.0;
  m_uflow_err = 0.0;
  m_oflow_err = 0.0;

  if( islog ) {
    double loglo = log10(lo);
    double loghi = log10(hi);
    double step = (loghi-loglo)/n;

    bins.push_back( pow(10,loglo) );
    for(int i=1; i<=n; i++) {
      bins.push_back( pow(10,loglo+i*step) );
      values.push_back( 0 );
      errors.push_back( 0 );
    }
  }
  else {
    double step = (hi-lo)/n;

    bins.push_back( lo );
    for(int i=1; i<=n; i++) {
      bins.push_back( lo+i*step );
      values.push_back( 0 );
      errors.push_back( 0 );
    }
  }
}

Histogram::Histogram(const double &lo, const double &hi, const int &n, 
                     const double& init, bool islog){
  using namespace std;
  m_uflow = 0.0;
  m_oflow = 0.0;
  m_uflow_err = 0.0;
  m_oflow_err = 0.0;

  if( islog ) {
    double loglo = log10(lo);
    double loghi = log10(hi);
    double step = (loghi-loglo)/n;

    bins.push_back( pow(10,loglo) );
    for(int i=1; i<=n; i++) {
      bins.push_back( pow(10,loglo+i*step) );
      values.push_back( init );
      errors.push_back( 0 );
    }
  }
  else {
    double step = (hi-lo)/n;

    bins.push_back( lo );
    for(int i=1; i<=n; i++) {
      bins.push_back( lo+i*step );
      values.push_back( init );
      errors.push_back( 0 );
    }
  }
}

Histogram::Histogram(const std::vector<double> &b) {
  using namespace std;
  Check(b);

  m_uflow = 0.0;
  m_oflow = 0.0;
  m_uflow_err = 0.0;
  m_oflow_err = 0.0;
  bins.insert(bins.end(),b.begin(),b.end());
  values.insert(values.end(),b.size()-1,0);
  errors.insert(errors.end(),b.size()-1,0);
}

Histogram::Histogram(const std::vector<double> &b, const double &init) {
  using namespace std;
  Check(b);

  m_uflow = 0.0;
  m_oflow = 0.0;
  m_uflow_err = 0.0;
  m_oflow_err = 0.0;
  bins.insert(bins.end(),b.begin(),b.end());
  values.insert(values.end(),b.size()-1,init);
  errors.insert(errors.end(),b.size()-1,0);
}

Histogram::Histogram(const std::vector<double> &b, const double &init, const double &ierr) {
  using namespace std;
  Check(b);

  m_uflow = 0.0;
  m_oflow = 0.0;
  m_uflow_err = 0.0;
  m_oflow_err = 0.0;
  bins.insert(bins.end(),b.begin(),b.end());
  values.insert(values.end(),b.size()-1,init);
  errors.insert(errors.end(),b.size()-1,ierr);
}

Histogram::Histogram(const std::vector<double> &b, const std::vector<double> &v) {
  using namespace std;
  assert(b.size()==v.size()+1);
  Check(b);

  m_uflow = 0.0;
  m_oflow = 0.0;
  m_uflow_err = 0.0;
  m_oflow_err = 0.0;
  bins.insert( bins.end(),b.begin(),b.end() );
  values.insert( values.end(),v.begin(),v.end() );
  errors.insert( errors.end(),v.size(),0);
}

Histogram::Histogram(const std::vector<double> &b, const std::vector<double> &v,
                     const std::vector<double> &e) {
  using namespace std;
  assert(b.size()==v.size()+1);
  assert(v.size()==e.size());
  Check(b);

  m_uflow = 0.0;
  m_oflow = 0.0;
  m_uflow_err = 0.0;
  m_oflow_err = 0.0;
  bins.insert( bins.end(),b.begin(),b.end() );
  values.insert( values.end(),v.begin(),v.end() );
  errors.insert( errors.end(),e.begin(),e.end() );
}

double Histogram::MinBin() const {
  return bins.at(0);
}

double Histogram::Bin(const int& b) const {
  return bins.at(b+1);
}

void Histogram::Normalize() {
  double sum = 0.0;

  for(unsigned int i=0; i < values.size(); i++) {
    sum += values[i];
  }

  if( sum > 0.0 ) {
    for(unsigned int i=0; i < values.size(); i++) {
      values[i] /= sum;
      errors[i] /= sum;
    }
  }
}

int Histogram::Search(const double& x) const {
  int retval;
  if( x < bins.front() ) {
    retval = UNDER;
  }
  else if( x > bins.back() ) {
    retval = OVER;
  }
  else {
    int l = 1;
    int u = bins.size()-1;
    int m = (u+l)/2;

    while( l != u ) {
      if( bins[l-1] <= x && x <= bins[m] ){
        u = m;
        m = (u+l-1)/2;
      }
      else {
        l = m+1;
        m = (u+l-1)/2;
      }
    }
    retval = l;
  }
  
  return retval;
}

void Histogram::Check(const std::vector<double> &v) {
  using namespace std;
  for(unsigned int i=1; i<v.size(); i++) {
    assert( v[i-1] < v[i] );
  }
}

void Histogram::Set(const int &b, const double &v) {
  values[b] = v;
}
  
void Histogram::Set(const double &x, const double &v) {
  int bin = Search(x);
  if( bin == UNDER ) {
    m_uflow += v;
  }
  else if( bin == OVER ) {
    m_oflow += v;
  }
  else {
    values[bin-1] = v;
  }
}
  
void Histogram::Set(const int &b, const double &v, const double &e) {
  values[b] = v;
  errors[b] = e;
}
  
void Histogram::Set(const double &x, const double &v, const double &e) {
  int bin = Search(x);
  if( bin == UNDER ) {
    m_uflow += v;
    m_uflow_err += e;
  }
  else if( bin == OVER ) {
    m_oflow += v;
    m_oflow_err += e;
  }
  else {
    values[bin-1] = v;
    errors[bin-1] = e;
  }
}

void Histogram::SetErr(const int &b, const double &e) {
  errors[b] = e;
}
  
void Histogram::SetErr(const double &x, const double &e) {
  int bin = Search(x);
  if( bin == UNDER ) {
    m_uflow_err += e;
  }
  else if( bin == OVER ) {
    m_oflow_err += e;
  }
  else {
    errors[bin-1] = e;
  }
}

unsigned int Histogram::Size() const {
  return values.size();
}

double Histogram::Get(const int &b) const {
  return values.at(b);
}

double Histogram::Get(const double &x) const{
  double retval;
  int bin = Search(x);
  if( bin == UNDER ) {
    retval = m_uflow;
  }
  else if( bin == OVER ) {
    retval = m_oflow;
  }
  else {
    retval = values.at(bin-1);
  }
  return retval;
}

double Histogram::GetErr(const int &b) const{
  return errors.at(b);
}

double Histogram::GetErr(const double &x) const {
  double retval;
  int bin = Search(x);
  if( bin == UNDER ) {
    retval = m_uflow_err;
  }
  else if( bin == OVER ) {
    retval = m_oflow_err;
  }
  else {
    retval = errors.at(bin-1);
  }
  return retval;
}

void Histogram::Convert(const Histogram& h) {
  if( h.bins.size() == 0 )
    return;

  for(unsigned int i=1; i<h.bins.size(); i++) {
    int start = Search(h.bins.at(i-1));
    int end = Search(h.bins.at(i));
    
    if( start == UNDER && end == UNDER ) {
      m_uflow += h.values.at(i-1);
      continue;
    }
    else if( start == OVER && end == OVER ) {
      m_oflow += h.values.at(i-1);
      continue;
    }
    else {
      if( start == UNDER ) {
        m_uflow += h.values.at(i-1) * (bins.front()-h.bins.at(i-1)) / (h.bins.at(i)-h.bins.at(i-1));
        start = 2;
      }

      if( end == OVER ) {
        m_oflow += h.values.at(i-1) * (h.bins.at(i)-bins.back()) / (h.bins.at(i)-h.bins.at(i-1));
        end = bins.size();
      }
    }

    for(int j=start; j<=end; j++) {
      if( j==start && j==end ) {
        values[j-1] += h.values.at(i-1);
      }
      else if ( j==start ) {
        values[j-1] += h.values.at(i-1) * (bins[j]-h.bins.at(i-1)) / (h.bins.at(i)-h.bins.at(i-1));
      }
      else if( j==end ) {
        values[j-1] += h.values.at(i-1) * (h.bins.at(i)-bins[j-1]) / (h.bins.at(i)-h.bins.at(i-1));
      }
      else { 
        values[j-1] += h.values.at(i-1) * (bins[j]-bins[j-1]) / (h.bins.at(i)-h.bins.at(i-1));
      }
    }
  }
}

void Histogram::Clear() {
  for(unsigned int i=0; i<values.size(); i++) {
    values[i] = 0.0;
  }
  for(unsigned int i=0; i<errors.size(); i++) {
    errors[i] = 0.0;
  }
}

std::vector<double> Histogram::GetBins(bool with_min) const {
  std::vector<double> retbins;
  
  unsigned int start = with_min ? 0 : 1;
  for(unsigned int i=start; i<bins.size(); i++) {
    retbins.push_back(bins.at(i));
  }

  return retbins;
}

std::vector<double> Histogram::GetBinCenters() const {
  std::vector<double> retbins;
  
  for(unsigned int i=1; i<bins.size(); i++) {
    retbins.push_back( (bins.at(i)+bins.at(i-1)) / 2.0 );
  }

  return retbins;
}

double Histogram::Sum() const {
  double sum = 0.0;
  
  sum += m_uflow + m_oflow;
  for(unsigned int i=0; i<Size(); i++) {
    sum += Get((int) i);
  }

  return sum;
}

Histogram& Histogram::operator*=(const double& mlt) {
  for(unsigned int i=0; i < values.size(); i++ ) {
    values[i] *= mlt;
    errors[i] *= mlt;
  }
  return *this;
}

Histogram& Histogram::operator/=(const double& div) {
  for(unsigned int i=0; i < values.size(); i++ ) {
    values[i] /= div;
    errors[i] /= div;
  }
  return *this;
}

Histogram& Histogram::operator+=(const Histogram& add) {
  using namespace std;
  assert( bins.size() == add.bins.size() );

  assert( (bins[0] - add.bins[0]) <= 1e-6*bins[0] );
  for(unsigned int i=1; i<bins.size(); i++ ) {
    assert( (bins[i] - add.bins[i])/bins[i] <= 1e-6 );
    values[i-1] += add.values[i-1];
    errors[i-1] = sqrt( pow(errors[i-1],2) + pow(add.errors[i-1],2) );
  }
  return *this;
}

Histogram& Histogram::operator-=(const Histogram& sub) {
  using namespace std;
  assert( bins.size() == sub.bins.size() );

  assert( (bins[0] - sub.bins[0]) <= 1e-6*bins[0] );
  for(unsigned int i=1; i<bins.size(); i++ ) {
    assert( (bins[i] - sub.bins[i])/bins[i] <= 1e-6 );
    values[i-1] -= sub.values[i-1];
    errors[i-1] = sqrt( pow(errors[i-1],2) + pow(sub.errors[i-1],2) );
  }
  return *this;
}

const Histogram operator*(const double& mlt, const Histogram& start) {
  Histogram result(start);
  return result *= mlt;
}
const Histogram operator*(const Histogram& start, const double& mlt) {
  Histogram result(start);
  return result *= mlt;
}

const Histogram operator/(const Histogram& start, const double& div) {
  Histogram result(start);
  return result /= div;
}

const Histogram operator+(const Histogram& add, const Histogram& start) {
  Histogram result(start);
  return result += add;
}

const Histogram operator-(const Histogram& sub, const Histogram& start) {
  Histogram result(start);
  return result -= sub;
}

} // end namespace data

//---------------------------------------------------------------------------//
// end Data_Histogram.cpp
//---------------------------------------------------------------------------//
