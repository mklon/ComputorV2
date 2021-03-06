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

#include "Helper.class.hpp"

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
	int 							_count_m;
	int 							_count_c;
	Helper							_help;
	std::string						_rec;
	std::map<std::string, func>		*_fun;
	std::map<std::string, comp_n>	*_com;
	std::map<std::string, double>	*_var;
	std::map<std::string, std::vector<std::vector<double >>>	*_mat;
public:
	Solver();
	Solver( const Solver &rhs );
	Solver	&operator=( const Solver &rhs );

	// Solve 1
	void		result( std::string lhs, std::string rhs );
	void		solve_line( std::string lhs, std::string rhs );
	double		find_var( std::string rhs );
	std::string	brackets( std::string rhs, int &i );
	std::string	power( std::string rhs, int &i );
	std::string	factor( std::string rhs, int &i );
	std::string	summary( std::string rhs, int &i );

	// Solve 2
	void		read_matrix( std::string lhs, std::string rhs );
	void		oper_hand( std::string lhs, std::string rhs );
	void		question_mark( std::string lhs, std::string rhs );
	void		equation( std::string lhs, std::string rhs );
	std::vector<double>					rows( std::string rhs, int &i );	//H
	std::vector<std::vector<double>>	lines( std::string rhs, int &i );	//H

	// Solve 3
	void		functions( std::string lhs, std::string rhs );
	void		func_info( std::string lhs, std::string value );
	std::string	func_sum( std::string lhs, std::string rhs );
	std::string	solve_func( std::string lhs, std::string rhs, int &i );

	// Solve 4
	std::string	operation( std::string lhs, std::string rhs, char op );
	std::string	matrix_op( std::string lhs, std::string rhs, char op );
	std::string	mat_n_mat( std::string lhs, std::string rhs, char op );
	std::string	add_sub_mat( std::string lhs, std::string rhs, char op );
	std::string	div_mat( std::string lhs, std::string rhs );
	std::string	mult_mat( std::string lhs, std::string rhs );
	std::string	mat_n_var( std::string lhs, std::string rhs, char op );

	// Solve 5
	void		complex( std::string lhs, std::string rhs ); // complex numbers
	std::string	comp_op(  std::string lhs, std::string rhs, char op  );


	int			get_count_m() const;
	int			get_count_c() const;
	void		set_count_m( int _count );
	void		set_count_c( int _count_c );
	void		set_rec( const std::string &_rec );
	void		set_fun( std::map<std::string, func> *_fun );
	void		set_var( std::map<std::string, double> *var );
	void		set_com( std::map<std::string, comp_n> *_com );
	void		set_mat( std::map<std::string, std::vector<std::vector<double>>> *mat );
	Helper		&get_help();

	~Solver();
};

#endif
