// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Helper.class.hpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: oposhiva <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/14 13:35:14 by oposhiva          #+#    #+#             //
//   Updated: 2018/06/14 13:35:14 by oposhiva         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef HELPER_CLASS_HPP
#define HELPER_CLASS_HPP

#include "Equation.class.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <map>

using	std::cout;
using	std::endl;

struct	comp_n {
	double	a;
	double	b;
};

struct	func{
	std::string	name;
	std::string	value;
};

class	Helper {
private:
	class HelpExp : public std::exception {
	private:
		std::string     _exptn_msg;
	public:
		HelpExp();
		HelpExp( const std::string & text );
		HelpExp( HelpExp const & rhs );

		HelpExp &	operator=( HelpExp const & rhs );

		const char	*what() const throw();

		~HelpExp();
	};
public:
	Helper();
	Helper( const Helper &rhs );

	Helper	&operator=( const Helper & rhs );

	bool		cont_opr( std::string rhs );
	void		size_check( std::vector<std::vector<double>> matrix );
	void		display_mat( std::vector<std::vector<double>> matrix );
	void		display_fun( std::string rhs );
	void		func_check( std::string rhs );
	void		str_check( std::string lhs, std::string rhs );
	bool		replace_str( std::string lhs, std::string rhs );
	bool		recursion_check( std::string lhs, std::string rhs );
	std::string	name( std::string rhs );
	std::string	word_split( std::string rhs );

	~Helper();
};

#endif
