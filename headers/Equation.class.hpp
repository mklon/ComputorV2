// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Equation.class.hpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: oposhiva <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/15 14:18:15 by oposhiva          #+#    #+#             //
//   Updated: 2018/06/15 14:18:16 by oposhiva         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef SOLUTION_CLASS_HPP
# define SOLUTION_CLASS_HPP

#include <iostream>
#include <sstream>
#include <vector>

class Equation {
private:
	int 				_degree;
	std::string			_var;
	std::string			_line;
	std::string			_result;
	std::vector<double>	_equation;
public:
	Equation();
	Equation( std::string line, std::string var );
	Equation( const Equation &rhs );

	const Equation	&operator=( const Equation &rhs );

	void	parse_line();
	void	degree_check();
	double	counter( std::vector<std::string> vec, std::string subs );
	double	numbers( std::vector<std::string> vec );
	void	solve_2degree();
	void	solve_1degree();
	void	solve_0degree();
	void	result();
	void	solve();

	~Equation();
};

#endif
