#define ShowMessages 1 // 0 or 1
#include <iostream>

#if ShowMessages
    #define MSG(x) cout << x << endl;
#else
    #define MSG(x);
#endif