#include "Validator.h"

void Validator::validate(const Film& f) {
	vector<string> msgs;
	if (f.getTitlu().size() == 0) msgs.push_back("titlu vid! ");
	if (f.getGen().size() == 0) msgs.push_back("gen vid! ");
	if (f.getAn() <= 0) msgs.push_back("an invalid! ");
	if (f.getActor().size() == 0) msgs.push_back("actor vid!  ");
	if (msgs.size() > 0) {
		throw ValidateException(msgs);
	}
}

ostream& operator<<(ostream& out, const ValidateException& ex) {
	for (const auto& msg : ex.msgs) {
		out << msg << " ";
	}
	return out;
}