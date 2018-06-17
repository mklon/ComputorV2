// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Computor.class.cpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: oposhiva <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/04 12:06:47 by oposhiva          #+#    #+#             //
//   Updated: 2018/06/04 12:06:47 by oposhiva         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "../headers/Computor.class.hpp"

Computor::Computor() {
	_solv.set_var( &_var );
	_solv.set_mat( &_mat );
	_solv.set_fun( &_fun );
	_solv.set_com( &_com );
}

Computor::Computor( const Computor &rhs ) {
	*this = rhs;
}

Computor	&Computor::operator=( const Computor &rhs ) {
	//!!!
	return ( *this );
}

void	Computor::clear() {
	if ( _solv.get_count() )
		for ( int i = 0; i < _solv.get_count(); i++ ) {
			_mat.erase( "@" + std::to_string(i) );
		}
	_solv.set_count( 0 );
	_solv.set_rec( "" );
}

void	Computor::var_handle( std::string lhs, std::string rhs ) {
	for ( auto i = 0; i < lhs.size(); i++ ) {
		if ( !isalpha( lhs[i] ) || lhs == "i" )
			throw ( CompExp( "invalid variable name" ));
	}

	if ( rhs.find('[') != std::string::npos ) {
		_solv.read_matrix( lhs, rhs );
	}
	else if ( _solv.get_help().is_complex( rhs ))
		_solv.complex( lhs, rhs );
	else
		_solv.solve_line( lhs, rhs );
}

void	Computor::lhs_handle( std::string lhs, std::string rhs ) {
	if ( _solv.get_help().cont_opr( lhs ) ) {
		_solv.oper_hand( lhs, rhs );
		return;
	}
	lhs = _solv.get_help().word_split( lhs );
	var_handle( lhs, rhs );
}

void	Computor::parse_line() {
	unsigned long int	i;
	std::string			part;
	std::istringstream	iss( _line );

	iss >> part;
	for ( auto j = 0; j < _line.size(); j++ )
		_line[j] = tolower( _line[j] );
	if ( part == "" )
		return;
	if (( i = _line.find( '=' )) == std::string::npos )
		throw ( CompExp( "missing equality symbol" ) );
	lhs_handle( _line.substr( 0, i ), _line.substr( i + 1 ));
}

void	Computor::run() {
	while ( std::getline( std::cin, _line ) ) {
		try {
			parse_line();
		}
		catch ( std::exception &e ) {
			cout << e.what() << endl;
		}
		clear();
	}
}

Computor::~Computor() {}

// CompExp

Computor::CompExp::CompExp() {}


Computor::CompExp::CompExp( const std::string & text ) {
	this->_exptn_msg = text;
}

Computor::CompExp::CompExp(CompExp const &rhs) {
	*this = rhs;
}

const char	*Computor::CompExp::what() const throw() {
	return ( this->_exptn_msg.c_str() );
}

Computor::CompExp	&Computor::CompExp::operator=(CompExp const &rhs) {
	this->_exptn_msg = rhs._exptn_msg;
	return ( *this );
}

Computor::CompExp::~CompExp() throw() {}
