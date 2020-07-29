#include <string>
#include <vector>
#include <stdexcept>
#include <numbers>
#include <cmath>
#include <algorithm>
#include <memory>
#include "shape.h"

// Unnamed namespace for helper functions
// and some structs for returning object's arguments from functions.
// In functions `begin` and `end` variables using for finding parameters from string.
// `begin` points one past the first white space after shape identifier.
namespace {

	// Convertin argument's string representation to double with error handling.
	double convert( std::string& str ) {
		try {

			{
				size_t dot_count = 0, minus_count = 0;

				for ( char c : str ) {
					if ( std::ispunct( c ) && c == '.' ) {
						++dot_count;
						if ( dot_count > 1 )
							throw std::exception();
						continue;
					}
					if ( std::ispunct( c ) && c == '-' ) {
						++minus_count;
						if ( minus_count > 1 )
							throw std::exception();
						continue;
					}
					if ( !std::isdigit( c ) )
						throw std::exception();
				}
			}

			double coord = std::stod( str );

			return coord;
		}
		catch ( ... ) {
			std::string s = "Non-numeric parameter value " + str + '\n';
			throw std::invalid_argument( s );
		}
	}

	struct point_arguments {
		double x;
		double y;
	};

	struct circle_arguments {
		double x;
		double y;
		double r;
	};

	struct rectangle_argument {
		double left_x_coord;
		double top_y_coord;
		double right_x_coord;
		double bottom_y_coord;
	};

	struct triangle_argument {
		double x1;
		double y1;
		double x2;
		double y2;
		double x3;
		double y3;
	};

	point_arguments convert_point_argument( std::string& shape_str ) {
		std::vector<std::string> param;

		size_t begin = shape_str.find( ' ' ) + 1, end = 0;

		while ( true ) {
			end = shape_str.find( ' ', begin );
			param.push_back( shape_str.substr( begin, ( end - begin ) ) );
			if ( end > shape_str.size() )
				break;
			begin = end + 1;
		}

		// if parameters for `Point` is not equal 2 throws exception
		if ( param.size() != 2 ) {
			throw std::invalid_argument( "Wrong number of parameters for shape identifier P\n" );
		}

		return { convert( param[ 0 ] ),  convert( param[ 1 ] ) };
	}

	circle_arguments convert_circle_argument( std::string& shape_str ) {
		std::vector<std::string> param;

		size_t begin = shape_str.find( ' ' ) + 1, end = 0;

		while ( true ) {
			end = shape_str.find( ' ', begin );
			param.push_back( shape_str.substr( begin, ( end - begin ) ) );
			if ( end > shape_str.size() )
				break;
			begin = end + 1;
		}

		// if parameters for `Circle` is not equal 3 throws exception
		if ( param.size() != 3 )
			throw std::invalid_argument( "Wrong number of parameters for shape identifier C\n" );

		return{ convert( param[ 0 ] ), convert( param[ 1 ] ), convert( param[ 2 ] ) };
	}

	rectangle_argument convert_rectangle_argument( std::string& shape_str ) {
		std::vector<std::string> param;

		size_t begin = shape_str.find( ' ' ) + 1, end = 0;

		while ( true ) {
			end = shape_str.find( ' ', begin );
			param.push_back( shape_str.substr( begin, ( end - begin ) ) );
			if ( end > shape_str.size() )
				break;
			begin = end + 1;
		}

		// if parameters for `Rectangle` is not equal 4 throws exception
		if ( param.size() != 4 )
			throw std::invalid_argument( "Wrong number of parameters for shape identifier R\n" );

		return { convert( param[ 0 ] ),convert( param[ 1 ] ), convert( param[ 2 ] ), convert( param[ 3 ] ) };
	}

	triangle_argument convert_triangle_argument( std::string& shape_str ) {
		std::vector<std::string> param;

		size_t begin = shape_str.find( ' ' ) + 1, end = 0;

		while ( true ) {
			end = shape_str.find( ' ', begin );
			param.push_back( shape_str.substr( begin, ( end - begin ) ) );
			if ( end > shape_str.size() )
				break;
			begin = end + 1;
		}

		// if parameters for `Triangle` is not equal 6 throws exception
		if ( param.size() != 6 )
			throw std::invalid_argument( "Wrong number of parameters for shape identifier T\n" );

		return { convert( param[ 0 ] ),	convert( param[ 1 ] ),
			convert( param[ 2 ] ),convert( param[ 3 ] ),
			convert( param[ 4 ] ),convert( param[ 5 ] ) };
	}

}	// unnamed namespace

namespace dynamic {

	double Shape::get_area() {
		return area_;
	}

	std::string Shape::get_string() {
		return text_;
	}


	Point::Point( std::string& shape_str ) {

		{
			auto temp = convert_point_argument( shape_str );

			x_coord_ = temp.x;
			y_coord_ = temp.y;
		}

		calculate_area();
		create_string();
	}

	void Point::calculate_area() {
		area_ = 0;
	};

	void Point::create_string() {
		text_ = std::to_string( area_ );
		text_ += " Point " +
			std::to_string( x_coord_ ) + ' ' +
			std::to_string( y_coord_ ) + '\n';
	}


	Circle::Circle( std::string& shape_str ) {

		{
			auto temp = convert_circle_argument( shape_str );

			x_coord_ = temp.x;
			y_coord_ = temp.y;
			radius_ = temp.r;
		}

		if ( radius_ <= 0 )
			throw std::invalid_argument( "Invalid Circle shape\n" );

		calculate_area();
		create_string();
	}

	void Circle::calculate_area() {
		// std::numbers::pi  since C++20, defined in <numbers>
		area_ = std::numbers::pi * pow( radius_, 2 );
	}

	void Circle::create_string() {

		text_ = std::to_string( area_ );
		text_ += " Circle " +
			std::to_string( x_coord_ ) + ' ' +
			std::to_string( y_coord_ ) + ' ' +
			std::to_string( radius_ ) + '\n';
	}


	Rectangle::Rectangle( std::string& shape_str ) {

		{
			auto temp = convert_rectangle_argument( shape_str );

			left_x_coord_ = temp.left_x_coord;
			top_y_coord_ = temp.top_y_coord;
			right_x_coord_ = temp.right_x_coord;
			bottom_y_coord_ = temp.bottom_y_coord;
		}

		// if left-top corner's coordinates or right-bottom corner's coordinates are incorrect, throws exception
		if ( left_x_coord_ >= right_x_coord_ || top_y_coord_ <= bottom_y_coord_ )
			throw std::invalid_argument( "Invalid Rectangle shape\n" );

		calculate_area();
		create_string();
	}

	void Rectangle::calculate_area() {
		area_ = ( right_x_coord_ - left_x_coord_ ) * ( top_y_coord_ - bottom_y_coord_ );
	}

	void Rectangle::create_string() {
		text_ = std::to_string( area_ );
		text_ += " Rectangle " +
			std::to_string( left_x_coord_ ) + ' ' +
			std::to_string( top_y_coord_ ) + ' ' +
			std::to_string( right_x_coord_ ) + ' ' +
			std::to_string( bottom_y_coord_ ) + '\n';
	}


	Triangle::Triangle( std::string& shape_str ) {

		{
			auto temp = convert_triangle_argument( shape_str );

			x1_ = temp.x1;
			y1_ = temp.y1;
			x2_ = temp.x2;
			y2_ = temp.y2;
			x3_ = temp.x3;
			y3_ = temp.y3;
		}

		// if all abscissas or ordinates are on the same line, throws exception
		if ( ( x1_ == x2_ && x2_ == x3_ ) || ( y1_ == y2_ && y2_ == y3_ ) )
			throw std::invalid_argument( "Invalid Triangle shape\n" );

		calculate_area();
		create_string();
	}

	void Triangle::calculate_area() {
		double side1 = sqrt( pow( x1_ - x2_, 2 ) + pow( y1_ - y2_, 2 ) );
		double side2 = sqrt( pow( x2_ - x3_, 2 ) + pow( y2_ - y3_, 2 ) );
		double side3 = sqrt( pow( x1_ - x3_, 2 ) + pow( y1_ - y3_, 2 ) );

		double half_perimeter = ( side1 + side2 + side3 ) / 2.;

		area_ = sqrt( half_perimeter * ( half_perimeter - side1 ) *
			( half_perimeter - side2 ) * ( half_perimeter - side3 ) );
	}

	void Triangle::create_string() {
		text_ = std::to_string( area_ );
		text_ += " Triangle " +
			std::to_string( x1_ ) + ' ' +
			std::to_string( y1_ ) + ' ' +
			std::to_string( x2_ ) + ' ' +
			std::to_string( y2_ ) + ' ' +
			std::to_string( x3_ ) + ' ' +
			std::to_string( y3_ ) + '\n';
	}
} // dynamic namespace

namespace semi_dynamic {

	Point::Point( std::string& shape_str ) :area_( 0 ) {

		{
			auto temp = convert_point_argument( shape_str );

			x_coord_ = temp.x;
			y_coord_ = temp.y;
		}

		create_string();
	}

	void Point::create_string() {
		text_ = std::to_string( area_ );
		text_ += " Point " +
			std::to_string( x_coord_ ) + ' ' +
			std::to_string( y_coord_ ) + '\n';
	}

	std::string Point::get_string() {
		return text_;
	}

	double Point::get_area() {
		return area_;
	}


	Circle::Circle( std::string& shape_str ) {

		{
			auto temp = convert_circle_argument( shape_str );

			x_coord_ = temp.x;
			y_coord_ = temp.y;
			radius_ = temp.r;
		}

		if ( radius_ <= 0 )
			throw std::invalid_argument( "Invalid Circle shape\n" );

		calculate_area();
		create_string();
	}

	void Circle::calculate_area() {
		// std::numbers::pi  since C++20, defined in <numbers>
		area_ = std::numbers::pi * pow( radius_, 2 );
	}

	double Circle::get_area() {
		return area_;
	}

	void Circle::create_string() {

		text_ = std::to_string( area_ );
		text_ += " Circle " +
			std::to_string( x_coord_ ) + ' ' +
			std::to_string( y_coord_ ) + ' ' +
			std::to_string( radius_ ) + '\n';
	}

	std::string Circle::get_string() {
		return text_;
	}


	Rectangle::Rectangle( std::string& shape_str ) {

		{
			auto temp = convert_rectangle_argument( shape_str );

			left_x_coord_ = temp.left_x_coord;
			top_y_coord_ = temp.top_y_coord;
			right_x_coord_ = temp.right_x_coord;
			bottom_y_coord_ = temp.bottom_y_coord;
		}

		// same as above
		if ( left_x_coord_ >= right_x_coord_ || top_y_coord_ <= bottom_y_coord_ )
			throw std::invalid_argument( "Invalid Rectangle shape\n" );

		calculate_area();
		create_string();
	}

	void Rectangle::calculate_area() {
		area_ = ( right_x_coord_ - left_x_coord_ ) * ( top_y_coord_ - bottom_y_coord_ );
	}

	double Rectangle::get_area() {
		return area_;
	}

	void Rectangle::create_string() {
		text_ = std::to_string( area_ );
		text_ += " Rectangle " +
			std::to_string( left_x_coord_ ) + ' ' +
			std::to_string( top_y_coord_ ) + ' ' +
			std::to_string( right_x_coord_ ) + ' ' +
			std::to_string( bottom_y_coord_ ) + '\n';
	}

	std::string Rectangle::get_string() {
		return text_;
	}


	Triangle::Triangle( std::string& shape_str ) {

		{
			auto temp = convert_triangle_argument( shape_str );

			x1_ = temp.x1;
			y1_ = temp.y1;
			x2_ = temp.x2;
			y2_ = temp.y2;
			x3_ = temp.x3;
			y3_ = temp.y3;
		}

		// same as above
		if ( ( x1_ == x2_ && x2_ == x3_ ) || ( y1_ == y2_ && y2_ == y3_ ) )
			throw std::invalid_argument( "Invalid Triangle shape\n" );

		calculate_area();
		create_string();
	}

	void Triangle::calculate_area() {
		double side1 = sqrt( pow( x1_ - x2_, 2 ) + pow( y1_ - y2_, 2 ) );
		double side2 = sqrt( pow( x2_ - x3_, 2 ) + pow( y2_ - y3_, 2 ) );
		double side3 = sqrt( pow( x1_ - x3_, 2 ) + pow( y1_ - y3_, 2 ) );

		double half_perimeter = ( side1 + side2 + side3 ) / 2.;

		area_ = sqrt( half_perimeter * ( half_perimeter - side1 ) *
			( half_perimeter - side2 ) * ( half_perimeter - side3 ) );
	}

	double Triangle::get_area() {
		return area_;
	}

	void Triangle::create_string() {
		text_ = std::to_string( area_ );
		text_ += " Triangle " +
			std::to_string( x1_ ) + ' ' +
			std::to_string( y1_ ) + ' ' +
			std::to_string( x2_ ) + ' ' +
			std::to_string( y2_ ) + ' ' +
			std::to_string( x3_ ) + ' ' +
			std::to_string( y3_ ) + '\n';
	}

	std::string Triangle::get_string() {
		return text_;
	}

} // semi_dynamic namespace

std::string construct( std::vector<std::string> shapes_description, int polymorphism_mechanism ) {

	std::string error_message( "Unrecognized shape identifier\n" );

	if ( polymorphism_mechanism == 0 ) {
		using shape_t = std::unique_ptr<dynamic::Shape>;

		std::vector<shape_t> shapes;

		for ( auto& shape_str : shapes_description ) {

			// Get a string from shape_str's first character to the first white space,
			// which will contain the shape identifier
			auto shape_id = shape_str.substr( 0, shape_str.find( ' ' ) );

			// If shape identifier is more than one symbol, returning error message
			if ( shape_id.size() != 1 )
				return  error_message;

			switch ( shape_str[ 0 ] ) {
			case 'R':
				shapes.emplace_back( std::make_unique<dynamic::Rectangle>( shape_str ) );
				break;
			case 'C':
				shapes.emplace_back( std::make_unique<dynamic::Circle>( shape_str ) );
				break;
			case 'P':
				shapes.emplace_back( std::make_unique<dynamic::Point>( shape_str ) );
				break;
			case 'T':
				shapes.emplace_back( std::make_unique<dynamic::Triangle>( shape_str ) );
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
	else if ( polymorphism_mechanism == 1 ) {
		using shape_t = semi_dynamic::shape_t;

		std::vector<shape_t> shapes;

		for ( auto& shape_str : shapes_description ) {

			// Same as above
			auto shape_id = shape_str.substr( 0, shape_str.find( ' ' ) );

			if ( shape_id.size() != 1 )
				return  error_message;

			switch ( shape_str[ 0 ] ) {
			case 'R':
				shapes.emplace_back( semi_dynamic::shape_t( semi_dynamic::Rectangle( shape_str ) ) );
				break;
			case 'C':
				shapes.emplace_back( semi_dynamic::shape_t( semi_dynamic::Circle( shape_str ) ) );
				break;
			case 'P':
				shapes.emplace_back( semi_dynamic::shape_t( semi_dynamic::Point( shape_str ) ) );
				break;
			case 'T':
				shapes.emplace_back( semi_dynamic::shape_t( semi_dynamic::Triangle( shape_str ) ) );
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
	else return "Unsupported polymorphism_mechanism value " + std::to_string( polymorphism_mechanism ) + '\n';
}

std::string sort_shape_areas( const std::string& in_shapes_str, int polymorphism_mechanism ){

	// for all shapes descriptions
	std::vector<std::string> shape_description;

	// for finding new line symbols for deviding shapes
	size_t begin = 0, end = 0;

	while ( true ) {
		end = in_shapes_str.find( '\n', begin );

		// if there isn't new line then break
		if ( end > in_shapes_str.size() )
			break;

		auto shape = in_shapes_str.substr( begin, ( end - begin ) );
		// triming string
		auto begin = shape.find_first_not_of( ' ' );
		auto end = shape.find_last_not_of( ' ' );

		shape_description.push_back( shape.substr( begin, end + 1 ) );

		begin = end + 1;
	}

	try {
		return construct( shape_description, polymorphism_mechanism );
	}
	catch ( std::exception& e ) {
		return e.what();
	}
	catch ( ... ) {
		return "Unexcepted error\n";
	}

}
