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

#include "Solver.class.hpp"

class	Solver;

class	Computor {
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
	Solver							_solv;
	std::string						_line;
	std::map<std::string, func>		_fun;
	std::map<std::string, double>	_var;
	std::map<std::string, comp_n>	_com;
	std::map<std::string, std::vector<std::vector<double >>>	_mat;

public:
	Computor();
	Computor( const Computor &rhs );

	Computor	&operator=( const Computor &rhs );

	void	run();
	void	parse_line();
	void	lhs_handle( std::string lhs, std::string rhs );
	void	var_handle( std::string lhs, std::string rhs );

	~Computor();
};

#endif
