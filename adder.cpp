#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <sys/stat.h>

// check if a file exists
inline bool exists(const std::string&);
// replace the _ with whitespaces so you can pass more than a word as parameter
inline void prepare(std::string&);

int main(int argc, char *argv[]) {
    // check whether the number of arguments is correct
    if (argc != 3) {
      std::cout << "There must be exactly 2 arguments: the name of the band and the filename \n";
    }
    else {
        std::string filename  = argv[2];
        std::string sentence = argv[1];

        //check whether the file already exists
        if (exists(filename)) {
            // put the existing words into a stack
            std::vector<std::string> stack;
            std::string temp;

            prepare(sentence);

            std::ifstream in(filename.c_str());

            // push all the sentences into a stack
            while (std::getline(in, temp)) {
              stack.push_back(temp);
            }

            in.close();

            // since the stack is already sorted, use binary search
            // to check whether the introduced sentence is already there
            if (binary_search(stack.begin(), stack.end(), sentence) == true) {
                std::cout << "The introduced sentence is already in the file\n";
            }
            else {
                // if the sentence isn't found, it is pushed into the stack
                // and the stack will be resorted
                stack.push_back(sentence);

                std::sort(stack.begin(), stack.end());

                std::ofstream out(filename.c_str());

                // finally, rewrite the file with the current stack
                for (std::vector<std::string>::iterator it = stack.begin(); it != stack.end(); ++it) {
                  out << *it << '\n';
                }

                out.close();
            }
        }
        else {
            // if the file doesn't exist, there's no need to try and sort the words, as it is the only one
            std::ofstream out(filename.c_str());
            // the file will be initiated with the introduced sentence
            out << sentence << '\n';

            out.close();
        }
    }

    return 0;
}

inline bool exists(const std::string& filename) {
    struct stat buffer;
    return (stat(filename.c_str(), &buffer) == 0);
}

inline void prepare(std::string& sentence) { std::replace(sentence.begin(), sentence.end(), '_', ' '); }
