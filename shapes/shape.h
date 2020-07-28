#pragma once

#include <string>
#include <variant>

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
}

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


	class shape_t {
	public:
		shape_t( std::variant<Point, Rectangle, Circle, Triangle> ob ) :var( ob ) {}

		double get_area() {
			//double area = 0;
			return std::visit( []( auto& a )-> double {return a.get_area(); }, var );
			//return area;
		}

		std::string get_string() {
			return std::visit( []( auto& a )->std::string {return a.get_string(); }, var );
		}
	private:
		std::variant<Point, Rectangle, Circle, Triangle> var;

	};


}

