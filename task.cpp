#include <iostream>
#include <string>

int main() {
    std::string userInput;
    std::cout << "Welcome to the Chatbot. Type 'exit' to end the conversation." << std::endl;

    while (true) {
        std::cout << "You: ";
        std::getline(std::cin, userInput);   

        if (userInput == "exit") {
            std ::cout << "Chatbot: Goodbye!" << std::endl;
            break;
        } else if (userInput == "hello") {
            std::cout << "Chatbot: Hi there How can I help you ?" << std::endl;
        } else if (userInput == "how are you?") {
            std::cout << "Chatbot: I'm just a program, but thanks for asking" << std::endl;
        } else if (userInput == "what is your name?") {
            std::cout << "Chatbot: I am a simple chatbot created for this task." << std::endl;
        } else {
            std::cout << "Chatbot: I'm sorry, I don't understand that." << std::endl;
        }
    }
    return 0;
}