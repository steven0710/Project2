#ifndef CSHANTY_TOKEN_H
#define CSHANTY_TOKEN_H

#include <string>

namespace cshanty{

class Position{
public: 
	Position(size_t lineI, size_t colI, size_t lineE, size_t colE)
	: myLineI(lineI), myColI(colI), myLineE(lineE), myColE(colE){
	}
	Position(Position * start, Position * end)
	: myLineI(start == nullptr ? 0 : start->myLineI), 
	  myColI(start == nullptr ? 0 : start->myColI), 
	  myLineE(end == nullptr ? 0 : end->myLineE), 
	  myColE(end == nullptr ? 0 : start->myColE){ 
	}
	virtual std::string begin() const{
		std::string result = "[" 
		+ std::to_string(myLineI)
		+ "," 
		+ std::to_string(myColI)
		+ "]";
		return result;
	}
	virtual std::string span() const{
		std::string result = begin()
		+ "-[" 
		+ std::to_string(myLineE)
		+ "," 
		+ std::to_string(myColE)
		+ "]";
		return result;
	}
private:
	const size_t myLineI;
	const size_t myColI;
	const size_t myLineE;
	const size_t myColE;

};

class Token{
public:
	Token(Position * pos, int kindIn);
	virtual std::string toString();
	size_t line() const;
	size_t col() const;
	int kind() const;
	const Position * pos() const;
protected:
	const Position * myPos;
private:
	const int myKind;
};

class IDToken : public Token{
public:
	IDToken(Position * posIn, std::string valIn);
	const std::string value() const;
	virtual std::string toString() override;
private:
	const std::string myValue;
	
};

class StrToken : public Token{
public:
	StrToken(Position * posIn, std::string valIn);
	virtual std::string toString() override;
	const std::string str() const;
private:
	const std::string myStr;
};

class IntLitToken : public Token{
public:
	IntLitToken(Position * posIn, int numIn);
	virtual std::string toString() override;
	int num() const;
private:
	const int myNum;
};

}

#endif
