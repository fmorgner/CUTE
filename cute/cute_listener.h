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

#ifndef CUTE_LISTENER_H_
#define CUTE_LISTENER_H_
#include "cute_base.h"
#include "cute_suite.h"
#include "cute_determine_chrono.h"
namespace cute {
  namespace chrono = impl_place_for_chrono::chrono;
  typedef chrono::steady_clock clock;

	struct null_listener{ // defines Contract of runner parameter
		void begin(suite const &, char const * /*info*/, size_t /*n_of_tests*/, clock::time_point const & /*start_time*/){}
		void end(suite const &, char const * /*info*/, clock::time_point const & /*end_time*/){}
		void start(test const &, clock::time_point const & /*start_time*/){}
		void success(test const &,char const * /*msg*/, clock::time_point const & /*end_time*/){}
		void failure(test const &,test_failure const &, clock::time_point const & /*end_time*/){}
		void error(test const &,char const * /*what*/, clock::time_point const & /*end_time*/){}
	};
}
#endif /* CUTE_LISTENER_H_ */

