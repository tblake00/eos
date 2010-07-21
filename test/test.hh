/* vim: set sw=4 sts=4 et foldmethod=syntax : */

#ifndef WILSON_FITTER_GUARD_TEST_TEST_HH
#define WILSON_FITTER_GUARD_TEST_TEST_HH 1

#include <string>
#include <src/utils/stringify.hh>

namespace test
{
    class TestCase
    {
        private:
            std::string _name;

        public:
            TestCase(const std::string & name);

            virtual ~TestCase();

            std::string name() const;

            virtual void run() const = 0;
    };

    class TestCaseFailedException
    {
        private:
            int _line;

            std::string _file;

            std::string _reason;

        public:
            TestCaseFailedException(int line, const std::string & file, const std::string & reason);

            const std::string & reason() const;

            std::string where() const;
    };

#define TEST_CHECK(a) \
    do \
    { \
        if (! (a)) \
            throw TestCaseFailedException(__LINE__, __FILE__, "'" #a "' is false"); \
    } \
    while (false)

#define TEST_CHECK_EQUAL(a, b) \
    do \
    { \
        if (! ((a) == (b))) \
            throw TestCaseFailedException(__LINE__, __FILE__, "'" #a "' is not equal to '" #b "'"); \
    } \
    while (false)

#define TEST_CHECK_NEARLY_EQUAL(a, b, eps) \
    do \
    { \
        if (std::abs((a - b)) <= eps) \
            break; \
        else \
            throw TestCaseFailedException(__LINE__, __FILE__, \
                    "'" #a "' = " + stringify(a) + " is not nearly-equal to '" #b "' = " + stringify(b) + " within '" + stringify(eps) + "'" \
                    + ", difference is '" + stringify(a - b) + "'"); \
    } \
    while (false)
}

#endif
