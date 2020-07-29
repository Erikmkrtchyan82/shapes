#pragma once

#include <string>
#include <vector>
#include <variant>

// Using virtual functions for dynamic polymorphism
namespace dynamic {

	class Shape {
	public:
		double get_area();
		std::string get_string();
	protected:
		virtual void calculate_area() = 0;
		virtual void create_string() = 0;
		double area_;
		std::string text_;
	};

	class Point : public Shape {
	public:
		Point( std::string& );
	private:
		void calculate_area() override;
		void create_string() override;

		double x_coord_;
		double y_coord_;
	};

	class Circle : public Shape {
	public:
		Circle( std::string& );
	private:
		void calculate_area() override;
		void create_string() override;

		double x_coord_;
		double y_coord_;
		double radius_;
	};

	class Rectangle : public Shape {
	public:
		Rectangle( std::string& );
	private:
		void calculate_area() override;
		void create_string() override;

		double left_x_coord_;
		double top_y_coord_;
		double right_x_coord_;
		double bottom_y_coord_;
	};

	class Triangle : public Shape {
	public:
		Triangle( std::string& );
	private:
		void calculate_area() override;
		void create_string() override;

		double x1_;
		double y1_;
		double x2_;
		double y2_;
		double x3_;
		double y3_;
	};
} // dynamic namespace

// Using std::variant and std::visit for semi-dynamic polymorphism
namespace semi_dynamic {

	class Point {
	public:
		Point( std::string& );
		std::string get_string();
		double get_area();
	private:
		void create_string();

		double x_coord_;
		double y_coord_;
		double area_;
		std::string text_;
	};

	class Circle {
	public:
		Circle( std::string& );
		std::string get_string();
		double get_area();
	private:
		void calculate_area();
		void create_string();

		double x_coord_;
		double y_coord_;
		double radius_;
		double area_;
		std::string text_;
	};

	class Rectangle {
	public:
		Rectangle( std::string& );
		std::string get_string();
		double get_area();
	private:
		void calculate_area();
		void create_string();

		double left_x_coord_;
		double top_y_coord_;
		double right_x_coord_;
		double bottom_y_coord_;
		double area_;
		std::string text_;
	};

	class Triangle {
	public:
		Triangle( std::string& );
		std::string get_string();
		double get_area();
	private:
		void calculate_area();
		void create_string();

		double x1_;
		double y1_;
		double x2_;
		double y2_;
		double x3_;
		double y3_;
		double area_;
		std::string text_;
	};

	// class for wrapping geometric objects classes
	class shape_t {
	public:

		shape_t( std::variant<Point, Rectangle, Circle, Triangle> ob ) :var_( ob ) {}

		double get_area() {
			return std::visit( []( auto& a ) -> double {return a.get_area(); }, var_ );
		}

		std::string get_string() {
			return std::visit( []( auto& a )->std::string {return a.get_string(); }, var_ );
		}

	private:
		std::variant<Point, Rectangle, Circle, Triangle> var_;
	};

} // semi_dynamic namespace

// Gets vector of strings, which every element is a shape description,
//	and polymorphism mechanism, which can be 0 for dynamic polymorphism, and 1 for semy-dynamic polymorphism.
// For dynamic polymorphism solution implemented in `dynamic` namespace,
//  with smart pointers and virtual functions.
// For semi-dynamic polymorphism solution implemented in `semi_dynamic` namespace,
//  with std::variant and std::visit.
// Returns already sorted shape's string representation or error message.
std::string construct( std::vector<std::string>, int );

// `in_shapes_str` contains all shapes descriptions, and all of them ends with new line symbol
// `polymorphism_mechanism` explained above
std::string sort_shape_areas( const std::string&, int );
