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

#include "Matrix.class.hpp"
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
	std::map<std::string, std::vector<std::vector<double >>>	*_mat;
public:
	Helper();
	Helper( const Helper &rhs );
	Helper	&operator=( const Helper &rhs );

	Matrix	*m;

	bool	cont_opr( std::string rhs );
	void	solve_line( std::string lhs, std::string rhs );
	std::string	operation( std::string lhs, std::string rhs, char op );
	std::string	summary( std::string rhs, int &i );
	std::string	factor( std::string rhs, int &i );
	std::string	brackets( std::string rhs, int &i );
	double	find_var( std::string rhs );

	void	set_var( std::map<std::string, double> *_var );

	void set_mat( std::map<std::string, std::vector<std::vector<double>>> *_mat );

	~Helper();
};

#endif
