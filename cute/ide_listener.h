/*********************************************************************************
 * This file is part of CUTE.
 *
 * CUTE is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CUTE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with CUTE.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright 2007-2013 Peter Sommerlad
 *
 *********************************************************************************/

#ifndef IDE_LISTENER_H_
#define IDE_LISTENER_H_
#include "cute_listener.h"
#include <iostream>
#include <algorithm>
#ifdef _MSC_VER
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <sstream>
#endif
namespace cute {
	template <typename Listener=null_listener>
	struct ide_listener: public Listener
	{
		ide_listener(std::ostream &os=std::cout):out(os) {}
		void begin(suite const &t,char const *info, size_t n_of_tests, clock::time_point const & start_time){
			out << std::dec << "\n#beginning " << info << " " << n_of_tests << '\n';
			Listener::begin(t,info,n_of_tests,start_time);
		}
		void end(suite const &t, char const *info, clock::time_point const & end_time){
			out << "\n#ending " << info << std::endl;
			Listener::end(t,info,end_time);
		}
		void start(test const &t, clock::time_point const & start_time){
			out << "\n#starting " << t.name()<<'\n';
			Listener::start(t, start_time);
		}
		void success(test const &t, char const *msg, clock::time_point const & end_time){
			out << "\n#success " <<  maskBlanks(t.name()) <<" " << msg<< '\n';
			Listener::success(t,msg,end_time);
		}
		void failure(test const &t,test_failure const &e, clock::time_point const & end_time){
			out << std::dec <<  "\n#failure " << maskBlanks(t.name()) << " " << e.filename << ":" << e.lineno << " " << (e.reason) << '\n';
			Listener::failure(t,e,end_time);
#ifdef _MSV_VER
			std::ostringstream os;
			os << std::dec << e.filename << "(" << e.lineno << ") : failure: " <<e.reason << " in " << t.name()<< std::endl;
			OutputDebugString(os.str().c_str());
#endif
		}
		void error(test const &t, char const *what, clock::time_point const & end_time){
			out << "\n#error " << maskBlanks(t.name()) << " " << what <<'\n';
			Listener::error(t,what,end_time);
#ifdef _MSV_VER
			std::ostringstream os;
			os << what << " error in " << t.name() << std::endl;
			OutputDebugString(os.str().c_str());
#endif
		}
		static std::string maskBlanks(std::string in) {
			std::transform(in.begin(),in.end(),in.begin(),blankToUnderscore());
			return in;
		}
	protected:
		struct blankToUnderscore{
            char operator()(char in) const {
			if (in == ' ') return '_';
			return in;
		}
        };
		std::ostream &out;
	};
}

#endif /*IDE_LISTENER_H_*/
