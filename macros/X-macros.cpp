#include <iostream>
using namespace std;

// #define FRUIT_LIST \
//     x(Apple) \
//     x(Mango) \
//     x(Orange) 

// #define x(name) name,
// enum Fruits {FRUIT_LIST};
// #undef x

// #define x(name) #name,
// const char* fruitnames[] = {FRUIT_LIST};
// #undef x


// X-macro list
#define ERROR_LIST \
    X(ERR_NONE,   "No error") \
    X(ERR_IO,     "IO failure") \
    X(ERR_TIMEOUT,"Timeout") \
    X(ERR_BUSY,   "Resource busy")

// 1. Enum
#define X(code, msg) code,
typedef enum { ERROR_LIST } ErrorCode;
#undef X

// 2. String descriptions
#define X(code, msg) msg,
static const char* ErrorMessages[] = { ERROR_LIST };
#undef X

// 3. swicth case expansion
#define X(code, msg) case code : printf("%s\n", msg); break;


int main(){

    ErrorCode err = ErrorCode::ERR_BUSY;

    switch (err) {
        ERROR_LIST
    }
    return 0;
}