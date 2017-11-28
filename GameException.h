#ifndef GAMEEXCEPTION_H_
#define GAMEEXCEPTION_H_

namespace game {
	// Exception type for the game
	class GameException : public std::exception
	{
	private:
		std::string message_;
	public:
		GameException(std::string message) : message_(message) {};
		virtual const char* what() const throw() { return message_.c_str(); };
		virtual ~GameException() throw() {};
	};
}

#endif