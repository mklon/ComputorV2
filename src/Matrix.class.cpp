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

void	Matrix::rows( std::string rhs, int &i ) {
 	int		j, end;

	while ( rhs[i] == ' ' || rhs[i] == '\t') i++;

	j = ++i;
	while ( true ) {
		while ( rhs[j] != ',' && rhs[j] != ']')
			j++;
		cout << rhs.substr( i, j - i ) << " ";
		i = ++j;
		if (rhs[i - 1] == ']')
			break;
	}
	cout << endl;

}

void	Matrix::lines( std::string rhs, int &i ) {
	while ( rhs[i] == ' ' || rhs[i] == '\t') i++;

	while ( i < rhs.size() ) {
		if ( rhs[i] == '[' )
			rows( rhs, ++i );
		i++;
	}
}

void	Matrix::read_matrix( std::string lhs, std::string rhs ) {
	int 	i = 0;

	lines( rhs, i );
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