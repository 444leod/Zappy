/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Test
*/

#include "Test.hpp"
#include <fstream>

void TestResult::setOutput(std::string output)
{
    _output = output;
}

void TestResult::setError(std::string error)
{
    _error = error;
}

void TestResult::setReturn(uint8_t ret)
{
    _return = ret;
}

void TestResult::setRunnedTime(std::chrono::milliseconds runned_time)
{
    _runned_time = runned_time;
}

std::string TestResult::getOutput()
{
    return _output;
}

std::string TestResult::getError()
{
    return _error;
}

uint8_t TestResult::getReturn()
{
    return _return;
}

std::chrono::milliseconds TestResult::getRunnedTime()
{
    return _runned_time;
}

void TestResult::setFailed(bool failed)
{
    _failed = failed;
}

bool TestResult::getFailed()
{
    return _failed;
}

Test::Test(std::string title, std::vector<std::string> params, std::string expected_output, std::string expected_error, int expected_return, std::optional<std::chrono::seconds> timeout = std::nullopt) : _title(title), _params(params), _expected_output(expected_output), _expected_error(expected_error), _expected_return(expected_return), _timeout(timeout)
{
}

TestResult Test::run(std::string binary_path)
{
    TestResult result;

    std::string command = binary_path + " ";

    if (_timeout.has_value()) {
        command = "timeout " + std::to_string(_timeout.value().count()) + " " + command;
    }
    for (auto &param : _params) {
        command += param + " ";
    }
    command += " > /tmp/zappy_test_output 2> /tmp/zappy_test_error";

    auto start = std::chrono::high_resolution_clock::now();

    int ret = std::system(command.c_str());
    int ret_val = WEXITSTATUS(ret);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::milliseconds runned_time = std::chrono::duration_cast<std::chrono::seconds>(end - start);

    std::ifstream output_file("/tmp/zappy_test_output");
    std::ifstream error_file("/tmp/zappy_test_error");
    std::string output((std::istreambuf_iterator<char>(output_file)), std::istreambuf_iterator<char>());
    std::string error((std::istreambuf_iterator<char>(error_file)), std::istreambuf_iterator<char>());

    result.setOutput(output);
    result.setError(error);
    result.setReturn(ret_val);
    result.setRunnedTime(runned_time);

    if (ret_val != _expected_return) {
        if (ret_val != 124 && _expected_return == 0) {
            result.setFailed(true);
        }
    }
    if (!output.starts_with(_expected_output)) {
        result.setFailed(true);
    }
    if (!error.starts_with(_expected_error)) {
        result.setFailed(true);
    }
    return result;
}

Tester::Tester(const std::string &binary_path) : _binary_path(binary_path)
{
    if (binary_path.empty()) {
        std::cerr << "Binary path is empty" << std::endl;
        exit(1);
    }
    if (access(binary_path.c_str(), F_OK) == -1) {
        std::cerr << "Binary path does not exist" << std::endl;
        exit(1);
    }
    if (access(binary_path.c_str(), X_OK) == -1) {
        std::cerr << "Binary path is not executable" << std::endl;
        exit(1);
    }
}

std::string getEscapedString(std::string str)
{
    std::string escaped = "";
    for (auto &c : str) {
        if (c == '"') {
            escaped += "\\\"";
        } else if (c == '\\') {
            escaped += "\\\\";
        } else if (c == '\n') {
            escaped += "\\n";
        } else if (c == '\t') {
            escaped += "\\t";
        } else {
            escaped += c;
        }
    }
    return escaped;
}

void Tester::test()
{
    uint32_t succedded = 0;
    uint32_t failed = 0;
    uint32_t total = _tests.size();
    uint32_t crashed = 0;

    for (auto &test : _tests) {
        TestResult result = test.second->run(_binary_path);
        if (result.getFailed()) {
            failed++;
            if (result.getReturn() == 137 || result.getReturn() == 124 || result.getReturn() == 139 || result.getReturn() == 136)
                crashed++;
            std::cout << "[\033[31;2mFAILED\033[0m] " << test.first << std::endl;
            std::cout << "Expected output: \"" << getEscapedString(test.second->_expected_output) << "\"\n";
            std::cout << "Output: \"" << getEscapedString(result.getOutput()) << "\"\n";
            std::cout << "Expected error: \"" << getEscapedString(test.second->_expected_error) << "\"\n";
            std::cout << "Error: \"" << getEscapedString(result.getError()) << "\"\n";
            std::cout << "Expected return: " << (int)test.second->_expected_return << std::endl;
            std::cout << "Return: " << (int)result.getReturn() << std::endl;
            std::cout << "Runned time: " << result.getRunnedTime().count() << "ms" << std::endl;
            std::cout << std::endl << std::endl;
        } else {
            succedded++;
            std::cout << "[\033[32mPASSED\033[0m] " << test.first << std::endl;
        }
    }
    std::printf("\nNombre de tests réussis : ");
    if (failed != 0 ) {
        printf("\033[1;32m%d\033[0m\033[31;2m/%d\033[0m\n", succedded, total);
        std::printf("\033[31;2m%d tests ont échoué, dont %d ont crash ou timeout.\033[0m\n", failed, crashed);
    } else {
        std::printf("\033[1;32m%d/%d\033[0m\n", succedded, total);
        std::printf("\033[32mTous les tests ont réussi !\033[0m");
    }
    exit(failed != 0);
}

void Tester::addTest(std::string title, std::vector<std::string> params, std::string expected_output, std::string expected_error, int expected_return, std::optional<std::chrono::seconds> timeout = std::nullopt)
{
    if (_tests.find(title) != _tests.end()) {
        std::cerr << "Test with title " << title << " already exists" << std::endl;
        return;
    }
    std::shared_ptr<Test> test = std::make_shared<Test>(title, params, expected_output, expected_error, expected_return, timeout);
    _tests[title] = test;
}

void Tester::addTest(Test test)
{
    if (_tests.find(test._title) != _tests.end()) {
        std::cerr << "Test with title " << test._title << " already exists" << std::endl;
        return;
    }

    _tests[test._title] = std::make_shared<Test>(test);
}
