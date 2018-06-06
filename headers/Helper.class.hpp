// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Helper.class.hpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: oposhiva <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/05 12:07:08 by oposhiva          #+#    #+#             //
//   Updated: 2018/06/05 12:07:08 by oposhiva         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef HELPER_CLASS_HPP
#define HELPER_CLASS_HPP

#include <iostream>
#include <sstream>
#include <cmath>
#include <map>

using	std::cout;
using	std::endl;

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
	std::map<std::string, double>	*_var;
public:
	Helper();
	Helper( const Helper &rhs );

	Helper	&operator=( const Helper &rhs );

	bool	cont_opr( std::string rhs );
	double	solve_line( std::string lhs, std::string rhs );
	double	summary( std::string rhs, int &i );
	double	factor( std::string rhs, int &i );
	double	brackets( std::string rhs, int &i );
	double	find_var( std::string rhs );

	void	set_var( std::map<std::string, double> *_var );

	~Helper();
};

#endif