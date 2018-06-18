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

Solver::Solver() : _count_m( 0 ), _count_c( 0 ), _rec ( "" ) {}

Solver::Solver( const Solver &rhs ) {
	*this = rhs;
}

Solver	&Solver::operator=( const Solver &rhs ) {
	this->_var = rhs._var;
	this->_mat = rhs._mat;
	this->_fun = rhs._fun;
	this->_com = rhs._com;
	this->_rec = rhs._rec;
	this->_help = rhs._help;
	this->_count_c = rhs._count_c;
	this->_count_m = rhs._count_m;
	return ( *this );
}

double	Solver::find_var( std::string rhs ) {
	if ( _var->find( rhs ) == _var->end() ) {
		for ( size_t i = 0; i < rhs.size(); i++ )
			if ( !isdigit( rhs[i] ) && rhs[i] != '.'&&
					rhs[i] != '^' && rhs[i] != '-' )
				throw ( SolvExp( "unknown variable: " + rhs ));
		if ( rhs == "" )
			throw ( SolvExp( "invalid designation" ));
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
	std::string	sub = rhs.substr( i - temp, i - j );
	if ( rhs[i] == '(' )
		return ( solve_func( sub, rhs, i ));
	return ( sub );
}

std::string	Solver::power( std::string rhs, int &i ) {
	int 		place;
	std::string	n1, n2;

	n1 = brackets( rhs, i );
	while ( i < static_cast<int>( rhs.size() )) {
		while ( rhs[i] == ' ' || rhs[i] == '\t') i++;
		place = i;
		if ( rhs[i] != '^' )
			return ( n1 );
		i++;
		n2 = brackets( rhs, i );
		n1 = operation( n1, n2, rhs[place] );

	}
	return ( n1 );
}

std::string	Solver::factor( std::string rhs, int &i ) {
	int 		place;
	std::string	n1, n2;

	n1 = power( rhs, i );
	while ( i < static_cast<int>( rhs.size() )) {
		while ( rhs[i] == ' ' || rhs[i] == '\t') i++;
		place = i;
		if ( rhs[i] != '*' && rhs[i] != '/' && rhs[i] != '%' )
			return ( n1 );
		i++;
		n2 = power( rhs, i );
		n1 = operation( n1, n2, rhs[place] );

	}
	return ( n1 );
}

std::string	Solver::summary( std::string rhs, int &i ) {
	int 		place;
	std::string	n1,n2;

	n1 = factor( rhs, i);
	while ( i < static_cast<int>( rhs.size() )) {
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
			get_help().display_mat( _mat->at( lhs ));
		else if ( _com->find( lhs ) != _com->end() )
			get_help().display_comp( _com->at( lhs ));
		else
			throw ( SolvExp( "unknown variable" ));
		return;
	}
	res = summary( rhs, i );
	while ( i < static_cast<int>( rhs.size() ))
		if ( rhs[i] != ' ' && rhs[i++] != '\t' )
			throw ( SolvExp( "invalid designation" ));
	if ( _fun->find( lhs ) != _fun->end() )
		_fun->erase( lhs );
	result( lhs, res );
}

void	Solver::result( std::string lhs, std::string rhs ) {
	if ( _mat->find( rhs ) != _mat->end() ) {
		if ( _mat->find( lhs ) != _mat->end() ) {
			_mat->at( lhs ) = _mat->at( rhs );
			if ( lhs != rhs )
				_mat->erase( rhs );
			if ( _var->find( lhs ) != _var->end() )
				_var->erase( lhs );
		} else
			_mat->insert( std::pair<std::string, std::vector<std::vector<double>>>( lhs, _mat->at( rhs )));
		if ( _var->find( lhs ) != _var->end() )
			_var->erase( lhs );
		if ( _com->find( lhs ) != _com->end() )
			_com->erase( lhs );
		get_help().display_mat( _mat->at( lhs ));
	}
	else if ( _var->find( rhs ) != _var->end() ) {
		if ( _var->find( lhs ) != _var->end() ) {
			_var->at( lhs ) = _var->at( rhs );
			if ( lhs != rhs )
				_var->erase( rhs );
		} else
			_var->insert( std::pair<std::string, double>( lhs, _var->at( rhs )));
		if ( _mat->find( lhs ) != _mat->end() )
			_mat->erase( lhs );
		if ( _com->find( lhs ) != _com->end() )
			_com->erase( lhs );
		cout << _var->at( lhs ) << endl;
	}
	else if ( _com->find( rhs ) != _com->end() ) {
		if ( _com->find( lhs ) != _com->end() ) {
			_com->at( lhs ) = _com->at( rhs );
			if ( lhs != rhs )
				_com->erase( rhs );
		} else
			_com->insert( std::pair<std::string, comp_n>( lhs, _com->at( rhs )));
		if ( _var->find( lhs ) != _var->end() )
			_var->erase( lhs );
		if ( _mat->find( lhs ) != _mat->end() )
			_mat->erase( lhs );
		_help.display_comp( _com->at( rhs ));
	}
	else {
		for ( int i = 0; i < static_cast<int>( rhs.size() ); i++ )
			if ( i == 0 && rhs[i] == '-' )
				continue;
			else if ( !isdigit( rhs[i] ) && rhs[i] != '.' )
				throw ( SolvExp( "unknown variable: " + rhs ));
		if ( _var->find( lhs ) == _var->end() )
			_var->insert( std::pair<std::string, double>( lhs , std::stod( rhs )));
		else
			_var->at( lhs ) = std::stod( rhs );
		if ( _mat->find( lhs ) != _mat->end() )
			_mat->erase( lhs );
		if ( _com->find( lhs ) != _com->end() )
			_com->erase( lhs );
		cout << _var->at( lhs ) << endl;
	}
}

Helper	&Solver::get_help() {
	return ( _help );
}


int		Solver::get_count_m() const {
	return _count_m;
}

int		Solver::get_count_c() const {
	return _count_c;
}

void	Solver::set_count_m( int count_m ) {
	Solver::_count_m = count_m;
}

void	Solver::set_count_c( int count_c ) {
	Solver::_count_c = count_c;
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

void	Solver::set_rec( const std::string &rec ) {
	this->_rec = rec;
}

void	Solver::set_com( std::map<std::string, comp_n> *com ) {
	this->_com = com;
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
