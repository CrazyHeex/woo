/***************************************************************************
 *   Copyright (C) 2004 by Olivier Galizzi                                 *
 *   olivier.galizzi@imag.fr                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __POINTERHANDLER_H__
#define __POINTERHANDLER_H__

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "SerializationExceptions.hpp"
#include "Serializable.hpp"
#include "ClassFactory.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

class Serializable;
class ClassFactory;

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

template<typename Type>
struct PointerHandler
{
	static void creator(Archive& , shared_ptr<Archive>& , string )
	{
		throw HandlerError(SerializationExceptions::SmartPointerNotSupported);
	}
	static bool accessor(Archive& , shared_ptr<Archive>& )
	{
		throw HandlerError(SerializationExceptions::SmartPointerNotSupported);
	}
};

///////////////////////////////////////////////////////////////////////////////////////////////////
/// shared_ptr											///
///////////////////////////////////////////////////////////////////////////////////////////////////

template<typename PointedType>
struct PointerHandler<shared_ptr<PointedType> >
{
	static void creator(Archive& ac, shared_ptr<Archive>& newAc, string typeStr)
	{
		string name = ac.getName();
		shared_ptr<PointedType> * tmpPtr;

		if(typeStr.size() != 0)
		{
			// FIXME : isn't it the same code code Serializable and custom ???
			if(boost::is_base_and_derived<Serializable,PointedType>::value)
			{
				shared_ptr<Serializable> newInstance = dynamic_pointer_cast<Serializable>(ClassFactory::instance().createShared(typeStr));
				tmpPtr		= any_cast< shared_ptr<PointedType>* >(ac.getAddress());
				
				// WARNING: this will not compile if you have 'int' or 'float' inside shared_ptr
				// but I'm not going to change this into reinterpret_cast just because of that.
				// nobody will have 'int' inside shared_ptr, and reinterpret_cast is here too risky hack.
				//
				// proper solution is to write template specialization for PointerHandler< int >
				// if you need it - then write it.
				
				*tmpPtr 	= dynamic_pointer_cast<PointedType>(newInstance);
				newAc 		= Archive::create(name,**tmpPtr);

// original h4x00r lines .....
//				Serializable * newInstance = dynamic_cast<Serializable*>(ClassFactory::instance().createPure(typeStr));
//				tmpPtr		= any_cast< shared_ptr<PointedType>* >(ac.getAddress());
//				*tmpPtr 	= shared_ptr<PointedType>(reinterpret_cast<PointedType*>(newInstance));
//				newAc 		= Archive::create(name,**tmpPtr);
			}
			else
			{
				// FIXME : creating pointer to custom class is not working!

				std::string error = FactoryExceptions::CantCreateClass + name + "  - Because pointers to custom class are not working!";
				throw FactoryCantCreate(error.c_str());

//				void * newInstance 	= ClassFactory::instance().createPureCustom(typeStr);
//				tmpPtr		= any_cast< shared_ptr<PointedType>* >(ac.getAddress());
//				*tmpPtr 	= shared_ptr<PointedType>(reinterpret_cast<PointedType*>(newInstance));
//				newAc 		= Archive::create(name,**tmpPtr);
			}
		}
		else
		{ // according to WARNING above - following lines are never executed ....
			tmpPtr=any_cast< shared_ptr<PointedType>* >(ac.getAddress());
			*tmpPtr = shared_ptr<PointedType>(new PointedType);
			newAc = Archive::create(name,**tmpPtr);
		}
	}

	static bool accessor(Archive& ac, shared_ptr<Archive>& newAc)
	{
		string name = ac.getName();
		shared_ptr<PointedType> * tmpPtr;
		tmpPtr=any_cast< shared_ptr<PointedType>* >(ac.getAddress());
		if(*tmpPtr == 0)
			return false;
		else
		{
			newAc = Archive::create(name,**tmpPtr);
			return true;
		}
	}
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

template<typename PointedType>
SerializableTypes::Type findType( shared_ptr<PointedType>& ,bool& fundamental, string& str)
{
	PointedType tmpV;
	bool tmpFundamental;

	SerializableTypes::Type t = findType(tmpV,tmpFundamental,str);

	fundamental = ( boost::is_fundamental<PointedType>::value || ((t==SerializableTypes::POINTER || t==SerializableTypes::CUSTOM_CLASS || t==SerializableTypes::CONTAINER) && tmpFundamental) );

	return SerializableTypes::POINTER;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

#endif // __POINTERHANDLER_H__

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
