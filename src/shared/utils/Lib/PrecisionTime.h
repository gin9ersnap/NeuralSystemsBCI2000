/////////////////////////////////////////////////////////////////////////////
// $Id$
// Authors: schalk@wadsworth.org, juergen.mellinger@uni-tuebingen.de
// Description: A class wrapper for the system's high precision timer.
//
// $BEGIN_BCI2000_LICENSE$
//
// This file is part of BCI2000, a platform for real-time bio-signal research.
// [ Copyright (C) 2000-2012: BCI2000 team and many external contributors ]
//
// BCI2000 is free software: you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.
//
// BCI2000 is distributed in the hope that it will be useful, but
//                         WITHOUT ANY WARRANTY
// - without even the implied warranty of MERCHANTABILITY or FITNESS FOR
// A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with
// this program.  If not, see <http://www.gnu.org/licenses/>.
//
// $END_BCI2000_LICENSE$
/////////////////////////////////////////////////////////////////////////////
#ifndef TINY_PRECISION_TIME_H
#define TINY_PRECISION_TIME_H

namespace Tiny
{

class PrecisionTime
{
 public:
  typedef unsigned short NumType;

  PrecisionTime()
    : mValue( 0 ) {}
  PrecisionTime( NumType value )
    : mValue( value ) {}

 private: // force the user to decide between UnsignedDiff and SignedDiff
  void operator-( PrecisionTime );

 public:
  operator NumType() const
    { return mValue; }

  static PrecisionTime Now();
  static NumType UnsignedDiff( NumType, NumType );
  static int     SignedDiff( NumType, NumType );

 private:
  NumType mValue;
};

} // namespace

using Tiny::PrecisionTime;

#endif // PRECISION_TIME_H
