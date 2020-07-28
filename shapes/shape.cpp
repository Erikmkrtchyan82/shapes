#include <string>
#include <vector>
#include <stdexcept>
#include <numbers>
#include "shape.h"


namespace {
	double convert( std::string& str ) {
		try {
			double coord;
			coord = std::stod( str );
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

		size_t n1 = shape_str.find( ' ' ) + 1, n2 = 0;

		while ( true ) {
			n2 = shape_str.find( ' ', n1 );
			param.push_back( shape_str.substr( n1, ( n2 - n1 ) ) );
			if ( n2 > shape_str.size() )
				break;
			n1 = n2 + 1;
		}

		if ( param.size() != 2 ) {
			throw std::invalid_argument( "Wrong number of parameters for shape identifier P\n" );
		}

		return { convert( param[ 0 ] ),  convert( param[ 1 ] ) };
	}

	circle_arguments convert_circle_argument( std::string& shape_str ) {
		std::vector<std::string> param;

		size_t n1 = shape_str.find( ' ' ) + 1, n2 = 0;

		while ( true ) {
			n2 = shape_str.find( ' ', n1 );
			param.push_back( shape_str.substr( n1, ( n2 - n1 ) ) );
			if ( n2 > shape_str.size() )
				break;
			n1 = n2 + 1;
		}

		if ( param.size() != 3 )
			throw std::invalid_argument( "Wrong number of parameters for shape identifier C\n" );

		return{ convert( param[ 0 ] ), convert( param[ 1 ] ), convert( param[ 2 ] ) };
	}

	rectangle_argument convert_rectangle_argument( std::string& shape_str ) {
		std::vector<std::string> param;

		size_t n1 = shape_str.find( ' ' ) + 1, n2 = 0;

		while ( true ) {
			n2 = shape_str.find( ' ', n1 );
			param.push_back( shape_str.substr( n1, ( n2 - n1 ) ) );
			if ( n2 > shape_str.size() )
				break;
			n1 = n2 + 1;
		}

		if ( param.size() != 4 )
			throw std::invalid_argument( "Wrong number of parameters for shape identifier R\n" );

		return { convert( param[ 0 ] ),convert( param[ 1 ] ), convert( param[ 2 ] ), convert( param[ 3 ] )
		};
	}

	triangle_argument convert_triangle_argument( std::string& shape_str ) {
		std::vector<std::string> param;

		size_t n1 = shape_str.find( ' ' ) + 1, n2 = 0;

		while ( true ) {
			n2 = shape_str.find( ' ', n1 );
			param.push_back( shape_str.substr( n1, ( n2 - n1 ) ) );
			if ( n2 > shape_str.size() )
				break;
			n1 = n2 + 1;
		}

		if ( param.size() != 6 )
			throw std::invalid_argument( "Wrong number of parameters for shape identifier T\n" );

		return { convert( param[ 0 ] ),	convert( param[ 1 ] ),convert( param[ 2 ] ),convert( param[ 3 ] ),convert( param[ 4 ] ),convert( param[ 5 ] ) };
	}

}

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
		//	std::numbers::pi  since C++20
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
}

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
		//	std::numbers::pi  since C++20
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

}

