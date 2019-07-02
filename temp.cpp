class Quote {
public:
	Quote(const string& book, double p);
};

class Bulk_quote : public Quote {
public:
	Bulk_quote(const std::string& book, double p,
				std::size_t qty, double disc) :
				Quote(book, p), min_qty(qty), discount(disc) { }
};

double Bulk_quote::net_price(size_t cnt) const
{
	if (cnt >= min_qty)
		return cnt * (1 - discount) * price;
	else
		return cnt * price;
}

Quote item;
Bulk_quote bulk;
Quote *p = &item;
p = &bulk;
Quote &r = bulk;



