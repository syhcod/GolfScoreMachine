#define OK -4
#define NO -3
#define UP -2
#define DN -1

#define IDLE -100

void initT();

char whatKey();

void setKey(char);

void setState(unsigned char max, const char* message);