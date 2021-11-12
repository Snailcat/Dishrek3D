/****************************************************************************************** 
 *	
 DirectX Framework Version 16.07.20											  *	
 *	Mouse.cpp																			  *
 *	Copyright 2016 PlanetShrek <http://www.planetShrek.net>								  *
 *																						  *
 *	This file is part of The Shrek DirectX Framework.									  *
 *																						  *
 *	The Shrek DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Shrek DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Shrek DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "ShrekWin.h"
#include "Mouse.h"

std::pair<float, float> Mouse::GetPos() const noexcept
{
	return { x,y };
}

float Mouse::GetPosX() const noexcept
{
	return x;
}

float Mouse::GetPosY() const noexcept
{
	return y;
}

bool Mouse::IsInWindow() const noexcept
{
	return isInWindow;
}

bool Mouse::LeftIsPressed() const noexcept
{
	return leftIsPressed;
}

bool Mouse::RightIsPressed() const noexcept
{
	return rightIsPressed;
}

std::optional<Mouse::Event> Mouse::Read() noexcept
{
	if( buffer.size() > 0u )
	{
		Mouse::Event e = buffer.front();
		buffer.pop();
		return e;
	}
	return {};
}

void Mouse::Flush() noexcept
{
	buffer = std::queue<Event>();
}

void Mouse::OnMouseMove( float newx,float newy ) noexcept
{
	x = newx;
	y = newy;

	buffer.push( Mouse::Event( Mouse::Event::Type::Move,*this ) );
	TrimBuffer();
}

void Mouse::OnMouseLeave() noexcept
{
	isInWindow = false;
	buffer.push( Mouse::Event( Mouse::Event::Type::Leave,*this ) );
	TrimBuffer();
}

void Mouse::OnMouseEnter() noexcept
{
	isInWindow = true;
	buffer.push( Mouse::Event( Mouse::Event::Type::Enter,*this ) );
	TrimBuffer();
}

void Mouse::OnLeftPressed(float x, float y ) noexcept
{
	leftIsPressed = true;

	buffer.push( Mouse::Event( Mouse::Event::Type::LPress,*this ) );
	TrimBuffer();
}

void Mouse::OnLeftReleased(float x, float y ) noexcept
{
	leftIsPressed = false;

	buffer.push( Mouse::Event( Mouse::Event::Type::LRelease,*this ) );
	TrimBuffer();
}

void Mouse::OnRightPressed(float x, float y ) noexcept
{
	rightIsPressed = true;

	buffer.push( Mouse::Event( Mouse::Event::Type::RPress,*this ) );
	TrimBuffer();
}

void Mouse::OnRightReleased(float x, float y ) noexcept
{
	rightIsPressed = false;

	buffer.push( Mouse::Event( Mouse::Event::Type::RRelease,*this ) );
	TrimBuffer();
}

void Mouse::OnWheelUp(float x, float y ) noexcept
{
	buffer.push( Mouse::Event( Mouse::Event::Type::WheelUp,*this ) );
	TrimBuffer();
}

void Mouse::OnWheelDown(float x, float y ) noexcept
{
	buffer.push( Mouse::Event( Mouse::Event::Type::WheelDown,*this ) );
	TrimBuffer();
}

void Mouse::TrimBuffer() noexcept
{
	while( buffer.size() > bufferSize )
	{
		buffer.pop();
	}
}

void Mouse::OnWheelDelta(float x, float y,int delta ) noexcept
{
	wheelDeltaCarry += delta;
	// generate events for every 120 
	while( wheelDeltaCarry >= WHEEL_DELTA )
	{
		wheelDeltaCarry -= WHEEL_DELTA;
		OnWheelUp( x,y );
	}
	while( wheelDeltaCarry <= -WHEEL_DELTA )
	{
		wheelDeltaCarry += WHEEL_DELTA;
		OnWheelDown( x,y );
	}
}
