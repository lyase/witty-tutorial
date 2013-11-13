#pragma once
/** \file  IObservers.h
*header file defining Observer  interfaces for User  the views may have concrete implementation so controler may know how to update the view
*\n
*\version  1.0
*\date 018/09/13 10:06:50
*       Revision:  none
*       Compiler:  gcc
*
*\author:  lyase.d, lyase.d@gmail.com
*        Company:
*
* =====================================================================================
*/

/*! A IBeatObserver   class
* \details This class is used to demonstrate a number of section commands.
* \author lyase Damasked
* \version 0.1a
* \date 1990-2013
* \pre First initialize the system.
* \bug  should be bug free
* \warning this class is for tracing and testing purposes only.
* \brief  these interfaces may be implemented for any observer of a  IBeatModel such as views ModelObserver(used in controller)
* \n once these interfaces are implemented an object may ask to "observerve" a IBeatModel
*
*/
/**
* Provides the observer interfaces.
*
*/

#include <iostream>

class IBeatObserver {
public:
     virtual void operator()() = 0;
     virtual ~IBeatObserver() {}
};
class IBPMObserver {
public:
     virtual void operator()(int bpm) = 0;
     virtual ~IBPMObserver() {}
};
