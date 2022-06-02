#include <string>
#include <vector>
using namespace std;

class Tokenizer {
private:
    int _pos;
    vector<string> _tokens;

public:
    Tokenizer(string data, string separators);
    int countTokens();
    string nextToken();
    bool hasMoreTokens();
};

