#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <memory>
#include <variant>

#include "shape.h"

template<int mechanism>
std::string f( std::vector<std::string> vec ) {
	std::string error_message( "Unrecognized shape identifier\n" );

	if constexpr ( mechanism == 0 ) {
		using shape_t = std::unique_ptr<dynamic::Shape>;

		std::vector<shape_t> shapes;

		for ( auto& x : vec ) {

			auto s = x.substr( 0, x.find( ' ' ) );

			if ( s.size() != 1 )
				return  error_message;

			switch ( x[ 0 ] ) {
			case 'R':
				shapes.emplace_back( std::make_unique<dynamic::Rectangle>( x ) );
				break;
			case 'C':
				shapes.emplace_back( std::make_unique<dynamic::Circle>( x ) );
				break;
			case 'P':
				shapes.emplace_back( std::make_unique<dynamic::Point>( x ) );
				break;
			case 'T':
				shapes.emplace_back( std::make_unique<dynamic::Triangle>( x ) );
				break;
			default:
				return error_message;
			}
		}

		std::sort( shapes.begin(), shapes.end(), []( shape_t& shape1, shape_t& shape2 ) {return shape1->get_area() < shape2->get_area(); } );

		std::string str{};
		std::for_each( shapes.begin(), shapes.end(), [&]( shape_t& sh ) {str += sh->get_string(); } );

		return str;
	}
	else if constexpr ( mechanism == 1 ) {
		using shape_t = semi_dynamic::shape_t;

		std::vector<shape_t> shapes;

		for ( auto& x : vec ) {

			auto s = x.substr( 0, x.find( ' ' ) );

			if ( s.size() != 1 )
				return  error_message;

			switch ( x[ 0 ] ) {
			case 'R':
				shapes.emplace_back( semi_dynamic::shape_t( semi_dynamic::Rectangle( x ) ) );
				break;
			case 'C':
				shapes.emplace_back( semi_dynamic::shape_t( semi_dynamic::Circle( x ) ) );
				break;
			case 'P':
				shapes.emplace_back( semi_dynamic::shape_t( semi_dynamic::Point( x ) ) );
				break;
			case 'T':
				shapes.emplace_back( semi_dynamic::shape_t( semi_dynamic::Triangle( x ) ) );
				break;
			default:
				return error_message;
			}
		}

		std::sort( shapes.begin(), shapes.end(), []( shape_t& a, shape_t& b ) {return a.get_area() < b.get_area(); } );

		std::string str{};
		std::for_each( shapes.begin(), shapes.end(), [&]( shape_t& sh ) {str += sh.get_string(); } );

		return str;
	}
	else return "Unsupported polymorphism_mechanism value " + std::to_string( mechanism ) + '\n';
}


// polymorphism_mechanism 0 for dynamic, 1 for semi-dynamic
std::string sort_shape_areas( const std::string& in_shapes_str, int polymorphism_mechanism ) {

	std::vector<std::string> vec;

	size_t n1 = 0;
	size_t n2 = 0;

	while ( true ) {
		n2 = in_shapes_str.find( '\n', n1 );
		if ( n2 > in_shapes_str.size() )
			break;
		vec.push_back( in_shapes_str.substr( n1, ( n2 - n1 ) ) );
		n1 = n2 + 1;
	}

	try {
		//????????????????????????????
		return f<polymorphism_mechanism>( vec );
	}
	catch ( std::exception& e ) {
		return e.what();
	}
	catch ( ... ) {
		return "Unexcepted error\n";
	}

}

std::string generate() {
	std::string text = "";
	text += "C 5 -9 1\n";
	text += "C 8 -88 9.1\n";
	text += "C 5 -9 6\n";
	text += "R -4.5 6 3 -1\n";
	text += "R 8 -5.26 9 -7\n";
	text += "R -1 1 2 -3\n";
	text += "P 5 2.85\n";
	text += "P 4 2\n";
	text += "P 8 5\n";
	text += "P -94 5\n";
	text += "T 4 5 -99 4 12 5\n";
	text += "T 9 -7 4 -2 2 5\n";
	text += "T 6 4 6 8 7 4\n";
	text += "T 0 5 0 1 1 0\n";
	text += "T 0 0 0 -10 100 0\n";

	return text;
}

int main() {

	std::string text = generate();

	constexpr int polymorphism_mechanism = 1;

	std::cout << sort_shape_areas( text, polymorphism_mechanism ) << std::endl;
	std::cout << sort_shape_areas( text, polymorphism_mechanism - 1 ) << std::endl;


	return 0;
}
