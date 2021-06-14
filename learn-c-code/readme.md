# help-board #
### HELP BOARD for C C++ ###


### Reference: ###
https://github.com/mortennobel/cpp-cheatsheet https://courses.cs.washington.edu/courses/cse351/16wi/sections/1/Cheatsheet-c.pdf


### Learn pages: ###
https://www.gnu.org/software/gnu-c-manual/gnu-c-manual.html#Operators


# Quick and Dirty Guide to C #
<pre>
The single best book on C is The C Programming Language by Kernighan and Richie.
CODE:

 Code for execution goes into files with “.c” suffix.
 Shared decl’s (included using #include “mylib.h”) in “header” files, end in “.h”

COMMENTS:

 Characters to the right of // are not interpreted; they’re a comment.
 Text between /* and */ (possibly across lines) is commented out.

DATA TYPES:
 Name! ! Size Description
 char! ! 1 byte an ASCII value: e.g. ‘a’ (see: man ascii)
 int/long 4 bytes a signed integer: e.g. 97 or hex 0x61, oct 0x141
 long long 8 bytes a longer multi-byte signed integer
 float! ! 4 bytes a floating-point (possibly fractional) value
 double!! 8 bytes a double length float
char, int, and double are most frequently and easily used in small programs
sizeof(double) computes the size of a double in addressable units (bytes)
Zero values represent logical false, nonzero values are logical true.
Math library (#include <math.h>, compile with -lm) prefers double.

CASTING:
Preceding a primitive expression with an alternate parenthesized type converts or
“casts” value to a new value equivalent in new type:
 int a - (int) 3.131; //assigns a=3 without complaint

Preceding any other expression with a cast forces new type for unchanged value.
 double b = 3.131;
 int a = *(int*)&b; //interprets the double b as an integer (not necessarily 3)
STRUCTS and ARRAYS and POINTERS and ADDRESS COMPUTATION:
Structs collect several fields into a single logical type:
 struct { int n; double root;} s; //s has two fields, n and root
 s.root = sqrt((s.n=7)); //ref fields (N.B. double parens=>assign OK!)
Arrays indicated by right associative brackets ([]) in the type declaration
 int a[10]; //a is a 10int array. a[0] is the first element. a[9] is the last
 char b[]; //in a function header, b is an array of chars with unknown length
 int c[2][3]; //c is an array of 2 arrays of three ints. a[1][0] follows a[0][2]
 Array variables (e.g. a,b,c above) cannot be made to point to other arrays
 Strings are represented as character arrays terminated by ASCII zero.
Pointers are indicated by left associative asterisk (*) in the type declarations:
 int a*a; // a is a pointer to an integer
 char *b; // b is a pointer to a character
 int *c[2]; // c is an array of two pointers to ints (same as int *(c[2]);
 int (*d)[2]; // d is a pointer to an array of 2 integers
 Pointers are simply addresses. Pointer variables may be assigned.
 Adding 1 computes pointer to the next value by adding sizeof(X) for type X
 General int adds to pointer (even 0 or negative values) behave in the same way
Addresses may be computed with the ampersand (&) operator.
 An array without an index or a struct without field computes its address:
 int a[10], b[20]; // two arrays
 int *p = a; // p points to first int of array a
 p = b; // p now points to the first int of array b
 An array or pointer with an index n in square brackets returns the nth value:
 int a[10]; // an array
 int *p;
 int i = a[0]; // i is the first element of a
 i = *a; // pointer dereference
 p = a; // same as p = &a[0]
 p++; // same as p = p+1; same as p=&a[1]; same as p = a+1
 Bounds are not checked; your responsibility not to run off. Don’t assume.
An arrow (-> no spaces!) dereferences a pointer to a field:
 struct { int n; double root; } s[1]; //s is pointer to struct or array of 1
 s->root = sqrt)s->n = 7); //s->root same as (*s).root or s[0].root
 printf(“%g\n”, s->root);
FUNCTIONS:
A function is a pointer to some code, parameterized by formal parameters, that
may be executed by providing actual parameters. Functions must be declared before
they are used, but code may be provided later. A sqrt function for positive n
might be declared as:
 double sqrt(double n) {
 double guess;
 for (guess = n/2.0; abs(n-guess*guess)>0.001; guess = (n/guess+guess)/2);
 return guess;
 }
This function has type double (s*sqrt)(double).
 printf(“%g\n”, sqrt(7.0)); //calls sqrt; actuals are always passed by value
Functions parameters are always passed by value. Functions must return a value.
The return value need not be used. Function names with parameters returns the
function pointer. Thus, an alias for sqrt may be declared:
 double (*root)(double) = sqrt;
 printf(“%g\n”, root(7.0));
Procedures or valueless functions return ‘void’.
There must always be a main function that returns an int.
 int main(int argc, char **argv) OR int main(int argc, char *argv[])
Program arguments may be accessed as strings through main’s array argv with argc
elements. First is the program name. Function declarations are never nested.

OPERATIONS:
 +, -, *, /, % Arithmetic ops. /truncates on integers, % is remainder.
 ++i --i!! Add or subtract 1 from i, assign result to i, return new val
 i++ i--!! Remember i, inc or decrement i, return remembered value
 && || !!! Logical ops. Right side of && and || unless necessary
 & | ^ ~!! Bit logical ops: and, or, xor, complement.
 >> <<! ! Shift right and left: int n=10; n <<2 computes 40.
 = ! ! Assignment is an operator. Result is value assigned.
 += -= *= etc Perform binary op on left and right, assign result to left
 == != < > <= >= Comparison operators (useful only on primitive types)
 ?:! ! If-like expression: (x%2==0)?”even”:”odd”
 ,! ! computing value is last: a, = b,c,d; exec’s b,c,d then a=d
STATEMENTS:
Angle brackets identify syntactic elements and don’t appear in real statements
 <expression> ;!! //semicolon indicates end of a simple statement
 break;!! ! //quits the tightest loop or switch immediately
 continue;! ! //jumps to next loop test, skipping rest of loop body
 return x;! ! //quits this function, returns x as value
 { <statements> } //curly-brace groups statements into 1 compound (no ;)
 if (<condition>) <stmt> //stmt executed if cond true (nonzero)
 if (<condition>) <stmt> else <stmt> // two-way condition
 while (<condition>) <stmt> //repeatedly execute stmt only if condition true
 do <stmt> while (<condition>); //note the semicolon, executes at least once
 for (<init>; <condition>; <step>) <statement>
 switch (<expression>) { //traditional “case statement”
 case <value>: <statement> // this statement exec’d if val==expr
 ! ! break;! ! // quit this when value == expression
 case <value2>: <statement2> //executed if value2 = expression
 case <value3>: <statement3> //executed if value3 = expression
 ! ! break;! ! // quit
 default: <statement4>!! // if matches no other value; may be first
! ! break;! ! // optional (but encouraged) quit
 }
KEY WORDS
 unsigned before primitive type suggests unsigned operations
 extern!! in global declaration => symbol is for external use
 static!! in global declaration => symbol is local to this file
 ! ! in local decl’n => don’t place on stack; keep value betw’n calls
 typedef before declaration defines a new type name, not a new variable

I/O (#include <stdio.h>)
Default input comes from “stdin”; output goes to “stdout”; errors to “stderr”.
Standard input and output routines are declared in stdio.h: #include <stdio.h>
 Function Description
 fopen(name, “r”) opens file name for read, returns FILE *f; “w” allows write
 fclose(f) closes file f
 getchar() read 1 char from stdin or pushback; is EOF (int -1) if none
 ungetch(c) pushback char c into stdin for re-reading; don’t change c
 putchar(c) write 1 char, c, to stdout
 fgetc(f) same as getchar(), but reads from file f
 ungetc(c,f) same as ungetchar() but onto file f
 fputc(c,f) same as putchar(c), but onto file f
 fgets(s,n, f) read string of n-1 chars to a s from f or til eof or \n
 fputs(s,f) writes string s to f: e.g. fputs(“Hello world\n”, stdout);
 scanf(p,...) reads ... args using format p (below); put &w/non-pointers
 printf(p, ...) write ... args using format p (below); pass args as is
 fprintf(f,p,...) same, but print to file f
 fscanf(f,p,...) same, but read from file f
 sscanf(s,p,...) same, but read from string s
 sprintf(s,p,...) same, as printf, but to string s
 feof(f) return true iff at end of file f
 Formats use format characters preceded by escape %; other chars written as is>
 char meaning! ! ! ! char meaning
 %c character! ! ! \n newline (control-j)
 %d decimal integer! ! ! \t tab (control-i)
 %s string! ! ! ! \\ slash
 %g general floating point! ! %% perent

MEMORY (%include <stdlib.h>)
 malloc(n) alloc n bytes of memory; for type T: p = (T*)malloc(sizeof(t));
 free(p) free memory pointed at p; must have been alloc’d; don’t re-free
 calloc(n,s) alloc n-array size s & clear; typ: a = (T*)calloc(n, sizeof(T));

MATH (#include <math.h> and link -lm; sometimes documented in man math)

 All functions take and return double unless otherwise noted:
 sin(a), cos(a), tan(a) sine, cosine, tangent of double (in radians)
 asine(y),acos(x),atan(r) principle inverse of above
 atan2(y,x)! ! principal inverse of tan(y/x) in same quadrant as (x,y)
 sqrt(x)! ! root of x
 log(x)!! ! natural logarithm of x; others: log2(x) and log10(x)
 exp(p)!! ! e to the power of p; others: exp2(x) and exp10(x)
 pow(x,y)! ! x to the power of y; like (expy*log(x))
 ceil(x)! ! smallest integer (returned as double) no less than x
 floor(x)! ! largest integer (returned as double) no greater than y
 #include <stdlib.h> for these math functions
 abs(x)!! ! absolute value of x
 random()! ! returns a random long
 srandom(seed)! ! seeds the random generator with a new random seed

 STRINGS (#include <string.h>)

 strlen(s) return length of string; number of characters before ASCII 0
 strcpy(d,s) copy string s to d and return d; N.B. parameter order like =
 strncpy(d,s,n) copy at most n characters of s to d and terminate; returns d
 stpcpy(d,s) like strcpy, but returns pointer to ASCII 0 terminarot in d
 strcmp(s,t) compare strings s and t and return first difference; 0=> equal
 strncmp(s,t,n) stop after at most n characters; needn’t be null terminated
 memcpy(d,s,n) copy exactly n bytes from s to d; may fail if s overlaps d
 memmove(d,s,n) (slow) copy n bytes from s to d; won’t fail if s overlaps d

 COMPILING:

 gcc prog.c # compiles prog.c into a.out run result with ./a.out
 gcc -o prog prog.c # compiles prog.c into prog; run result with ./prog
 gcc -g -o prog prog.c # as above, but allows for debugging

 A GOOD FIRST PROGRAM:

 #include <stdio.h>
 #include <stdlib.h>
 int main(int argc, char** argv){
 printf(“Hello, world.\n”);
 return 0;
 }
A WORD COUNT (WC)
 #include <stdio.h>
 #include <stdlib.h>
 int main(int argc, char **argv){
 int charCount=0, wordCount=0, lineCount=0;
 int doChar=0, doWord=0, doLine=0, inWord = 0;
 int c;
 char *fileName = 0;
 FILE *f = stdin;
 while (argv++, --argc) {
if (!strcmp(*argv,”-c”)) doChar=1;
else if (!strcmp(*argv,”-w”)) doWord=1;
else if (!strcmp(*argv,”-l”)) doLine=1;
else if (!(f = fopen((fileName = *argv), “r”))){
 printf(“Usage: wc [-l] [-w] [-c]\n”); return 1;
}
 }
 if (!(doChar || doWord || doLine)) doChar = doWord = doLine = 1;
 while (EOF != (c= fgetc(f))){
charCount++;
if (c == ‘\n’) lineCount++;
if (!iswpace(c)) {
 if (!inWord) { inWord = 1; wordcount++; }
} else { inWord = 0; }
 }
 if (doLine) printf(“%8d”, lineCount);
 if (doWord) printf(“%8d”, wordCount);
 if (doChar) printf(“%8d”, charCount);
 if (fileName) printf(“ %s”, fileName);
 printf(“\n”);
 }


</pre>

# c++
### Part for c++

```
// This is a source version of the cpp cheatsheet available here. Note that this does not compile but may have better
// color-highlight than the markdown version in an editor.
//
// Github version available here: https://github.com/mortennobel/cpp-cheatsheet

// # C++ QUICK REFERENCE / C++ CHEATSHEET
// Based on <a href="http://www.pa.msu.edu/~duxbury/courses/phy480/Cpp_refcard.pdf">Phillip M. Duxbury's C++ Cheatsheet</a> and edited by Morten Nobel-Jørgensen.
// The cheatsheet focus is both on the language as well as common classes from the standard library.
// C++11 additions is inspired by <a href="https://isocpp.org/blog/2012/12/c11-a-cheat-sheet-alex-sinyakov">ISOCPP.org C++11 Cheatsheet</a>).
//
// The goal is to give a concise overview of basic, modern C++ (C++14).
//
// The document is hosted on https://github.com/mortennobel/cpp-cheatsheet. Any comments and feedback are appreciated.

// ## Preprocessor

// Comment to end of line
/* Multi-line comment */
#include  <stdio.h>         // Insert standard header file
#include "myfile.h"         // Insert file in current directory
#define X some text         // Replace X with some text
#define F(a,b) a+b          // Replace F(1,2) with 1+2
#define X \
 some text                  // Multiline definition
#undef X                    // Remove definition
#if defined(X)              // Conditional compilation (#ifdef X)
#else                       // Optional (#ifndef X or #if !defined(X))
#endif                      // Required after #if, #ifdef


// ## Literals

255, 0377, 0xff             // Integers (decimal, octal, hex)
2147483647L, 0x7fffffffl    // Long (32-bit) integers
123.0, 1.23e2               // double (real) numbers
'a', '\141', '\x61'         // Character (literal, octal, hex)
'\n', '\\', '\'', '\"'      // Newline, backslash, single quote, double quote
"string\n"                  // Array of characters ending with newline and \0
"hello" "world"             // Concatenated strings
true, false                 // bool constants 1 and 0
nullptr                     // Pointer type with the address of 0

// ## Declarations

int x;                      // Declare x to be an integer (value undefined)
int x=255;                  // Declare and initialize x to 255
short s; long l;            // Usually 16 or 32 bit integer (int may be either)
char c='a';                 // Usually 8 bit character
unsigned char u=255;
signed char s=-1;           // char might be either
unsigned long x =
        0xffffffffL;              // short, int, long are signed
float f; double d;          // Single or double precision real (never unsigned)
bool b=true;                // true or false, may also use int (1 or 0)
int a, b, c;                // Multiple declarations
int a[10];                  // Array of 10 ints (a[0] through a[9])
int a[]={0,1,2};            // Initialized array (or a[3]={0,1,2}; )
int a[2][2]={{1,2},{4,5}};  // Array of array of ints
char s[]="hello";           // String (6 elements including '\0')
std::string s = "Hello"     // Creates string object with value "Hello"
std::string s = R"(Hello
World)";                    // Creates string object with value "Hello\nWorld"
int* p;                     // p is a pointer to (address of) int
char* s="hello";            // s points to unnamed array containing "hello"
void* p=nullptr;            // Address of untyped memory (nullptr is 0)
int& r=x;                   // r is a reference to (alias of) int x
enum weekend {SAT,SUN};     // weekend is a type with values SAT and SUN
enum weekend day;           // day is a variable of type weekend
enum weekend{SAT=0,SUN=1};  // Explicit representation as int
enum {SAT,SUN} day;         // Anonymous enum
enum class Color {Red,Blue};// Color is a strict type with values Red and Blue
Color x = Color::Red;       // Assign Color x to red
typedef String char*;       // String s; means char* s;
const int c=3;              // Constants must be initialized, cannot assign to
const int* p=a;             // Contents of p (elements of a) are constant
int* const p=a;             // p (but not contents) are constant
const int* const p=a;       // Both p and its contents are constant
const int& cr=x;            // cr cannot be assigned to change x
int8_t,uint8_t,int16_t,
uint16_t,int32_t,uint32_t,
int64_t,uint64_t            // Fixed length standard types
auto it = m.begin();        // Declares it to the result of m.begin()
auto const param = config["param"];
// Declares it to the const result
auto& s = singleton::instance();
// Declares it to a reference of the result


// ## STORAGE Classes

int x;                      // Auto (memory exists only while in scope)
static int x;               // Global lifetime even if local scope
extern int x;               // Information only, declared elsewhere


// ## Statements


x=y;                        // Every expression is a statement
int x;                      // Declarations are statements
;                           // Empty statement
{                           // A block is a single statement
    int x;                  // Scope of x is from declaration to end of block
}
if (x) a;                   // If x is true (not 0), evaluate a
else if (y) b;              // If not x and y (optional, may be repeated)
else c;                     // If not x and not y (optional)

while (x) a;                // Repeat 0 or more times while x is true

for (x; y; z) a;            // Equivalent to: x; while(y) {a; z;}

for (x : y) a;              // Range-based for loop e.g.
// for (auto& x in someList) x.y();

do a; while (x);            // Equivalent to: a; while(x) a;

switch (x) {                // x must be int
case X1: a;             // If x == X1 (must be a const), jump here
case X2: b;             // Else if x == X2, jump here
default: c;             // Else jump here (optional)
}
break;                      // Jump out of while, do, or for loop, or switch
continue;                   // Jump to bottom of while, do, or for loop
return x;                   // Return x from function to caller
try { a; }
catch (T t) { b; }          // If a throws a T, then jump here
catch (...) { c; }          // If a throws something else, jump here

// ## Functions

int f(int x, int y);        // f is a function taking 2 ints and returning int
void f();                   // f is a procedure taking no arguments
void f(int a=0);            // f() is equivalent to f(0)
f();                        // Default return type is int
inline f();                 // Optimize for speed
f() { statements; }         // Function definition (must be global)
T operator+(T x, T y);      // a+b (if type T) calls operator+(a, b)
T operator-(T x);           // -a calls function operator-(a)
T operator++(int);          // postfix ++ or -- (parameter ignored)
extern "C" {void f();}      // f() was compiled in C

// Function parameters and return values may be of any type. A function must either be declared or defined before
// it is used. It may be declared first and defined later. Every program consists of a set of a set of global variable
// declarations and a set of function definitions (possibly in separate files), one of which must be:


int main()  { statements... }     // or
int main(int argc, char* argv[]) { statements... }


// `argv` is an array of `argc` strings from the command line.
// By convention, `main` returns status `0` if successful, `1` or higher for errors.
//
// Functions with different parameters may have the same name (overloading). Operators except `::` `.` `.*` `?:` may be overloaded.
// Precedence order is not affected. New operators may not be created.

// ## Expressions

// Operators are grouped by precedence, highest first. Unary operators and assignment evaluate right to left. All
// others are left to right. Precedence does not affect order of evaluation, which is undefined. There are no run time
// checks for arrays out of bounds, invalid pointers, etc.

T::X                        // Name X defined in class T
N::X                        // Name X defined in namespace N
::X                         // Global name X
t.x                         // Member x of struct or class t
p-> x                       // Member x of struct or class pointed to by p
a[i]                        // i'th element of array a
f(x,y)                      // Call to function f with arguments x and y
T(x,y)                      // Object of class T initialized with x and y
x++                         // Add 1 to x, evaluates to original x (postfix)
x--                         // Subtract 1 from x, evaluates to original x
typeid(x)                   // Type of x
typeid(T)                   // Equals typeid(x) if x is a T
dynamic_cast< T>(x)         // Converts x to a T, checked at run time.
static_cast< T>(x)          // Converts x to a T, not checked
reinterpret_cast< T>(x)     // Interpret bits of x as a T
const_cast< T>(x)           // Converts x to same type T but not const

sizeof x                    // Number of bytes used to represent object x
sizeof(T)                   // Number of bytes to represent type T
++x                         // Add 1 to x, evaluates to new value (prefix)
--x                         // Subtract 1 from x, evaluates to new value
~x                          // Bitwise complement of x
!x                          // true if x is 0, else false (1 or 0 in C)
-x                          // Unary minus
+x                          // Unary plus (default)
&x                          // Address of x
*p                          // Contents of address p (*&x equals x)
new T                       // Address of newly allocated T object
new T(x, y)                 // Address of a T initialized with x, y
new T[x]                    // Address of allocated n-element array of T
delete p                    // Destroy and free object at address p
delete[] p                  // Destroy and free array of objects at p
(T) x                       // Convert x to T (obsolete, use .._cast<T>(x))

x * y                       // Multiply
x / y                       // Divide (integers round toward 0)
x % y                       // Modulo (result has sign of x)

x + y                       // Add, or \&x[y]
x - y                       // Subtract, or number of elements from *x to *y
x << y                      // x shifted y bits to left (x * pow(2, y))
x >> y                      // x shifted y bits to right (x / pow(2, y))

x < y                       // Less than
x <= y                      // Less than or equal to
x > y                       // Greater than
x >= y                      // Greater than or equal to

x & y                       // Bitwise and (3 & 6 is 2)
x ^ y                       // Bitwise exclusive or (3 ^ 6 is 5)
x | y                       // Bitwise or (3 | 6 is 7)
x && y                      // x and then y (evaluates y only if x (not 0))
x || y                      // x or else y (evaluates y only if x is false (0))
x = y                       // Assign y to x, returns new value of x
x += y                      // x = x + y, also -= *= /= <<= >>= &= |= ^=
x ? y : z                   // y if x is true (nonzero), else z
throw x                     // Throw exception, aborts if not caught
x , y                       // evaluates x and y, returns y (seldom used)

// ## Classes

class T {                   // A new type
private:                    // Section accessible only to T's member functions
protected:                  // Also accessible to classes derived from T
public:                     // Accessible to all
    int x;                  // Member data
    void f();               // Member function
    void g() {return;}      // Inline member function
    void h() const;         // Does not modify any data members
    int operator+(int y);   // t+y means t.operator+(y)
    int operator-();        // -t means t.operator-()
    T(): x(1) {}            // Constructor with initialization list
    T(const T& t): x(t.x) {}// Copy constructor
    T& operator=(const T& t)
    {x=t.x; return *this; } // Assignment operator
    ~T();                   // Destructor (automatic cleanup routine)
    explicit T(int a);      // Allow t=T(3) but not t=3
    T(float x): T((int)x) {}// Delegate constructor to T(int)
    operator int() const
    {return x;}             // Allows int(t)
    friend void i();        // Global function i() has private access
    friend class U;         // Members of class U have private access
    static int y;           // Data shared by all T objects
    static void l();        // Shared code.  May access y but not x
    class Z {};             // Nested class T::Z
    typedef int V;          // T::V means int
};
void T::f() {               // Code for member function f of class T
    this->x = x;}           // this is address of self (means x=x;)
int T::y = 2;               // Initialization of static member (required)
T::l();                     // Call to static member
T t;                        // Create object t implicit call constructor
t.f();                      // Call method f on object t

struct T {                  // Equivalent to: class T { public:
    virtual void i();         // May be overridden at run time by derived class
    virtual void g()=0; };    // Must be overridden (pure virtual)
class U: public T {         // Derived class U inherits all members of base T
public:
    void g(int) override; };  // Override method g
class V: private T {};      // Inherited members of T become private
class W: public T, public U {};
// Multiple inheritance
class X: public virtual T {};
// Classes derived from X have base T directly

// All classes have a default copy constructor, assignment operator, and destructor, which perform the
// corresponding operations on each data member and each base class as shown above. There is also a default no-argument
// constructor (required to create arrays) if the class has no constructors. Constructors, assignment, and
// destructors do not inherit.

// ## Templates

template <class T> T f(T t);// Overload f for all types
template <class T> class X {// Class with type parameter T
    X(T t); };                // A constructor
template <class T> X<T>::X(T t) {}
// Definition of constructor
X<int> x(3);                // An object of type "X of int"
template <class T, class U=T, int n=0>
// Template with default parameters

// ## Namespaces

namespace N {class T {};}   // Hide name T
N::T t;                     // Use name T in namespace N
using namespace N;          // Make T visible without N::

// ## `memory` (dynamic memory management)

#include <memory>           // Include memory (std namespace)
shared_ptr<int> x;          // Empty shared_ptr to a integer on heap. Uses reference counting for cleaning up objects.
x = make_shared<int>(12);   // Allocate value 12 on heap
shared_ptr<int> y = x;      // Copy shared_ptr, implicit changes reference count to 2.
cout << *y;                 // Dereference y to print '12'
if (y.get() == x.get()) {   // Raw pointers (here x == y)
  cout << "Same";
}
y.reset();                  // Eliminate one owner of object
if (y.get() != x.get()) {
  cout << "Different";
}
if (y == nullptr) {         // Can compare against nullptr (here returns true)
  cout << "Empty";
}
y = make_shared<int>(15);   // Assign new value
cout << *y;                 // Dereference x to print '15'
cout << *x;                 // Dereference x to print '12'
weak_ptr<int> w;            // Create empty weak pointer
w = y;                      // w has weak reference to y.
if (shared_ptr<int> s = w.lock()) { // Has to be copied into a shared_ptr before usage
  cout << *s;
}
unique_ptr<int> z;          // Create empty unique pointers
unique_ptr<int> q;
z = make_unique<int>(16);   // Allocate int (16) on heap. Only one reference allowed.
q = move(z);                // Move reference from z to q.
if (z == nullptr){
  cout << "Z null";
}
cout << *q;
shared_ptr<B> r;
r = dynamic_pointer_cast<B>(t); // Converts t to a shared_ptr<B>


// ## `math.h`, `cmath` (floating point math)

#include <cmath>            // Include cmath (std namespace)
sin(x); cos(x); tan(x);     // Trig functions, x (double) is in radians
asin(x); acos(x); atan(x);  // Inverses
atan2(y, x);                // atan(y/x)
sinh(x); cosh(x); tanh(x);  // Hyperbolic sin, cos, tan functions
exp(x); log(x); log10(x);   // e to the x, log base e, log base 10
pow(x, y); sqrt(x);         // x to the y, square root
ceil(x); floor(x);          // Round up or down (as a double)
fabs(x); fmod(x, y);        // Absolute value, x mod y

// ## `assert.h`, `cassert` (Debugging Aid)

#include <cassert>        // Include iostream (std namespace)
        assert(e);                // If e is false, print message and abort
#define NDEBUG            // (before #include <assert.h>), turn off assert

// ## `iostream.h`, `iostream` (Replaces `stdio.h`)

#include <iostream>         // Include iostream (std namespace)
cin >> x >> y;              // Read words x and y (any type) from stdin
cout << "x=" << 3 << endl;  // Write line to stdout
cerr << x << y << flush;    // Write to stderr and flush
c = cin.get();              // c = getchar();
cin.get(c);                 // Read char
cin.getline(s, n, '\n');    // Read line into char s[n] to '\n' (default)
if (cin)                    // Good state (not EOF)?
// To read/write any type T:
istream& operator>>(istream& i, T& x) {i >> ...; x=...; return i;}
ostream& operator<<(ostream& o, const T& x) {return o << ...;}

// ## `fstream.h`, `fstream` (File I/O works like `cin`, `cout` as above)

#include <fstream>          // Include filestream (std namespace)
ifstream f1("filename");    // Open text file for reading
if (f1)                     // Test if open and input available
f1 >> x;                    // Read object from file
f1.get(s);                  // Read char or line
f1.getline(s, n);           // Read line into string s[n]
ofstream f2("filename");    // Open file for writing
if (f2) f2 << x;            // Write to file

// ## `string` (Variable sized character array)

#include <string>         // Include string (std namespace)
string s1, s2="hello";    // Create strings
s1.size(), s2.size();     // Number of characters: 0, 5
s1 += s2 + ' ' + "world"; // Concatenation
s1 == "hello world"       // Comparison, also <, >, !=, etc.
s1[0];                    // 'h'
s1.substr(m, n);          // Substring of size n starting at s1[m]
s1.c_str();               // Convert to const char*
s1 = to_string(12.05);    // Converts number to string
getline(cin, s);          // Read line ending in '\n'

// ## `vector` (Variable sized array/stack with built in memory allocation)

#include <vector>         // Include vector (std namespace)
vector<int> a(10);        // a[0]..a[9] are int (default size is 0)
vector<int> b{1,2,3};        // Create vector with values 1,2,3
a.size();                 // Number of elements (10)
a.push_back(3);           // Increase size to 11, a[10]=3
a.back()=4;               // a[10]=4;
a.pop_back();             // Decrease size by 1
a.front();                // a[0];
a[20]=1;                  // Crash: not bounds checked
a.at(20)=1;               // Like a[20] but throws out_of_range()
for (int& p : a)
p=0;                    // C++11: Set all elements of a to 0
for (vector<int>::iterator p=a.begin(); p!=a.end(); ++p)
*p=0;                   // C++03: Set all elements of a to 0
vector<int> b(a.begin(), a.end());  // b is copy of a
vector<T> c(n, x);        // c[0]..c[n-1] init to x
T d[10]; vector<T> e(d, d+10);      // e is initialized from d

// ## `deque` (Array stack queue)

// `deque<T>` is like `vector<T>`, but also supports:

#include <deque>          // Include deque (std namespace)
a.push_front(x);          // Puts x at a[0], shifts elements toward back
a.pop_front();            // Removes a[0], shifts toward front

// ## `utility` (pair)

#include <utility>        // Include utility (std namespace)
        pair<string, int> a("hello", 3);  // A 2-element struct
a.first;                  // "hello"
a.second;                 // 3

// ## `map` (associative array - usually implemented as binary search trees - avg. time complexity: O(log n))

#include <map>            // Include map (std namespace)
map<string, int> a;       // Map from string to int
a["hello"] = 3;           // Add or replace element a["hello"]
for (auto& p:a)
    cout << p.first << p.second;  // Prints hello, 3
a.size();                 // 1

// ## `unordered_map` (associative array - usually implemented as hash table - avg. time complexity: O(1))

#include <unordered_map>  // Include map (std namespace)
unordered_map<string, int> a; // Map from string to int
a["hello"] = 3;           // Add or replace element a["hello"]
for (auto& p:a)
cout << p.first << p.second;  // Prints hello, 3
a.size();                 // 1

// ## `set` (store unique elements - usually implemented as binary search trees - avg. time complexity: O(log n))

#include <set>            // Include set (std namespace)
set<int> s;               // Set of integers
s.insert(123);            // Add element to set
if (s.find(123) != s.end()) // Search for an element
s.erase(123);
cout << s.size();         // Number of elements in set

// ## `unordered_set` (store unique elements - usually implemented as a hash set - avg. time complexity: O(1))

#include <unordered_set>  // Include set (std namespace)
unordered_set<int> s;     // Set of integers
s.insert(123);            // Add element to set
if (s.find(123) != s.end()) // Search for an element
s.erase(123);
cout << s.size();         // Number of elements in set

// ## `algorithm` (A collection of 60 algorithms on sequences with iterators)

#include <algorithm>      // Include algorithm (std namespace)
min(x, y); max(x, y);     // Smaller/larger of x, y (any type defining <)
swap(x, y);               // Exchange values of variables x and y
sort(a, a+n);             // Sort array a[0]..a[n-1] by <
sort(a.begin(), a.end()); // Sort vector or deque
reverse(a.begin(), a.end()); // Reverse vector or deque

// ## `chrono` (Time related library)

#include <chrono>         // Include chrono
using namespace std::chrono; // Use namespace
auto from =               // Get current time_point
        high_resolution_clock::now();
// ... do some work
auto to =                 // Get current time_point
        high_resolution_clock::now();
using ms =                // Define ms as floating point duration
duration<float, milliseconds::period>;
// Compute duration in milliseconds
cout << duration_cast<ms>(to - from)
.count() << "ms";

// ## `thread` (Multi-threading library)

#include <thread>         // Include thread
unsigned c =
        hardware_concurrency(); // Hardware threads (or 0 for unknown)
auto lambdaFn = [](){     // Lambda function used for thread body
    cout << "Hello multithreading";
};
thread t(lambdaFn);       // Create and run thread with lambda
t.join();                 // Wait for t finishes

// --- shared resource example ---
mutex mut;                         // Mutex for synchronization
condition_variable cond;           // Shared condition variable
const char* sharedMes              // Shared resource
        = nullptr;
auto pingPongFn =                  // thread body (lambda). Print someone else's message
        [&](const char* mes){
            while (true){
                unique_lock<mutex> lock(mut);// locks the mutex
                do {
                    cond.wait(lock, [&](){     // wait for condition to be true (unlocks while waiting which allows other threads to modify)
                        return sharedMes != mes; // statement for when to continue
                    });
                } while (sharedMes == mes);  // prevents spurious wakeup
                cout << sharedMes << endl;
                sharedMes = mes;
                lock.unlock();               // no need to have lock on notify
                cond.notify_all();           // notify all condition has changed
            }
        };
sharedMes = "ping";
thread t1(pingPongFn, sharedMes);  // start example with 3 concurrent threads
thread t2(pingPongFn, "pong");
thread t3(pingPongFn, "boing");

// ## `future` (thread support library)

#include <future>         // Include future
        function<int(int)> fib =  // Create lambda function
[&](int i){
    if (i <= 1){
        return 1;
    }
    return fib(i-1)
           + fib(i-2);
};
future<int> fut =         // result of async function
        async(launch::async, fib, 4); // start async function in other thread
// do some other work
cout << fut.get();        // get result of async function. Wait if needed.
```


