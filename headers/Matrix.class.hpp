// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Matrix.class.hpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: oposhiva <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/06 12:55:21 by oposhiva          #+#    #+#             //
//   Updated: 2018/06/06 12:55:21 by oposhiva         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef MATRIX_CLASS_HPP
#define MATRIX_CLASS_HPP

#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <map>

using	std::cout;
using	std::endl;

class	Matrix {
private:
	class MtrxExp : public std::exception {
	private:
		std::string     _exptn_msg;
	public:
		MtrxExp();
		MtrxExp( const std::string & text );
		MtrxExp( MtrxExp const & rhs );

		MtrxExp &	operator=( MtrxExp const & rhs );

		const char	*what() const throw();

		~MtrxExp();
	};
	std::map<std::string, double>	*_var;
	std::map<std::string, std::vector<std::vector<double >>>	*_mat;
public:
	Matrix();
	Matrix( const Matrix &rhs );

	Matrix	&operator=( const Matrix &rhs );

	void	read_matrix( std::string lhs, std::string rhs );
	void	size_check( std::vector<std::vector<double>> matrix );
	void	display_mat( std::vector<std::vector<double>> matrix );
	double	find_var( std::string rhs );
	std::vector<std::vector<double>>	lines( std::string rhs, int &i );
	std::vector<double>					rows( std::string rhs, int &i );

	void	set_var( std::map<std::string, double> *_var );
	void	set_mat( std::map<std::string, std::vector<std::vector<double>>> *_mat );

	~Matrix();
};

#endif