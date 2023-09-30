#pragma once
#include <functional>
#include <vector>
#include <string>

class CmdParser {

	public:

		struct Arg {
			std::string arg;
			std::string param;
		};

		struct Handler {
			std::vector<std::string> args;
			std::function<void(const CmdParser::Arg &arg)> cmd =
				[](const CmdParser::Arg &arg) {};
			bool needs_arg = false;
		};

		CmdParser(
			const std::vector<std::string>& args,
			const std::vector<CmdParser::Handler>& handlers
		);

	private:

		std::string _cmd;
		std::vector<std::string> _args;
		std::vector<CmdParser::Handler> _handlers;

	public:

		inline std::string cmd(void) { return this -> _cmd; }
		inline std::vector<std::string> args(void) { return this -> _args; }
		inline std::vector<CmdParser::Handler> handlers(void) { return this -> _handlers; }

		void parse(void);
};
