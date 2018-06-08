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
}

Computor::Computor( const Computor &rhs ) {
	*this = rhs;
}

Computor	&Computor::operator=( const Computor &rhs ) {
	//!!!
	return ( *this );
}

void	Computor::var_handle( std::string lhs, std::string rhs ) {
	if ( isdigit( lhs[0] ) || lhs == "i" )
		throw ( CompExp( "invalid variable name" ));

	if ( rhs.find('[') != std::string::npos ) {
		_solv.read_matrix( lhs, rhs );
	}
	else if ( rhs.find('i') != std::string::npos )
		_solv.complex( lhs, rhs );
	else
		_solv.solve_line( lhs, rhs );
}

void	Computor::lhs_handle( std::string lhs, std::string rhs ) {
	int 				i = 0;
	std::istringstream	iss( lhs );

	if ( _solv.cont_opr( lhs ) ) {
		cout << "oper_handle" << endl;
		return;
	}
	while ( iss ) {
		iss >> lhs;
		i++;
		if ( i > 2 )
			throw ( CompExp( "invalid variable name" ));
	}
	if ( lhs[lhs.size() - 1] == ')' )
		cout << "func_handle" << endl;
	else
		var_handle( lhs, rhs );
}

void	Computor::parse_line() {
	unsigned long int	i;
	std::string			part;
	if ( _line == "" )
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
