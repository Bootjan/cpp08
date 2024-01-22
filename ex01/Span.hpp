/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 22:29:22 by bootjan           #+#    #+#             */
/*   Updated: 2024/01/20 14:11:32 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
# define SPAN_HPP

# include <iomanip>
# include <iostream>

class Span
{
	private:
		const unsigned int	N;
		size_t				_len;
		int*				_arr;
	public:
		Span();
		Span(unsigned int n);
		Span( const Span& rhs);
		Span&	operator=( const Span& rhs);
		~Span();

		void	addNumber( int x );
		void	addRange( int start, int end );
		void	addRange( int start, int end, int increment );
		void	printNumbers( void ) const;
		int		shortestSpan( void ) const;
		int		longestSpan( void ) const;

		struct	ExecuteException : public std::runtime_error
		{
			ExecuteException(const std::string& message) : std::runtime_error(message) {}
		};

		struct	NotEnoughValues : public ExecuteException
		{
			NotEnoughValues() : ExecuteException("Not enough values to compute span") {}
		};

		struct	SpanFull : public ExecuteException
		{
			SpanFull() : ExecuteException("Span is full") {}
		};
};

Span::Span( void )
	:	N(100)
	,	_len(0)
{
	_arr = new int[N];
}

Span::Span( unsigned int n )
	:	N(n)
	,	_len(0)
{
	_arr = new int[N];
}

Span::Span( const Span& rhs )
	:	N(rhs.N)
	,	_len(rhs._len)
{
	_arr = new int[N];
	for (size_t idx = 0; idx < _len; idx++)
		_arr[idx] = rhs._arr[idx];
}

Span&	Span::operator=( const Span& rhs)
{
	if (this == &rhs)
		return *this;
	_len = rhs._len > N ? N : rhs._len;
	delete[] _arr;
	_arr = new int[N];
	for (size_t idx = 0; idx < _len; idx++)
		_arr[idx] = rhs._arr[idx];
	return *this;
}

Span::~Span()
{
	delete[] _arr;
}

void	Span::addNumber( int num )
{
	if (_len == N)
		throw SpanFull();
	_arr[_len++] = num;
}

void	Span::addRange( int start, int end )
{
	while (start < end)
		addNumber(start++);
}

void	Span::addRange( int start, int end, int increment )
{
	while (start < end)
	{
		addNumber(start);
		start += increment;
	}
}

void	Span::printNumbers( void ) const
{
	for (size_t idx = 0; idx < _len; idx++)
		std::cout << _arr[idx] << std::endl;
}

int		computeShortestSpan(int *arr, size_t len)
{
	int	ret = std::abs(arr[0] - arr[1]);
	for (size_t idx1 = 0; idx1 < len - 1; idx1++)
		for (size_t idx2 = idx1 + 1; idx2 < len; idx2++)
			if (std::abs(arr[idx1] - arr[idx2]) < ret)
				ret = std::abs(arr[idx1] - arr[idx2]);
	return ret;
}

int		Span::shortestSpan( void ) const
{
	if (_len <= 1)
		throw NotEnoughValues();
	return computeShortestSpan(_arr, _len);
}

int		computeLongestSpan(int *arr, size_t len)
{
	int	ret = std::abs(arr[0] - arr[1]);
	for (size_t idx1 = 0; idx1 < len - 1; idx1++)
		for (size_t idx2 = idx1 + 1; idx2 < len; idx2++)
			if (std::abs(arr[idx1] - arr[idx2]) > ret)
				ret = std::abs(arr[idx1] - arr[idx2]);
	return ret;
}

int		Span::longestSpan( void ) const
{
	if (_len <= 1)
		throw NotEnoughValues();
	return computeLongestSpan(_arr, _len);
}

#endif
