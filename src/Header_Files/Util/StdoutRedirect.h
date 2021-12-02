#pragma once
#include <iostream>

namespace ic {

    class StdoutRedirect {
    public:
		template<typename Fn>
		static void runFunctionRedirectedCout(Fn fn) {

			std::ofstream out("out.txt");
			std::streambuf* coutbuf = std::cout.rdbuf(); //save old buf
			std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!

			fn(); //call function

			std::cout.rdbuf(coutbuf); //reset to standard output again
		}

        static void redirectCout() {
            out.open("out.txt");
            buf = std::cout.rdbuf(); //save old buf
            std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
        }

        static void restoreCout() {
            if (buf != nullptr) {
                std::cout.rdbuf(buf); //reset to standard output again
                out.close();
            }
            buf = nullptr;
        }

        inline static std::ofstream out;
        inline static std::streambuf* buf = nullptr;

    };
}