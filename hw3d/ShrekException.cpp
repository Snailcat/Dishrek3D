/******************************************************************************************
*	Shrek Direct3D Engine																  *
*	Copyright 2018 PlanetShrek <http://www.planetShrek.net>								  *
*																						  *
*	This file is part of Shrek Direct3D Engine.											  *
*																						  *
*	Shrek Direct3D Engine is free software: you can redistribute it and/or modify		  *
*	it under the terms of the GNU General Public License as published by				  *
*	the Free Software Foundation, either version 3 of the License, or					  *
*	(at your option) any later version.													  *
*																						  *
*	The Shrek Direct3D Engine is distributed in the hope that it will be useful,		  *
*	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
*	GNU General Public License for more details.										  *
*																						  *
*	You should have received a copy of the GNU General Public License					  *
*	along with The Shrek Direct3D Engine.  If not, see <http://www.gnu.org/licenses/>.    *
******************************************************************************************/
#include "ShrekException.h"
#include <sstream>


ShrekException::ShrekException( int line,const char* file ) noexcept
	:
	line( line ),
	file( file )
{}

const char* ShrekException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* ShrekException::GetType() const noexcept
{
	return "Shrek Exception";
}

int ShrekException::GetLine() const noexcept
{
	return line;
}

const std::string& ShrekException::GetFile() const noexcept
{
	return file;
}

std::string ShrekException::GetOriginString() const noexcept
{
	std::ostringstream oss;
	oss << "[File] " << file << std::endl
		<< "[Line] " << line;
	return oss.str();
}