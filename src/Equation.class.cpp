// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Equation.class.cpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: oposhiva <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/15 14:18:04 by oposhiva          #+#    #+#             //
//   Updated: 2018/06/15 14:18:05 by oposhiva         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "../headers/Equation.class.hpp"
#include <cmath>
#include "sstream"

Equation::Equation() {}

Equation::Equation( const Equation &rhs ) {
	*this = rhs;
}

Equation::Equation( std::string line, std::string var )
		: _degree( 0 ), _var( var ), _line( line ) {}

const Equation& Equation::operator=( const Equation &rhs ) {
	this->_degree = rhs._degree;
	this->_var = rhs._var;
	this->_line = rhs._line;
	this->_result = rhs._result;
	this->_equation = rhs._equation;
	return ( *this );
}

double	Equation::numbers( std::vector<std::string> vec ) {
	double	num = 0;
	auto	i = std::find( vec.begin(), vec.end(), "=" );

	for ( int j = 0; j < static_cast<int>( vec.size() ); j++ ) {
		if ( ( isdigit( vec[j][0] ) || ( vec[j][0] == '-'
			&& isdigit( vec[j][1] ))) && vec[j + 1] != "*" ) {
			if (( vec[j - 1] == "+" && i - vec.begin() > j ) ||
				( vec[j - 1] == "-" && i - vec.begin() < j ) || !j )
				num += std::stod( vec[j] );
			else
				num -= std::stod( vec[j] );
		}
	}
	return ( num );
}

double	Equation::counter( std::vector<std::string> vec, std::string subs ) {
	auto	i = std::find( vec.begin(), vec.end(), "=" );
	double	num = 0;

	for (  auto j = std::find( vec.begin(), vec.end(), subs); j != vec.end() ;
		   j = std::find( j + 1, vec.end(), subs )) {
		if ( vec[j - vec.begin() - 1] == "*" ) {

			if (( vec[j - vec.begin() - 3] == "-" && i > j ) ||
				( vec[j - vec.begin() - 3] == "+" && i < j ) ||
				vec[j - vec.begin() - 3] == "=")
				num -= std::stod( vec[j - vec.begin() - 2] );
			else
				num += std::stod( vec[j - vec.begin() - 2] );
		}
		else
		if (( vec[j - vec.begin() - 1] == "+" && i > j ) ||
			( vec[j - vec.begin() - 1] == "-" && i < j ) ||
				j - vec.begin() == 0)
			num += 1;
		else
			num -= 1;
	}
	return ( num );
}

void	Equation::degree_check() {
	int 			temp;
	std::string		deg;

	for ( size_t i = 0; i != std::string::npos; i = _line.find( _var + "^", i + 1 )) {
		if ( _line[i + 2] - '0' < 3 && _line[i + 3] == ' ' )
			continue;
		std::istringstream	iss(_line.substr( i + 2 ));
		iss >> temp;
		if ( temp > _degree )
			_degree = temp;
	}
}

void	Equation::parse_line() {
	std::vector<std::string>	line;
	std::istringstream			iss( _line );

	while ( iss ) {
		std::string subs;
		iss >> subs;
		line.push_back( subs );
	}
	_equation.push_back( counter( line, _var + "^2" ));
	_equation.push_back( counter( line, _var ) + counter( line, _var + "^1" ));
	_equation.push_back( counter( line, _var + "^0" ) + numbers( line ));
	for ( size_t i = 0; i < _equation.size(); i++ )
		if ( _equation[i] ) {
			_degree = 2 - i;
			break ;
		}
}

void	Equation::solve_2degree(  ) {
	double 	x1, x2;
	double D = _equation[1]*_equation[1] - 4*_equation[0]*_equation[2];

	if ( D > 0 ) {
		x1 = ( -1 * _equation[1] - sqrt( D )) / ( 2 * _equation[0] );
		x2 = ( -1 * _equation[1] + sqrt( D )) / ( 2 * _equation[0] );
		_result = "Result for R:\n";
		_result += _var + "1 = " + std::to_string( x1 ) + "\nx2 = "
				   +  std::to_string( x2 ) + "\n";
	}
	else if ( D == 0 ) {
		x1 = ( -1 * _equation[1] ) / ( 2 * _equation[0] );
		_result = "Discriminant is equal to 0!\n";
		_result = _var + " = " + std::to_string( x1 ) + "\n";
	}
	else {
		_result = "Result for C:\n";
		x1 = ( -1 * _equation[1] ) / ( 2 * _equation[0] );
		x2 = ( -1 * _equation[1] ) / ( 2 * _equation[0] );
		_result += _var + "1 = " + std::to_string( x1 ) + " + " + std::to_string( sqrt( -1 * D )) + "i\n";
		_result += _var + "2 = " + std::to_string( x2 ) + " - " + std::to_string( sqrt( -1 * D )) + "i\n";
	}
}

void	Equation::solve_1degree() {
	double x;

	x = -1 * _equation[2] / _equation[1];
	_result = "x = " + std::to_string( x ) + "\n";
}

void	Equation::solve_0degree() {
	if ( !_equation[2] )
		_result = "The solution is all the real numbers!";
	else
		_result = "The equation has no solution!";
}

void	Equation::result() {
	//std::cout << "Polynomial degree: " << _degree << std::endl;
	std::cout << _result;
}

void	Equation::solve() {
	degree_check();
	if ( _degree > 2 ) {
		_result = "the polynomial degree is greater than 2\n";
		result();
		return;
	}
	parse_line();
	if ( _degree == 2 )
		solve_2degree();
	else if ( _degree == 1 )
		solve_1degree();
	else
		solve_0degree();
	result();
}

Equation::~Equation() {}
