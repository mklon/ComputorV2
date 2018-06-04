// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Computor.class.hpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: oposhiva <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/04 12:07:04 by oposhiva          #+#    #+#             //
//   Updated: 2018/06/04 12:07:05 by oposhiva         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef COMPUTOR_CLASS_HPP
#define	COMPUTOR_CLASS_HPP

#include <iostream>
#include <sstream>
#include <vector>

using	std::cout;
using	std::endl;

class Computor {
private:
	class CompExp : public std::exception {
	private:
		std::string     _exptn_msg;
	public:
		CompExp();
		CompExp( const std::string & text );
		CompExp( CompExp const & rhs );

		CompExp &	operator=( CompExp const & rhs );

		virtual const   char *what() const throw();

		virtual ~CompExp() throw();
	};
	std::string	_line;
public:
	Computor();
	Computor( const Computor &rhs );

	Computor	&operator=( const Computor &rhs );

	void	run();
	void	parse_line();

	~Computor();
};

#endif
