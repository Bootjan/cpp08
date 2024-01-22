/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:15:37 by bootjan           #+#    #+#             */
/*   Updated: 2024/01/21 15:23:24 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

# include <iostream>

template <typename MutantStack>
class MStackIterator
{
	public:
		using	ValueType = typename MutantStack::ValueType;
		using	PointerType = ValueType*;
		using	ReferenceType = ValueType&;
	private:
		PointerType	_ptr;
	public:
		MStackIterator( void ) : _ptr(nullptr) {};
		MStackIterator( PointerType ptr ) : _ptr(ptr) {};
		MStackIterator( const MStackIterator& rhs ) : _ptr(rhs._ptr) {};
		MStackIterator&	operator=( const MStackIterator& rhs );
		MStackIterator&	operator=( const PointerType& rhs );
		~MStackIterator() {};

		MutantStack*	getPtr( void ) const;
		MStackIterator	operator++( int );
		MStackIterator	operator--( int );
		MStackIterator&	operator++( void );
		MStackIterator&	operator--( void );
		ReferenceType	operator*( void ) const { return *_ptr; };
		bool			operator==( const MStackIterator& rhs ) const { return (_ptr == rhs._ptr); };
		bool			operator!=( const MStackIterator& rhs ) const { return (_ptr != rhs._ptr); };
};

template <typename MutantStack>
MStackIterator<MutantStack>&	MStackIterator<MutantStack>::operator=( const MStackIterator& rhs )
{
	if (this != &rhs)
		_ptr = rhs._ptr;
	return *this;
}

template <typename MutantStack>
MStackIterator<MutantStack>&		MStackIterator<MutantStack>::operator=( const PointerType& rhs )
{
	_ptr = rhs;
	return *this;
}

template <typename MutantStack>
MutantStack*	MStackIterator<MutantStack>::getPtr( void ) const
{
	return _ptr;
}

template <typename MutantStack>
MStackIterator<MutantStack>		MStackIterator<MutantStack>::operator++( int )
{
	MStackIterator	temp = *this;
	_ptr++;
	return temp;
}

template <typename MutantStack>
MStackIterator<MutantStack>			MStackIterator<MutantStack>::operator--( int )
{
	MStackIterator	temp = *this;
	_ptr--;
	return temp;
}

template <typename MutantStack>
MStackIterator<MutantStack>			&MStackIterator<MutantStack>::operator++( void )
{
	_ptr++;
	return *this;
}

template <typename MutantStack>
MStackIterator<MutantStack>			&MStackIterator<MutantStack>::operator--( void )
{
	_ptr--;
	return *this;
}

template <typename T>
class MutantStack
{
	private:
		T*		_arr;
		size_t	_len;
	public:
		using	ValueType = T;
		using	iterator = MStackIterator<MutantStack<T>>;
		MutantStack();
		MutantStack( const MutantStack& rhs );
		MutantStack&	operator=( const MutantStack& rhs );
		~MutantStack();
		void	push( T el );
		void	pop( void );
		T		top( void ) const;
		size_t	size( void ) const;
		T*		begin( void ) const;
		T*		end( void ) const;

		struct ExecuteException : public std::runtime_error
		{
			ExecuteException(const std::string& message) : std::runtime_error(message) {}
		};

		struct EmptyStack : ExecuteException
		{
			EmptyStack() : ExecuteException("Stack is empty") {}
		};
};

template <typename T>
MutantStack<T>::MutantStack( void )
	:	_arr(nullptr)
	,	_len(0)
{
}

template <typename T>
MutantStack<T>::MutantStack( const MutantStack& rhs )
	:	_arr(nullptr)
	,	_len(_len)
{
	if (_len > 0)
	{
		_arr = new T[_len];
		std::memcpy(_arr, rhs._len, sizeof(T) * _len);
	}
}

template <typename T>
MutantStack<T>&	MutantStack<T>::operator=( const MutantStack& rhs )
{
	if (this == &rhs)
		return *this;
	_len = rhs._len;
	delete[] _arr;
	_arr = nullptr;
	if (_len > 0)
	{
		_arr = new T[_len];
		std::memcpy(_arr, rhs._len, sizeof(T) * _len);
	}
	return *this;
}

template <typename T>
MutantStack<T>::~MutantStack()
{
	delete[] _arr;
}

template <typename T>
void	MutantStack<T>::push( T el )
{
	T*	newArr = new T[_len + 1];
	std::memcpy(newArr, _arr, sizeof(T) * _len);
	delete[] _arr;
	_arr = nullptr;
	newArr[_len++] = el;
	_arr = newArr;
}

template <typename T>
void	MutantStack<T>::pop( void )
{
	if (_len == 0)
		throw EmptyStack();
	T*	newArr = NULL;
	if (_len > 1)
	{
		newArr = new T[_len - 1];
		std::memcpy(newArr, _arr, sizeof(T) * --_len);
	}
	delete[] _arr;
	_arr = newArr;
}

template <typename T>
T	MutantStack<T>::top( void ) const
{
	if (_len == 0)
		throw EmptyStack();
	return _arr[_len - 1];
}

template <typename T>
size_t	MutantStack<T>::size( void ) const
{
	return _len;
}

template <typename T>
T*	MutantStack<T>::begin( void ) const
{
	return _arr;
}

template <typename T>
T*	MutantStack<T>::end( void ) const
{
	if (_len == 0)
		return nullptr;
	return _arr + _len;
}

#endif