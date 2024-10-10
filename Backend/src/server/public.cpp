#include "public.hpp"
#include <iostream>
#include <dlfcn.h>
#include <string>


std::vector<std::string> stringToArray(std::string str)
{
    std::vector<std::string> result;
    int start = 0;
    int curr = str.find(',');
    while (curr != std::string::npos)
    {
        result.push_back(str.substr(start,curr-start));
        start = curr + 1;
        curr = str.find(',',start);
    }
    result.push_back(str.substr(start));
    return result;
}
std::string getCurrentTimeString()
{
    auto now = std::chrono::system_clock::now();
    auto now_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&now_t), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}
std::string chatglm(std::string& question, std::string& model_path) {
    void* handle = dlopen("/usr/local/bin/libchatgml.so", RTLD_NOW);
    std::string promt = "请帮我把一下句子分割成不同的要做的todo事项，以,分割每一个todo项,你的回答不需要任何其他内容，只有todo事项和,组成:";
	question = promt + question;
    typedef std::string (*HelloFunctionType)(std::string&, std::string&);
    HelloFunctionType hello_function = reinterpret_cast<HelloFunctionType>(dlsym(handle, "hello"));
    std::string answer = hello_function(question, model_path);
    dlclose(handle);
    return answer;
}

std::string getHupuRes() 
{
    std::array<char, 128> buffer;
    std::string result;

    FILE* pipe = popen("python3 /home/workspace/AI-Todo/pythonScript/hupu.py", "r");
    if (!pipe) {
        std::cerr << "Failed to open pipe for output" << std::endl;
        return "error";
    }

    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        result += buffer.data();
    }
    int returnCode = pclose(pipe);
    return result;
};