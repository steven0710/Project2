#ifndef __CSHANTY_SCANNER_HPP__
#define __CSHANTY_SCANNER_HPP__ 1

#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include "grammar.hh"
#include "errors.hpp"

using TokenKind = cshanty::Parser::token;

namespace cshanty{

class Scanner : public yyFlexLexer{
public:
   
   Scanner(std::istream *in) : yyFlexLexer(in)
   {
	lineNum = 1;
	colNum = 1;
   };
   virtual ~Scanner() {
   };

   //get rid of override virtual function warning
   using FlexLexer::yylex;

   // YY_DECL defined in the flex cshanty.l
   virtual int yylex( cshanty::Parser::semantic_type * const lval);

   int makeBareToken(int tagIn){
	size_t len = static_cast<size_t>(yyleng);
	Position * pos = new Position(
	  this->lineNum, this->colNum,
	  this->lineNum, this->colNum+len);
        this->yylval->lexeme = new Token(pos, tagIn);
        colNum += len;
        return tagIn;
   }

   void errIllegal(size_t l, size_t c, std::string match){
	cshanty::Report::fatal(l, c, "Illegal character "
		+ match);
   }

   void errStrEsc(size_t l, size_t c){
	cshanty::Report::fatal(l, c, "String literal with bad"
	" escape sequence ignored");
   }

   void errStrUnterm(size_t l, size_t c){
	cshanty::Report::fatal(l, c, "Unterminated string"
	" literal ignored");
   }

   void errStrEscAndUnterm(size_t l, size_t c){
	cshanty::Report::fatal(l, c, "Unterminated string literal"
	" with bad escape sequence ignored");
   }

   void errIntOverflow(size_t l, size_t c){
	cshanty::Report::fatal(l, c, "Integer literal too large;"
	" using max value");
   }

   void warn(int lineNumIn, int colNumIn, std::string msg){
	std::cerr << lineNumIn << ":" << colNumIn 
		<< " ***WARNING*** " << msg << std::endl;
   }

   void error(int lineNumIn, int colNumIn, std::string msg){
	std::cerr << lineNumIn << ":" << colNumIn 
		<< " ***ERROR*** " << msg << std::endl;
   }

   static std::string tokenKindString(int tokenKind);

   void outputTokens(std::ostream& outstream);

private:
   cshanty::Parser::semantic_type *yylval = nullptr;
   size_t lineNum;
   size_t colNum;
};

} /* end namespace */

#endif /* END __CSHANTY_SCANNER_HPP__ */
