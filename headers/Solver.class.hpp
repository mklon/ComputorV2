// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Solver.class.hpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: oposhiva <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/08 11:53:30 by oposhiva          #+#    #+#             //
//   Updated: 2018/06/08 11:53:30 by oposhiva         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef SOLVER_CLASS_HPP
#define SOLVER_CLASS_HPP

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

class	Solver {
private:
	class SolvExp : public std::exception {
	private:
		std::string     _exptn_msg;
	public:
		SolvExp();
		SolvExp( const std::string & text );
		SolvExp( SolvExp const & rhs );

		SolvExp &	operator=( SolvExp const & rhs );

		const char	*what() const throw();

		~SolvExp();
	};
	std::map<std::string, double>	*_var;
	std::map<std::string, std::vector<std::vector<double >>>	*_mat;
public:
	Solver();
	Solver( const Solver &rhs );
	Solver	&operator=( const Solver &rhs );

	// Solve 1
	bool		cont_opr( std::string rhs );
	double		find_var( std::string rhs );
	void		solve_line( std::string lhs, std::string rhs );
	std::string	factor( std::string rhs, int &i );
	std::string	summary( std::string rhs, int &i );
	std::string	operation( std::string lhs, std::string rhs, char op );

	// Solve 2
	void		size_check( std::vector<std::vector<double>> matrix );
	void		read_matrix( std::string lhs, std::string rhs );
	void		display_mat( std::vector<std::vector<double>> matrix );
	std::string	brackets( std::string rhs, int &i );
	std::vector<double>					rows( std::string rhs, int &i );
	std::vector<std::vector<double>>	lines( std::string rhs, int &i );

	// Solve 3
	void		complex( std::string lhs, std::string rhs );
	comp_n		read_cm( std::string rhs );

	void		set_var( std::map<std::string, double> *var );
	void		set_mat( std::map<std::string, std::vector<std::vector<double>>> *mat );

	~Solver();
};

#endif
