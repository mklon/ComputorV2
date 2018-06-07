// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Matrix.class.cpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: oposhiva <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/06 12:55:08 by oposhiva          #+#    #+#             //
//   Updated: 2018/06/06 12:55:09 by oposhiva         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "../headers/Matrix.class.hpp"


Matrix::Matrix() {}

Matrix::Matrix( const Matrix &rhs ) {
	*this = rhs;
}

Matrix& Matrix::operator=( const Matrix &rhs ) {
	//!!!
	return ( *this );
}

Matrix::~Matrix() {}

void	Matrix::set_mat( std::map<std::string, std::vector<std::vector<double>>> *_mat ) {
	Matrix::_mat = _mat;
}

double	Matrix::find_var( std::string rhs ) {
	if ( _var->find( rhs ) == _var->end() ) {
		for ( int i = 0; i < rhs.size(); i++ )
			if ( !isdigit( rhs[i] ) && rhs[i] != '.'&&
				 rhs[i] != '^' )
				throw ( MtrxExp( "unknown variable: " + rhs ));
		if ( rhs == "" )
			throw ( MtrxExp( "invalid matrix definition" ));
		return ( std::stod( rhs ));
	}
	else {
		return ( _var->at(rhs) );
	}
}

void	Matrix::display_mat( std::vector<std::vector<double>> matrix ) {
	for ( int i = 0; i < matrix.size(); i++ ) {
		cout << "[ ";
		for ( int j = 0; j < matrix[i].size(); j++ ) {
			cout << matrix[i][j];
			if ( j != matrix[i].size() - 1 )
				cout << " , ";
		}
		cout << " ]" << endl;
	}
}

void	Matrix::size_check( std::vector<std::vector<double>> matrix ) {
	int		size = matrix[0].size();

	for ( int i = 1; i < matrix.size(); i++ )
		if ( matrix[i].size() != size )
			throw ( MtrxExp( "invalid matrix definition" ));
}

std::vector<double>	Matrix::rows( std::string rhs, int &i ) {
 	int		j;
	std::vector<double>	row;

	i++;
	while ( true ) {
		while ( rhs[i] == ' ' || rhs[i] == '\t') i++;
		j = i;

		while ( rhs[j] != ',' && rhs[j] != ']' && rhs[j] != ' ' ) {
			if ( !isdigit( rhs[i] ) && rhs[i] != '.' && !isalpha( rhs[i] ))
				throw ( MtrxExp( "unknown variable" ));
			j++;
		}
		row.push_back( find_var( rhs.substr( i, j - i )));
		i = j;
		while ( rhs[i] == ' ' || rhs[i] == '\t') i++;
		if ( rhs[i] != ',' && rhs[i] != ']' )
			throw ( MtrxExp( "invalid matrix definition" ));
		if (rhs[i++] == ']')
			break;

	}
	return ( row );
}

std::vector<std::vector<double>>	Matrix::lines( std::string rhs, int &i ) {
	std::vector<std::vector<double>>	line;
	while ( rhs[i] == ' ' || rhs[i] == '\t') i++;

	if ( rhs[i++] != '[' )
		throw ( MtrxExp( "[" ));
	while ( true ) {
		while ( rhs[i] == ' ' || rhs[i] == '\t') i++;

		if ( rhs[i] == '[' )
			line.push_back( rows( rhs, i ));

		while ( rhs[i] == ' ' || rhs[i] == '\t') i++;

		if ( rhs[i] != ';' && rhs[i] != ']' )
			throw ( MtrxExp( "invalid matrix definition" ));
		if ( rhs[i] == ']')
			break;
		i++;
	}
	size_check( line );
	return ( line );
}

//a = [ [ 1 , 2 ] ; [ 3 , 4 ] ]

void	Matrix::read_matrix( std::string lhs, std::string rhs ) {
	int 	i = 0;
	std::vector<std::vector<double>>	res;

	if ( _var->find( lhs ) != _var->end() )
		throw ( MtrxExp( "can't put the matrix in a numerical variable" ));


	res = lines( rhs, i );
	while ( ++i < rhs.size() )
		if ( rhs[i] != ' ' && rhs[i] != '\t' )
			throw ( MtrxExp( "invalid matrix definition" ));

	if ( _mat->find( lhs ) != _mat->end() )
		_mat->at( lhs ) = res;
	else
		_mat->insert( std::pair<std::string, std::vector<std::vector<double>>>( lhs, res ));
	display_mat( res );
}

void Matrix::set_var( std::map<std::string, double> *_var ) {
	Matrix::_var = _var;
}

// MtrxExp

Matrix::MtrxExp::MtrxExp() {}


Matrix::MtrxExp::MtrxExp( const std::string & text ) {
	this->_exptn_msg = text;
}

Matrix::MtrxExp::MtrxExp( MtrxExp const &rhs ) {
	*this = rhs;
}

const char	*Matrix::MtrxExp::what() const throw() {
	return ( this->_exptn_msg.c_str() );
}

Matrix::MtrxExp	&Matrix::MtrxExp::operator=( MtrxExp const &rhs ) {
	this->_exptn_msg = rhs._exptn_msg;
	return ( *this );
}

Matrix::MtrxExp::~MtrxExp() throw() {}