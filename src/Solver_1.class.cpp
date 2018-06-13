// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Solver_1.class.cpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: oposhiva <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/08 11:53:06 by oposhiva          #+#    #+#             //
//   Updated: 2018/06/08 11:53:07 by oposhiva         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "../headers/Solver.class.hpp"

Solver::Solver() : _count( 0 ) {}

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
					rhs[i] != '^' && rhs[i] != '-' )
				throw ( SolvExp( "unknown variable: " + rhs ));
		if ( rhs == "" )
			throw ( SolvExp( "invalid rhs" ));
		return ( std::stod( rhs ));
	}
	else {
		return ( _var->at(rhs) );
	}
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
	std::string			res;
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
	res = summary( rhs, i );
	while ( i < rhs.size() )
		if ( rhs[i] != ' ' && rhs[i++] != '\t' )
			throw ( SolvExp( "invalid rhs" ));
	result( lhs, res );
}

void	Solver::result( std::string lhs, std::string rhs ) {
	//!!!!!СЛОЖН0

	if ( _mat->find( rhs ) != _mat->end() ) {
		if ( _mat->find( lhs ) != _mat->end() ) {
			_mat->at( lhs ) = _mat->at( rhs );
			if ( lhs != rhs )
				_mat->erase( rhs );
		}
		else if ( _var->find( lhs ) != _var->end() ) {
			_mat->insert( std::pair<std::string, std::vector<std::vector<double>>>( lhs, _mat->at( rhs )));
			_var->erase( lhs );
		} else
			_mat->insert( std::pair<std::string, std::vector<std::vector<double>>>( lhs, _mat->at( rhs )));
		display_mat( _mat->at( lhs ));
	}
	else if ( _var->find( rhs ) != _var->end() ) {
		if ( _var->find( lhs ) != _var->end() ) {
			_var->at( lhs ) = _var->at( rhs );
			_var->erase( rhs );
		}
		else if ( _mat->find( lhs ) != _mat->end() ) {
			_var->insert( std::pair<std::string, double >( lhs, _var->at( rhs )));
			_mat->erase( lhs );
		} else
			_var->insert( std::pair<std::string, double>( lhs , _var->at( rhs )));
		cout << _var->at( lhs ) << endl;
	}
	else {
		if ( _var->find( lhs ) == _var->end() )
			_var->insert( std::pair<std::string, double>( lhs , std::stod( rhs )));
		else
			_var->at( lhs ) = std::stod( rhs );
		cout << _var->at( lhs ) << endl;
	}

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

void	Solver::set_fun( std::map<std::string, func> *fun ) {
	this->_fun = fun;
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

Solver::SolvExp::~SolvExp() {}
