#ifndef POINT_H_
#define POINT_H_

class Point {

public:
  Point() : col_(0), row_(0) {}
  Point(int row, int col) : col_(col), row_(row) {}

  int row() const { return row_; }
  int col() const { return col_; }

  friend bool operator==(const Point& lhs, const Point& rhs);

private:
  int col_;
  int row_;
}; // Point

#endif // POINT_H_
