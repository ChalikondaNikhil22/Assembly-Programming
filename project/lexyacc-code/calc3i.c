#include <stdio.h>
#include "calc3.h"
#include "y.tab.h"

#define UMINUSI 0
#define FACTI 1
#define LNTWOI 2
#define GCDI 3

// Rest of your code remains the same


// Function prototypes for operations
void perform_UMINUS();
void perform_FACT();
void perform_LNTWO();
void perform_GCD();

static int lbl;
int var = 7;

// Define a structure to hold operation information
struct ArithmeticOperation {
    char operator;
    const char *operationName;
};

// Function to perform arithmetic operation based on the operator
void perform_Arithmetic(char opt) {
    // Define an array of structures for supported operations
    struct ArithmeticOperation operations[] = {
        {'+', "add_opr"},
        {'-', "sub_opr"},
        {'*', "mul_opr"},
        {'/', "div_opr"}
    };

    const char *operationName = NULL;

    // Search for the operator in the array of structures
    for (size_t i = 0; i < sizeof(operations) / sizeof(operations[0]); ++i) {
        operationName = (operations[i].operator == opt) ? operations[i].operationName : operationName;
    }

    // Handle unsupported operation or error using a ternary operator
    operationName = (operationName == NULL) ? "unsupported_op" : operationName;

    printf("\tpopq\t%%rbx\n");
    printf("\tpopq\t%%rax\n");
    printf("\tcall\t%s\n", operationName);
    printf("\tpushq\t%%rdx\n");
}

// Define a structure to map comparison operators to instructions
struct OperatorInstruction {
    char operatorSymbol;
    const char* instruction;
};

// Define a function to select the appropriate instruction
const char* selectInstruction(char op) {
    const struct OperatorInstruction operationMappings[] = {
        {'<', "jge"},
        {'>', "jle"},
        {'G', "jl"},
        {'L', "jg"},
        {'N', "je"},
        {'E', "jne"}
        // Add more mappings if needed
    };

    for (size_t i = 0; i < sizeof(operationMappings) / sizeof(operationMappings[0]); ++i) {
        if (op == operationMappings[i].operatorSymbol) {
            return operationMappings[i].instruction;
        }
    }
    return NULL; // Return NULL for unsupported operations
}

void perform_Comparison(char opt) {
    printf("\tpopq\t%%rbx\n");
    printf("\tpopq\t%%rax\n");

    const char* instruction = selectInstruction(opt);

    if (instruction) {
        printf("\tcmpq\t%%rbx, %%rax\n");
        printf("\t%s\t", instruction);
    } else {
        // Handle unsupported operation or error
        printf("Unsupported operation\n");
    }
}


void (*operationFunctions[])(void) = {
    [UMINUSI] = perform_UMINUS,
    [FACTI] = perform_FACT,
    [LNTWOI] = perform_LNTWO,
    [GCDI] = perform_GCD,
};

// Sample function definitions (replace these with your actual functions)
void perform_UMINUS() {
    printf("\tpopq\t%%r8\n\tneg\t%%r8\n\tpushq\t%%r8\n");
}

void perform_FACT() {
    printf("\tpopq\t%%rdi\n\tcall\tfact\n\tpushq\t%%rbp\n");
}

void perform_LNTWO() {
    printf("\tpopq\t%%rdi\n\tcall\ttwo\n\tpushq\t%%rdi\n");
}

void perform_GCD() {
    printf("\tpopq\t%%rdi\n\tpopq\t%%rsi\n\tcall\tgcd\n\tpushq\t%%rbp\n");
}

// Function to perform arithmetic operation based on the operator using function pointers
void performOperation(char opt) {
    // Use ternary operator to check if the operation is supported
    (operationFunctions[opt] != NULL) ? operationFunctions[opt]() : printf("Unsupported operation\n");
}


int ex(nodeType *p) {
    int lbl1, lbl2;

    if (!p) return 0;
    switch(p->type) {
    case typeCon:
        printf("\tpushq	$%d\n", p->con.value);

        break;
    case typeId:
        printf("\tpushq\t%c\n", p->id.i + 'a');
        break;
    case typeOpr:
        switch(p->opr.oper) {
        case WHILE:
            printf("L%03d:\n", lbl1 = lbl++);
	    ex(p->opr.op[0]);
            printf("\tL%03d\n", lbl2 = lbl++);
            ex(p->opr.op[1]);
            printf("\tjmp\tL%03d\n", lbl1);
            printf("L%03d:\n", lbl2);
            break;
        case IF:
            ex(p->opr.op[0]);
            if (p->opr.nops > 2) {
                /* if else */
                printf("\tL%03d\n", lbl1 = lbl++);
                ex(p->opr.op[1]);
                printf("\tjmp\tL%03d\n", lbl2 = lbl++);
                printf("L%03d:\n", lbl1);
                ex(p->opr.op[2]);
                printf("L%03d:\n", lbl2);
            } else {
                /* if */
                printf("\tL%03d\n", lbl1 = lbl++);
                ex(p->opr.op[1]);
                printf("L%03d:\n", lbl1);
            }
            break;
        case PRINT:
            ex(p->opr.op[0]);
            printf("\tmovq\t$format,\t%%rdi\n\tpopq\t%%rsi\n\tpushq\t$0\n\tcall\tprintf\n\tpopq\t%%rsi\n");
            break;
        case '=':
            ex(p->opr.op[1]);
            printf("\tpopq\t%c\n", p->opr.op[0]->id.i + 'a');
            break;
        case UMINUS:
            ex(p->opr.op[0]);
            performOperation(UMINUSI);
            break;
        case FACT:
            ex(p->opr.op[0]);
            performOperation(FACTI);
            break;
        case LNTWO:
            ex(p->opr.op[0]);
            performOperation(LNTWOI);
            break;
        default:
            ex(p->opr.op[0]);
            ex(p->opr.op[1]);
            switch(p->opr.oper) {
            case GCD:
                performOperation(GCDI);
                break;
            case '+':
                perform_Arithmetic('+');
                break;
            case '-':
                perform_Arithmetic('-');
                break;
            case '*':
                perform_Arithmetic('*');
                break;
            case '/':
                perform_Arithmetic('/');
                break;
            case '<':
                perform_Comparison('<');
                break;
            case '>':
                perform_Comparison('>');
                break;
            case GE:
                perform_Comparison('G');
                break;
            case LE:
                perform_Comparison('L');
                break;
            case NE:
                perform_Comparison('N');
                break;
            case EQ:
                perform_Comparison('E');
                break;
    }
    }
    }
    return 0;
}