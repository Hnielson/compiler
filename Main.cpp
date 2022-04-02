#include "Token.h"
#include "StateMachine.h"
#include "Scanner.h"
#include "Symbol.h"
#include "Node.h"
#include "Parser.h"

void scanFile(string filename)
{
	ScannerClass scanner(filename);
	TokenClass tc;
	do {
		tc = scanner.GetNextToken();
		cout << tc << endl;
	} while(tc.GetTokenType() != ENDFILE_TOKEN);
}

void testNodes()
{
	StartNode *start = new StartNode(new ProgramNode(new BlockNode(new StatementGroupNode())));
	cout << "deleting start" << endl;
	delete start;

	PlusNode *plus = new PlusNode(new IntegerNode(10), new IntegerNode(20));
	cout << plus->Evaluate() << endl;
	cout << "deleting plusNode" << endl;
	delete plus;

	EqualNode *le = new EqualNode(new IntegerNode(5), new IntegerNode(5));
	cout << le->Evaluate() << endl;
	cout << "deleting lessEqualNode" << endl;
	delete le;

	GreaterEqualNode *func = new GreaterEqualNode(new PlusNode(new TimesNode(new IntegerNode(1), new IntegerNode(3)), new DivideNode(new MinusNode(new IntegerNode(5), new PlusNode(new IntegerNode(3), new IntegerNode(2))), new IntegerNode(10))), new TimesNode(new IntegerNode(2), new TimesNode(new PlusNode(new IntegerNode(3), new IntegerNode(2)), new PlusNode(new IntegerNode(2), new IntegerNode(2)))));
	cout << func->Evaluate() << endl;
	cout << "deleting book function" << endl;
	delete func;
}

void testParser()
{
	ScannerClass* sc = new ScannerClass("input.txt");
	SymbolTableClass* st = new SymbolTableClass();
	ParserClass p(sc, st);
	p.Start();
}

void Interpret(string inputFile)
{
	// Create scanner, symbol table, and parser objets.
	ScannerClass *scanner = new ScannerClass(inputFile);
	SymbolTableClass *symbolTable = new SymbolTableClass();
	ParserClass *parser = new ParserClass(scanner, symbolTable);

	//Do the parsing, which results in a parse tree.
	parser->Start()->Interpret();
	cout << "Finished building the parse tree" << endl;
}

void CodeAndExecute(string inputFile)
{
	// Create scanner, symbol table, and parser objects.
	ScannerClass scanner(inputFile);
	SymbolTableClass symbolTable;
	ParserClass parser(&scanner, &symbolTable);
	// Do the parsing, which results in a parse tree.
	StartNode* root = parser.Start();
	// Create the machine code instructions from the parse tree
	InstructionsClass machineCode;
	root->Code(machineCode);
	machineCode.Finish();
	machineCode.PrintAllMachineCodes();
	// Execute the machine code instructions previously created
	machineCode.Execute();
	// cleanup recursively
	delete root;
}

int main()
{
	// scanFile("Input.txt");
	// testNodes();
	// testParser();
	//Interpret("Input.txt");
	CodeAndExecute("Input.txt");
	return 0;
}