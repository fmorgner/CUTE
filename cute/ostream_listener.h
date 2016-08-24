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
 * Copyright 2007-2009 Peter Sommerlad
 *
 *********************************************************************************/

#ifndef OSTREAM_LISTENER_H_
#define OSTREAM_LISTENER_H_
#include "cute_listener.h"
#include <iostream>
namespace cute {
	// a "root" listener displaying output, use it as an example on how to build your own, e.g., for XML output
	template <typename Listener=null_listener>
	struct ostream_listener:Listener
	{
		std::ostream &out;
    clock::time_point suite_start;
    clock::time_point test_start;
	public:
		ostream_listener(std::ostream &os=std::cerr):out(os) {}
		void begin(suite const &t,char const *info, size_t n_of_tests, clock::time_point const & start_time){
			out << "beginning: " << info << std::endl;
			suite_start = start_time;
			Listener::begin(t,info, n_of_tests, start_time);
		}
		void end(suite const &t, char const *info, clock::time_point const & end_time){
			chrono::milliseconds time_taken = chrono::duration_cast<chrono::milliseconds>(end_time - suite_start);
			out << "ending: " << info << " (took " << time_taken.count() << "ms)" << std::endl;
			Listener::end(t,info,end_time);
		}
		void start(test const &t, clock::time_point const & start_time){
			out << "starting: " << t.name() << std::endl;
			test_start = start_time;
			Listener::start(t, start_time);
		}
		void success(test const &t, char const *msg, clock::time_point const & end_time){
			chrono::milliseconds time_taken = chrono::duration_cast<chrono::milliseconds>(end_time - test_start);
			out << t.name() << " " << msg << " (took " << time_taken.count() << "ms)" << std::endl;
			Listener::success(t,msg,end_time);
		}
		void failure(test const &t,test_failure const &e, clock::time_point const & end_time){
			chrono::milliseconds time_taken = chrono::duration_cast<chrono::milliseconds>(end_time - test_start);
			out << std::dec << e.filename << ":" << e.lineno << ": testcase failed: " << e.reason << " in " << t.name()
				<< " (took " << time_taken.count() << "ms)" << std::endl;
			Listener::failure(t,e,end_time);
		}
		void error(test const &t, char const *what, clock::time_point const & end_time = clock::now()){
			chrono::milliseconds time_taken = chrono::duration_cast<chrono::milliseconds>(end_time - test_start);
			out << what << " in " << t.name() << " (took " << time_taken.count() << "ms)" << std::endl;
			Listener::error(t,what,end_time);
		}
	};
}
#endif /*OSTREAM_LISTENER_H_*/
