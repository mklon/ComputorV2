// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Helper.class.cpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: oposhiva <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/14 13:34:49 by oposhiva          #+#    #+#             //
//   Updated: 2018/06/14 13:34:55 by oposhiva         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "../headers/Helper.class.hpp"

Helper::Helper() {}

Helper::Helper( const Helper &rhs ) {
	*this = rhs;
}

Helper& Helper::operator=( const Helper &rhs ) {
	( void )rhs;
	return ( *this );
}

bool	Helper::cont_opr( std::string rhs ) {
	// + - * / %
	if ( rhs.find( '+' ) != std::string::npos ||
		 rhs.find( '-' ) != std::string::npos ||
		 rhs.find( '*' ) != std::string::npos ||
		 rhs.find( '/' ) != std::string::npos ||
		 rhs.find( '^' ) != std::string::npos ||
		 rhs.find( '(' ) != std::string::npos ||
		 rhs.find( '%' ) != std::string::npos )
		return ( true );
	return ( false );
}

void	Helper::size_check( std::vector<std::vector<double>> matrix ) {
	size_t	size = matrix[0].size();

	for ( size_t i = 1; i < matrix.size(); i++ )
		if ( matrix[i].size() != size )
			throw ( HelpExp( "invalid matrix definition" ));
}

void	Helper::display_mat( std::vector<std::vector<double>> matrix ) {
	for ( size_t i = 0; i < matrix.size(); i++ ) {
		cout << "[ ";
		for ( size_t j = 0; j < matrix[i].size(); j++ ) {
			cout << matrix[i][j];
			if ( j != matrix[i].size() - 1 )
				cout << " , ";
		}
		cout << " ]" << endl;
	}
}

void	Helper::func_check( std::string rhs ) {
	size_t	i = -1;

	while ( ++i < rhs.size() ) {
		if ( rhs[i] == '+' || rhs[i] == '*' ||
			 rhs[i] == '/' || rhs[i] == '-' || rhs[i] == '^' ) {
			i++;
			while ( rhs[i] == ' ' || rhs[i] == '\t') i++;
			if ( rhs[i] == '+' || rhs[i] == '*' ||
				 rhs[i] == '/' || rhs[i] == '-' || rhs[i] == '^' )
				throw ( HelpExp( "invalid function definition" ));
		}
		if ((( isdigit( rhs[i] ) || isalpha( rhs[i] ) ) &&
				( rhs[i + 1] == ' ' || rhs[i + 1] == '\t'))) {
			i++;
			while ( rhs[i] == ' ' || rhs[i] == '\t') i++;
			if ( rhs[i] != '+' && rhs[i] != '*' && rhs[i] != '/' && rhs[i] != ')'
				 && rhs[i] != '-' && rhs[i] != '^' && i < rhs.size() )
				throw ( HelpExp( "invalid function definition" ));
		}
	}
}

void	Helper::display_fun( std::string rhs ) {
	size_t	i = -1;

	while ( ++i < rhs.size() ) {
		if ( rhs[i] == ' ' || rhs[i] =='\t')
			continue;
		if ( rhs[i] == '+' || rhs[i] == '*' ||
			 rhs[i] == '/' || rhs[i] == '-' )
			cout << " ";
		cout << rhs[i];
		if ( rhs[i] == '+' || rhs[i] == '*' ||
			 rhs[i] == '/' || rhs[i] == '-' )
			cout << " ";
	}
	cout << endl;
}

void	Helper::display_comp( comp_n rhs ) {
	cout << rhs.a << " ";
	if ( rhs.b >= 0 ) {
		cout << "+ ";
		cout << rhs.b << "i" << endl;
	}
	else {
		cout << "- ";
		cout << -1 * rhs.b << "i" << endl;
	}
}

void	Helper::str_check( std::string lhs, std::string rhs ) {
	for ( size_t i = 0; i < lhs.size(); i++ ) {
		if ( !isalpha( lhs[i] ))
			throw ( HelpExp( "invalid function definition" ));
	}
	for ( size_t i = 0; i < rhs.size(); i++ ) {
		if ( !isdigit( rhs[i] ) && !isalpha( rhs[i] )
			 && rhs[i] != '\t' && rhs[i] != '+'
			 && rhs[i] != '-' && rhs[i] != '/'
			 && rhs[i] != '*' && rhs[i] != '%'
			 && rhs[i] != '^' && rhs[i] != ' '
			 && rhs[i] != '(' && rhs[i] != ')'
			 && rhs[i] != '.')
			throw ( HelpExp( "invalid definition" ));
	}
	func_check( rhs );
}

bool	Helper::replace_str( std::string lhs, std::string rhs ) {
	int 	j = 0;

	for ( auto i = rhs.find( lhs ); i != std::string::npos; i = rhs.find( lhs, i + 1 )) {
		j = i + lhs.size();
		rhs.replace( i, lhs.size(), "" );
	}
	for ( size_t i = 0; i < rhs.size(); i++ ) {
		if ( !isdigit( rhs[i] )
			 && rhs[i] != '\t' && rhs[i] != '+'
			 && rhs[i] != '-' && rhs[i] != '*'
			 && rhs[i] != '^' && rhs[i] != ' '
			 && rhs[i] != '.')
			return ( true );
	}
	return ( false );
}

std::string	Helper::word_split( std::string rhs ) {
	int 				i = 0;
	std::istringstream	iss( rhs );

	while ( iss ) {
		iss >> rhs;
		if ( ++i > 2 )
			throw ( HelpExp( "invalid definition" ));
	}
	if ( rhs == "" )
		throw ( HelpExp( "invalid definition" ));
	return ( rhs );
}

std::string	Helper::name( std::string rhs ) {
	size_t	i = 0;

	while ( rhs[i] == ' ' || rhs[i] == '\t' ) i++;
	while ( ++i < rhs.size() )
		if ( rhs[i] == ' ' || rhs[i] == '\t' )
			throw ( HelpExp( "invalid function name" ));
	return ( word_split( rhs ));
}

bool	Helper::recursion_check( std::string lhs, std::string rhs ) {
	int 	j = 0;

	for ( auto i = rhs.find( lhs ); i != std::string::npos; i = rhs.find( lhs, i + 1 )) {
		j = i + lhs.size();
		if ( rhs[j] == '(' && !isalpha( rhs[i - 1] ))
			return ( true );
	}
	return ( false );
}

bool	Helper::is_complex( std::string rhs ) {

	for ( auto i = rhs.find( "i" ); i != std::string::npos; i = rhs.find( "i", i + 1 )) {
		if ( !isalpha( rhs[i - 1]) && !isalpha( rhs[i + 1]) )
			return ( true );
	}
	return ( false );
}

Helper::~Helper() {}

// HelpExp

Helper::HelpExp::HelpExp() {}


Helper::HelpExp::HelpExp( const std::string & text ) {
	this->_exptn_msg = text;
}

Helper::HelpExp::HelpExp(HelpExp const &rhs) {
	*this = rhs;
}

const char	*Helper::HelpExp::what() const throw() {
	return ( this->_exptn_msg.c_str() );
}

Helper::HelpExp	&Helper::HelpExp::operator=(HelpExp const &rhs) {
	this->_exptn_msg = rhs._exptn_msg;
	return ( *this );
}

Helper::HelpExp::~HelpExp() {}
