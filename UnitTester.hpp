#ifndef UNIT_TESTER_HPP
#define UNIT_TESTER_HPP

#include <cassert>
#include <vector>
#include <string>
#include <iostream>
#include <cstring>

#define ASSERT(x) { \
        const bool b = (x); cout << #x << ": " << (b ? "OK" : "ERREUR") << endl; assert(b); \
    } (void)0

/// static: permet la définition de plusieurs fonctions avec le même nom
/// (contourner la one definition rule ODR)
/// sinon on devrait utiliser des éléments non portables / standards comme __COUNTER__

#define TEST_VAR_NAME(uid) test_runner_##uid
#define TEST_FUN_NAME(uid) test_##uid

#define TEST(name) TEST_2(name, __LINE__)
#define TEST_2(name, uid) \
    static void TEST_FUN_NAME(uid)(); \
    static UnitTestRunner TEST_VAR_NAME(uid) = UnitTestRunner(&TEST_FUN_NAME(uid), name); \
    static void TEST_FUN_NAME(uid)()

using test_type = void(*)();

struct Test {
    test_type fun;
    std::string name;
};

/**
 * Enregistre tous les tests
 */
class UnitTester {
public:
    using storage_type = std::vector<Test>;

    static void run(const Test& test) {
        using namespace std;

        std::string title;
        title += "Test ";
        title += test.name;
        title += " ";

        cout << title << string(max(size_t(2), 50 - title.size()), '-') << endl;
        test.fun();
    }


    static void runAll() {
        using namespace std;

        for(const auto& test : storage()) {
            run(test);
        }
    }

    static void run(const std::string& name) {
        using namespace std;
        bool found = false;
        int i = std::atoi(name.c_str());

        if(i >= 1 && i <= storage().size()) {
            run(storage().at(i - 1));
            found = true;
        }

        if(!found) {
            for(const auto& test : storage()) {
                if(test.name == name) {
                    test.fun();
                    found = true;
                }
            }
        }

        if(!found) {
            cout << "Test introuvable." << endl;
        }
    }

    static void help() {
        using namespace std;

        cout << "Test list:" << endl;

        int i = 0;
        for(const auto& test : storage()) {

            cout << "     "  << (++i) << ") " << test.name << endl;
        }
    }

private:
    static storage_type & storage() {
        static storage_type s;
        return s;
    }

    static void register_test(const Test& test) {
        storage().push_back(test);
    }

    friend class UnitTestRunner;
};

/**
 * Lance automatiquement un test à l'instanciation
 */
class UnitTestRunner {
public:
    explicit UnitTestRunner(test_type fun, const char *name) noexcept {
        UnitTester::register_test({fun, name});
    }
};

#endif


