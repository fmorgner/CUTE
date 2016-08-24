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
 * Copyright 2007 Peter Sommerlad
 *
 *********************************************************************************/

#ifndef CUTE_COUNTING_LISTENER_H_
#define CUTE_COUNTING_LISTENER_H_
#include "cute_listener.h"
namespace cute{
	template <typename Listener=null_listener>
	struct counting_listener:Listener{
		counting_listener()
		:Listener()
		,numberOfTests(0),successfulTests(0),failedTests(0),errors(0),numberOfSuites(0),numberOfTestsInSuites(0),totalTimeTaken(0){}

		counting_listener(Listener const &s)
		:Listener(s)
		,numberOfTests(0),successfulTests(0),failedTests(0),errors(0),numberOfSuites(0),numberOfTestsInSuites(0),totalTimeTaken(0){}

		void begin(suite const &s,char const *info, size_t n_of_tests, clock::time_point const & start_time){
			++numberOfSuites;
			numberOfTestsInSuites+=n_of_tests;
			Listener::begin(s,info, n_of_tests, start_time);
		}
		void end(suite const &s, char const *info, clock::time_point const & end_time){
			averageTimePerTest = totalTimeTaken / numberOfSuites;
			Listener::end(s,info,end_time);
		}
		void start(test const &t, clock::time_point const & start_time){
			++numberOfTests;
			test_start = start_time;
			Listener::start(t, start_time);
		}
		void success(test const &t,char const *msg, clock::time_point const & end_time){
			++successfulTests;
			totalTimeTaken += chrono::duration_cast<chrono::milliseconds>(end_time - test_start).count();
			Listener::success(t,msg,end_time);
		}
		void failure(test const &t,test_failure const &e, clock::time_point const & end_time){
			++failedTests;
			totalTimeTaken += chrono::duration_cast<chrono::milliseconds>(end_time - test_start).count();
			Listener::failure(t,e,end_time);
		}
		void error(test const &t,char const *what, clock::time_point const & end_time){
			++errors;
			totalTimeTaken += chrono::duration_cast<chrono::milliseconds>(end_time - test_start).count();
			Listener::error(t,what,end_time);
		}
		size_t numberOfTests;
		size_t successfulTests;
		size_t failedTests;
		size_t errors;
		size_t numberOfSuites;
		size_t numberOfTestsInSuites;
		size_t totalTimeTaken;
		size_t averageTimePerTest;

		private:
			clock::time_point test_start;
	};
}
#endif /*CUTE_COUNTING_LISTENER_H_*/
