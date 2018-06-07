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

#include "../headers/Helper.class.hpp"

Helper::Helper() {}

Helper::Helper( const Helper &rhs ) {
	*this = rhs;
}

Helper	&Helper::operator=( const Helper &rhs ) {
	//!!!
	return ( *this );
}

double	Helper::find_var( std::string rhs ) {

	if ( _var->find( rhs ) == _var->end() ) {
		for ( int i = 0; i < rhs.size(); i++ )
			if ( !isdigit( rhs[i] ) && rhs[i] != '.'&&
					rhs[i] != '^' )
				throw ( HelpExp( "unknown variable: " + rhs ));
		if ( rhs == "" )
			throw ( HelpExp( "invalid rhs" ));
		return ( std::stod( rhs ));
	}
	else {
		return ( _var->at(rhs) );
	}
}

std::string	Helper::operation( std::string lhs, std::string rhs, char op ) {


	return ( " ");
}

std::string	Helper::brackets( std::string rhs, int &i ) {
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

std::string	Helper::factor( std::string rhs, int &i ) {
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

std::string	Helper::summary( std::string rhs, int &i ) {
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

void	Helper::solve_line( std::string lhs, std::string rhs ) {
	int					i = 0;
	double				res;
	std::string			temp;
	std::istringstream	iss( rhs );

	iss >> temp;
	if ( temp == "?" ) {
		if ( _var->find( lhs ) != _var->end() )
			cout << _var->at( lhs ) << endl;
		else if ( _mat->find( lhs ) != _mat->end() )
			m->display_mat( _mat->at( lhs ));
		else
			throw ( HelpExp( "unknown variable" ));
		return;
	}

	if ( _mat->find( lhs ) != _mat->end() )
		throw ( HelpExp( "can't put number in a matrix variable" ));

	res = std::stod( summary( rhs, i ));
	while ( i < rhs.size() )
		if ( rhs[i] != ' ' && rhs[i++] != '\t' )
			throw ( HelpExp( "invalid rhs" ));

	if ( _var->find( lhs ) != _var->end() )
		_var->at( lhs ) = res;
	else
		_var->insert( std::pair<std::string, double>( lhs , res ));
	cout << _var->at( lhs ) << endl;
}

bool	Helper::cont_opr( std::string rhs ) {
	// + - * / %
	if ( rhs.find( '+' ) != std::string::npos ||
			rhs.find( '-' ) != std::string::npos ||
			rhs.find( '*' ) != std::string::npos ||
			rhs.find( '/' ) != std::string::npos ||
			rhs.find( '%' ) != std::string::npos )
		return ( true );
	return ( false );
}

Helper::~Helper() {}

void	Helper::set_var( std::map<std::string, double> *_var ) {
	Helper::_var = _var;
}

void	Helper::set_mat( std::map<std::string, std::vector<std::vector<double>>> *_mat ) {
	Helper::_mat = _mat;
}

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

Helper::HelpExp::~HelpExp() throw() {}
