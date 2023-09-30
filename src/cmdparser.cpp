#include "cmdparser.hpp"

CmdParser::CmdParser(const std::vector<std::string>& args,
			const std::vector<CmdParser::Handler>& handlers) {

	int c = 0;
	for ( std::string arg : args )

		if ( c++ == 0 ) this -> _cmd = arg;
		else this -> _args.push_back(arg);

	this -> _handlers = handlers;

}

#include <iostream>

struct ArgHandler {

	int index;
	std::string cmd;
	std::string arg;
	bool needs_arg;

	ArgHandler() : index(-1), cmd(""), arg(""), needs_arg(false) {}

	void reset() {
		this -> cmd = "";
		this -> arg = "";
		this -> index = -1;
		this -> needs_arg = false;
	}

};

void CmdParser::parse(void) {

	std::cout << "cmd: " << this -> _cmd << std::endl;

	std::vector<CmdParser::Arg> parsed;
	ArgHandler p_handler;

	//int c = 0;
	for ( std::string arg : this -> _args ) {

		int i = 0;
		bool unlisted = true;

		if ( p_handler.needs_arg ) {
			p_handler.arg = arg;

			std::cout << "handling #" << p_handler.index << ": " <<
				p_handler.cmd << " with param " << p_handler.arg << std::endl;

			p_handler.reset();
			continue;
		}

		for ( CmdParser::Handler handler : this -> _handlers ) {

			for ( std::string h_arg : handler.args )
				if ( h_arg == arg ) {

					unlisted = false;

					p_handler.index = i;
					p_handler.cmd = arg;
					p_handler.needs_arg = handler.needs_arg;

					if ( p_handler.needs_arg )
						break;

					// run handler + reset

					std::cout << "handling #" << p_handler.index << ": " <<
						p_handler.cmd << " without param" << std::endl;

					p_handler.reset();
					break;
				}
			i++;
		}

		if ( !unlisted )
			continue;

		// unlisted

		i = 0;

		for ( CmdParser::Handler handler : this -> _handlers )
			if ( handler.args.size() == 1 && handler.args[0].empty()) {

				p_handler.index = i;
				p_handler.cmd = arg;

				std::cout << "handling unknown #" << i << ": " <<
					p_handler.cmd << std::endl;

				break;
			}

/*
		std::cout << "#" << c << ": " << arg << std::endl;
		prevArg = arg;
		c++;
*/
	}

	if ( p_handler.needs_arg ) {

		std::cout << "parameter missing for #" << p_handler.index << ": " <<
			p_handler.cmd << std::endl;

		p_handler.reset();
	}

/*
	this -> _handlers[0].cmd("", "");
*/
}
