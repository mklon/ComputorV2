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

void Matrix::set_mat( std::map<std::string, std::vector<std::vector<double>>> *_mat ) {
	Matrix::_mat = _mat;
}

void Matrix::read_matrix( std::string rhs ) {

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