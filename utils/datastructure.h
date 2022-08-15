#include <string>

using namespace std;
#define ANYData struct AnyData

//------------定义数据结构2--------------------
enum EType {
	E_bool, E_char, E_short, E_int, E_usint, E_long,
	E_float, E_double
};


ANYData
{
	EType Eflag;
	union {
		bool   bVal;
		char   cVal;
		short  sval;
		int    ival;
		unsigned int uival;
		long   lval;
		float  fval;
		double dval;
	};

	AnyData(bool val) {
		Eflag = E_bool;
		bVal = val;
	}
	AnyData(char val) {
		Eflag = E_char;
		cVal = val;
	}
	AnyData(short val) {
		Eflag = E_short;
		sval = val;
	}
	AnyData(int val) {
		Eflag = E_int;
		ival = val;
	}
	AnyData(unsigned int val) {
		Eflag = E_usint;
		uival = val;
	}
	AnyData(long val) {
		Eflag = E_long;
		lval = val;
	}
	AnyData(float val) {
		Eflag = E_float;
		fval = val;
	}
	AnyData(double val) {
		Eflag = E_double;
		dval = val;
	}

	EType getType() {
		return Eflag;
	}


	void getVal(bool& val) {
		if (Eflag == E_bool)
			val = bVal;
	}
	void getVal(char& val) {
		if (Eflag == E_char)
			val = cVal;
	}
	void getVal(short& val) {
		if (Eflag == E_short)
			val = sval;
	}
	void getVal(int& val) {
		if (Eflag == E_int)
			val = ival;
	}
	void getVal(unsigned int& val) {
		if (Eflag == E_usint)
			val = uival;
	}
	void getVal(long& val) {
		if (Eflag == E_long)
			val = lval;
	}
	void getVal(float& val) {
		if (Eflag == E_float)
			val = fval;
	}
	void getVal(double& val) {
		if (Eflag == E_double)
			val = dval;
	}

	friend ostream& operator<<(ostream& out, AnyData& data);

};
inline ostream& operator<<(ostream& out, AnyData& data) {
	switch (data.Eflag) {
	case E_bool:
		out << data.bVal;
		break;

	case E_char:
		out << data.cVal;
		break;

	case E_short:
		out << data.sval;
		break;

	case E_int:
		out << data.ival;
		break;

	case E_usint:
		out << data.uival;
		break;

	case E_long:
		out << data.lval;
		break;

	case E_float:
		out << data.fval;
		break;

	case E_double:
		out << data.dval;
		break;
	}
	return out;
}
