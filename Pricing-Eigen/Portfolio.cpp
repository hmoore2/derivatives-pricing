#include "Portfolio.h"
#include "CallOption.h"
#include "PutOption.h"

using namespace std;


class PortfolioImpl : public Portfolio {
 public:
  /* Returns the number of items in the portfolio*/
  int Size() const;
  /*  Add a new security to the portfolio,
	  returns the index at which it was added */
  int Add( double quantity,
		   shared_ptr<Priceable> security );
  /*  Update the quantity at a given index */
  void SetQuantity( int index, double quantity );
  /*  Compute the current price */
  double Price(
	  const BlackScholesModel& model, bool antithetic) const;

  vector<double> quantities;
  vector< shared_ptr<Priceable> > securities;
};

int PortfolioImpl::Size() const {
	return quantities.size();
}

int PortfolioImpl::Add( double quantity,
						shared_ptr<Priceable> security ) {
	quantities.push_back( quantity );
	securities.push_back( security );
	return quantities.size();
}

double PortfolioImpl::Price(
	const BlackScholesModel& model, bool antithetic ) const {
	double ret = 0;
	int n = Size();
	for (int i=0; i<n; i++) {
		ret += quantities[i]
			* securities[i]->Price( model, true);
	}
	return ret;
}
void PortfolioImpl::SetQuantity( int index,
								 double quantity ) {
	quantities[index] = quantity;
}

/**
 *   Create a Portfolio
 */
shared_ptr<Portfolio> Portfolio::NewInstance() {
	shared_ptr<Portfolio> ret=
		make_shared<PortfolioImpl>();
	return ret;
}
