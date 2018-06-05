// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Helper.class.hpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: oposhiva <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/05 12:07:08 by oposhiva          #+#    #+#             //
//   Updated: 2018/06/05 12:07:08 by oposhiva         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef HELPER_CLASS_HPP
#define HELPER_CLASS_HPP

#include <iostream>
#include <cmath>

class	Helper {
private:
public:
	Helper();
	Helper( const Helper &rhs );

	Helper	&operator=( const Helper &rhs );

	bool	cont_opr( std::string rhs );
	double	summary( std::string rhs, int &i );
	double	factor( std::string rhs, int &i );
	double	brackets( std::string rhs, int &i );


	~Helper();
};

#endif
/*
 * 2 + 4 *2 - 5 %4 + 2 * (4 + 5)
 * 2 + 4 *2 - 5 %4 + 2 * (4 + 5)
 */
