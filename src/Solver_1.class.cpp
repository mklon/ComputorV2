// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Helper.class.cpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: oposhiva <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/05 12:06:50 by oposhiva          #+#    #+#             //
//   Updated: 2018/06/05 12:06:51 by oposhiva         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "../headers/Solver.class.hpp"

Solver::Solver() {}

Solver::Solver( const Solver &rhs ) {
	*this = rhs;
}

Solver	&Solver::operator=( const Solver &rhs ) {
	//!!!
	return ( *this );
}

double	Solver::find_var( std::string rhs ) {

	if ( _var->find( rhs ) == _var->end() ) {
		for ( int i = 0; i < rhs.size(); i++ )
			if ( !isdigit( rhs[i] ) && rhs[i] != '.'&&
					rhs[i] != '^' )
				throw ( SolvExp( "unknown variable: " + rhs ));
		if ( rhs == "" )
			throw ( SolvExp( "invalid rhs" ));
		return ( std::stod( rhs ));
	}
	else {
		return ( _var->at(rhs) );
	}
}

std::string	Solver::operation( std::string lhs, std::string rhs, char op ) {


	return ( " ");
}

std::string	Solver::brackets( std::string rhs, int &i ) {
	std::string	n;
	int		j, temp= 0;

	while ( rhs[i] == ' ' || rhs[i] == '\t') i++;

	j = i;
	if ( rhs[i] == '(' ) {
		i++;
		n = summary( rhs, i );
		if ( rhs[i] == ')' )
			i++;
		return ( n );
	}
	while ( isdigit( rhs[j + temp] ) ||
			isalpha( rhs[j + temp] ) ||
			rhs[j + temp] == '.' ) temp++;
	i += temp;
	std::string	temp1 = rhs.substr( i - temp, i - j );
	return ( temp1 );
}

std::string	Solver::factor( std::string rhs, int &i ) {
	int 		place;
	std::string	n1, n2;

	n1 = brackets( rhs, i );
	while ( i < rhs.size() ) {
		while ( rhs[i] == ' ' || rhs[i] == '\t') i++;
		place = i;
		if ( rhs[i] != '*' && rhs[i] != '/' && rhs[i] != '%' && rhs[i] !='^' )
			return ( n1 );
		i++;
		n2 = brackets( rhs, i );
		n1 = operation( n1, n2, rhs[place] );

	}
	return ( n1 );
}

std::string	Solver::summary( std::string rhs, int &i ) {
	int 		place;
	std::string	n1,n2;

	n1 = factor( rhs, i);
	while ( i < rhs.size() ) {
		while ( rhs[i] == ' ' || rhs[i] == '\t') i++;
		place = i;
		if ( rhs[i] != '+' && rhs[i] != '-' )
			return ( n1 );
		i++;
		n2 = factor( rhs, i );
		n1 = operation( n1, n2, rhs[place] );
	}
	return ( n1 );
}

void	Solver::solve_line( std::string lhs, std::string rhs ) {
	int					i = 0;
	double				res;
	std::string			temp;
	std::istringstream	iss( rhs );

	iss >> temp;
	if ( temp == "?" ) {
		if ( _var->find( lhs ) != _var->end() )
			cout << _var->at( lhs ) << endl;
		else if ( _mat->find( lhs ) != _mat->end() )
			display_mat( _mat->at( lhs ));
		else
			throw ( SolvExp( "unknown variable" ));
		return;
	}

	if ( _mat->find( lhs ) != _mat->end() )
		throw ( SolvExp( "can't put number in a matrix variable" ));

	res = std::stod( summary( rhs, i ));
	while ( i < rhs.size() )
		if ( rhs[i] != ' ' && rhs[i++] != '\t' )
			throw ( SolvExp( "invalid rhs" ));

	if ( _var->find( lhs ) != _var->end() )
		_var->at( lhs ) = res;
	else
		_var->insert( std::pair<std::string, double>( lhs , res ));
	cout << _var->at( lhs ) << endl;
}

bool	Solver::cont_opr( std::string rhs ) {
	// + - * / %
	if ( rhs.find( '+' ) != std::string::npos ||
			rhs.find( '-' ) != std::string::npos ||
			rhs.find( '*' ) != std::string::npos ||
			rhs.find( '/' ) != std::string::npos ||
			rhs.find( '%' ) != std::string::npos )
		return ( true );
	return ( false );
}

void	Solver::set_var( std::map<std::string, double> *var ) {
	this->_var = var;
}

void	Solver::set_mat( std::map<std::string, std::vector<std::vector<double>>> *mat ) {
	this->_mat = mat;
}

Solver::~Solver() {}

// SolvExp

Solver::SolvExp::SolvExp() {}


Solver::SolvExp::SolvExp( const std::string & text ) {
	this->_exptn_msg = text;
}

Solver::SolvExp::SolvExp(SolvExp const &rhs) {
	*this = rhs;
}

const char	*Solver::SolvExp::what() const throw() {
	return ( this->_exptn_msg.c_str() );
}

Solver::SolvExp	&Solver::SolvExp::operator=(SolvExp const &rhs) {
	this->_exptn_msg = rhs._exptn_msg;
	return ( *this );
}

Solver::SolvExp::~SolvExp() throw() {}
