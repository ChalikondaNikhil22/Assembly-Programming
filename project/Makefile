LDIR=./lib
SDIR=./src
BDIR=./bin
ODIR=./objects
CDIR=./lexyacc-code

CC=gcc

all: parser lexer compiler

$(ODIR)/%.o:$(SDIR)/%.s
	gcc -g -c -o $@ $<

# Rule to generate parser files using Bison
.PHONY: parser
parser: $(CDIR)/calc3.y
	@echo "Generating parser files using Bison..."
	cd $(dir $<) && \
	bison -y -d $(notdir $<)
	@echo "Parser files generated: $@"

# Rule to generate lexer files using Flex
.PHONY: lexer
lexer: $(CDIR)/calc3.l
	@echo "Generating lexer files using Flex..."
	cd $(dir $<) && \
	flex $(notdir $<)
	@echo "Lexer files generated: $@"


compiler: 
	cd $(CDIR); gcc -g -c y.tab.c -o y.tab.o
	cd $(CDIR); gcc -g -c lex.yy.c -o lex.yy.o
	cd $(CDIR); gcc y.tab.o lex.yy.o calc3i.c -o ../$(BDIR)/calc3i.exe
	cd $(CDIR); gcc y.tab.o lex.yy.o calc3i.c -o ../$(BDIR)/calc3i
	gcc -g -c ./src/fact.s -o ./lib/fact.o
	gcc -g -c ./src/gcd.s -o ./lib/gcd.o
	gcc -g -c ./src/lntwo.s -o ./lib/lntwo.o
	gcc -g -c ./src/operators.s -o ./lib/operators.o


clean:
	rm -f bin/*
	rm -f lib/*
	rm -f object/*
	rm -f build/*
	rm -f lexyacc-code/lex.yy.o
	rm -f lexyacc-code/y.tab.o
	rm -f lexyacc-code/y.tab.c
	rm -f lexyacc-code/y.tab.h
	rm -f lexyacc-code/lex.yy.c