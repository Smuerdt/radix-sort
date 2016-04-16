#include "Dataset.h"

#include <cstdint>
#include <random>
#include <numeric>

template <typename DataType>
const char* const Dataset<DataType>::name = "UNKNOWN";

template <typename DataType>
const char* const Zeros<DataType>::name = "Zeros";

template <typename DataType>
const char* const Random<DataType>::name = "Uniform random";

template <typename DataType>
const char* const Range<DataType>::name = "Range";

template <typename DataType>
const char* const InvertedRange<DataType>::name = "Inverted range";

template <typename DataType>
Zeros<DataType>::Zeros()
{
	std::fill(dataset.begin(), dataset.end(), 0);
}

template <typename DataType>
Random<DataType>::Random()
{
	std::string seedStr("Schmutz :P");
	std::seed_seq seed(seedStr.begin(), seedStr.end());
	std::mt19937 generator(seed);

	/// TODO("Adapt to signed integers, later on.");
	std::uniform_int_distribution<DataType> dis(std::numeric_limits<DataType>::min(), std::numeric_limits<DataType>::max());
	// fill the array with some values
	std::generate(dataset.begin(), dataset.end(), std::bind(dis, generator));

	// Ensure that min and max are in the input array
	*dataset.begin() = std::numeric_limits<DataType>::max();
	*(dataset.end() - 1) = std::numeric_limits<DataType>::min();
}

template <typename DataType>
InvertedRange<DataType>::InvertedRange()
{
	std::iota(dataset.begin(), dataset.end(), std::numeric_limits<DataType>::min());
	std::reverse(dataset.begin(), dataset.end());
}

template <typename DataType>
Range<DataType>::Range()
{
	std::iota(dataset.begin(), dataset.end(), std::numeric_limits<DataType>::min());
}

template struct Dataset < int32_t > ;
template struct Dataset < int64_t > ;
template struct Dataset < uint32_t > ;
template struct Dataset < uint64_t > ;

template struct Random < int32_t > ;
template struct Random < int64_t > ;
template struct Random < uint32_t > ;
template struct Random < uint64_t > ;

template struct Zeros < int32_t > ;
template struct Zeros < int64_t > ;
template struct Zeros < uint32_t > ;
template struct Zeros < uint64_t > ;

template struct Range < int32_t > ;
template struct Range < int64_t > ;
template struct Range < uint32_t > ;
template struct Range < uint64_t > ;

template struct InvertedRange < int32_t >;
template struct InvertedRange < int64_t >;
template struct InvertedRange < uint32_t >;
template struct InvertedRange < uint64_t >;