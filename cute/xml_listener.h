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
 * Copyright 2007-2015 Peter Sommerlad
 *
 *********************************************************************************/

#ifndef XML_LISTENER_H_
#define XML_LISTENER_H_
#include "cute_listener.h"
#include "cute_xml_file.h" // for convenience
#include <iomanip>
#include <ostream>
#include <sstream>
namespace cute {
	template <typename Listener=null_listener>
	class xml_listener:public Listener
	{
	protected:
		std::string mask_xml_chars(std::string in){
			std::string::size_type pos=0;
			while((pos=in.find_first_of("\x00\x01\x02\x03\x04\x05\x06\x07\x08\x0b\x0c\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\"&'<>", pos, 34))!=std::string::npos){
				switch(in[pos]){
				case '&': in.replace(pos,1,"&amp;"); pos +=5; break;
				case '<': in.replace(pos,1,"&lt;"); pos += 4; break;
				case '>': in.replace(pos,1,"&gt;"); pos += 4; break;
				case '"': in.replace(pos,1,"&quot;"); pos+=6; break;
				case '\'':in.replace(pos,1,"&apos;"); pos+=6; break;
				default:
					char c = in[pos];
					std::string replacement = "0x" + cute_to_string::hexit(c);
					in.replace(pos, 1, replacement); pos += replacement.size(); break;
					break;
				}
			}
			return in;
		}

		void write_time_attribute(chrono::milliseconds const & duration, std::ostream & dest) {
			std::ios_base::fmtflags old = dest.flags();
			dest << std::dec << std::fixed << std::setprecision(3);
			dest << " time=\"" << duration.count() / 1000.f << '"';
			dest.setf(old);
		}

		std::ostream &out;
		std::string current_suite;
		std::ostringstream test_buffer;
		clock::time_point suite_start;
		clock::time_point test_start;
	public:
		xml_listener(std::ostream &os):out(os) {
			out << "<testsuites>\n";
		}
		~xml_listener(){
			out << "</testsuites>\n"<< std::flush;
		}

		void begin(suite const &t,char const *info, size_t n_of_tests, clock::time_point const & start_time){
			current_suite=mask_xml_chars(info);
			suite_start = start_time;
			out << std::dec << "\t<testsuite name=\"" << current_suite << "\" tests=\"" << n_of_tests << "\"";
			Listener::begin(t,info, n_of_tests, start_time);
		}
		void end(suite const &t, char const *info, clock::time_point const & end_time){
			write_time_attribute(chrono::duration_cast<chrono::milliseconds>(end_time - suite_start), out);
			out << ">\n";
			out << test_buffer.str();
			out << "\t</testsuite>\n";
			current_suite.clear();
			test_buffer.clear();
			test_buffer.str("");
			Listener::end(t,info, end_time);
		}
		void start(test const &t, clock::time_point const & start_time){
			test_buffer << "\t\t<testcase classname=\""<<current_suite <<"\" name=\""<< mask_xml_chars(t.name())<<"\"";
			test_start = start_time;
			Listener::start(t, start_time);
		}
		void success(test const &t, char const *msg, clock::time_point const & end_time){
			write_time_attribute(chrono::duration_cast<chrono::milliseconds>(end_time - test_start), test_buffer);
			test_buffer << "/>\n";
			Listener::success(t,msg,end_time);
		}
		void failure(test const &t,test_failure const &e, clock::time_point const & end_time){
			write_time_attribute(chrono::duration_cast<chrono::milliseconds>(end_time - test_start), test_buffer);
			test_buffer << std::dec <<  ">\n\t\t\t<failure message=\"" << mask_xml_chars(e.filename) << ":" << e.lineno << " "
				<< mask_xml_chars(e.reason) << "\">\n"<<mask_xml_chars(e.reason)<<"\n\t\t\t</failure>\n\t\t</testcase>\n";
			Listener::failure(t,e,end_time);
		}
		void error(test const &t, char const *what, clock::time_point const & end_time){
			write_time_attribute(chrono::duration_cast<chrono::milliseconds>(end_time - test_start), test_buffer);
			test_buffer << ">\n\t\t\t<error message=\"" << mask_xml_chars(t.name()) << " " << mask_xml_chars(what)
				<< "\" type=\"unexpected exception\">\n"<<mask_xml_chars(what)
				<<"\n\t\t\t</error>\n\t\t</testcase>\n";
			Listener::error(t,what,end_time);
		}
	};
}

#endif /*IDE_LISTENER_H_*/
