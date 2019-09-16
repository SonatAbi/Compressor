// DO NOT MODIFY THIS FILE
//
#include "treap_bst.h"

#define CXXTEST_ABORT_TEST_ON_FAIL
#include <cxxtest/TestSuite.h>

#include <map>
#include <random>
#include <sstream>
#include <string>

// number of random increments
const unsigned int N = 1000;

// BST with integer keys and string values
typedef TreapBST<std::mt19937::result_type, std::string> TreeType;

class TreapBST_Tests : public CxxTest::TestSuite
{
private:
    std::string hint;

    std::mt19937 gen;
    std::random_device rd;

public:
    void testEmpty()
    {
        hint = "hint: I tested empty before and after insert/removes";

        TreeType t;
        TSM_ASSERT(hint.c_str(), t.empty());

        t.insert(18, "18");
        TSM_ASSERT(hint.c_str(), !t.empty());

        t.insert(61, "61");
        TSM_ASSERT(hint.c_str(), !t.empty());

        t.insert(1, "1");
        TSM_ASSERT(hint.c_str(), !t.empty());

        t.remove(18);
        TSM_ASSERT(hint.c_str(), !t.empty());

        t.remove(1);
        TSM_ASSERT(hint.c_str(), !t.empty());

        t.remove(61);
        TSM_ASSERT(hint.c_str(), t.empty());
    }

    void testInsertInorder()
    {
        hint = "hint: I tested insert of in order keys";

        std::map<std::mt19937::result_type, std::string> check;

        TreeType t;

        for (std::mt19937::result_type i = 0; i < N; ++i) {
            std::stringstream ss;
            ss << i;
            std::string s = ss.str();
            check[i] = s;
            t.insert(i, s);
        }

        for (auto& v : check) {
            bool found;
            std::string result = t.search(v.first, found);
            TSM_ASSERT(hint.c_str(), found);
            TSM_ASSERT(hint.c_str(), result == v.second);
        }

    }

    void testInsertRemoveInorder()
    {
        hint = "hint: I tested insert and remove of in order keys";

        std::map<std::mt19937::result_type, std::string> check;

        TreeType t;

        for (std::mt19937::result_type i = 0; i < N; ++i) {
            std::stringstream ss;
            ss << i;
            std::string s = ss.str();
            check[i] = s;
            t.insert(i, s);

            bool found;
            t.search(i, found);
            TSM_ASSERT(hint.c_str(), found);
        }

        std::mt19937::result_type i = 0;
        while (!t.empty()) {
            for (auto& v : check) {
                bool found;
                std::string result = t.search(v.first, found);
                TSM_ASSERT(hint.c_str(), found);
                TSM_ASSERT(hint.c_str(), result == v.second);
            }
            t.remove(i);
            check.erase(i);
            ++i;
        }
    }

    void testInsertRandom()
    {
        hint = "hint: I tested insert of random ordered keys";

        gen.seed(rd());

        std::map<std::mt19937::result_type, std::string> check;

        TreeType t;

        for (unsigned int i = 0; i < N; ++i) {
            std::mt19937::result_type rv = gen();

            if (check.find(rv) != check.end())
                break;

            std::stringstream ss;
            ss << rv;
            std::string rv_str = ss.str();

            check[rv] = rv_str;
            t.insert(rv, rv_str);
        }

        for (auto& v : check) {
            bool found;
            std::string result = t.search(v.first, found);
            TSM_ASSERT(hint.c_str(), found);
            TSM_ASSERT(hint.c_str(), result == v.second);
        }
    }

    void testInsertRemoveRandom()
    {
        hint = "hint: I tested insert and remove of random ordered keys";

        gen.seed(rd());

        std::map<std::mt19937::result_type, std::string> check;

        TreeType t;

        for (unsigned int i = 0; i < N; ++i) {
            std::mt19937::result_type rv = gen();

            if (check.find(rv) != check.end())
                break;

            std::stringstream ss;
            ss << rv;
            std::string rv_str = ss.str();

            check[rv] = rv_str;
            t.insert(rv, rv_str);
        }

        std::mt19937::result_type rv;
        while (!t.empty()) {
            for (auto& v : check) {
                bool found;
                std::string result = t.search(v.first, found);
                TSM_ASSERT(hint.c_str(), found);
                TSM_ASSERT(hint.c_str(), result == v.second);
            }
            rv = check.begin()->first;
            t.remove(rv);
            check.erase(rv);
        }
        TSM_ASSERT(hint.c_str(), t.empty() && check.empty());
    }

    void testCopy()
    {
        hint = "hint: I tested the copy constructor";

        gen.seed(rd());

        std::map<std::mt19937::result_type, std::string> check;

        TreeType t1;

        for (unsigned int i = 0; i < N; ++i) {
            std::mt19937::result_type rv = gen();

            if (check.find(rv) != check.end())
                break;

            std::stringstream ss;
            ss << rv;
            std::string s = ss.str();
            check[rv] = s;
            t1.insert(rv, s);
        }

        TreeType t2 = t1;

        for (auto& v : check) {
            bool found;
            std::string result = t2.search(v.first, found);
            TSM_ASSERT(hint.c_str(), found);
            TSM_ASSERT(hint.c_str(), result == v.second);
        }
    }

    void testCopyEmpty()
    {
        hint = "hint: I tested the copy constructor for empty trees";

        TreeType t1;
        TreeType t2 = t1;

        TSM_ASSERT(hint.c_str(), t1.empty());
        TSM_ASSERT(hint.c_str(), t2.empty());
    }

    void testCopyAssign()
    {
        hint = "hint: I tested the copy constructor";

        gen.seed(rd());

        std::map<std::mt19937::result_type, std::string> check;

        TreeType t1, t2;

        for (unsigned int i = 0; i < N; ++i) {
            std::mt19937::result_type rv = gen();

            if (check.find(rv) != check.end())
                break;

            std::stringstream ss;
            ss << rv;
            std::string rv_str = ss.str();

            check[rv] = rv_str;
            t1.insert(rv, rv_str);
        }

        t2 = t1;

        for (auto& v : check) {
            bool found;
            std::string result = t2.search(v.first, found);
            TSM_ASSERT(hint.c_str(), found);
            TSM_ASSERT(hint.c_str(), result == v.second);
        }
    }

    void testCopyAssignEmpty()
    {
        hint = "hint: I tested the copy assignment for empty trees";

        TreeType t1;
        TreeType t2;

        t1 = t2;

        TSM_ASSERT(hint.c_str(), t1.empty());
        TSM_ASSERT(hint.c_str(), t2.empty());
    }

    void testExceptions()
    {
        hint = "hint: I tested all exceptions.";

        TreeType t;

        std::mt19937::result_type k = 100;
        std::string v = "100";

        TSM_ASSERT_THROWS(hint.c_str(), t.remove(k), std::logic_error);

        t.insert(k, v);

        TSM_ASSERT_THROWS(hint.c_str(), t.insert(k, v), std::logic_error);
    }
};
