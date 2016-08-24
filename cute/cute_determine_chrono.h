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
 * Copyright 2016 Felix Morgner
 *
 *********************************************************************************/

#ifndef CUTE_DETERMINE_CHRONO_H_
#define CUTE_DETERMINE_CHRONO_H_
#include "cute_determine_version.h"
#if defined(USE_STD11)
#include <chrono>
#else
#define BOOST_SYSTEM_NO_DEPRECATED
#define BOOST_CHRONO_HEADER_ONLY
#define BOOST_CHRONO_DONT_PROVIDE_HYBRID_ERROR_HANDLING
#include <boost/chrono.hpp>
#endif
#if defined(USE_STD11)
	namespace impl_place_for_chrono = std;
#else
	namespace impl_place_for_chrono = boost;
#endif

#endif /* CUTE_DETERMINE_CHRONO_H_ */
