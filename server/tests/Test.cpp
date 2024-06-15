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
    _runnedTime = runned_time;
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
    return _runnedTime;
}

void TestResult::setFailed(bool failed)
{
    _failed = failed;
}

bool TestResult::getFailed()
{
    return _failed;
}

Test::Test(std::string title, std::vector<std::string> params, std::string expectedOutput, std::string expectedError, int expectedReturn, std::optional<std::chrono::seconds> timeout = std::nullopt) : _title(title), _params(params), _expectedOutput(expectedOutput), _expectedError(expectedError), _expectedReturn(expectedReturn), _timeout(timeout)
{
}

TestResult Test::run(std::string binaryPath)
{
    TestResult result;

    std::string command = binaryPath + " ";

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

    if (ret_val != _expectedReturn) {
        if (ret_val != 124 && _expectedReturn == 0) {
            result.setFailed(true);
        }
    }
    if (!output.starts_with(_expectedOutput)) {
        result.setFailed(true);
    }
    if (!error.starts_with(_expectedError)) {
        result.setFailed(true);
    }
    return result;
}

Tester::Tester(const std::string &binaryPath) : _binaryPath(binaryPath)
{
    if (binaryPath.empty()) {
        std::cerr << "Binary path is empty" << std::endl;
        exit(1);
    }
    if (access(binaryPath.c_str(), F_OK) == -1) {
        std::cerr << "Binary path does not exist" << std::endl;
        exit(1);
    }
    if (access(binaryPath.c_str(), X_OK) == -1) {
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
        TestResult result = test.second->run(_binaryPath);
        if (result.getFailed()) {
            failed++;
            if (result.getReturn() == 137 || result.getReturn() == 124 || result.getReturn() == 139 || result.getReturn() == 136)
                crashed++;
            std::cout << "[\033[31;2mFAILED\033[0m] " << test.first << std::endl;
            std::cout << "Expected output: \"" << getEscapedString(test.second->_expectedOutput) << "\"\n";
            std::cout << "Output: \"" << getEscapedString(result.getOutput()) << "\"\n";
            std::cout << "Expected error: \"" << getEscapedString(test.second->_expectedError) << "\"\n";
            std::cout << "Error: \"" << getEscapedString(result.getError()) << "\"\n";
            std::cout << "Expected return: " << (int)test.second->_expectedReturn << std::endl;
            std::cout << "Return: " << (int)result.getReturn() << std::endl;
            std::cout << "Runned time: " << result.getRunnedTime().count() << "ms" << std::endl;
            std::cout << std::endl << std::endl;
        } else {
            succedded++;
            #ifdef SILENT
            std::cout << "[\033[32mPASSED\033[0m] " << test.first << std::endl;
            #endif
        }
    }
    std::printf("Nombre de tests réussis: ");
    if (failed != 0 ) {
        printf("\033[1;32m%d\033[0m\033[31;2m/%d\033[0m\n", succedded, total);
        std::printf("\033[31;2m%d tests ont échoué, dont %d ont crash ou timeout.\033[0m\n", failed, crashed);
    } else {
        std::printf("\033[1;32m%d/%d\033[0m\n", succedded, total);
        std::printf("\033[32mTous les tests ont réussi !\033[0m\n");
    }
    exit(failed != 0);
}

void Tester::addTest(std::string title, std::vector<std::string> params, std::string expectedOutput, std::string expectedError, int expectedReturn, std::optional<std::chrono::seconds> timeout = std::nullopt)
{
    if (_tests.find(title) != _tests.end()) {
        std::cerr << "Test with title " << title << " already exists" << std::endl;
        return;
    }
    std::shared_ptr<Test> test = std::make_shared<Test>(title, params, expectedOutput, expectedError, expectedReturn, timeout);
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
