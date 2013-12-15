#ifndef _TASK4_5_SOLUTION_H_
#define _TASK4_5_SOLUTION_H_

#include <vector>
#include <boost/thread.hpp>

namespace task4_5
{
	typedef std::vector< std::vector< int > > data_type;
	typedef data_type matrix_type;

	// 
	class FindMinMaxElementsInMatrix : virtual protected boost::noncopyable {
		typedef std::vector<int> row_type;

	  class FindMinMaxElementsInRow : virtual protected boost::noncopyable {
	  public:
		FindMinMaxElementsInRow(FindMinMaxElementsInMatrix* parent,
								const row_type& row);
		void Run();

	  private:
		const row_type& row_;
		FindMinMaxElementsInMatrix* parent_;
	  };

    friend class FindMinMaxElementsInRow;
	  typedef boost::shared_ptr<FindMinMaxElementsInRow> RowProcessorPtr;

	public:
	  explicit FindMinMaxElementsInMatrix(const matrix_type& matrix);

  private:
	  void PutRowResults(const std::pair<int, int>& rr);

  public:
	  void Perform();
	  int GetMinElement() const;
	  int GetMaxElement() const;

	private:
	  int minimal_element_;
	  int maximal_element_;

	  boost::mutex rows_results_guard_;
	  boost::thread_group thg_;
	  
	  std::vector<std::pair<int, int> > rows_results_;  
	  const matrix_type& matrix_;
	};

	//
	class solution
	{
	public:
		explicit solution( const data_type& data );
		int get_min() const;
		int get_max() const;
	private:
		FindMinMaxElementsInMatrix data_processor_;
	};
}

#endif // _TASK4_5_SOLUTION_H_